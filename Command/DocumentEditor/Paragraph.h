#pragma once
#include <memory>
#include "IParagraph.h"
#include "History.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& text, CHistory & history);
	std::string GetText()const;
	void SetText(const std::string& text);
private:
	std::string m_text;
	CHistory & m_history;
};

