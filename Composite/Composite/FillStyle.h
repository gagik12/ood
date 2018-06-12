#pragma once
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:
	CFillStyle(bool enabled, RGBColor color);

	optional<bool> IsEnabled()const;
	void Enable(bool enable);

	optional<RGBColor> GetColor()const;
	void SetColor(RGBColor color);
private:
	bool m_enabled;
	RGBColor m_color;
};

