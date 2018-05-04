#include "stdafx.h"
#include "StringUtils.h"

void CStringUtils::LeftTrim(std::string & str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

void CStringUtils::EncodeSpecialCharacters(std::string & str)
{
	static const std::map<std::string, std::string> ESCAPE_CODES = {
		{ "<", "&lt;" },
		{ ">", "&gt;" },
		{ "'", "&apos;" },
		{ "&", "&amp;" },
		{ "\"", "&quot;" },
	};

	for (auto escapeCode : ESCAPE_CODES)
	{
		boost::replace_all(str, escapeCode.first, escapeCode.second);
	}
}

std::string CStringUtils::GetRandomString(std::size_t length)
{
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	std::default_random_engine randomEngine(std::time(nullptr));
	std::uniform_int_distribution<std::size_t> distribution(0, alphabet.size() - 1);

	std::string str;
	while (str.size() < length)
	{
		str += alphabet[distribution(randomEngine)];
	}
	return str;
}