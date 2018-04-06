#include "stdafx.h"
#include "Client.h"
#include "PictureDraft.h"
#include "Canvas.h"

CClient::CClient(IDesigner & designer, IPainter & painter)
	: m_designer(designer)
	, m_painter(painter)
	, m_canvas(std::make_unique<CCanvas>(std::cout))
{
}

void CClient::OrderPictures(std::istream & cin)
{
	CPictureDraft pictureDraft = m_designer.CreateDraft(std::cin);
	m_painter.DrawPicture(pictureDraft, *m_canvas);
}