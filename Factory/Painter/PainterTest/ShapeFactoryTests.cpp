#include "stdafx.h"
#include "../Shape.h"
#include "../Triangle.h"
#include "../Rectangle.h"
#include "../Ellipse.h"
#include "../RegularPolygon.h"
#include "../ShapeFactory.h"
#include "TestUtils.h"

template <typename Ex, typename Fn>
void ExpectException(Fn && fn, std::string const& expectedDescription)
{
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		return e.what() == expectedDescription;
	});
}

struct SShapeFactoryFixture
{
	CShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(ShapeFactory, SShapeFactoryFixture)
	BOOST_AUTO_TEST_CASE(throws_exception_when_the_input_data_is_not_valid)
	{
		std::string commandLine = "Circle";
		ExpectException<std::invalid_argument>([&] {
			factory.CreateShape(commandLine);
		}, "Invalid shape type!");

		commandLine = "Triangle white";
		ExpectException<std::invalid_argument>([&] {
			factory.CreateShape(commandLine);
		}, "Color not found");

		commandLine = "Triangle red e22 22e 100 100 12 202";
		ExpectException<std::invalid_argument>([&] {
			factory.CreateShape(commandLine);
		}, "Invalid point");

	}

	BOOST_AUTO_TEST_CASE(can_create_triangle)
	{
		std::string commandLine = "Triangle red 10 10 100 20 20 400";
		auto shape = factory.CreateShape(commandLine);
		CTriangle* triangle = dynamic_cast<CTriangle*>(shape.get());
		BOOST_REQUIRE(triangle != nullptr);

		CTestUtils::CheckColor(triangle->GetColor(), RGBColor{255, 0, 0});
		CTestUtils::CheckPoint(triangle->GetVertex1(), CPoint(10, 10));
		CTestUtils::CheckPoint(triangle->GetVertex2(), CPoint(100, 20));
		CTestUtils::CheckPoint(triangle->GetVertex3(), CPoint(20, 400));
	}

	BOOST_AUTO_TEST_CASE(can_create_rectangle)
	{
		std::string commandLine = "Rectangle green 10 10 100 20";
		auto shape = factory.CreateShape(commandLine);
		CRectangle* rectangle = dynamic_cast<CRectangle*>(shape.get());
		BOOST_REQUIRE(rectangle != nullptr);

		CTestUtils::CheckColor(rectangle->GetColor(), RGBColor{ 0, 255, 0 });
		CTestUtils::CheckPoint(rectangle->GetLeftTop(), CPoint(10, 10));
		CTestUtils::CheckPoint(rectangle->GetRightBottom(), CPoint(100, 20));
	}

	BOOST_AUTO_TEST_CASE(can_create_ellipse)
	{
		std::string commandLine = "Ellipse blue 10 10 100 20";
		auto shape = factory.CreateShape(commandLine);
		CEllipse* ellipse = dynamic_cast<CEllipse*>(shape.get());
		BOOST_REQUIRE(ellipse != nullptr);

		CTestUtils::CheckColor(ellipse->GetColor(), RGBColor{ 0, 0, 255 });
		CTestUtils::CheckPoint(ellipse->GetCenter(), CPoint(10, 10));
		BOOST_CHECK_EQUAL(ellipse->GetHorizontalRadius(), 100);
		BOOST_CHECK_EQUAL(ellipse->GetVerticalRadius(), 20);
	}

	BOOST_AUTO_TEST_CASE(can_create_regularPolygon)
	{
		std::string commandLine = "RegularPolygon blue 10 10 100 2000";
		auto shape = factory.CreateShape(commandLine);
		CRegularPolygon* regularPolygon = dynamic_cast<CRegularPolygon*>(shape.get());
		BOOST_REQUIRE(regularPolygon != nullptr);

		CTestUtils::CheckColor(regularPolygon->GetColor(), RGBColor{ 0, 0, 255 });
		CTestUtils::CheckPoint(regularPolygon->GetCenter(), CPoint(10, 10));
		BOOST_CHECK_EQUAL(regularPolygon->GetRadius(), 100);
		BOOST_CHECK_EQUAL(regularPolygon->GetVertexCount(), 2000);
	}
BOOST_AUTO_TEST_SUITE_END()