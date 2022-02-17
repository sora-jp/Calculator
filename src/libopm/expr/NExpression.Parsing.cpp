#include "CommonTokenStream.h"
#include "NExpression.h"
#include "NExpressionNode.h"
#include "antlr-gen/InfixLexer.h"
#include "antlr-gen/InfixParser.h"
using namespace antlr4;

void Convert(InfixParser::ExpressionContext* expr, NExpressionNode* node, const NExpressionContext& ctx);
void Convert(InfixParser::PrimaryContext* primary, NExpressionNode* node, const NExpressionContext& ctx)
{
	if (auto* c = primary->constant(); c)
		node->op = NOperation{ NOpType::Constant, wrap(parse(c->getText().c_str())) };

	if (auto* h = primary->histref(); h)
	{
		const auto& expr = ctx.get(atoi(h->INTEGER()->getText().c_str()));
		node->op = expr.top->op;
		node->setChildren({});

		for (const auto* c : expr.top->children) node->children.push_back(c->copy());
	}

	if (auto* e = primary->expression(); e)
		Convert(e, node, ctx);

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
			Convert(param, n, ctx);
			node->children.push_back(n);
		}
	}
}

void Convert(InfixParser::FactorContext* factor, NExpressionNode* node, const NExpressionContext& ctx);
void Convert(InfixParser::SecondaryContext* secondary, NExpressionNode* node, const NExpressionContext& ctx)
{
	auto* opNode = secondary->POW();

	if (opNode)
	{
		auto* lhs = new NExpressionNode();
		auto* rhs = new NExpressionNode();

		node->setChildren({ lhs, rhs });
		node->op = NOperation{ NOpType::FunctionCall, "pow" };

		Convert(secondary->secondary(), lhs, ctx);
		Convert(secondary->factor(), rhs, ctx);
	}
	else
	{
		Convert(secondary->primary(), node, ctx);
	}
}

void Convert(InfixParser::FactorContext* factor, NExpressionNode* node, const NExpressionContext& ctx)
{
	auto* opNode = factor->PLUS();
	if (!opNode) opNode = factor->MINUS();

	if (opNode)
	{
		auto* lhs = new NExpressionNode();

		node->setChildren({ lhs });
		node->op = NOperation{ NOpType::Unary, opNode->getText() };

		Convert(factor->factor(), lhs, ctx);
	}
	else
	{
		Convert(factor->secondary(), node, ctx);
	}
}

void Convert(InfixParser::TermContext* term, NExpressionNode* node, const NExpressionContext& ctx)
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

		Convert(term->term(), lhs, ctx);
		Convert(term->factor(), rhs, ctx);
	}
	else if (term->term())
	{
		auto* lhs = new NExpressionNode();
		auto* rhs = new NExpressionNode();

		node->setChildren({ lhs, rhs });
		node->op = NOperation{ NOpType::Binary, "*" };

		Convert(term->factor(), lhs, ctx);
		Convert(term->term(), rhs, ctx);
	}
	else
	{
		Convert(term->factor(), node, ctx);
	}
}

void Convert(InfixParser::ExpressionContext* expr, NExpressionNode* node, const NExpressionContext& ctx)
{
	auto* opNode = expr->PLUS();
	if (!opNode) opNode = expr->MINUS();

	if (opNode)
	{
		auto* rhs = new NExpressionNode();
		auto* lhs = new NExpressionNode();

		node->setChildren({ lhs, rhs });
		node->op = NOperation{ NOpType::Binary, opNode->getText() };

		Convert(expr->expression(), lhs, ctx);
		Convert(expr->term(), rhs, ctx);
	}
	else
	{
		Convert(expr->term(), node, ctx);
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

NExpression NExpressionParser::parse(NErrorCollection& outErrors, const NExpressionContext& ctx, const std::string& in) const
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
		Convert(a->expression(), expr.top, ctx);
	}
	else if (auto* f = top->functionDef(); f)
	{
		expr.type = NExpressionType::FunctionDefinition;
		expr.fnData.push_back(f->funcWVars()->ID()->getText());
		for (uint32_t i = 0; i < f->funcWVars()->variable().size(); i++) expr.fnData.push_back(f->funcWVars()->variable(i)->ID()->getText());
		Convert(f->expression(), expr.top, ctx);
	}
	else
	{
		expr.type = NExpressionType::Expression;
		Convert(top->expression(), expr.top, ctx);
	}
	//std::cout << in << std::endl;
	//Print(expr);

	//std::cout << "AFTER CONSTANT FOLDING" << std::endl;
	ConstantFoldAll(expr.top);
	//Print(expr);

	return expr;
}
