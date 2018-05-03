#include "stdafx.h"
#include "Paragraph.h"

CParagraph::CParagraph(std::string const& text)
	: m_text(text)
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string& text)
{
	m_text = text;
}