#pragma once
#include "Shape.h"
#include "Float.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
	CEllipse(CPoint const& center, float horizontalRadius, float verticalRadius, Color color);

	void Draw(ICanvas & canvas) const override;
	CPoint GetCenter() const;
	float GetHorizontalRadius() const;
	float GetVerticalRadius() const;
private:
	CPoint m_center;
	float m_horizontalRadius;
	float m_verticalRadius;
};

