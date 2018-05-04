#pragma once
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(boost::filesystem::path const& path, int width, int height);
	boost::filesystem::path GetPath() const override;
	void SetPath(std::string const& path) override;
	int GetWidth() const override;
	int GetHeight() const override;
	void Resize(int width, int height) override;
private:
	int m_width;
	int m_height;
	boost::filesystem::path m_path;
};