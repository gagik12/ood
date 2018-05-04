#include "stdafx.h"
#include "Image.h"

CImage::CImage(boost::filesystem::path const& path, int width, int height)
	: m_path(path)
	, m_width(width)
	, m_height(height)
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
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}