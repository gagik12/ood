#pragma once
#include "IShapeFactory.h"
#include "ColorUtil.h"
#include "RGBColor.h"

typedef std::unique_ptr<CShape> ShapePtr;
typedef std::map<std::string, std::function<ShapePtr(std::istringstream & description, RGBColor const& color)>> ShapeCreationMap;

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	ShapePtr CreateShape(std::string const& description) override;

private:
	ShapeCreationMap m_shapeCreationMap;

	static ShapePtr CreateEllipse(std::istringstream & stream, RGBColor const& color);
	static ShapePtr CreatePolygon(std::istringstream & stream, RGBColor const& color);
	static ShapePtr CreateRectangle(std::istringstream & stream, RGBColor const& color);
	static ShapePtr CreateTriangle(std::istringstream & stream, RGBColor const& color);
};
