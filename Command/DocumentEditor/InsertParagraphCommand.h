#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "Paragraph.h"

class CInsertParagraphCommand : public CAbstractCommand
{
public:
	CInsertParagraphCommand(IParagraphPtr const& paragraph, size_t index, std::vector<CDocumentItem> & documentItems);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	IParagraphPtr m_paragraph;
	size_t m_index;
	std::vector<CDocumentItem> & m_documentItems;
};

