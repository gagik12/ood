#pragma once
#include "IOutlineStyle.h"

class COutlineStyle : public IOutlineStyle
{
public:
	COutlineStyle(bool enabled, RGBAColor color, float thickness);

	optional<bool> IsEnabled()const;
	void Enable(bool enable);

	optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);

	float GetOutlineThikness() const;
	void SetOutlineThikness(float thikness);
private:
	bool m_enabled;
	RGBAColor m_color;
	float m_thickness;
};

