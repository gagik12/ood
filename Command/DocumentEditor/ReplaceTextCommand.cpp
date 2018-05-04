#include "stdafx.h"
#include "ReplaceTextCommand.h"


CReplaceTextCommand::CReplaceTextCommand(std::string const& newText, size_t index, std::vector<CDocumentItem> & documentItems)
	: m_index(index)
	, m_newText(newText)
	, m_documentItems(documentItems)
	, m_oldText(documentItems.at(index).GetParagraph()->GetText())
{
}

void CReplaceTextCommand::DoExecute()
{
	auto & paragraph = m_documentItems.at(m_index).GetParagraph();
	paragraph->SetText(m_newText);
	//m_paragraph->SetText(m_newText);
}

void CReplaceTextCommand::DoUnexecute()
{
	auto & paragraph = m_documentItems.at(m_index).GetParagraph();
	paragraph->SetText(m_oldText);
}
