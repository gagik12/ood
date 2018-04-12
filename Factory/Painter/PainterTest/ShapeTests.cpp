#include "stdafx.h"
#include "../ICanvas.h"
#include "../Shape.h"
#include "../Triangle.h"
#include "../Rectangle.h"
#include "../Ellipse.h"
#include "../RegularPolygon.h"
#include "TestUtils.h"
namespace
{
	class CStreamCanvas : public ICanvas
	{
	public:
		CStreamCanvas(boost::test_tools::output_test_stream & stream)
			: m_stream(stream)
		{
		}

		void SetColor(RGBColor const& color) override
		{
			m_color = color;
			m_stream << "Set Color: " << int(m_color.r) << " " << int(m_color.g) << " " << int(m_color.b) << std::endl;
		}

		void DrawLine(CPoint const& from, CPoint const& to) override
		{
			m_stream << "Draw line: from [" << from << "] to [" << to << "]" << std::endl;
		}

		void DrawEllipse(CPoint const& center, float width, float height) override
		{
			m_stream << "Draw ellipse center [" << center << "], Width: " << width << " height: " << height << std::endl;
		}
	private:
		boost::test_tools::output_test_stream & m_stream;
		RGBColor m_color;
	};
}
class Circle : public CShape
{
public:
	Circle(RGBColor const& color)
		: CShape(color)
	{
	}

	void Draw(ICanvas& canvas)const override
	{
		canvas.SetColor(GetColor());
		canvas.DrawLine(CPoint(100, 20), CPoint(20, 20));
	}
};

BOOST_AUTO_TEST_SUITE(Shape)
	BOOST_AUTO_TEST_CASE(has_color)
	{
		RGBColor color{255, 0, 0};
		Circle circle(color);
		CTestUtils::CheckColor(circle.GetColor(), color);
	}
	BOOST_AUTO_TEST_CASE(triangle_can_be_drawn_on_canvas)
	{
		boost::test_tools::output_test_stream stream;

		CTriangle triangle(CPoint(10, 10), CPoint(210, 210), CPoint(110, 110), {255, 0, 0});
		CStreamCanvas canvas(stream);
		triangle.Draw(canvas);

		BOOST_CHECK(stream.is_equal(
			"Set Color: 255 0 0\n"
			"Draw line: from [10 : 10] to [210 : 210]\n"
			"Draw line: from [210 : 210] to [110 : 110]\n"
			"Draw line: from [110 : 110] to [10 : 10]\n"));
	}

	BOOST_AUTO_TEST_CASE(rectangle_can_be_drawn_on_canvas)
	{
		boost::test_tools::output_test_stream stream;

		CRectangle rectangle(CPoint(10, 10), CPoint(210, 210), { 0, 255, 0 });
		CStreamCanvas canvas(stream);
		rectangle.Draw(canvas);

		BOOST_CHECK(stream.is_equal(
			"Set Color: 0 255 0\n"
			"Draw line: from [10 : 10] to [210 : 10]\n"
			"Draw line: from [210 : 10] to [210 : 210]\n"
			"Draw line: from [210 : 210] to [10 : 210]\n"
			"Draw line: from [10 : 210] to [10 : 10]\n"));
	}

	BOOST_AUTO_TEST_CASE(ellipse_can_be_drawn_on_canvas)
	{
		boost::test_tools::output_test_stream stream;

		CEllipse ellipse(CPoint(10, 10), 10, 100, { 0, 0, 255 });
		CStreamCanvas canvas(stream);
		ellipse.Draw(canvas);

		BOOST_CHECK(stream.is_equal(
			"Set Color: 0 0 255\n"
			"Draw ellipse center [0 : -90], Width: 20 height: 200\n"));
	}

	BOOST_AUTO_TEST_CASE(regular_polygon_can_be_drawn_on_canvas)
	{
		boost::test_tools::output_test_stream stream;

		CRegularPolygon regularPolygon(CPoint(10, 10), 10, 3, { 0, 0, 255 });
		CStreamCanvas canvas(stream);
		regularPolygon.Draw(canvas);

		BOOST_CHECK(stream.is_equal(
			"Set Color: 0 0 255\n"
			"Draw line: from [10 : 20] to [18.6603 : 5]\n"
			"Draw line: from [18.6603 : 5] to [1.33975 : 5]\n"
			"Draw line: from [1.33975 : 5] to [10 : 20]\n"));
	}
BOOST_AUTO_TEST_SUITE_END()