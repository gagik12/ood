#pragma once
#include "Shape.h"
#include "Float.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
	CEllipse(CPoint const& center, CFloat const& horizontalRadius, CFloat const& verticalRadius, Color color);

	void Draw(ICanvas & canvas) const override;
	CPoint GetCenter() const;
	CFloat GetHorizontalRadius() const;
	CFloat GetVerticalRadius() const;
private:
	CPoint m_center;
	CFloat m_horizontalRadius;
	CFloat m_verticalRadius;
};

