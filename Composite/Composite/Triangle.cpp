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
	float minX = std::min({ m_point1.GetX(), m_point1.GetX(), m_point1.GetX() });
	float maxX = std::max({ m_point1.GetX(), m_point1.GetX(), m_point1.GetX() });

	float minY = std::min({ m_point1.GetY(), m_point1.GetY(), m_point1.GetY() });
	float maxY = std::max({ m_point1.GetY(), m_point1.GetY(), m_point1.GetY() });

	return RectD{ minX, minY, maxX - minX, maxY - minY };
}

void CTriangle::SetFrame(const RectD & rect)
{
	const auto oldFrame = GetFrame();
	auto UpdatePoint = [&](CPoint & point) {
		float scaleX = (point.GetX() - oldFrame.left) / oldFrame.width;
		float scaleY = (point.GetY() - oldFrame.top) / oldFrame.height;
		point = CPoint(rect.left + rect.left * scaleX, rect.top + rect.top * scaleY);
	};
	UpdatePoint(m_point1);
	UpdatePoint(m_point2);
	UpdatePoint(m_point3);
}

void CTriangle::DrawBehavior(ICanvas & canvas)const
{
	canvas.DrawTriangle(m_point1, m_point2, m_point3);
}