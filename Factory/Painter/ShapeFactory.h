#pragma once
#include "IShapeFactory.h"
#include "ColorUtil.h"

typedef std::unique_ptr<CShape> ShapePtr;
typedef std::map<std::string, std::function<ShapePtr(std::istringstream & description, Color color)>> ShapeCreationMap;

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	ShapePtr CreateShape(std::string const& description) override;

private:
	ShapeCreationMap m_shapeCreationMap;

	static ShapePtr CreateEllipse(std::istringstream & stream, Color color);
	static ShapePtr CreatePolygon(std::istringstream & stream, Color color);
	static ShapePtr CreateRectangle(std::istringstream & stream, Color color);
	static ShapePtr CreateTriangle(std::istringstream & stream, Color color);
};
