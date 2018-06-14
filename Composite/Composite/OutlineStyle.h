#pragma once
#include "IOutlineStyle.h"

class COutlineStyle : public IOutlineStyle
{
public:
	COutlineStyle(bool enabled, RGBColor color, float thickness);

	optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	optional<RGBColor> GetColor()const override;
	void SetColor(RGBColor color) override;

	optional<float> GetOutlineThikness() const override;
	void SetOutlineThikness(float thikness) override;
private:
	bool m_enabled;
	RGBColor m_color;
	float m_thickness;
};

