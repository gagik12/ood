#pragma once
#include "AbstractWindow.h"
#include "ICanvas.h"
#include "IPainter.h"

typedef std::unique_ptr<ICanvas> CanvasPtr;

class CWindow : public CAbstractWindow
{
public:
    CWindow(IPainter & painter, CPictureDraft & pictureDraft);

protected:
    void OnWindowEvent(const SDL_Event &event) override;
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 & size) override;

private:
    void SetupView(const glm::ivec2 & size);
	CanvasPtr m_canvas;
	IPainter & m_painter;
	CPictureDraft & m_pictureDraft;
};