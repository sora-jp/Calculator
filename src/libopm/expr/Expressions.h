#pragma once
#include "NExpression.h"

namespace Expression
{
	NExpression parse(NErrorCollection& outErrors, const NExpressionContext& ctx, const std::string& str);
	NExpression rewrite(const NExpression& expr, NExpressionRewriter& writer);

	template<typename T, typename... Args, std::enable_if_t<std::is_base_of_v<NExpressionRewriter, T> && std::is_constructible_v<T, Args...>, bool> = true>
	NExpression rewrite(const NExpression& expr, Args&&... args)
	{
		T rewriter(args...);
		return rewrite(expr, rewriter);
	}

	NCompiledExpression compile(NErrorCollection& outErrors, const NExpression& expr);

	bool isConstant(const NExpressionNode* node);
	OpmValue constantEval(const NExpressionNode* node);
}