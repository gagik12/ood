#include "stdafx.h"
#include "Canvas.h"


CCanvas::CCanvas(std::ostream & outStream)
	: m_outStream(outStream)
{
}
//Triangle red 10 10 400 400 200 500
void CCanvas::SetColor(RGBColor const& color)
{
	m_color = color;
	glColor3f(GLfloat(m_color.r / MAX_RGB_COLOR_VALUE), GLfloat(m_color.g / MAX_RGB_COLOR_VALUE), GLfloat(m_color.b / MAX_RGB_COLOR_VALUE));
}

void CCanvas::DrawLine(CPoint const& from, CPoint const& to)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2f(from.GetX(), from.GetY());
		glVertex2f(to.GetX(), to.GetY());
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

void CCanvas::DrawEllipse(CPoint const& center, float width, float height)
{
	std::cout << "Draw ellipse center [" << center << "], Width: " << width << " height: " << height << std::endl;
}