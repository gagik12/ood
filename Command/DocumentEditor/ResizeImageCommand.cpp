#include "stdafx.h"
#include "ResizeImageCommand.h"
#include "IImage.h"

CResizeImageCommand::CResizeImageCommand(std::pair<int, int> const& newSize, size_t index, std::vector<CDocumentItem> & documentItems)
	: m_newSize(newSize)
	, m_index(index)
	, m_documentItems(documentItems)
{
	auto image = m_documentItems.at(m_index).GetImage();
	m_oldSize = std::make_pair(image->GetWidth(), image->GetHeight());
}

void CResizeImageCommand::DoExecute()
{
	auto & image = m_documentItems.at(m_index).GetImage();
	image->Resize(m_newSize.first, m_newSize.second);
}

void CResizeImageCommand::DoUnexecute()
{
	auto & image = m_documentItems.at(m_index).GetImage();
	image->Resize(m_oldSize.first, m_oldSize.second);
}
