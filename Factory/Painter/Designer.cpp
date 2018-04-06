#include "stdafx.h"
#include "PictureDraft.h"
#include "Designer.h"


CDesigner::CDesigner(IShapeFactory& factory)
	: m_factory(factory)
{
}

CPictureDraft CDesigner::CreateDraft(std::istream &data)
{
	CPictureDraft draft;
	std::string line;
	while (std::getline(data, line))
	{
		try
		{
			auto shape = m_factory.CreateShape(std::istringstream(line));
			draft.AddShape(std::move(shape));
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return draft;
}