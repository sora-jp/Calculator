#pragma once
#include <vector>

enum class NOpType
{
	Invalid, Binary, Unary, Constant, Variable, FunctionCall, HistoryRef
};

typedef OpmValue(*BinaryOp)(const OpmValue&, const OpmValue&);
typedef OpmValue(*UnaryOp)(const OpmValue&);

struct NOperation
{
	NOpType type = NOpType::Invalid;
	int32_t histIndex = -1;
	std::string payload = {};
	OpmValue constant;

	NOperation() = default;
	NOperation(NOpType type, int32_t histIndex) : type(type), histIndex(histIndex) {}
	NOperation(NOpType type, const std::string& payload) : type(type), payload(payload) {}
	NOperation(NOpType type, OpmValue constant) : type(type), constant(std::move(constant)) {}

	NOperation(const NOperation& other) : type(other.type), payload(other.payload), constant(other.constant), histIndex(other.histIndex) {}
	NOperation(NOperation&& other) noexcept : type(other.type), payload(std::move(other.payload)), constant(std::move(other.constant)), histIndex(other.histIndex)
	{
		other.type = NOpType::Invalid;
	}

	NOperation& operator=(const NOperation& other)
	{
		type = other.type;
		payload = other.payload;
		constant = other.constant;
		histIndex = other.histIndex;
		return *this;
	}

	NOperation& operator=(NOperation&& other) noexcept
	{
		type = other.type;
		payload = std::move(other.payload);
		constant = std::move(other.constant);
		histIndex = other.histIndex;
		other.type = NOpType::Invalid;
		return *this;
	}
};

struct NExpressionNode
{
	NOperation op;
	std::vector<NExpressionNode*> children;

	NExpressionNode() = default;
	NExpressionNode(NOperation op, const std::initializer_list<NExpressionNode*> list) : op(std::move(op)), children(list) {}
	NExpressionNode(NOperation op) : op(std::move(op)) {}

	NExpressionNode* child(uint32_t idx) const { return idx < children.size() ? children[idx] : nullptr; }
	
	void setChildren(std::initializer_list<NExpressionNode*> newChildren)
	{
		for (const auto* c : children) delete c;
		children = newChildren;
	}

	NExpressionNode* copy() const
	{
		auto* ret = new NExpressionNode();
		ret->op = op;
		for (const auto* c : children)
		{
			ret->children.push_back(c->copy());
		}
		return ret;
	}

	~NExpressionNode()
	{
		for (const auto* c : children) delete c;
	}
};

enum class NExpressionType
{
	Expression, FunctionDefinition, VariableAssignment
};

struct NExpression
{
	NExpressionType type = NExpressionType::Expression;
	std::string varName;
	std::vector<std::string> fnData {};
	NExpressionNode* top = nullptr;

	NExpression() = default;
	NExpression(NExpressionType type, const std::string& varName, const std::vector<std::string>& fnData, NExpressionNode* top) : type(type), varName(varName), fnData(fnData), top(top) {}
	NExpression(const NExpression& other) : type(other.type), varName(other.varName), fnData(other.fnData), top(other.top != nullptr ? other.top->copy() : nullptr) {}
	NExpression(NExpression&& other) noexcept : type(other.type), varName(std::move(other.varName)), fnData(std::move(other.fnData)), top(other.top)
	{
		other.top = nullptr;
	}

	NExpression& operator=(const NExpression& other)
	{
		if (&other == this) return *this;
		type = other.type;
		varName = other.varName;
		fnData = other.fnData;
		top = other.top ? other.top->copy() : nullptr;
		return *this;
	}

	~NExpression()
	{
		delete top;
	}
};

inline NExpressionNode* binOp(NExpressionNode* a, const std::string& op, NExpressionNode* b) { return new NExpressionNode{ {NOpType::Binary, op}, {a, b} }; }
inline NExpressionNode* unOp(const std::string& op, NExpressionNode* a) { return new NExpressionNode{ {NOpType::Unary, op}, {a} }; }
inline NExpressionNode* fnCall(const std::string& fn, const std::initializer_list<NExpressionNode*> c) { return new NExpressionNode{ {NOpType::FunctionCall, fn}, c }; }
inline NExpressionNode* var(const std::string& v) { return new NExpressionNode{ { NOpType::Variable, v }, {} }; }

inline void binOp(NExpressionNode* a, const std::string& op, NExpressionNode* b, NExpressionNode* res) 
{
	res->op = {NOpType::Binary, op};
	res->setChildren({ a, b });
}

inline void unOp(const std::string& op, NExpressionNode* a, NExpressionNode* res)
{
	res->op = { NOpType::Unary, op };
	res->setChildren({ a });
}

inline void fnCall(const std::string& fn, const std::initializer_list<NExpressionNode*> c, NExpressionNode* res)
{
	res->op = { NOpType::FunctionCall, fn };
	res->setChildren(c);
}

inline void var(const std::string& v, NExpressionNode* res)
{
	res->op = { NOpType::Variable, v };
	res->setChildren({ });
}

inline NExpressionNode* add(NExpressionNode* a, NExpressionNode* b) { return binOp(a, "+", b); }
inline NExpressionNode* sub(NExpressionNode* a, NExpressionNode* b) { return binOp(a, "-", b); }
inline NExpressionNode* mul(NExpressionNode* a, NExpressionNode* b) { return binOp(a, "*", b); }
inline NExpressionNode* div(NExpressionNode* a, NExpressionNode* b) { return binOp(a, "/", b); }
inline NExpressionNode* neg(NExpressionNode* a) { return unOp("-", a); }
inline NExpressionNode* pow(NExpressionNode* a, NExpressionNode* b) { return fnCall("pow", { a, b }); }
inline NExpressionNode* ln(NExpressionNode* a) { return fnCall("ln", { a }); }
inline NExpressionNode* exp(NExpressionNode* a) { return fnCall("exp", { a }); }

template<typename T, enable_if_opm_type<T> = true>
inline NExpressionNode* constant(const T& a) { return new NExpressionNode{ std::move<NOperation>({NOpType::Constant, wrap<T>(a)}), {}}; }

inline NExpressionNode* constant(const OpmValue& a) { return new NExpressionNode{ {NOpType::Constant, a}, {} }; }

inline void add(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { binOp(a, "+", b, res); }
inline void sub(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { binOp(a, "-", b, res); }
inline void mul(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { binOp(a, "*", b, res); }
inline void div(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { binOp(a, "/", b, res); }
inline void neg(NExpressionNode* a, NExpressionNode* res) { unOp("-", a, res); }
inline void pow(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { fnCall("pow", { a, b }, res); }
inline void ln(NExpressionNode* a, NExpressionNode* res) { fnCall("ln", { a }, res); }
inline void exp(NExpressionNode* a, NExpressionNode* res) { fnCall("exp", { a }, res); }

inline bool is(const NExpressionNode* node, NOpType type, const std::string& payload) { return node->op.type == type && node->op.payload == payload; }
inline bool is_add(const NExpressionNode* node) { return is(node, NOpType::Binary, "+"); }
inline bool is_sub(const NExpressionNode* node) { return is(node, NOpType::Binary, "-"); }
inline bool is_mul(const NExpressionNode* node) { return is(node, NOpType::Binary, "*"); }
inline bool is_div(const NExpressionNode* node) { return is(node, NOpType::Binary, "/"); }
inline bool is_neg(const NExpressionNode* node) { return is(node, NOpType::Unary , "-"); }
inline bool is_pow(const NExpressionNode* node) { return is(node, NOpType::FunctionCall, "pow"); }
inline bool is_ln (const NExpressionNode* node) { return is(node, NOpType::FunctionCall, "ln"); }
inline bool is_exp(const NExpressionNode* node) { return is(node, NOpType::FunctionCall, "exp"); }
inline bool is_constant(const NExpressionNode* node) { return node->op.type == NOpType::Constant; }
inline bool is_var(const NExpressionNode* node) { return node->op.type == NOpType::Variable; }
inline bool is_var(const NExpressionNode* node, const std::string& var) { return is(node, NOpType::Variable, var); }