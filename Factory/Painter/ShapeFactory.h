#pragma once
#include "IShapeFactory.h"
#include "ColorUtil.h"

typedef std::unique_ptr<CShape> ShapePtr;
typedef std::map<std::string, std::function<ShapePtr(std::istream & description, Color color)>> ShapeCreationMap;

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	ShapePtr CreateShape(std::istream & description) override;

private:
	ShapeCreationMap m_shapeCreationMap;

	static ShapePtr CreateEllipse(std::istream & description, Color color);
	static ShapePtr CreatePolygon(std::istream & description, Color color);
	static ShapePtr CreateRectangle(std::istream & description, Color color);
	static ShapePtr CreateTriangle(std::istream & description, Color color);
};
