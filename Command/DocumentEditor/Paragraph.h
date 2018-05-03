#pragma once
#include <memory>
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& text);
	std::string GetText()const;
	void SetText(const std::string& text);
private:
	std::string m_text;
};

