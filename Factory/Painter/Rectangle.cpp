#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(CPoint const& leftTop, CPoint const& rightBottom, RGBColor const& color)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, m_rightTop(rightBottom.GetX(), leftTop.GetY())
	, m_leftBottom(leftTop.GetX(), rightBottom.GetY())
{
}

void CRectangle::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_leftTop, m_rightTop);
	canvas.DrawLine(m_rightTop, m_rightBottom);
	canvas.DrawLine(m_rightBottom, m_leftBottom);
	canvas.DrawLine(m_leftBottom, m_leftTop);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}