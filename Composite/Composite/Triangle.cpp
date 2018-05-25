#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle(CPoint const& point1, CPoint const& point2, CPoint const& point3)
	: m_point1(point1)
	, m_point2(point2)
	, m_point3(point3)
{
}

RectD CTriangle::GetFrame()
{
	return RectD();
}

void CTriangle::SetFrame(const RectD & rect)
{
	//m_frame = rect;
}

void CTriangle::DrawBehavior(ICanvas & canvas)const
{
	canvas.MoveTo(m_point1.GetX(), m_point1.GetY());
	canvas.LineTo(m_point2.GetX(), m_point2.GetY());
	canvas.LineTo(m_point3.GetX(), m_point3.GetY());
	canvas.LineTo(m_point1.GetX(), m_point1.GetY());
}