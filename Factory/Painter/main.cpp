// Painter.cpp: определяет точку входа для консольного приложения.
//
//git sub3
#include "stdafx.h"
#include "Designer.h"
#include "Painter.h"
#include "Client.h"
#include "Canvas.h"

void PrintInstructions()
{
	std::cout << "Rectangle <color> <left top point> <right bottom point>" << std::endl;
	std::cout << "Triangle <color> <point1> <point2> <point3>" << std::endl;
	std::cout << "Ellipse <color> <center point> <horizontal radius> <vertical radius>" << std::endl;
	std::cout << "RegularPolygon <color> <center point> <radius> <vertex count>" << std::endl;
}

int main()
{
	PrintInstructions();

	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	CPainter painter;

	CClient client(designer, painter);
	
	client.OrderPictures(std::cin);
	
	return 0;
}

