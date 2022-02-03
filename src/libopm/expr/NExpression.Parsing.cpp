#include "CommonTokenStream.h"
#include "NExpression.h"
#include "NExpressionNode.h"
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
	if (!opNode) opNode = term->MOD();
	if (!opNode) opNode = term->MULT();

	if (opNode)
	{
		auto* lhs = new NExpressionNode();
		auto* rhs = new NExpressionNode();

		node->setChildren({ lhs, rhs });
		node->op = NOperation{ NOpType::Binary, opNode->getText() };

		Convert(term->term(), lhs);
		Convert(term->factor(), rhs);
	}
	else if (term->term())
	{
		auto* lhs = new NExpressionNode();
		auto* rhs = new NExpressionNode();

		node->setChildren({ lhs, rhs });
		node->op = NOperation{ NOpType::Binary, "*" };

		Convert(term->factor(), lhs);
		Convert(term->term(), rhs);
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
		auto* rhs = new NExpressionNode();
		auto* lhs = new NExpressionNode();

		node->setChildren({ lhs, rhs });
		node->op = NOperation{ NOpType::Binary, opNode->getText() };

		Convert(expr->expression(), lhs);
		Convert(expr->term(), rhs);
	}
	else
	{
		Convert(expr->term(), node);
	}
}

class NErrorListener : public BaseErrorListener
{
public:
	NErrorCollection* errs;

	void syntaxError(Recognizer* recognizer, Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override
	{
		errs->push_back({ ErrorType::Error, ErrorClass::Parsing, msg});
	}
};

NExpression NExpressionParser::parse(NErrorCollection& outErrors, const std::string& in) const
{
	ANTLRInputStream stream(in);
	InfixLexer lexer(&stream);
	CommonTokenStream tokens(&lexer);
	InfixParser parser(&tokens);

	NErrorListener errListener;
	errListener.errs = &outErrors;
	parser.addErrorListener(&errListener);

	NExpression expr {NExpressionType::Expression, "", {}, nullptr};
	auto* top = parser.eval();

	if (!outErrors.empty()) return expr;

	expr.top = new NExpressionNode();
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
		expr.type = NExpressionType::Expression;
		Convert(top->expression(), expr.top);
	}
	//std::cout << in << std::endl;
	//Print(expr);

	//std::cout << "AFTER CONSTANT FOLDING" << std::endl;
	ConstantFoldAll(expr.top);
	//Print(expr);

	return expr;
}
