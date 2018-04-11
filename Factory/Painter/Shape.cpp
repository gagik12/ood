#include "stdafx.h"
#include "Shape.h"

CShape::CShape(RGBColor const& color)
	: m_color(color)
{
}

RGBColor CShape::GetColor() const
{
	return m_color;
}