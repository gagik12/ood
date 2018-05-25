#include "stdafx.h"
#include "Ellipse.h"


CEllipse::CEllipse(CPoint const& center, double horizontalRadius, double verticalRadius)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

RectD CEllipse::GetFrame()
{
	auto leftTop = CPoint(m_center.GetX() - m_horizontalRadius, m_center.GetY() - m_verticalRadius);
	return RectD{ leftTop.GetX(), leftTop.GetY(), 2 * m_horizontalRadius, 2 * m_verticalRadius };
}

void CEllipse::SetFrame(const RectD & rect)
{
	m_center = CPoint(rect.left + rect.width / 2, rect.top + rect.height / 2);
	m_horizontalRadius = rect.width / 2;
	m_verticalRadius = rect.height / 2;
}

void CEllipse::DrawBehavior(ICanvas & canvas)const
{
	double width = 2 * m_horizontalRadius;
	double height = 2 * m_verticalRadius;
	canvas.DrawEllipse(m_center.GetX() - m_horizontalRadius, m_center.GetY() - m_verticalRadius, width, height);
}