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
#include "ISlide.h"

std::shared_ptr<IShape> CreateHouse()
{
	auto house = std::make_shared<CGroupShape>();

	auto roof = std::make_shared<CTriangle>(CPoint(300, 50), CPoint(150, 130), CPoint(450, 130));
	roof->GetFillStyle()->SetColor(RGBColor{ 150, 75, 0 });
	roof->GetOutlineStyle()->SetOutlineThikness(7);
	roof->GetOutlineStyle()->SetColor(RGBColor{ 150, 100, 0 });

	auto base = std::make_shared<CRectangle>(CPoint(170, 125), 260.f, 200.f);

	auto window = std::make_shared<CRectangle>(CPoint(230, 175), 50.f, 60.f);
	window->GetFillStyle()->SetColor(RGBColor{ 255, 255, 255 });

	auto door = std::make_shared<CRectangle>(CPoint(320, 195), 70.f, 120.f);
	door->GetFillStyle()->SetColor(RGBColor{ 250, 235, 170 });

	house->InsertShape(roof, 1);
	house->InsertShape(base, 0);
	house->InsertShape(window, 2);
	house->InsertShape(door, 2);

	house->SetFrame(RectD{ 100, 200, 200, 500 });
	//house->SetFrame(RectD{ 100, 200, 100, 100 });

	return house;
}

std::shared_ptr<IShape> CreateWorld()
{
	auto world = std::make_shared<CGroupShape>();

	auto grass = std::make_shared<CRectangle>(CPoint(0, 260), 600.f, 340.f);
	grass->GetFillStyle()->SetColor(RGBColor{ 0, 195, 0 });

	auto sky = std::make_shared<CRectangle>(CPoint(0, 0), 600.f, 260.f);
	sky->GetFillStyle()->SetColor(RGBColor{ 120, 219, 226 });
	sky->GetOutlineStyle()->SetColor(RGBColor{ 120, 219, 226 });

	auto sun = std::make_shared<CEllipse>(CPoint(0, 0), 30.f, 30.f);
	sun->GetFillStyle()->SetColor(RGBColor{ 253, 233, 16 });

	world->InsertShape(grass, 1);
	world->InsertShape(sky, 0);
	world->InsertShape(sun, 2);

	return world;
}

std::shared_ptr<ISlide> CreatePicture()
{
	auto slide = std::make_shared<CSlide>(600, 600);

	auto world = CreateWorld();
	auto house = CreateHouse();

	slide->AddShape(world);
	slide->AddShape(house);
	
	return slide;
}

int main()
{	
	auto picture = CreatePicture();

	CWindow window(*picture);
	window.ShowFixedSize({ 600, 600 });
	window.EnterMainLoop();
    return 0;
}

