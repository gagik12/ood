#pragma once
#include "Point.h"
#include "Float.h"
#include "ColorUtil.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(CPoint const& from, CPoint const& to) = 0;
	virtual void DrawEllipse(CPoint const& center, float width, float height) = 0;
	virtual ~ICanvas() = default;
};