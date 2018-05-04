#pragma once
class CStringUtils
{
public:
	static void LeftTrim(std::string & str);
	static void EncodeSpecialCharacters(std::string & str);
	static std::string GetRandomString(std::size_t length);
};

