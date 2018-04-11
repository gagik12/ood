#pragma once
#include "Shape.h"
#include "Point.h"

class CTriangle : public CShape
{
public:
	CTriangle(CPoint const& point1, CPoint const& point2, CPoint const& point3, RGBColor const& color);

	void Draw(ICanvas & canvas) const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
private:
	CPoint m_point1;
	CPoint m_point2;
	CPoint m_point3;
};

