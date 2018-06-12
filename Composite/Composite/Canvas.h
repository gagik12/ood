#pragma once
#include "ICanvas.h"
#include "RGBColor.h"

class CCanvas : public ICanvas
{
public:
	CCanvas();

	void SetFillColor(RGBColor const& color) override;
	void SetOutlineThickness(GLfloat thickness) override;
	void SetLineColor(RGBColor color) override;

	void DrawEllipse(CPoint const& leftTop, float width, float height) override;
	void DrawTriangle(CPoint const& point1, CPoint const& point2, CPoint const& point3) override;
	void DrawRectangle(CPoint const& leftTop, double width, double height) override;
private:
	void DrawPoint(CPoint const& point) override;
	void DrawLine(CPoint const& from, CPoint const& to) override;
	void FillShape(std::vector<CPoint> const& points) override;
	void DrawOutline(std::vector<CPoint> const& points) override;

	GLfloat m_outlineThickness;
	RGBColor m_lineColor;
	RGBColor m_fillColor;
};

