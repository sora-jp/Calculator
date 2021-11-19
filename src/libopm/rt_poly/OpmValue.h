#pragma once
#include "OpmNum.hpp"
#include "complex/OpmComplex.hpp"
#include <type_traits>

enum class ValueType : uint8_t
{
	Invalid, Real, Complex
};

template<typename T> constexpr ValueType TypeOf = ValueType::Invalid;
template<> constexpr ValueType TypeOf<OpmNum> = ValueType::Real;
template<> constexpr ValueType TypeOf<OpmComplex> = ValueType::Complex;

template<typename T> struct is_opm_type : std::false_type {};
template<> struct is_opm_type<OpmNum> : std::true_type {};
template<> struct is_opm_type<OpmComplex> : std::true_type {};

template<typename T>
constexpr bool is_opm_type_v = is_opm_type<T>::value;

template<typename T>
using enable_if_opm_type = std::enable_if_t<is_opm_type_v<T>, bool>;

class OpmValue
{
	ValueType m_type;
	size_t m_size;
	void* m_value;

public:
	constexpr OpmValue() : m_type(ValueType::Invalid), m_size(0), m_value(nullptr) {}
	constexpr OpmValue(void* value, const ValueType type, const size_t size) : m_type(type), m_size(size), m_value(value) {}
	OpmValue(const OpmValue& other) : m_type(other.m_type), m_size(other.m_size), m_value(nullptr)
	{
		if (other.m_type == ValueType::Invalid) return;
		m_value = malloc(m_size);
		if (m_value == nullptr)
		{
			m_type = ValueType::Invalid;
			return;
		}
		memcpy(m_value, other.m_value, m_size);
	}
	OpmValue(OpmValue&& other) noexcept : m_type(other.m_type), m_size(other.m_size), m_value(other.m_value)
	{
		other.m_type = ValueType::Invalid;
		other.m_size = 0;
		other.m_value = nullptr;
	}

	~OpmValue() { if (m_value) free(m_value); }

	ValueType type() const { return m_type; }
	void* value() const { return m_value; }
	OpmValue& roundToNearest();
	OpmValue& normalize();
	OpmValue& operator=(const OpmValue& other);
	OpmValue& operator=(OpmValue&& other) noexcept;
	bool operator==(const OpmValue& other) const;
};

inline bool OpmValue::operator==(const OpmValue& other) const
{
	return other.m_value == m_value && other.m_type == m_type;
}

inline OpmValue& OpmValue::operator=(const OpmValue& other)
{
	if (&other == this) return *this;
	m_type = other.m_type;
	m_size = other.m_size;
	if (other.m_type == ValueType::Invalid) return *this;
	const auto nv = malloc(m_size);
	if (nv == nullptr)
	{
		m_type = ValueType::Invalid;
		return *this;
	}
	memcpy(nv, other.m_value, m_size);
	if (m_value) free(m_value);
	m_value = nv;
	return *this;
}

template<typename T, enable_if_opm_type<T> = true>
OpmValue&& wrap(const T& value)
{
	const auto ptr = malloc(sizeof(T));
	if (ptr == nullptr)
	{
		return std::move(OpmValue());
	}
	memcpy(ptr, &value, sizeof(T));
	return std::move(OpmValue(ptr, TypeOf<T>, sizeof(T)));
}

inline OpmValue&& wrap(const OpmComplex& value, bool downcast = true)
{
	if (is_zero(value.imag) && downcast) return wrap(value.real);
	return wrap<OpmComplex>(value);
}

template<typename T, enable_if_opm_type<std::remove_all_extents_t<T>> = true>
T* unwrap(OpmValue& value)
{
	if (value.type() != TypeOf<std::remove_all_extents_t<T>>) return nullptr;
	return static_cast<T*>(value.value());
}

template<typename T, enable_if_opm_type<std::remove_all_extents_t<T>> = true>
const T* unwrap(const OpmValue& value)
{
	if (value.type() != TypeOf<std::remove_all_extents_t<T>>) return nullptr;
	return static_cast<const T*>(value.value());
}