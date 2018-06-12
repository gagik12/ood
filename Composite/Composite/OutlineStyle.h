#pragma once
#include "IOutlineStyle.h"

class COutlineStyle : public IOutlineStyle
{
public:
	COutlineStyle(bool enabled, RGBColor color, float thickness);

	optional<bool> IsEnabled()const;
	void Enable(bool enable);

	optional<RGBColor> GetColor()const;
	void SetColor(RGBColor color);

	optional<float> GetOutlineThikness() const;
	void SetOutlineThikness(float thikness);
private:
	bool m_enabled;
	RGBColor m_color;
	float m_thickness;
};

