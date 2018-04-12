#include "stdafx.h"
#include "TestUtils.h"

void CTestUtils::CheckColor(RGBColor const& shapeColor, RGBColor const& expectedColor)
{
	BOOST_CHECK(shapeColor.r == expectedColor.r);
	BOOST_CHECK(shapeColor.g == expectedColor.g);
	BOOST_CHECK(shapeColor.b == expectedColor.b);
}

void CTestUtils::CheckPoint(CPoint const& shapePoint, CPoint const& expectedPoint)
{
	BOOST_CHECK(shapePoint.GetX() == expectedPoint.GetX());
	BOOST_CHECK(shapePoint.GetY() == expectedPoint.GetY());
}