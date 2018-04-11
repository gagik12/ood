#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(CPoint const& point1, CPoint const& point2, CPoint const& point3, RGBColor const& color)
	: CShape(color)
	, m_point1(point1)
	, m_point2(point2)
	, m_point3(point3)
{
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_point1, m_point2);
	canvas.DrawLine(m_point2, m_point3);
	canvas.DrawLine(m_point3, m_point1);
}

CPoint CTriangle::GetVertex1() const
{
	return m_point1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_point2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_point3;
}
