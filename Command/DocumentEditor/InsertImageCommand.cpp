#include "stdafx.h"
#include "InsertImageCommand.h"
#include "FileUtils.h"
#include "StringUtils.h"

CInsertImageCommand::CInsertImageCommand(IImagePtr const& image, size_t index, std::vector<CDocumentItem> & documentItems)
	: m_image(image)
	, m_index(index)
	, m_documentItems(documentItems)
	, m_originalImagePath(image->GetPath())
{
}

void CInsertImageCommand::DoExecute()
{
	//C:\Users\vadim\Desktop\img.png
	if (m_imageName.empty())
	{
		m_imageName = CStringUtils::GetRandomString(m_originalImagePath.filename().size());
	}

	if (boost::filesystem::exists(m_originalImagePath))
	{
		std::string imagePath = FOLDER_WITH_IMAGES + m_imageName + m_originalImagePath.extension().string();
		CFileUtils::CopyImageInFolder(m_originalImagePath, m_imageName);
		m_image->SetPath(imagePath);
	}
	m_documentItems.emplace(m_documentItems.begin() + m_index, CDocumentItem(m_image, nullptr));
}

void CInsertImageCommand::DoUnexecute()
{
	m_documentItems.erase(m_documentItems.begin() + m_index);
	boost::filesystem::remove(FOLDER_WITH_IMAGES + m_imageName + m_originalImagePath.extension().string());
}
