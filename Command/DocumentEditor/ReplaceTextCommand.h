#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "Paragraph.h"

class CReplaceTextCommand : public CAbstractCommand
{
public:
	CReplaceTextCommand(std::string const& newText, IParagraphPtr & paragraph);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	std::string m_oldText;
	std::string m_newText;
	IParagraphPtr & m_paragraph;
};

