#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream & outStream);

	void SetColor(Color color) override;
	void DrawLine(CPoint const& from, CPoint const& to) override;
	void DrawEllipse(CPoint const& center, float width, float height) override;
private:
	std::ostream & m_outStream;
	Color m_color;
};

