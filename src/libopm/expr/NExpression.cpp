#include "NExpression.h"
#include "antlr-gen/InfixLexer.h"
#include "antlr-gen/InfixParser.h"
#include "antlr-gen/InfixListener.h"
#include "antlr-gen/InfixBaseListener.h"

using namespace antlr4;

struct ConversionListener : public InfixBaseListener
{
	NExpressionNode* curNode;

private:
	void enterExpression(InfixParser::ExpressionContext* ctx) override
	{

	}
};

NExpression NExpressionParser::parse(const std::string& in)
{
	ANTLRInputStream stream(in);
	InfixLexer lexer(&stream);
	CommonTokenStream tokens(&lexer);
	InfixParser parser(&tokens);

	ConversionListener list;
	NExpression expr;
	list.curNode = &expr.top;

	tree::ParseTree* top = parser.eval();
	tree::ParseTreeWalker::DEFAULT.walk(&list, top);

	return expr;
}