#pragma once
#include "ICanvas.h"
#include "PictureDraft.h"

class IPainter
{
public:
	virtual void DrawPicture(CPictureDraft& draft, ICanvas& canvas) = 0;
};
