#ifndef LIBCSV_H
#define LIBCSV_H

#include <string>
#include <vector>

extern "C"
{
	/**
	 * @brief Processes a CSV string and applies work columns and row filters.
	 *
	 * @param csv The CSV data as a C-string.
	 * @param workColumns The columns to work with as a C-string.
	 * @param rowFilter The row filter as a C-string.
	 */
	void processCsv(const char *csv, const char *workColumns,
					const char *rowFilter)
		__attribute__((visibility("default")));

	/**
	 * @brief Processes a CSV file and applies work columns and row filters.
	 *
	 * @param csvFilePath The path to the CSV file as a C-string.
	 * @param workColumns The columns to work with as a C-string.
	 * @param rowFilter The row filter as a C-string.
	 */
	void processCsvFile(const char *csvFilePath, const char *workColumns,
						const char *rowFilter)
		__attribute__((visibility("default")));
}

/**
 * @brief Parses a single line of CSV data into individual fields.
 *
 * @param csvLine The CSV line to parse.
 * @return A vector of strings, each representing a field in the CSV line.
 */
std::vector<std::string> parseCsvLine(const std::string &csvLine);

/**
 * @brief Parses the header line of a CSV file.
 *
 * @param csv The CSV data as a string.
 * @return A vector of strings, each representing a header in the CSV file.
 */
std::vector<std::string> parseCsvHeader(const std::string &csv);

/**
 * @brief Maps the work columns to their corresponding indices in the header.
 *
 * @param headers A vector of strings representing the headers.
 * @param workColumns The columns to work with as a string.
 * @return A vector of integers, each representing the index of a work column in the header.
 */
std::vector<int> mapWorkColumns(const std::vector<std::string> &headers,
								const std::string &workColumns);

/**
 * @brief Applies the filters to a row of CSV data.
 *
 * @param headers A vector of strings representing the headers.
 * @param rowData A vector of strings representing the row data.
 * @param rowFilters A vector of strings representing the row filters.
 * @return True if the row satisfies the filters, false otherwise.
 */
bool applyFilters(const std::vector<std::string> &headers,
				  const std::vector<std::string> &rowData,
				  const std::vector<std::string> &rowFilters);

/**
 * @brief Checks if a value satisfies a filter condition.
 *
 * @param comparator The comparator used in the filter (e.g., "=", "<=", ">").
 * @param value The value to check.
 * @param filterValue The filter value to compare against.
 * @return True if the value satisfies the filter condition, false otherwise.
 */
bool checkFilter(const std::string &comparator, const std::string &value,
				 const std::string &filterValue);

#endif // LIBCSV_H
