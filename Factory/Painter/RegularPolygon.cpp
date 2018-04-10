#include "stdafx.h"
#include "RegularPolygon.h"


CRegularPolygon::CRegularPolygon(CPoint const& center, float radius, unsigned vertexCount, Color color)
	: CShape(color)
	, m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
{
	for (size_t i = 0; i < m_vertexCount; ++i)
	{
		float angle =  static_cast<float>(2 * M_PI * i / m_vertexCount);
		float x = m_center.GetX() + m_radius * std::sin(angle);
		float y = m_center.GetY() + m_radius * std::cos(angle);
		m_points.push_back(CPoint(x, y));
	}
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	for (size_t i = 0; i < m_points.size(); ++i)
	{
		canvas.DrawLine(m_points.at(i), m_points.at((i + 1) % m_points.size()));
	}
}

CPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

float CRegularPolygon::GetRadius() const
{
	return m_radius;
}

size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}