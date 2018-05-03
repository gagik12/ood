#include "stdafx.h"
#include "StreamParsingError.h"

CStreamParsingError::CStreamParsingError(std::string const& message)
	: std::invalid_argument(message)
{
}