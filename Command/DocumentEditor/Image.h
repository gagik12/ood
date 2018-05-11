#pragma once
#include "IImage.h"
#include "IHistory.h"

class CImage : public IImage
{
public:
	CImage(boost::filesystem::path const& path, std::pair<int, int> const& size, IHistory & history);
	boost::filesystem::path GetPath() const override;
	void SetPath(std::string const& path) override;
	int GetWidth() const override;
	int GetHeight() const override;
	void Resize(int width, int height) override;
private:
	std::pair<int, int> m_size;
	boost::filesystem::path m_path;
	IHistory & m_history;
};