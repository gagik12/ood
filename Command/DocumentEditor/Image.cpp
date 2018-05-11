#include "stdafx.h"
#include "Image.h"
#include "ResizeImageCommand.h"

CImage::CImage(boost::filesystem::path const& path, std::pair<int, int> const& size, IHistory & history)
	: m_path(path)
	, m_size(size)
	, m_history(history)
{
}

boost::filesystem::path CImage::GetPath() const
{
	return m_path;
}

void CImage::SetPath(std::string const& path)
{
	m_path = path;
}

int CImage::GetWidth() const
{
	return m_size.first;
}

int CImage::GetHeight() const
{
	return m_size.second;
}

void CImage::Resize(int width, int height)
{
	m_history.AddAndExecuteCommand(std::make_unique<CResizeImageCommand>(m_size, std::make_pair(width, height)));
}