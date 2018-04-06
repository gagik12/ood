#pragma once
#include "Shape.h"
#include "Point.h"
#include "Float.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(CPoint const& center, CFloat const& radius, unsigned vertexCount, Color color);

	void Draw(ICanvas& canvas) const override;
	CPoint GetCenter() const;
	CFloat GetRadius() const;
	size_t GetVertexCount() const;
private:
	std::vector<CPoint> m_points;
	CPoint m_center;
	CFloat m_radius;
	unsigned m_vertexCount;
};

