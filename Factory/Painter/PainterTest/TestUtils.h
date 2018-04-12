#pragma once
#include "../RGBColor.h"
#include "../Point.h"

class CTestUtils
{
public:
	static void CTestUtils::CheckColor(RGBColor const& shapeColor, RGBColor const& expectedColor);
	static void CTestUtils::CheckPoint(CPoint const& shapePoint, CPoint const& expectedPoint);
};

