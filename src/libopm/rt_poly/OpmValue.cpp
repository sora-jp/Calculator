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