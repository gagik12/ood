#include "stdafx.h"
#include "Shape.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "ShapeFactory.h"
#include "Point.h" 
#include "Float.h"

CShapeFactory::CShapeFactory()
	: m_shapeCreationMap({
		{ ShapeType::RECTANGLE, std::bind(&CShapeFactory::CreateRectangle, std::placeholders::_1, std::placeholders::_2) },
		{ ShapeType::TRIANGLE, std::bind(&CShapeFactory::CreateTriangle, std::placeholders::_1, std::placeholders::_2) },
		{ ShapeType::ELLIPSE, std::bind(&CShapeFactory::CreateEllipse, std::placeholders::_1, std::placeholders::_2) },
		{ ShapeType::POLYGON, std::bind(&CShapeFactory::CreatePolygon, std::placeholders::_1, std::placeholders::_2) },
})
{
}

ShapePtr CShapeFactory::CreateShape(std::istream & description)
{
	ShapePtr result;

	std::string shapeType;
	std::string colorStr;

	description >> shapeType;
	description >> colorStr;

	auto it = m_shapeCreationMap.find(shapeType);
	if (it != m_shapeCreationMap.end())
	{
		result = it->second(description, CColorUtil::ToColor(colorStr));
	}
	else
	{
		throw std::invalid_argument("Invalid shape type!");
	}

	return result;
}


ShapePtr CShapeFactory::CreateEllipse(std::istream & description, Color color)
{
	CPoint center;
	CFloat horizontalRadius;
	CFloat verticalRadius;
	
	description >> center;
	description >> horizontalRadius;
	description >> verticalRadius;

	return std::make_unique<CEllipse>(center, horizontalRadius, verticalRadius, color);
}

ShapePtr CShapeFactory::CreatePolygon(std::istream & description, Color color)
{
	CPoint center;
	CFloat radius;
	unsigned vertexCount;

	description >> center;
	description >> radius;
	if (!(description >> vertexCount))
	{
		throw std::invalid_argument("Invalid value");
	}

	return std::make_unique<CRegularPolygon>(center, radius, vertexCount, color);
}

ShapePtr CShapeFactory::CreateRectangle(std::istream & description, Color color)
{
	CPoint leftTop;
	CPoint rightBottom;

	description >> leftTop;
	description >> rightBottom;

	return std::make_unique<CRectangle>(leftTop, rightBottom, color);
}

ShapePtr CShapeFactory::CreateTriangle(std::istream & description, Color color)
{
	CPoint point1;
	CPoint point2;
	CPoint point3;

	
	description >> point1;
	description >> point2;
	description >> point3;

	return std::make_unique<CTriangle>(point1, point2, point3, color);
}