#include "stdafx.h"
#include "InsertImageCommand.h"
#include "FileUtils.h"
#include "StringUtils.h"

CInsertImageCommand::CInsertImageCommand(IImagePtr const& image, size_t index, std::vector<CDocumentItem> & documentItems)
	: m_image(image)
	, m_index(index)
	, m_documentItems(documentItems)
{
}

void CInsertImageCommand::DoExecute()
{
	//C:\Users\vadim\Desktop\img.png
	if (!boost::filesystem::exists(m_imagePath))
	{
		auto originalPath = m_image->GetPath();
		std::string newImageName = CStringUtils::GetRandomString(originalPath.filename().size());
		m_imagePath = FOLDER_WITH_IMAGES + newImageName + originalPath.extension().string();
		CFileUtils::CopyImageInFolder(originalPath, newImageName);
		m_image->SetPath(m_imagePath.string());
	}
	m_documentItems.emplace(m_documentItems.begin() + m_index, CDocumentItem(m_image, nullptr));
}

void CInsertImageCommand::DoUnexecute()
{
	m_documentItems.erase(m_documentItems.begin() + m_index);
}
