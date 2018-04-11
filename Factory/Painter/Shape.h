#pragma once
#include "ColorUtil.h"
#include "ICanvas.h"

namespace ShapeType
{
	std::string const TRIANGLE = "Triangle";
	std::string const ELLIPSE = "Ellipse";
	std::string const RECTANGLE = "Rectangle";
	std::string const POLYGON = "RegularPolygon";
}

class CShape
{
public:
	CShape(RGBColor const& color);
	virtual ~CShape() = default;
	virtual void Draw(ICanvas & canvas) const = 0;
	RGBColor GetColor()const;
private:
	RGBColor m_color;
};

