#pragma once
#include "Shape.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
	CEllipse(CPoint const& center, float horizontalRadius, float verticalRadius);
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;
protected:
	void DrawBehavior(ICanvas & canvas)const override;
private:
	CPoint m_center;
	float m_horizontalRadius;
	float m_verticalRadius;

};

