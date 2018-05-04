#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "Paragraph.h"

class CReplaceTextCommand : public CAbstractCommand
{
public:
	CReplaceTextCommand(std::string const& newText, size_t index, std::vector<CDocumentItem> & documentItems);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	size_t m_index;
	std::string m_oldText;
	std::string m_newText;
	std::vector<CDocumentItem> & m_documentItems;
};

