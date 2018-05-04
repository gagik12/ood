#pragma once

const std::string FOLDER_WITH_IMAGES = "images/";

class CFileUtils
{
public:
	static void CopyImageInFolder(boost::filesystem::path const& imagePath, std::string const& newImageName);
	static void CopyFolderWithImage(boost::filesystem::path const& from, boost::filesystem::path const& to);
	static void ClearFolder(boost::filesystem::path const& folder);
};

