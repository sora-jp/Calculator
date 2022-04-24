#include "OpmValue.h"

OpmValue& OpmValue::roundToNearest()
{
	if (m_type == TypeOf<OpmNum>) unwrap<OpmNum>(*this)->roundToNearest();
	if (m_type == TypeOf<OpmComplex>) unwrap<OpmComplex>(*this)->roundToNearest();
	return *this;
}

OpmValue& OpmValue::normalize()
{
	if (m_type == TypeOf<OpmNum>) unwrap<OpmNum>(*this)->normalize();
	if (m_type == TypeOf<OpmComplex>) unwrap<OpmComplex>(*this)->normalize();
	return *this;
}

OpmValue& OpmValue::operator=(OpmValue&& other) noexcept
{
	m_type = other.m_type;
	m_size = other.m_size;
	m_value = other.m_value;

	other.m_type = ValueType::Invalid;
	other.m_size = 0;
	other.m_value = nullptr;

	return *this;
}
