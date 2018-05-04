#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "IImage.h"

class CInsertImageCommand : public CAbstractCommand
{
public:
	CInsertImageCommand(IImagePtr const& image, size_t index, std::vector<CDocumentItem> & documentItems);
protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	IImagePtr m_image;
	boost::filesystem::path m_imagePath;
	size_t m_index;
	std::vector<CDocumentItem> & m_documentItems;
};

