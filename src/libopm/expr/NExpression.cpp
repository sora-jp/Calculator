#include "NExpression.h"
#include "antlr-gen/InfixLexer.h"
#include "antlr-gen/InfixParser.h"

using namespace antlr4;

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
		if (m_unary.find(p) != m_unary.end() && node->children.size() == 1) return m_unary.at(p)(ConstantEval(node->child(0)));
		if (m_binary.find(p) != m_binary.end() && node->children.size() == 2) return m_binary.at(p)(ConstantEval(node->child(0)), ConstantEval(node->child(1)));
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

void ExprToString(std::string& out, const NExpressionNode* node, int lastPrec = 0)
{
	//if (node == nullptr) return;
	//for (int32_t i = 0; i < lastPrec; i++) std::cout << "  ";
	//if (node->op.type != NOpType::Constant) std::cout << node->op.payload << " (" << ToString(node->op.type) << ")" << std::endl;
	//else
	//{
	//	char s[256] = {};
	//	format(node->op.constant, s, FormatMode::Standard);
	//	std::cout << s << " (Constant)" << std::endl;
	//}
	//for (auto* c : node->children) Print(c, lastPrec + 1);

	//return;
	auto prec = precedence(node->op);
	bool paren = prec < lastPrec && lastPrec != -1 && prec != -1;
	if (paren) out.append("(");

	if (node->op.type == NOpType::Unary)
	{
		out.append(node->op.payload);
		ExprToString(out, node->child(0), prec);
	}
	if (node->op.type == NOpType::Binary || (node->op.type == NOpType::FunctionCall && node->op.payload == "pow"))
	{
		auto p = node->op.payload;
		if (p == "pow") p = "^";
		ExprToString(out, node->child(0), prec);
		out.append(" ");
		out.append(p);
		out.append(" ");
		ExprToString(out, node->child(1), prec);
	}
	if (node->op.type == NOpType::Variable) out.append(node->op.payload);
	if (node->op.type == NOpType::Constant)
	{
		char buf[256] = {};
		format(node->op.constant, buf, FormatMode::Standard);
		out.append(buf);
	}
	if (node->op.type == NOpType::FunctionCall && node->op.payload != "pow")
	{
		out.append(node->op.payload);
		out.append("(");
		for (uint32_t i = 0; i < node->children.size(); i++)
		{
			if (i == 0) ExprToString(out, node->child(0), prec);
			else
			{
				out.append(", ");
				ExprToString(out, node->child(i), prec);
			}
		}
		out.append(")");
	}

	if (paren) out.append(")");
}

std::string ExprToString(const NExpressionNode* node)
{
	std::string s;
	ExprToString(s, node);
	return s;
}

std::string NExpressionParser::ToString(const NExpression& expr)
{
	std::string o;
	if (expr.type == NExpressionType::VariableAssignment)
	{
		o = expr.varName;
		o += " = ";
		ExprToString(o, expr.top);
	}
	if (expr.type == NExpressionType::FunctionDefinition)
	{
		o = expr.fnData[0] + "(";
		for (uint32_t i = 1; i < expr.fnData.size(); i++)
		{
			if (i == 1) o += expr.fnData[i];
			else o += ", " + expr.fnData[i];
		}
		o += ") = ";
		ExprToString(o, expr.top);
	}
	if (expr.type == NExpressionType::Expression)
	{
		ExprToString(o, expr.top);
	}
	return o;
}

void NExpressionParser::Print(const NExpression& expr)
{
	std::cout << ExprToString(expr.top);
	std::cout << std::endl;
}

NExpression NExpressionParser::rewrite(NExpressionRewriter& rew, const NExpression& expr) const
{
	NExpression output = {expr.type, expr.varName, expr.fnData, nullptr};
	output.top = rew.rewrite(expr.top);
	ConstantFoldAll(output.top);
	return output;
}

void NExpressionParser::compileRecursive(NErrorCollection& errs, std::vector<NCompiledOp>& ops, const NExpressionNode* node) const
{
	if (node == nullptr) return;
	for (auto* c : node->children) compileRecursive(errs, ops, c);

	if (node->op.type == NOpType::Constant) ops.emplace_back(node->op.constant);
	if (node->op.type == NOpType::Variable) ops.emplace_back(node->op.payload);
	if (node->op.type == NOpType::HistoryRef) ops.emplace_back(node->op.histIndex);
	if (node->op.type == NOpType::Unary) 
	{
		if (m_unary.find(node->op.payload) == m_unary.end())
		{
			errs.push_back({ ErrorType::Error, ErrorClass::Compilation, "Cannot find unary operation '" + node->op.payload + "'" });
			return;
		}
		ops.emplace_back(m_unary.at(node->op.payload));
	}
	if (node->op.type == NOpType::Binary) 
	{
		if (m_binary.find(node->op.payload) == m_binary.end())
		{
			errs.push_back({ ErrorType::Error, ErrorClass::Compilation, "Cannot find binary operation '" + node->op.payload + "'" });
			return;
		}

		for (uint32_t i = 0; i < node->children.size() - 1; i++)
			ops.emplace_back(m_binary.at(node->op.payload));
	}
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

NCompiledExpression NExpressionParser::compile(NErrorCollection& outErrors, const NExpression& expr) const
{
	//assert(expr.type == NExpressionType::Expression);
	if (!outErrors.empty()) return NCompiledExpression{};

	NCompiledExpression out;
	compileRecursive(outErrors, out.m_ops, expr.top);
	return out;
}
