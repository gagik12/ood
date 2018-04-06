#include "stdafx.h"
#include "Point.h"

CPoint::CPoint()
{
}

CPoint::CPoint(float x, float y)
	: m_x(x)
	, m_y(y)
{
}

float CPoint::GetX() const
{
	return m_x;
}

float CPoint::GetY() const
{
	return m_y;
}

std::istream & operator>>(std::istream & stream, CPoint & point)
{
	if (!(stream >> point.m_x && stream >> point.m_y))
	{
		throw std::invalid_argument("Invalid point");
	}
	return stream;
}

std::ostream & operator<<(std::ostream& stream, CPoint const& point)
{
	stream << point.m_x << " : " << point.m_y;
	return stream;
}