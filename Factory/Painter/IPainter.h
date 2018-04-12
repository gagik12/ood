#pragma once
#include "ICanvas.h"
#include "PictureDraft.h"

class IPainter
{
public:
	virtual void DrawPicture(CPictureDraft const& draft, ICanvas& canvas) = 0;
};
