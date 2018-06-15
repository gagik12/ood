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
	float minX = std::min({ m_point1.GetX(), m_point2.GetX(), m_point3.GetX() });
	float maxX = std::max({ m_point1.GetX(), m_point2.GetX(), m_point3.GetX() });

	float minY = std::min({ m_point1.GetX(), m_point2.GetX(), m_point3.GetX() });
	float maxY = std::max({ m_point1.GetX(), m_point2.GetX(), m_point3.GetX() });

	return RectD{ minX, minY, maxX - minX, maxY - minY };
}

void CTriangle::SetFrame(const RectD & rect)
{
	const auto oldFrame = GetFrame();
	auto UpdatePoint = [&](CPoint & point) {
		float scaleX = (point.GetX() - oldFrame.left) / oldFrame.width;
		float scaleY = (point.GetY() - oldFrame.top) / oldFrame.height;
		point = CPoint(rect.left + rect.width * scaleX, rect.top + rect.height * scaleY);
	};
	UpdatePoint(m_point1);
	UpdatePoint(m_point2);
	UpdatePoint(m_point3);
}

void CTriangle::DrawBehavior(ICanvas & canvas)const
{
	canvas.DrawTriangle(m_point1, m_point2, m_point3);
}