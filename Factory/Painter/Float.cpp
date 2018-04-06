#include "stdafx.h"
#include "Float.h"


CFloat::CFloat()
{
}

float CFloat::GetValue()
{
	return m_value;
}

std::istream & operator >> (std::istream & stream, CFloat & fl)
{
	if (!(stream >> fl.m_value))
	{
		throw std::invalid_argument("Invalid value");
	}
	return stream;
}

std::ostream & operator<<(std::ostream& stream, CFloat const& fl)
{
	stream << fl.m_value;
	return stream;
}