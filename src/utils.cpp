#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

std::string find_comparator(const std::string &str)
{
	std::string nonAlphaChars;
	std::vector<std::string> comparators{"!=", "<=", ">=", ">", "<", "="};
	for (const std::string &comp : comparators)
	{
		size_t pos = str.find(comp);
		if (pos != std::string::npos)
			return (comp);
	}
	std::copy_if(str.begin(), str.end(), std::back_inserter(nonAlphaChars), [](char c)
				 { return !std::isalpha(c); });
	return nonAlphaChars;
}

std::string find_header(const std::string &str, const std::vector<std::string> &headers)
{
	for (const std::string &header : headers)
	{
		size_t pos = str.find(header);
		if (pos != std::string::npos)
			return (header);
	}
	return "";
}

std::string find_value(const std::string &str, std::string comparator)
{
	size_t pos = str.find(comparator);
	if (pos != std::string::npos)
	{
		std::string result = str.substr(pos + comparator.size());
		return result;
	}
	return "";
}

void printVector(std::vector<int> vecInt, std::vector<std::string> vecString)
{
	for (size_t i = 0; i < vecInt.size(); ++i)
	{
		int colIdx = vecInt[i];
		std::cout << vecString[colIdx];
		if (i < vecInt.size() - 1)
			std::cout << ",";
	}
	std::cout << std::endl;
}
