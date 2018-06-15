#include "stdafx.h"
#include "../Composite/GroupShape.h"
#include "../Composite/Ellipse.h"
#include "../Composite/Triangle.h"
#include "../Composite/Rectangle.h"
#include "../Composite/CommonTypes.h"
#include "../Composite/Point.h"

/*struct SGroupShapeFixture
{
	SGroupShapeFixture()
	{
		groupShape.InsertShape(std::make_shared<CTriangle>(CPoint{ 0, 0 }, 10.f, 10.f));
		groupShape.InsertShape(std::make_shared<CEllipse>(CPoint{ 10, 10 }, 15.f, 15.f));
		groupShape.InsertShape(std::make_shared<CRectangle>(CPoint{ 0, 0 }, CPoint{ 1, 1 }, CPoint{ 0, 3 }));
	}

	CGroupShape groupShape;
};

BOOST_FIXTURE_TEST_SUITE(group_shape_fixture, SGroupShapeFixture)
BOOST_AUTO_TEST_SUITE_END()*/