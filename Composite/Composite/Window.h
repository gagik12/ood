#pragma once
#include "AbstractWindow.h"
#include "ICanvas.h"
#include "IDrawable.h"

typedef std::unique_ptr<ICanvas> CanvasPtr;

class CWindow : public CAbstractWindow
{
public:
    CWindow(IDrawable & drawableObject);

protected:
    void OnWindowEvent(const SDL_Event &event) override;
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 & size) override;

private:
    void SetupView(const glm::ivec2 & size);
	CanvasPtr m_canvas;
	IDrawable & m_drawableObject;
};