#include "stdafx.h"
#include "DeleteItemCommand.h"


CDeleteItemCommand::CDeleteItemCommand(size_t index, std::vector<CDocumentItem> & documentItems)
	: m_index(index)
	, m_documentItems(documentItems)
	, m_documentItem(documentItems.at(m_index))
{
}

void CDeleteItemCommand::DoExecute()
{
	m_documentItems.erase(m_documentItems.begin() + m_index);
}

void CDeleteItemCommand::DoUnexecute()
{
	m_documentItems.emplace(m_documentItems.begin() + m_index, m_documentItem);
}
