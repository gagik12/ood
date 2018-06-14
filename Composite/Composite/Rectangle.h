#pragma once
#include "Shape.h"
#include "Point.h"

class CRectangle : public CShape
{
public:
	CRectangle(CPoint const& leftTop, float width, float height);
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;
protected:
	void DrawBehavior(ICanvas & canvas)const override;
private:
	CPoint m_leftTop;
	float m_width;
	float m_height;
};

