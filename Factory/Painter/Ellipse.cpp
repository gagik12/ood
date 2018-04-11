#include "stdafx.h"
#include "Ellipse.h"


CEllipse::CEllipse(CPoint const& center, float horizontalRadius, float verticalRadius, RGBColor const& color)
	: CShape(color)
	, m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

void CEllipse::Draw(ICanvas & canvas) const
{
	float width = 2 * m_horizontalRadius;
	float height = 2 * m_verticalRadius;
	CPoint leftTop(m_center.GetX() - m_horizontalRadius, m_center.GetY() - m_verticalRadius);
	canvas.SetColor(GetColor());
	canvas.DrawEllipse(leftTop, width, height);
}

CPoint CEllipse::GetCenter() const
{
	return m_center;
}

float CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

float CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}