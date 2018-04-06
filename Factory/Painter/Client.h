#pragma once
#include "IDesigner.h"
#include "IPainter.h"
#include "ICanvas.h"

typedef std::unique_ptr<ICanvas> CanvasPtr;

class CClient
{
public:
	CClient(IDesigner & designer, IPainter & painter);
	void OrderPictures(std::istream & cin);

private:
	IDesigner & m_designer;
	IPainter & m_painter;
	CanvasPtr m_canvas;
};

