#pragma once
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:
	CFillStyle(bool enabled, RGBAColor color);

	optional<bool> IsEnabled()const;
	void Enable(bool enable);

	optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);
private:
	bool m_enabled;
	RGBAColor m_color;
};

