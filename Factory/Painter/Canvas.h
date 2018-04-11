#pragma once
#include "ICanvas.h"
#include "RGBColor.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream & outStream);

	void SetColor(RGBColor const& color) override;
	void DrawLine(CPoint const& from, CPoint const& to) override;
	void DrawEllipse(CPoint const& leftTop, float width, float height) override;
private:
	std::ostream & m_outStream;
	RGBColor m_color;

	void DrawPoint(CPoint const& point) const;
};

