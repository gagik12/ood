#include "stdafx.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "FillStyle.h"
#include "OutlineStyle.h"
#include "IShape.h"
#include "Point.h"
#include "GroupShape.h"
#include "Canvas.h"
#include "Slide.h"

int main()
{
	auto triangle = std::make_shared<CTriangle>(CPoint(100, 200), CPoint(200, 100), CPoint(150, 150));
	auto rectangle = std::make_shared<CRectangle>(CPoint(100, 100), 200.0, 200.0);
	auto ellipse = std::make_shared<CEllipse>(CPoint(50, 50), 50.0, 30.0);
	
	auto house = std::make_shared<CGroupShape>();
	house->InsertShape(triangle, 1);
	house->InsertShape(rectangle, 1);
	house->InsertShape(ellipse, 1);

	CCanvas canvas(std::cout);
	//house->Draw(canvas);

	auto slide = std::make_shared<CSlide>(100, 200);
	slide->AddShape(house);
	slide->Draw(canvas);
    return 0;
}

