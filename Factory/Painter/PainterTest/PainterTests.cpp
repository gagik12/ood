#include "stdafx.h"
#include "../IPainter.h"
#include "../PictureDraft.h"
#include "../Painter.h"
namespace
{
	class EllipseShape : public CShape
	{
	public:
		EllipseShape()
			: CShape(RGBColor{ 0, 0, 0 })
		{
		}

		void Draw(ICanvas& canvas)const override
		{
			canvas.SetColor(GetColor());
			canvas.DrawEllipse(CPoint{ 0, 0 }, 10, 10);
		}
	};

	class TriangleShape : public CShape
	{
	public:
		TriangleShape()
			: CShape(RGBColor{ 0, 0, 0 })
		{
		}

		void Draw(ICanvas& canvas)const override
		{
			canvas.SetColor(GetColor());
			canvas.DrawLine(CPoint{ 0, 0 }, CPoint{ 200, 10 });
			canvas.DrawLine(CPoint{ 200, 10 }, CPoint{ 0, 10 });
			canvas.DrawLine(CPoint{ 200, 10 }, CPoint{ 0, 0 });
		}
	};

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
BOOST_AUTO_TEST_SUITE(Painter)
	BOOST_AUTO_TEST_CASE(draws_in_order_of_adding_shapes)
	{
		boost::test_tools::output_test_stream strm;

		CStreamCanvas canvas(strm);

		CPainter painter;
		CPictureDraft draft;

		draft.AddShape(std::make_unique<EllipseShape>());
		draft.AddShape(std::make_unique<TriangleShape>());

		painter.DrawPicture(draft, canvas);
		BOOST_CHECK(strm.is_equal(
			"Draw ellipse center [0 : 0], Width: 10 height: 10\n"
			"Draw line: from [0 : 0] to [200 : 10]\n"
			"Draw line: from [200 : 10] to [0 : 10]\n"
			"Draw line: from [200 : 10] to [0 : 0]\n"));
	}
BOOST_AUTO_TEST_SUITE_END()