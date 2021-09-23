#include "Expressions.hpp"
#include <cassert>

enum class TokenType : uint8_t
{
	Invalid, LParen, RParen, Operator, Identifier, Comma, Number
};

struct Token
{
	TokenType type;
	std::string text;
};

bool isop(const char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void Tokenize(const std::string& str, std::vector<Token>& outTokens)
{
	Token curToken = {TokenType::Invalid, ""};

	for (char c : str)
	{
		if (curToken.type == TokenType::Identifier)
		{
			if (!std::isalpha(c) && !std::isdigit(c))
			{
				outTokens.push_back(curToken);
				curToken.type = TokenType::Invalid;
				curToken.text = "";
			}
			else curToken.text += c;
		}

		if (curToken.type == TokenType::Number)
		{
			if (!std::isdigit(c) && c != '.' && c != 'i')
			{
				outTokens.push_back(curToken);
				curToken.type = TokenType::Invalid;
				curToken.text = "";
			}
			else curToken.text += c;
		}

		if (std::isblank(c)) continue;
		if (curToken.type == TokenType::Invalid)
		{
			if (isop(c)) 
			{
				auto opTok = Token { TokenType::Operator, std::string() + c };
				if (opTok.text == "-" && (outTokens.empty() || (outTokens.back().type != TokenType::Number && outTokens.back().type != TokenType::RParen))) opTok.text = "-u";
				outTokens.push_back(opTok);
			}
			else if (c == '(') outTokens.push_back({TokenType::LParen  , ""});
			else if (c == ')') outTokens.push_back({TokenType::RParen  , ""});
			else if (c == ',') outTokens.push_back({TokenType::Comma   , ""});
			else if (std::isalpha(c)) 
			{
				curToken.type = TokenType::Identifier;
				curToken.text += c;
			}
			else if (std::isdigit(c) || c == '.')
			{
				curToken.type = TokenType::Number;
				if (c == '.') curToken.text = "0";
				curToken.text += c;
			}
		}
	}

	if (curToken.type != TokenType::Invalid) outTokens.push_back(curToken);
}

const char* GetText(const TokenType type)
{
	switch (type)
	{
	case TokenType::Invalid: return "Invalid";
	case TokenType::LParen: return "LParen";
	case TokenType::RParen: return "RParen";
	case TokenType::Operator: return "Operator";
	case TokenType::Identifier: return "Identifier";
	case TokenType::Comma: return "Comma";
	case TokenType::Number: return "Number";
	default: return "WTF";
	}
}

void LogTokens(const std::vector<Token>& tokens)
{
	for (const auto& t : tokens)
	{
		std::cout << t.text << " (" << GetText(t.type) << ")" << std::endl;
	}
}

int GetPrecedence(const std::string& op)
{
	if (op == "^") return 4;
	if (op == "-u") return 4;
	if (op == "*" || op == "/") return 2;
	if (op == "+" || op == "-") return 1;
	return 0;
}

bool IsLAssoc(const std::string& op)
{
	if (op == "+" || op == "-") return true;
	if (op == "*" || op == "/") return true;
	return false;
}

OpmValue sub(const OpmValue& a, const OpmValue& b) { return a - b; }
OpmValue neg(const OpmValue& a) { return -a; }

Operation ExpressionParser::ToOp(const Token& token) const
{
	if (token.type == TokenType::Number)
	{
		if (token.text.back() == 'i') return Operation(OpmComplex(0, parse(token.text.c_str())), token.text);
		return Operation(parse(token.text.c_str()), token.text);
	}
	if (token.type == TokenType::Identifier)
	{
		if (m_unaryFns.count(token.text) != 0) return Operation(m_unaryFns.at(token.text), token.text);
		if (m_binaryFns.count(token.text) != 0) return Operation(m_binaryFns.at(token.text), token.text);
		return Operation(token.text, token.text);
	}
	if (token.type == TokenType::Operator)
	{
		if (token.text == "+")  return Operation(operator+, token.text);
		if (token.text == "-")  return Operation(sub,       token.text);
		if (token.text == "-u") return Operation(neg,       token.text);
		if (token.text == "*")  return Operation(operator*, token.text);
		if (token.text == "/")  return Operation(operator/, token.text);
		if (token.text == "^")  return Operation(pow,		token.text);
	}

	assert(false);
	return Operation();
}

/*

while there are tokens to be read:
    read a token
    if the token is:
    - a number:
        put it into the output queue
    - a function:
        push it onto the operator stack 
    - an operator o1:
        while (
            there is an operator o2 other than the left parenthesis at the top
            of the operator stack, and (o2 has greater precedence than o1
            or they have the same precedence and o1 is left-associative)
        ):
            pop o2 from the operator stack into the output queue
        push o1 onto the operator stack
    - a left parenthesis (i.e. "("):
        push it onto the operator stack
    - a right parenthesis (i.e. ")"):
        while the operator at the top of the operator stack is not a left parenthesis:
            {assert the operator stack is not empty}
            // If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. /
            pop the operator from the operator stack into the output queue
        {assert there is a left parenthesis at the top of the operator stack}
        pop the left parenthesis from the operator stack and discard it
        if there is a function token at the top of the operator stack, then:
            pop the function from the operator stack into the output queue
/ After the while loop, pop the remaining items from the operator stack into the output queue. /
while there are tokens on the operator stack:
    // If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. /
    {assert the operator on top of the stack is not a (left) parenthesis}
    pop the operator from the operator stack onto the output queue

 */

Expression ExpressionParser::Parse(const std::string& string) const
{
	Expression out;
	std::vector<Token> tokens;
	Tokenize(string, tokens);
	//LogTokens(tokens);
	std::vector<Token> opStack;

	for (auto& token : tokens)
	{		
		if (token.type == TokenType::Number) out.PushOp(ToOp(token));
		if (token.type == TokenType::Identifier) 
		{
			if (IsFn(token.text)) opStack.push_back(token);
			else out.PushOp(ToOp(token));
		}
		if (token.type == TokenType::Operator)
		{
			while (!opStack.empty() && opStack.back().type == TokenType::Operator && 
				(GetPrecedence(opStack.back().text) >  GetPrecedence(token.text) 
			 || (GetPrecedence(opStack.back().text) == GetPrecedence(token.text) && IsLAssoc(opStack.back().text)))
				)
			{
				out.PushOp(ToOp(opStack.back()));
				opStack.pop_back();
			}
			opStack.push_back(token);
		}
		if (token.type == TokenType::LParen)
		{
			opStack.push_back(token);
		}
		if (token.type == TokenType::RParen || token.type == TokenType::Comma)
		{
			while (opStack.back().type != TokenType::LParen)
			{
				out.PushOp(ToOp(opStack.back()));
				opStack.pop_back();
			}
			assert(opStack.back().type == TokenType::LParen);
			if (token.type != TokenType::Comma) opStack.pop_back();
			if (opStack.empty()) continue;
			if (opStack.back().type == TokenType::Identifier || (opStack.back().type == TokenType::Operator && opStack.back().text == "-u"))
			{
				out.PushOp(ToOp(opStack.back()));
				opStack.pop_back();
			}
		}
	}
	while (!opStack.empty())
	{
		assert(opStack.back().type != TokenType::LParen);
		out.PushOp(ToOp(opStack.back()));
		opStack.pop_back();
	}

	out.Print();

	return out;
}
