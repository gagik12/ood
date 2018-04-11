#pragma once
#include "Point.h"
#include "Float.h"
#include "ColorUtil.h"
#include "RGBColor.h"

class ICanvas
{
public:
	virtual void SetColor(RGBColor const& color) = 0;
	virtual void DrawLine(CPoint const& from, CPoint const& to) = 0;
	virtual void DrawEllipse(CPoint const& leftTop, float width, float height) = 0;
	virtual ~ICanvas() = default;
};