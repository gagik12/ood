#include "stdafx.h"
#include "Paragraph.h"
#include "ChangeStringCommand.h"

CParagraph::CParagraph(std::string const& text, IHistory & history)
	: m_text(text)
	, m_history(history)
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string& text)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_text, text));
}