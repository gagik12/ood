#include "stdafx.h"
#include "Window.h"
#include "Canvas.h"

CWindow::CWindow(IDrawable & drawableObject)
	: m_drawableObject(drawableObject)
	, m_canvas(std::make_unique<CCanvas>(std::cout))
{
}

void CWindow::OnWindowEvent(const SDL_Event &event)
{
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	SetBackgroundColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	(void)deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	//m_drawableObject.Draw(*m_canvas);
	static const GLfloat LINE_WIDTH = 2;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(LINE_WIDTH);
	glBegin(GL_LINES);
	glVertex2f(100, 222);
	glVertex2f(200, 433);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}

void CWindow::SetupView(const glm::ivec2 & size)
{
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}
