#pragma once

#include "NExpression.h"

class NDerivativeRewriter final : public NExpressionRewriter
{
	NExpressionNode* rewrite(const NExpressionNode* node) override;
	NExpressionNode* derive(const NExpressionNode* node) const;
};