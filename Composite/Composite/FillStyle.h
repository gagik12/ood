#pragma once
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:
	CFillStyle(bool enabled, RGBColor color);

	optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	optional<RGBColor> GetColor()const override;
	void SetColor(RGBColor color) override;
private:
	bool m_enabled;
	RGBColor m_color;
};

