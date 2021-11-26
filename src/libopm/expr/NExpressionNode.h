#pragma once

enum class NOpType
{
	Invalid, Binary, Unary, Constant, Variable, FunctionCall
};

typedef OpmValue(*BinaryOp)(const OpmValue&, const OpmValue&);
typedef OpmValue(*UnaryOp)(const OpmValue&);

struct NOperation
{
	NOpType type = NOpType::Invalid;
	std::string payload = {};
	OpmValue constant;

	NOperation() = default;
	NOperation(NOpType type, const std::string& payload) : type(type), payload(payload) {}
	NOperation(NOpType type, OpmValue constant) : type(type), constant(std::move(constant)) {}

	NOperation(const NOperation& other) : type(other.type), payload(other.payload), constant(other.constant) {}
	NOperation(NOperation&& other) noexcept : type(other.type), payload(std::move(other.payload)), constant(std::move(other.constant))
	{
		other.type = NOpType::Invalid;
	}

	NOperation& operator=(const NOperation& other)
	{
		type = other.type;
		payload = other.payload;
		constant = other.constant;
		return *this;
	}

	NOperation& operator=(NOperation&& other) noexcept
	{
		type = other.type;
		payload = std::move(other.payload);
		constant = std::move(other.constant);

		other.type = NOpType::Invalid;
		return *this;
	}
};

struct NExpressionNode
{
	NOperation op;

	//NExpressionNode* parent = nullptr;
	NExpressionNode* left = nullptr;
	NExpressionNode* right = nullptr;

	NExpressionNode* copy() const
	{
		auto* ret = new NExpressionNode();
		ret->op = op;
		if (left)
		{
			ret->left = left->copy();
			//ret->left->parent = ret;
		}
		if (right)
		{
			ret->right = right->copy();
			//ret->right->parent = ret;
		}
		return ret;
	}

	~NExpressionNode()
	{
		delete left;
		delete right;
	}
};

struct NExpression
{
	NExpressionNode* top;

	NExpression(NExpressionNode* top) : top(top) {}
	NExpression(const NExpression& other) : top(other.top != nullptr ? other.top->copy() : nullptr) {}

	~NExpression()
	{
		delete top;
	}
};

inline NExpressionNode* binOp(NExpressionNode* a, const std::string& op, NExpressionNode* b) { return new NExpressionNode{ {NOpType::Binary, op}, a, b }; }
inline NExpressionNode* unOp(const std::string& op, NExpressionNode* a) { return new NExpressionNode{ {NOpType::Unary, op}, a }; }
inline NExpressionNode* fnCall(const std::string& fn, NExpressionNode* a, NExpressionNode* b) { return new NExpressionNode{ {NOpType::FunctionCall, fn}, a, b }; }
inline NExpressionNode* var(const std::string& v) { return new NExpressionNode{ { NOpType::Variable, v }, nullptr, nullptr }; }

inline void binOp(NExpressionNode* a, const std::string& op, NExpressionNode* b, NExpressionNode* res) 
{
	res->op = {NOpType::Binary, op};
	res->left = a;
	res->right = b;
}

inline void unOp(const std::string& op, NExpressionNode* a, NExpressionNode* res)
{
	res->op = { NOpType::Unary, op };
	res->left = a;
	res->right = nullptr;
}

inline void fnCall(const std::string& fn, NExpressionNode* a, NExpressionNode* b, NExpressionNode* res)
{
	res->op = { NOpType::FunctionCall, fn };
	res->left = a;
	res->right = b;
}

inline void var(const std::string& v, NExpressionNode* res)
{
	res->op = { NOpType::Variable, v };
	res->left = res->right = nullptr;
}


inline NExpressionNode* add(NExpressionNode* a, NExpressionNode* b) { return binOp(a, "+", b); }
inline NExpressionNode* sub(NExpressionNode* a, NExpressionNode* b) { return binOp(a, "-", b); }
inline NExpressionNode* mul(NExpressionNode* a, NExpressionNode* b) { return binOp(a, "*", b); }
inline NExpressionNode* div(NExpressionNode* a, NExpressionNode* b) { return binOp(a, "/", b); }
inline NExpressionNode* neg(NExpressionNode* a) { return unOp("-", a); }
inline NExpressionNode* pow(NExpressionNode* a, NExpressionNode* b) { return fnCall("pow", a, b); }
inline NExpressionNode* ln(NExpressionNode* a) { return fnCall("ln", a, nullptr); }
inline NExpressionNode* exp(NExpressionNode* a) { return fnCall("exp", a, nullptr); }

template<typename T, enable_if_opm_type<T> = true>
inline NExpressionNode* constant(const T& a) { return new NExpressionNode{ std::move<NOperation>({NOpType::Constant, wrap<T>(a)}), nullptr, nullptr }; }

inline NExpressionNode* constant(const OpmValue& a) { return new NExpressionNode{ {NOpType::Constant, a}, nullptr, nullptr }; }

inline void add(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { binOp(a, "+", b, res); }
inline void sub(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { binOp(a, "-", b, res); }
inline void mul(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { binOp(a, "*", b, res); }
inline void div(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { binOp(a, "/", b, res); }
inline void neg(NExpressionNode* a, NExpressionNode* res) { unOp("-", a, res); }
inline void pow(NExpressionNode* a, NExpressionNode* b, NExpressionNode* res) { fnCall("pow", a, b, res); }
inline void ln(NExpressionNode* a, NExpressionNode* res) { fnCall("ln", a, nullptr, res); }
inline void exp(NExpressionNode* a, NExpressionNode* res) { fnCall("exp", a, nullptr, res); }

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