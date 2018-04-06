#pragma once
#include "ColorUtil.h"
#include "ICanvas.h"

namespace ShapeType
{
	std::string const TRIANGLE = "triangle";
	std::string const ELLIPSE = "ellipse";
	std::string const RECTANGLE = "rectangle";
	std::string const POLYGON = "polygon";
}

class CShape
{
public:
	CShape(Color color);
	virtual ~CShape() = default;
	virtual void Draw(ICanvas & canvas) const = 0;
	Color GetColor()const;
private:
	Color m_color;
};

