#include "stdafx.h"
#include "FileUtils.h"

void CFileUtils::CopyImageInFolder(boost::filesystem::path const& imagePath, std::string const& newImageName)
{
	boost::filesystem::path directory(FOLDER_WITH_IMAGES);

	if (!boost::filesystem::exists(directory))
	{
		boost::filesystem::create_directory(directory);
	}
	boost::filesystem::copy_file(imagePath, FOLDER_WITH_IMAGES + newImageName + imagePath.extension().string());
}

void CFileUtils::CopyFolderWithImage(boost::filesystem::path const& from, boost::filesystem::path const& to)
{
	CFileUtils::ClearFolder(to / from);
	if (!boost::filesystem::exists(to / from))
	{
		boost::filesystem::create_directory(to / from);
	}
	for (auto file : boost::filesystem::directory_iterator(from))
	{
		boost::filesystem::path current(file.path());
		boost::filesystem::copy_file(current, to / current);
	}
}

void CFileUtils::ClearFolder(boost::filesystem::path const& folder)
{
	if (boost::filesystem::exists(folder))
	{
		boost::filesystem::remove_all(folder);
	}
}