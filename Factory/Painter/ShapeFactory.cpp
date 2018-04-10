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

ShapePtr CShapeFactory::CreateShape(std::string const& description)
{
	ShapePtr result;

	std::string shapeType;
	std::string colorStr;
	std::istringstream stream(description);

	stream >> shapeType;
	stream >> colorStr;

	auto it = m_shapeCreationMap.find(shapeType);
	if (it != m_shapeCreationMap.end())
	{
		result = it->second(stream, CColorUtil::ToColor(colorStr));
	}
	else
	{
		throw std::invalid_argument("Invalid shape type!");
	}

	return result;
}


ShapePtr CShapeFactory::CreateEllipse(std::istringstream & stream, Color color)
{
	CPoint center;
	float horizontalRadius;
	float verticalRadius;
	
	stream >> center;
	if (!(stream >> horizontalRadius && stream >> verticalRadius))
	{
		throw std::invalid_argument("Invalid value");
	}

	return std::make_unique<CEllipse>(center, horizontalRadius, verticalRadius, color);
}

ShapePtr CShapeFactory::CreatePolygon(std::istringstream & stream, Color color)
{
	CPoint center;
	float radius;
	unsigned vertexCount;

	stream >> center;
	if (!(stream >> radius && stream >> vertexCount))
	{
		throw std::invalid_argument("Invalid value");
	}

	return std::make_unique<CRegularPolygon>(center, radius, vertexCount, color);
}

ShapePtr CShapeFactory::CreateRectangle(std::istringstream & stream, Color color)
{
	CPoint leftTop;
	CPoint rightBottom;

	stream >> leftTop;
	stream >> rightBottom;

	return std::make_unique<CRectangle>(leftTop, rightBottom, color);
}

ShapePtr CShapeFactory::CreateTriangle(std::istringstream & stream, Color color)
{
	CPoint point1;
	CPoint point2;
	CPoint point3;

	
	stream >> point1;
	stream >> point2;
	stream >> point3;

	return std::make_unique<CTriangle>(point1, point2, point3, color);
}