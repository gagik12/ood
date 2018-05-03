#include "stdafx.h"
#include "InsertParagraphCommand.h"

CInsertParagraphCommand::CInsertParagraphCommand(IParagraphPtr const& paragraph, size_t index, std::vector<CDocumentItem> & documentItems)
	: m_paragraph(paragraph)
	, m_index(index)
	, m_documentItems(documentItems)
{
}

void CInsertParagraphCommand::DoExecute()
{
	m_documentItems.emplace(m_documentItems.begin() + m_index, CDocumentItem(nullptr, m_paragraph));
}

void CInsertParagraphCommand::DoUnexecute()
{
	m_documentItems.erase(m_documentItems.begin() + m_index);
}
