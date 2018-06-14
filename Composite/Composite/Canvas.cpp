#include "stdafx.h"
#include "Canvas.h"


CCanvas::CCanvas()
{
}

void CCanvas::SetFillColor(RGBColor const& color)
{
	m_fillColor = color;
}

void CCanvas::SetOutlineThickness(GLfloat thickness)
{
	m_outlineThickness = thickness;
}

void CCanvas::SetLineColor(RGBColor color)
{
	m_lineColor = color;
}

void CCanvas::DrawLine(CPoint const& from, CPoint const& to)
{
	glColor3f(GLfloat(m_lineColor.r / MAX_RGB_COLOR_VALUE), GLfloat(m_lineColor.g / MAX_RGB_COLOR_VALUE), GLfloat(m_lineColor.b / MAX_RGB_COLOR_VALUE));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(m_outlineThickness);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_LINES);
		glVertex2f(from.GetX(), from.GetY());
		glVertex2f(to.GetX(), to.GetY());
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

void CCanvas::DrawTriangle(CPoint const& point1, CPoint const& point2, CPoint const& point3)
{
	std::vector<CPoint> points = { point1, point2, point3 };
	DrawOutline(points);
	FillShape(points);
}

void CCanvas::DrawRectangle(CPoint const& leftTop, float width, float height)
{
	CPoint rightTop(leftTop.GetX() + width, leftTop.GetY());
	CPoint rightBottom(leftTop.GetX() + width, leftTop.GetY() + height);
	CPoint leftBottom(leftTop.GetX(), leftTop.GetY() + height);
	std::vector<CPoint> points = { leftTop, rightTop, rightBottom, leftBottom };
	DrawOutline(points);
	FillShape(points);
}

void CCanvas::DrawEllipse(CPoint const& leftTop, float width, float height)
{
	std::vector<CPoint> points;
	for (float angle = 0; angle <= 360; angle += 0.1f)
	{
		CPoint point(leftTop.GetX() + cosf(angle) * width, leftTop.GetY() + sinf(angle) * height);
		points.push_back(point);
	}
	DrawOutline(points);
	FillShape(points);
}

void CCanvas::DrawPoint(CPoint const& point)
{
	glColor3f(m_lineColor.r / MAX_RGB_COLOR_VALUE, m_lineColor.g / MAX_RGB_COLOR_VALUE, m_lineColor.b / MAX_RGB_COLOR_VALUE);
	glPointSize(m_outlineThickness);
	glBegin(GL_POINTS);
		glVertex2f(point.GetX(), point.GetY());
	glEnd();
	glFlush();
}

void CCanvas::FillShape(std::vector<CPoint> const& points)
{
	glColor3f(m_fillColor.r / MAX_RGB_COLOR_VALUE, GLfloat(m_fillColor.g / MAX_RGB_COLOR_VALUE), GLfloat(m_fillColor.b / MAX_RGB_COLOR_VALUE));
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_FAN);
		for (auto const& point : points)
		{
			glVertex2f(point.GetX(), point.GetY());
		}
	glEnd();
}

void CCanvas::DrawOutline(std::vector<CPoint> const& points)
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		DrawLine(points.at(i), points.at((i + 1) % points.size()));
	}
}