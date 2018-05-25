#pragma once
#include "ICanvas.h"
class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream & ostream);

	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double left, double top, double width, double height) override;
	void SetOutlineThickness(double thickness) override;
private:
	std::ostream & m_ostream;
};

