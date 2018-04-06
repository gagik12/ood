#include "stdafx.h"
#include "RegularPolygon.h"


CRegularPolygon::CRegularPolygon(CPoint const& center, CFloat const& radius, unsigned vertexCount, Color color)
	: CShape(color)
	, m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
{
	for (size_t i = 0; i < m_vertexCount; ++i)
	{
		float angle =  static_cast<float>(2 * M_PI * i / m_vertexCount);
		float x = m_center.GetX() + m_radius.GetValue() * std::sin(angle);
		float y = m_center.GetY() + m_radius.GetValue() * std::cos(angle);
		m_points.push_back(CPoint(x, y));
	}
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	for (size_t i = 0; i < m_points.size() - 1; ++i)
	{
		canvas.DrawLine(m_points.at(i), m_points.at(i + 1));
	}
	canvas.DrawLine(m_points.at(m_points.size() - 1), m_points.at(0));
}

CPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

CFloat CRegularPolygon::GetRadius() const
{
	return m_radius;
}

size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}