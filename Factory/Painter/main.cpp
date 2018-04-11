// Painter.cpp: определяет точку входа для консольного приложения.
//
//git sub3
#include "stdafx.h"
#include "Designer.h"
#include "Painter.h"
#include "Client.h"
#include "Canvas.h"
#include "Window.h"

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

	CPictureDraft pictureDraft = designer.CreateDraft(std::cin);

	CWindow window(painter, pictureDraft);
	window.ShowFixedSize({ 600, 600 });
	window.EnterMainLoop();

	return 0;
}

