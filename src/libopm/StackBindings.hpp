#pragma once
#include "rt_poly/OpmValue.h"
#include <functional>
#include <type_traits>
#include <array>

template<int Size>
class OpmStack
{
public:
	OpmValue numbers[Size] {};
	int m_sp = 0;

	const OpmValue& Pop()
	{
		if (m_sp <= 0) return numbers[0];
		
		--m_sp;
		return numbers[m_sp];
	}
	
	void Push(const OpmValue& num)
	{
		if (m_sp < 0) m_sp = 0;
		
		if (m_sp >= Size)
		{
			for (int i = 0; i < Size - 1; i++)
			{
				numbers[i] = std::move(numbers[i + 1]);
			}
			numbers[Size - 1] = num;
		}
		else 
		{
		
			numbers[m_sp] = num;
			++m_sp;
		}
	}

	[[nodiscard]] int StackSize() const { return m_sp; }
	const OpmValue& operator[](int idx) const { return numbers[idx]; }
};