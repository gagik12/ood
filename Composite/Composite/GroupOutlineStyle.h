#pragma once
#include "IOutlineStyle.h"

typedef std::function<void(std::function<void(std::shared_ptr<IOutlineStyle>&)>)> OutlineStyleEnumerator;

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(OutlineStyleEnumerator & enumerator);
	optional<bool> IsEnabled()const;
	void Enable(bool enable);

	optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);

	optional<float> GetOutlineThikness() const;
	void SetOutlineThikness(float thikness);
private:
	OutlineStyleEnumerator & m_enumerator;
};

