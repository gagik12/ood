#pragma once
#include "Shape.h"
#include "Point.h"

class CTriangle : public CShape
{
public:
	CTriangle(CPoint const& point1, CPoint const& point2, CPoint const& point3);
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;
protected:
	void DrawBehavior(ICanvas & canvas)const override;
private:
	CPoint m_point1;
	CPoint m_point2;
	CPoint m_point3;
};

