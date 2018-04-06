// Painter.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Designer.h"
#include "Painter.h"
#include "Client.h"
#include "Canvas.h"

int main()
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	CPainter painter;

	CClient client(designer, painter);

	client.OrderPictures(std::cin);

    return 0;
}

