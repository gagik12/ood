#pragma once

#include <boost/optional.hpp>
#include "CommonTypes.h"
using boost::optional;

class IStyle
{
public:
	virtual optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual optional<RGBColor> GetColor()const = 0;
	virtual void SetColor(RGBColor color) = 0;

	virtual ~IStyle() = default;
};