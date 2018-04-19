#include "stdafx.h"
#include "../Designer.h"
#include "../IDesigner.h"
#include "../Shape.h"
#include "../PictureDraft.h"
#include "../Triangle.h"
#include "../Rectangle.h"

typedef std::vector<std::string> ShapeDescriptions;

class Designer : public IDesigner
{
public:
	Designer(IShapeFactory& factory, boost::test_tools::output_test_stream & testStream)
		: m_factory(factory)
		, m_testStream(testStream)
	{}

	CPictureDraft CreateDraft(std::istream &data)
	{
		CPictureDraft draft;
		std::string line;
		while (std::getline(data, line))
		{
			try
			{
				auto shape = m_factory.CreateShape(line);
				draft.AddShape(std::move(shape));
				m_testStream << line << std::endl;
			}
			catch (std::exception & e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		return draft;
	}
private:
	IShapeFactory& m_factory;
	boost::test_tools::output_test_stream & m_testStream;
};

struct SDesignerFixture
{
	SDesignerFixture()
		: factory(CShapeFactory())
		, designer(factory, testStream)
	{
	}

	CShapeFactory factory;
	Designer designer;
	boost::test_tools::output_test_stream testStream;
};

BOOST_FIXTURE_TEST_SUITE(SDesigner, SDesignerFixture)
	BOOST_AUTO_TEST_CASE(returns_empty_draft_when_stream_is_empty)
	{
		std::istringstream stream;
		auto draft = designer.CreateDraft(stream);
		BOOST_CHECK(draft.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(can_create_draft)
	{
		ShapeDescriptions shapeDescriptions = {
			"Triangle red 10 10 200 10 100 50",
			"Ellipse blue 100 100 200 10",
			"Rectangle green 10 10 200 10"
		};

		std::stringstream stream;
		for (auto description : shapeDescriptions)
		{
			stream << description << std::endl;
		}

		auto draft = designer.CreateDraft(stream);
		BOOST_CHECK(!draft.IsEmpty());
		BOOST_CHECK(testStream.is_equal(
			"Triangle red 10 10 200 10 100 50\n"
			"Ellipse blue 100 100 200 10\n"
			"Rectangle green 10 10 200 10\n"));
	}
BOOST_AUTO_TEST_SUITE_END()