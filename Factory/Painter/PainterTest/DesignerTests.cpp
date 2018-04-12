#include "stdafx.h"
#include "../Designer.h"
#include "../Shape.h"
#include "../PictureDraft.h"
#include "../Triangle.h"
#include "../Rectangle.h"

typedef std::vector<std::string> ShapeDescriptions;

struct SDesignerFixture
{
	SDesignerFixture()
		: factory(CShapeFactory())
		, designer(factory)
	{
	}

	CShapeFactory factory;
	CDesigner designer;
};

BOOST_FIXTURE_TEST_SUITE(Designer, SDesignerFixture)
	BOOST_AUTO_TEST_CASE(returns_empty_draft_when_stream_is_empty)
	{
		std::istringstream stream;
		auto draft = designer.CreateDraft(stream);
		BOOST_CHECK(draft.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(can_create_draft)
	{
		ShapeDescriptions shapeDescriptions = {
			"Trinagle red 10 10 200 10 100 50",
			"Rectangle green 10 10 200 10"
		};

		std::stringstream stream;
		for (auto description : shapeDescriptions)
		{
			stream << description << std::endl;
		}

		auto draft = designer.CreateDraft(stream);
		BOOST_CHECK(!draft.IsEmpty());
	}
BOOST_AUTO_TEST_SUITE_END()