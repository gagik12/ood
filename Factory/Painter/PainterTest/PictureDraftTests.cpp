#include "stdafx.h"
#include "../PictureDraft.h"
#include "../Shape.h"

struct SPictureDraftFixture
{
	CPictureDraft draft;

};

class CCircle : public CShape
{
public:
	CCircle()
		: CShape({ 255, 0, 0 })
	{
	}

	void Draw(ICanvas& /*canvas*/) const override
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(PictureDraft, SPictureDraftFixture)
	BOOST_AUTO_TEST_CASE(after_initialization_picture_draft_is_empty)
	{
		BOOST_CHECK(draft.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(picture_draft_can_store_shapes)
	{
		std::unique_ptr<CShape> shape1 = std::make_unique<CCircle>();
		std::unique_ptr<CShape> shape2 = std::make_unique<CCircle>();

		draft.AddShape(move(shape1));
		draft.AddShape(move(shape2));

		BOOST_CHECK(!draft.IsEmpty());
	}
BOOST_AUTO_TEST_SUITE_END()