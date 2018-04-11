#pragma once
#include "Shape.h"
#include "Point.h"
#include "Float.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(CPoint const& center, float radius, unsigned vertexCount, RGBColor const& color);

	void Draw(ICanvas& canvas) const override;
	CPoint GetCenter() const;
	float GetRadius() const;
	size_t GetVertexCount() const;
private:
	std::vector<CPoint> m_points;
	CPoint m_center;
	float m_radius;
	unsigned m_vertexCount;
};

