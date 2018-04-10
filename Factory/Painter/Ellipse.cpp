#include "stdafx.h"
#include "Ellipse.h"


CEllipse::CEllipse(CPoint const& center, float horizontalRadius, float verticalRadius, Color color)
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

float CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

float CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}