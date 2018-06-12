#include "stdafx.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "FillStyle.h"
#include "OutlineStyle.h"
#include "IShape.h"
#include "Point.h"
#include "GroupShape.h"
#include "Slide.h"
#include "Window.h"

int main()
{
	auto triangle = std::make_shared<CTriangle>(CPoint(300, 50), CPoint(150, 130), CPoint(450, 130));
	auto rectangle = std::make_shared<CRectangle>(CPoint(170, 125), 260.0, 200.0);
	auto ellipse = std::make_shared<CEllipse>(CPoint(400, 50), 50.0, 30.0);
	
	auto house = std::make_shared<CGroupShape>();
	house->InsertShape(triangle, 1);
	house->InsertShape(rectangle, 0);
	house->InsertShape(ellipse, 1);

	CWindow window(*house);
	window.ShowFixedSize({ 600, 600 });
	window.EnterMainLoop();
    return 0;
}

