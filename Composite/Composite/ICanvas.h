#pragma once
#include "CommonTypes.h"
#include "Point.h"
#include "RGBColor.h"

class ICanvas
{
public:
	virtual void SetFillColor(RGBColor const& color) = 0;
	virtual void SetOutlineThickness(GLfloat thickness) = 0;
	virtual void SetLineColor(RGBColor color) = 0;

	virtual void DrawEllipse(CPoint const& leftTop, float width, float height) = 0;
	virtual void DrawTriangle(CPoint const& point1, CPoint const& point2, CPoint const& point3) = 0;
	virtual void DrawRectangle(CPoint const& leftTop, double width, double height) = 0;
	virtual ~ICanvas() = default;
private:
	virtual void FillShape(std::vector<CPoint> const& points) = 0;
	virtual void DrawOutline(std::vector<CPoint> const& points) = 0;
	virtual void DrawPoint(CPoint const& point) = 0;
	virtual void DrawLine(CPoint const& from, CPoint const& to) = 0;
};


/*class ICanvas
{
public:
	virtual void SetLineColor(RGBColor color) = 0;
	virtual void BeginFill(RGBColor color) = 0;
	virtual void EndFill() = 0;
	virtual void MoveTo(double x, double y) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void DrawEllipse(double left, double top, double width, double height) = 0;
	virtual void SetOutlineThickness(double thickness) = 0;
	virtual void DrawPoint(CPoint const& point) = 0;

	virtual ~ICanvas() = default;
};*/