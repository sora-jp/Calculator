#pragma once
#include <map>

#include "../rt_poly/OpmDynamic.h"
#include "NExpressionNode.h"
#include <string>
#include <utility>
#include <vector>

#include "StackBindings.hpp"
#define EXPR_STACK_DEPTH 16

struct FunctionImplementation;
struct FunctionDefinition
{
	std::string name;
	uint32_t paramCount;
};

enum class ErrorType
{
	Invalid, Info, Warning, Error
};

enum class ErrorClass
{
	Parsing, Conversion, Binding, Compilation, Evaluation
};

struct NExpressionError
{
	ErrorType type;
	ErrorClass cls;
	std::string err;
};

typedef std::vector<NExpressionError> NErrorCollection;

class NExpressionContext
{
	friend struct NCompiledOp;
	std::function<NExpression& (int)> m_resolveReference;
	std::map<std::string, OpmValue> m_variables;
	std::vector<std::pair<FunctionDefinition, FunctionImplementation>> m_userFuncs;

public:
	NExpressionContext() = default;
	NExpressionContext(std::function<NExpression&(int)> resolve) : m_resolveReference(std::move(resolve)) {}
	OpmValue get(const std::string& s) const { return m_variables.at(s); }
	NExpression& get(int histIdx) const { return m_resolveReference(histIdx); }
	const FunctionImplementation* get(const FunctionDefinition& f) const;
	void set(const OpmNum& val, const std::string& s) { m_variables[s] = wrap(val); }
	void set(const OpmComplex& val, const std::string& s) { m_variables[s] = wrap(val); }
	void set(const OpmValue& val, const std::string& s) { m_variables[s] = val; }
	void set(const FunctionImplementation& val, const FunctionDefinition& fn);
};

struct NCompiledOp
{
	NOpType type;

	std::string var;
	int histIdx = 0;
	OpmValue constant;
	union
	{
		UnaryOp unary = nullptr;
		BinaryOp binary;
	};
	FunctionDefinition fn = {};

	NCompiledOp(const int idx) : type(NOpType::HistoryRef), histIdx(idx) {}
	NCompiledOp(std::string var) : type(NOpType::Variable), var(std::move(var)) {}
	NCompiledOp(OpmValue constant) : type(NOpType::Constant), constant(std::move(constant)) {}
	NCompiledOp(UnaryOp op) : type(NOpType::Unary), unary(op) {}
	NCompiledOp(BinaryOp op) : type(NOpType::Binary), binary(op) {}
	NCompiledOp(FunctionDefinition fn) : type(NOpType::FunctionCall), fn(std::move(fn)) {}

	void operator()(NErrorCollection& outErrors, const NExpressionContext& ctx, OpmStack<EXPR_STACK_DEPTH>& stack) const;
};

class NCompiledExpression
{
	friend class NExpressionParser;
	std::vector<NCompiledOp> m_ops;

public:
	OpmValue exec(NErrorCollection& outErrors, const NExpressionContext& ctx) const;
};

class NExpressionRewriter
{
	friend class NExpressionParser;
public:
	virtual ~NExpressionRewriter() = default;
	virtual NExpressionNode* rewrite(const NExpressionNode* node) = 0;
};

struct FunctionImplementation
{
	NExpression expr;
	NCompiledExpression cachedExpr;
	std::vector<std::string> arguments;
};

class NExpressionParser
{
	std::unordered_map<std::string, UnaryOp> m_unary;
	std::unordered_map<std::string, BinaryOp> m_binary;

	void compileRecursive(NErrorCollection& errs, std::vector<NCompiledOp>& ops, const NExpressionNode* node) const;
	bool ConstantFoldR(NExpressionNode* node) const;
	void ConstantFoldAll(NExpressionNode* node) const;

public:
	NExpressionParser();
	NExpressionParser(std::unordered_map<std::string, UnaryOp> unary, std::unordered_map<std::string, BinaryOp> binary) : m_unary(std::move(unary)), m_binary(std::move(binary)) {}
	void registerFn(const std::string& name, UnaryOp val) { m_unary[name] = val; }
	void registerFn(const std::string& name, BinaryOp val) { m_binary[name] = val; }

	NExpression parse(NErrorCollection& outErrors, const NExpressionContext& ctx, const std::string& in) const;
	NExpression rewrite(NExpressionRewriter& rew, const NExpression& expr) const;
	NCompiledExpression compile(NErrorCollection& outErrors, const NExpression& expr) const;

	bool IsConstant(const NExpressionNode* node) const;
	OpmValue ConstantEval(const NExpressionNode* node) const;
	static void Print(const NExpression& expr);
	static std::string ToString(const NExpression& expr);
};