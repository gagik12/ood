#pragma once
#include "Shape.h"
#include "Point.h"

class CRectangle : public CShape
{
public:
	CRectangle(CPoint const& leftTop, CPoint const& rightBottom, Color color);
	void Draw(ICanvas & canvas) const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
	CPoint m_rightTop;
	CPoint m_leftBottom;
};

