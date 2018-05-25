#pragma once
#include "Shape.h"
#include "Point.h"

class CRectangle : public CShape
{
public:
	CRectangle(CPoint const& leftTop, double width, double height);
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;
protected:
	void DrawBehavior(ICanvas & canvas)const override;
private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
};

