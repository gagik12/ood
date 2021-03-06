#include "stdafx.h"
#include "Painter.h"
#include "Shape.h"

void CPainter::DrawPicture(CPictureDraft const& draft, ICanvas& canvas)
{
	for (const auto& shape : draft)
	{
		shape.Draw(canvas);
	}
}
