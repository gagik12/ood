#include "stdafx.h"
#include "ReplaceTextCommand.h"


CReplaceTextCommand::CReplaceTextCommand(std::string const& newText, IParagraphPtr & paragraph)
	: m_paragraph(paragraph)
	, m_newText(newText)
	, m_oldText(paragraph->GetText())
{
}

void CReplaceTextCommand::DoExecute()
{
	m_paragraph->SetText(m_newText);
}

void CReplaceTextCommand::DoUnexecute()
{
	m_paragraph->SetText(m_oldText);
}
