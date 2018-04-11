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
	static const GLfloat LINE_WIDTH = 2;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(LINE_WIDTH);
	glBegin(GL_LINES);
		glVertex2f(from.GetX(), from.GetY());
		glVertex2f(to.GetX(), to.GetY());
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

//http://www.opennet.ru/docs/RUS/qt3_prog/images/fig8.1.png
void CCanvas::DrawEllipse(CPoint const& leftTop, float width, float height)
{
	for (float angle = 0; angle <= 360; angle += 0.1f)
	{
		CPoint point(leftTop.GetX() + cosf(angle) * width, leftTop.GetY() + sinf(angle) * height);
		DrawPoint(point);
	}
}

void CCanvas::DrawPoint(CPoint const& point) const
{
	static const GLfloat POINT_SIZE = 2;

	glPointSize(POINT_SIZE);
	glBegin(GL_POINTS);
		glVertex2f(point.GetX(), point.GetY());
	glEnd();
	glFlush();
}