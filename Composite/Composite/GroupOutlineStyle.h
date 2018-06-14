#pragma once
#include "IOutlineStyle.h"

typedef std::function<void(std::function<void(IOutlineStyle&)>)> OutlineStyleEnumerator;

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(OutlineStyleEnumerator & enumerator);
	optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	optional<RGBColor> GetColor()const override;
	void SetColor(RGBColor color) override;

	optional<float> GetOutlineThikness() const override;
	void SetOutlineThikness(float thikness) override;
private:
	OutlineStyleEnumerator & m_enumerator;
};

