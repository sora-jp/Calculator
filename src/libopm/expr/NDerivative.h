#pragma once

#include "NExpression.h"

class NDerivative final : public NExpressionRewriter
{
	NExpressionNode* rewrite(const NExpressionContext& ctx, const NExpressionNode* node) override;
	NExpressionNode* derive(const NExpressionContext& ctx, const NExpressionNode* node) const;
};
