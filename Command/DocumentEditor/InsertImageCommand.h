#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "IImage.h"

class CInsertImageCommand : public CAbstractCommand
{
public:
	CInsertImageCommand(IImagePtr const& image, size_t index, std::vector<CDocumentItem> & documentItems);
	~CInsertImageCommand();
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	IImagePtr m_image;
	std::string m_imageName;
	size_t m_index;
	std::vector<CDocumentItem> & m_documentItems;
	const std::string DELETION_MARKER = "DEL";
};

