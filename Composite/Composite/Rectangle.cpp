#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(CPoint const& leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

RectD CRectangle::GetFrame()
{
	return RectD{ m_leftTop.GetX(), m_leftTop.GetY(), m_width, m_height };
}

void CRectangle::SetFrame(const RectD & rect)
{
	m_leftTop = CPoint(rect.left, rect.top);
	m_width = rect.width;
	m_height = rect.height;
}

void CRectangle::DrawBehavior(ICanvas & canvas)const
{
	canvas.MoveTo(m_leftTop.GetX(), m_leftTop.GetY());
	canvas.LineTo(m_leftTop.GetX() + m_width, m_leftTop.GetY());
	canvas.LineTo(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
	canvas.LineTo(m_leftTop.GetX(), m_leftTop.GetY() + m_height);
	canvas.LineTo(m_leftTop.GetX(), m_leftTop.GetY());
}
