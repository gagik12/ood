#pragma once

class CStreamParsingError : public std::invalid_argument
{
public:
	CStreamParsingError(std::string const& message);
};

