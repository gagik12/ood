#include "stdafx.h"
#include "Window.h"
#include "Canvas.h"

CWindow::CWindow(IPainter & painter, CPictureDraft & pictureDraft)
	: m_painter(painter)
	, m_pictureDraft(pictureDraft)
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
	m_painter.DrawPicture(m_pictureDraft, *m_canvas);
    //m_canvas.DrawShapes(shapes);
}

void CWindow::SetupView(const glm::ivec2 & size)
{
    const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
