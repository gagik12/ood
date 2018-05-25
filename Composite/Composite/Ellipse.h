#pragma once
#include "Shape.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
	CEllipse(CPoint const& center, double horizontalRadius, double verticalRadius);
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;
protected:
	void DrawBehavior(ICanvas & canvas)const override;
private:
	CPoint m_center;
	double m_horizontalRadius;
	double m_verticalRadius;

};

