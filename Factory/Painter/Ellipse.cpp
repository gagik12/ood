#include "stdafx.h"
#include "Ellipse.h"


CEllipse::CEllipse(CPoint const& center, CFloat const& horizontalRadius, CFloat const& verticalRadius, Color color)
	: CShape(color)
	, m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

void CEllipse::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

CPoint CEllipse::GetCenter() const
{
	return m_center;
}

CFloat CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

CFloat CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}