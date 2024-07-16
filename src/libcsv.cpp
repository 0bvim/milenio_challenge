#include "libcsv.hpp"
#include "utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

void processCsv(const char *csv, const char *workColumns, const char *rowFilter)
{
	std::istringstream csvStream(csv);
	std::string csvLine;
	std::getline(csvStream, csvLine);
	std::vector<std::string> headers = parseCsvHeader(csvLine);
	std::vector<int> selectedCols = mapWorkColumns(headers, workColumns);
	std::istringstream filterStream(rowFilter);
	std::vector<std::string> rowFilters;
	std::string filterLine;
	while (std::getline(filterStream, filterLine))
	{
		if (!filterLine.empty())
			rowFilters.push_back(filterLine);
	}
	printVector(selectedCols, headers);
	while (std::getline(csvStream, csvLine))
	{
		std::vector<std::string> rowData = parseCsvLine(csvLine);
		if (applyFilters(headers, rowData, rowFilters))
			printVector(selectedCols, rowData);
	}
}

void processCsvFile(const char *csvFilePath, const char *workColumns,
					const char *rowFilter)
{
	std::ifstream file(csvFilePath);
	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << csvFilePath << std::endl;
		return;
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	std::string content = buffer.str();
	processCsv(content.c_str(), workColumns, rowFilter);
}

std::vector<std::string> parseCsvLine(const std::string &csvLine)
{
	std::vector<std::string> tokens;
	std::istringstream ss(csvLine);
	std::string token;
	while (std::getline(ss, token, ','))
		tokens.push_back(token);
	return tokens;
}

std::vector<std::string> parseCsvHeader(const std::string &csv)
{
	return parseCsvLine(csv); // Assumes header is the first line of CSV
}

std::vector<int> mapWorkColumns(const std::vector<std::string> &headers,
								const std::string &workColumns)
{
	std::vector<int> selectedCols;
	// if parameter is empty, set all headers up
	if (workColumns.empty())
		for (size_t i = 0; i < headers.size(); ++i)
			selectedCols.push_back(i);
	else
	{
		std::istringstream ss(workColumns);
		std::string columnName;
		while (std::getline(ss, columnName, ','))
		{
			auto it = std::find(headers.begin(), headers.end(), columnName);
			if (it != headers.end())
				selectedCols.push_back(std::distance(headers.begin(), it));
		}
	}
	return selectedCols;
}

bool applyFilters(const std::vector<std::string> &headers,
				  const std::vector<std::string> &rowData,
				  const std::vector<std::string> &rowFilters)
{
	for (const auto &filter : rowFilters)
	{
		std::string headerName, comparator, valueStr;
		comparator = find_comparator(filter);
		headerName = find_header(filter, headers);
		valueStr = find_value(filter, comparator);

		size_t headerIdx = std::distance(
			headers.begin(), std::find(headers.begin(), headers.end(), headerName));
		if (headerIdx >= headers.size())
		{
			std::cerr << "Header '" << headerName << "' not found in CSV string"
					  << std::endl;
			return false;
		}
		std::string cellValue = rowData[headerIdx];
		if (!checkFilter(comparator, cellValue, valueStr))
			return false;
	}
	return true;
}

bool checkFilter(const std::string &comparator,
				 const std::string &value,
				 const std::string &filterValue)
{
	if (comparator == "=")
		return value == filterValue;
	if (comparator == ">")
		return value > filterValue;
	if (comparator == "<")
		return value < filterValue;
	if (comparator == "!=")
		return value != filterValue;
	if (comparator == ">=")
		return value >= filterValue;
	if (comparator == "<=")
		return value <= filterValue;
	std::cerr << "Invalid filter: '" << comparator << "'" << std::endl;
	return false;
}
