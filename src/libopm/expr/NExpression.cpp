#include "NExpression.h"
#include "antlr-gen/InfixLexer.h"
#include "antlr-gen/InfixParser.h"

using namespace antlr4;

void Convert(InfixParser::ExpressionContext* expr, NExpressionNode* node);
void Convert(InfixParser::PrimaryContext* primary, NExpressionNode* node)
{
	if (auto* c = primary->constant(); c)
		node->op = NOperation{ NOpType::Constant, wrap(parse(c->getText().c_str())) };

	if (auto* h = primary->histref(); h)
		node->op = NOperation{ NOpType::HistoryRef, h->INTEGER()->getText() };

	if (auto* e = primary->expression(); e) 
		Convert(e, node);

	if (auto* v = primary->variable(); v)
		node->op = NOperation{ NOpType::Variable, v->getText() };

	if (auto* f = primary->func(); f)
	{
		node->op = NOperation{ NOpType::FunctionCall, f->ID()->getText() };
		auto* p = f->params();

		auto s = p->expression().size();
		node->children.reserve(s);

		for (auto* param : p->expression())
		{
			auto* n = new NExpressionNode();
			Convert(param, n);
			node->children.push_back(n);
		}
	}
}

void Convert(InfixParser::FactorContext* factor, NExpressionNode* node);
void Convert(InfixParser::SecondaryContext* secondary, NExpressionNode* node)
{
	auto* opNode = secondary->POW();

	if (opNode)
	{
		auto* lhs = new NExpressionNode();
		auto* rhs = new NExpressionNode();

		node->setChildren({ lhs, rhs });
		node->op = NOperation{ NOpType::FunctionCall, "pow" };

		Convert(secondary->secondary(), lhs);
		Convert(secondary->factor(), rhs);
	}
	else
	{
		Convert(secondary->primary(), node);
	}
}

void Convert(InfixParser::FactorContext* factor, NExpressionNode* node)
{
	auto* opNode = factor->PLUS();
	if (!opNode) opNode = factor->MINUS();

	if (opNode)
	{
		auto* lhs = new NExpressionNode();
		
		node->setChildren({ lhs });
		node->op = NOperation{ NOpType::Unary, opNode->getText() };
		
		Convert(factor->factor(), lhs);
	}
	else
	{
		Convert(factor->secondary(), node);
	}
}

void Convert(InfixParser::TermContext* term, NExpressionNode* node)
{
	auto* opNode = term->DIV();
	//if (!opNode) opNode = term->MOD();
	if (!opNode) opNode = term->MULT();

	if (opNode)
	{
		auto* rhs = new NExpressionNode();

		node->children.push_back(rhs);
		node->op = NOperation{ NOpType::Binary, "*"};

		if (term->DIV())
		{
			rhs->op = NOperation{ NOpType::Unary, "inv" };
			auto* target = new NExpressionNode();
			rhs->setChildren({ target });
			rhs = target;
		}

		Convert(term->term(), node);
		Convert(term->factor(), rhs);
	}
	else
	{
		auto* n = new NExpressionNode();
		node->children.push_back(n);
		std::reverse(node->children.begin(), node->children.end());
		Convert(term->factor(), node);
	}
}

void Convert(InfixParser::ExpressionContext* expr, NExpressionNode* node)
{
	auto* opNode = expr->PLUS();
	if (!opNode) opNode = expr->MINUS();

	if (opNode)
	{
		auto* rhs = new NExpressionNode();
		node->children.push_back(rhs);
		node->op = NOperation { NOpType::Binary, "+" };

		if (expr->MINUS())
		{
			rhs->op = NOperation{ NOpType::Unary, "-" };
			auto* target = new NExpressionNode();
			rhs->setChildren({ target });
			rhs = target;
		}

		Convert(expr->expression(), node);
		Convert(expr->term(), rhs);
	}
	else
	{
		auto* n = new NExpressionNode();
		node->children.push_back(n);
		std::reverse(node->children.begin(), node->children.end());
		Convert(expr->term(), n);
	}
}

bool NExpressionParser::IsConstant(const NExpressionNode* node) const
{
	if (node == nullptr) return true;
	if (node->op.type == NOpType::Constant) return true;
	//if (node->op.type == NOpType::FunctionCall) return false;
	if (node->op.type == NOpType::Variable) return false;
	if (node->op.type == NOpType::HistoryRef) return false;
	if (node->op.type == NOpType::FunctionCall && (m_binary.find(node->op.payload) == m_binary.end() && m_unary.find(node->op.payload) == m_unary.end())) return false;

	bool constant = true;
	for (auto* c : node->children) constant &= IsConstant(c);
	return constant;
}

OpmValue NExpressionParser::ConstantEval(const NExpressionNode* node) const
{
	if (node->op.type == NOpType::Constant)
	{
		return node->op.constant;
	}
	if (node->op.type == NOpType::Unary)
	{
		auto& p = node->op.payload;
		if (p == "+") return ConstantEval(node->child(0));
		if (p == "-") return -ConstantEval(node->child(0));
	}
	if (node->op.type == NOpType::Binary)
	{
		auto& p = node->op.payload;
		if (p == "+") return ConstantEval(node->child(0)) + ConstantEval(node->child(1));
		if (p == "-") return ConstantEval(node->child(0)) - ConstantEval(node->child(1));
		if (p == "*") return ConstantEval(node->child(0)) * ConstantEval(node->child(1));
		if (p == "/") return ConstantEval(node->child(0)) / ConstantEval(node->child(1));
		if (p == "^") return pow(ConstantEval(node->child(0)), ConstantEval(node->child(1)));
	}
	if (node->op.type == NOpType::FunctionCall)
	{
		auto& p = node->op.payload;
		if (m_unary.find(p) != m_unary.end() && node->child(1) == nullptr) return m_unary.at(p)(ConstantEval(node->child(0)));
		if (m_binary.find(p) != m_binary.end()) return m_binary.at(p)(ConstantEval(node->child(0)), ConstantEval(node->child(1)));
	}

	return OpmValue {};
}

bool NExpressionParser::ConstantFoldR(NExpressionNode* node) const
{
	if (node == nullptr) return false;

	bool didFold = false;
	if (IsConstant(node) && node->op.type != NOpType::Constant)
	{
		auto n = ConstantEval(node).roundToNearest();
		node->setChildren({});
		
		node->op = NOperation{ NOpType::Constant, n };

		didFold = true;
	}
	if (!didFold)
	{
		for (auto* c : node->children) didFold |= ConstantFoldR(c);
	}

	return didFold;
}

void NExpressionParser::ConstantFoldAll(NExpressionNode* node) const
{
	while (ConstantFoldR(node));
}

std::string ToString(const NOpType type)
{
	switch (type)
	{
	case NOpType::Invalid: return "Invalid";
	case NOpType::Binary: return "Binary";
	case NOpType::Unary: return "Unary";
	case NOpType::Constant: return "Constant";
	case NOpType::Variable: return "Variable";
	case NOpType::FunctionCall: return "FunctionCall";
	case NOpType::HistoryRef: return "HistoryRef";
	}
}

int precedence(const NOperation& op)
{
	if (op.type == NOpType::Binary)
	{
		if (op.payload == "+") return 1;
		if (op.payload == "-") return 1;
		if (op.payload == "*") return 2;
		if (op.payload == "/") return 2;
		if (op.payload == "^") return 3;
	}
	if (op.type == NOpType::Unary && op.payload == "-") return 4;
	if (op.type == NOpType::FunctionCall && op.payload == "pow") return 3;
	return -1;
}

void Print(const NExpressionNode* node, int lastPrec = 0)
{
	if (node == nullptr) return;
	for (int32_t i = 0; i < lastPrec; i++) std::cout << "  ";
	if (node->op.type != NOpType::Constant) std::cout << node->op.payload << " (" << ToString(node->op.type) << ")" << std::endl;
	else
	{
		char s[256] = {};
		format(node->op.constant, s, FormatMode::Standard);
		std::cout << s << " (Constant)" << std::endl;
	}
	for (auto* c : node->children) Print(c, lastPrec + 1);

	return;
	auto prec = precedence(node->op);
	bool paren = prec < lastPrec && lastPrec != -1 && prec != -1;
	if (paren) std::cout << "(";

	if (node->op.type == NOpType::Unary)
	{
		std::cout << node->op.payload;
		Print(node->child(0), prec);
	}
	if (node->op.type == NOpType::Binary || (node->op.type == NOpType::FunctionCall && node->op.payload == "pow"))
	{
		auto p = node->op.payload;
		if (p == "pow") p = "^";
		Print(node->child(0), prec);
		std::cout << " " << p << " ";
		Print(node->child(1), prec);
	}
	if (node->op.type == NOpType::Variable) std::cout << node->op.payload;
	if (node->op.type == NOpType::Constant)
	{
		char buf[256] = {};
		format(node->op.constant, buf, FormatMode::Standard);
		std::cout << buf;
	}
	if (node->op.type == NOpType::FunctionCall && node->op.payload != "pow")
	{
		std::cout << node->op.payload << "(";
		Print(node->child(0), prec);
		if (node->child(1))
		{
			std::cout << ", ";
			Print(node->child(1), prec);
		}
		std::cout << ")";
	}

	if (paren) std::cout << ")";
}

void NExpressionParser::Print(const NExpression& expr)
{
	::Print(expr.top);
	std::cout << std::endl;
}

NExpression NExpressionParser::parse(const std::string& in) const
{
	ANTLRInputStream stream(in);
	InfixLexer lexer(&stream);
	CommonTokenStream tokens(&lexer);
	InfixParser parser(&tokens);
	
	NExpression expr = { new NExpressionNode() };
	auto* top = parser.eval();

	if (auto* a = top->assignment(); a)
	{
		expr.type = NExpressionType::VariableAssignment;
		expr.varName = a->variable()->ID()->getText();
		Convert(a->expression(), expr.top);
	}
	else if (auto* f = top->functionDef(); f)
	{
		expr.type = NExpressionType::FunctionDefinition;
		expr.fnData.push_back(f->funcWVars()->ID()->getText());
		for (uint32_t i = 0; i < f->funcWVars()->variable().size(); i++) expr.fnData.push_back(f->funcWVars()->variable(i)->ID()->getText());
		Convert(f->expression(), expr.top);
	}
	else 
	{
		Convert(top->expression(), expr.top);
	}
	std::cout << in << std::endl;
	Print(expr);

	//std::cout << "AFTER CONSTANT FOLDING" << std::endl;
	ConstantFoldAll(expr.top);
	//Print(expr);

	return expr;
}

NExpression NExpressionParser::rewrite(NExpressionRewriter& rew, const NExpression& expr) const
{
	NExpression output = {nullptr};
	output.top = rew.rewrite(expr.top);
	ConstantFoldAll(output.top);
	return output;
}

void NExpressionParser::compileRecursive(std::vector<NCompiledOp>& ops, const NExpressionNode* node) const
{
	if (node == nullptr) return;
	for (auto* c : node->children) compileRecursive(ops, c);

	if (node->op.type == NOpType::Constant) ops.emplace_back(node->op.constant);
	if (node->op.type == NOpType::Variable) ops.emplace_back(node->op.payload);
	if (node->op.type == NOpType::Unary) ops.emplace_back(m_unary.at(node->op.payload));
	if (node->op.type == NOpType::Binary) ops.emplace_back(m_binary.at(node->op.payload));
	if (node->op.type == NOpType::FunctionCall)
	{
		if (m_unary.find(node->op.payload) != m_unary.end() && node->children.size() == 1) ops.emplace_back(m_unary.at(node->op.payload));
		else if (m_binary.find(node->op.payload) != m_binary.end() && node->children.size() == 2) ops.emplace_back(m_binary.at(node->op.payload));
		else ops.emplace_back(FunctionDefinition{ node->op.payload, static_cast<uint32_t>(node->children.size()) });
		//else assert(false);
	}
}

static OpmValue ident(const OpmValue& val) { return val; }

NExpressionParser::NExpressionParser()
{
	m_unary["-"] = operator-;
	m_unary["+"] = ident;

	m_binary["+"] = operator+;
	m_binary["-"] = operator-;
	m_binary["*"] = operator*;
	m_binary["/"] = operator/;
	m_binary["^"] = pow;
}

NCompiledExpression NExpressionParser::compile(const NExpression& expr) const
{
	assert(expr.type == NExpressionType::Expression);

	NCompiledExpression out;
	compileRecursive(out.m_ops, expr.top);
	return out;
}
