#pragma once
#include <memory>
#include "IParagraph.h"
#include "IHistory.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& text, IHistory & history);
	std::string GetText()const;
	void SetText(const std::string& text);
private:
	std::string m_text;
	IHistory & m_history;
};

