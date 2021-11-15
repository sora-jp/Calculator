#include "NExpression.h"
#include "antlr-gen/InfixLexer.h"
#include "antlr-gen/InfixParser.h"

using namespace antlr4;

void Convert(InfixParser::ExpressionContext* expr, NExpressionNode* node);
void Convert(InfixParser::PrimaryContext* primary, NExpressionNode* node)
{
	if (auto* c = primary->constant(); c)
		node->op = NOperation{ NOpType::Constant, wrap(parse(c->getText().c_str())) };

	if (auto* e = primary->expression(); e) 
		Convert(e, node);

	if (auto* v = primary->variable(); v)
		node->op = NOperation{ NOpType::Variable, v->getText() };

	if (auto* f = primary->func(); f)
	{
		node->op = NOperation{ NOpType::FunctionCall, f->ID()->getText() };
		auto* p = f->params();

		auto s = p->expression().size();
		if (s >= 1)
		{
			node->left = new NExpressionNode();
			Convert(p->expression(0), node->left);
		}
		if (s >= 2)
		{
			node->right = new NExpressionNode();
			Convert(p->expression(1), node->right);
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

		node->left = lhs;
		node->right = rhs;
		node->op = NOperation{ NOpType::Binary, opNode->getText() };

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
		
		node->left = lhs;
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
	if (!opNode) opNode = term->MOD();
	if (!opNode) opNode = term->MULT();

	if (opNode)
	{
		auto* lhs = new NExpressionNode();
		auto* rhs = new NExpressionNode();

		node->left = lhs;
		node->right = rhs;
		node->op = NOperation{ NOpType::Binary, opNode->getText() };

		Convert(term->term(), lhs);
		Convert(term->factor(), rhs);
	}
	else
	{
		Convert(term->factor(), node);
	}
}

void Convert(InfixParser::ExpressionContext* expr, NExpressionNode* node)
{
	auto* opNode = expr->PLUS();
	if (!opNode) opNode = expr->MINUS();

	if (opNode)
	{
		auto* lhs = new NExpressionNode();
		auto* rhs = new NExpressionNode();

		node->left = lhs;
		node->right = rhs;
		node->op = NOperation { NOpType::Binary, opNode->getText() };

		Convert(expr->expression(), lhs);
		Convert(expr->term(), rhs);
	}
	else
	{
		Convert(expr->term(), node);
	}
}

void Convert(InfixParser::EvalContext* topLevel, NExpressionNode& node)
{
	Convert(topLevel->expression(), &node);
}

bool IsConstant(NExpressionNode* node)
{
	if (node == nullptr) return true;
	if (node->op.type == NOpType::Constant) return true;
	//if (node->op.type == NOpType::FunctionCall) return false;
	if (node->op.type == NOpType::Variable) return false;
	return IsConstant(node->left) && IsConstant(node->right);
}

OpmValue ConstantEval(NExpressionNode* node)
{
	if (node->op.type == NOpType::Constant)
	{
		return node->op.constant;
	}
	if (node->op.type == NOpType::Unary)
	{
		auto& p = node->op.payload;
		if (p == "+") return ConstantEval(node->left);
		if (p == "-") return -ConstantEval(node->left);
	}
	if (node->op.type == NOpType::Binary)
	{
		auto& p = node->op.payload;
		if (p == "+") return ConstantEval(node->left) + ConstantEval(node->right);
		if (p == "-") return ConstantEval(node->left) - ConstantEval(node->right);
		if (p == "*") return ConstantEval(node->left) * ConstantEval(node->right);
		if (p == "/") return ConstantEval(node->left) / ConstantEval(node->right);
		if (p == "^") return pow(ConstantEval(node->left), ConstantEval(node->right));
	}
}

bool ConstantFoldR(NExpressionNode* node)
{
	if (node == nullptr) return false;

	bool didFold = false;
	if (IsConstant(node) && node->op.type != NOpType::Constant)
	{
		auto n = ConstantEval(node);
		delete node->left;
		delete node->right;
		node->left = node->right = nullptr;

		node->op = NOperation{ NOpType::Constant, n };

		didFold = true;
	}
	if (!didFold)
	{
		didFold = ConstantFoldR(node->left) || ConstantFoldR(node->right);
	}

	return didFold;
}

void ConstantFoldAll(NExpressionNode* node)
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
	}
}

void Print(NExpressionNode* node, int depth = 0)
{
	if (node == nullptr) return;
	for (auto i = 0; i < depth; i++) std::cout << " ";

	if (node->op.type != NOpType::Constant) std::cout << node->op.payload << " (" << ToString(node->op.type) << ")" << std::endl;
	else
	{
		char s[256] = {};
		format(node->op.constant, s, FormatMode::Standard);
		std::cout << s << " (Constant)" << std::endl;
	}

	Print(node->left, depth + 1);
	Print(node->right, depth + 1);
}

NExpression NExpressionParser::parse(const std::string& in)
{
	ANTLRInputStream stream(in);
	InfixLexer lexer(&stream);
	CommonTokenStream tokens(&lexer);
	InfixParser parser(&tokens);
	
	NExpression expr;
	
	auto* top = parser.eval();
	Convert(top, expr.top);
	std::cout << in << std::endl;
	Print(&expr.top);

	std::cout << "AFTER CONSTANT FOLDING" << std::endl;
	ConstantFoldAll(&expr.top);
	Print(&expr.top);

	return expr;
}

void NExpressionParser::compileRecursive(std::vector<NCompiledOp>& ops, const NExpressionNode* node)
{
	if (node == nullptr) return;
	compileRecursive(ops, node->right);
	compileRecursive(ops, node->left);

	if (node->op.type == NOpType::Constant) ops.emplace_back(node->op.constant);
	if (node->op.type == NOpType::Variable) ops.emplace_back(node->op.payload);
	if (node->op.type == NOpType::Unary) ops.emplace_back(m_unary[node->op.payload]);
	if (node->op.type == NOpType::Binary) ops.emplace_back(m_binary[node->op.payload]);
	if (node->op.type == NOpType::FunctionCall)
	{
		if (m_unary.find(node->op.payload) != m_unary.end()) ops.emplace_back(m_unary[node->op.payload]);
		else if (m_binary.find(node->op.payload) != m_binary.end()) ops.emplace_back(m_binary[node->op.payload]);
		else assert(false);
	}
}

OpmValue ident(const OpmValue& val) { return val; }

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

NCompiledExpression NExpressionParser::compile(const NExpression& expr)
{
	NCompiledExpression out;
	compileRecursive(out.m_ops, &expr.top);
	return out;
}
