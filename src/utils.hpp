#pragma once

#include <string>
#include <vector>

/**
 * @brief Finds the first comparator in a given string.
 *
 * @param str The string to search for the comparator.
 * @return The comparator found in the string, or an empty string if no comparator is found.
 */
std::string find_comparator(const std::string &str);

/**
 * @brief Finds the header from a list of headers in a given string.
 *
 * @param str The string to search for the header.
 * @param headers A vector of header strings to search within.
 * @return The header found in the string, or an empty string if no header is found.
 */
std::string find_header(const std::string &str, const std::vector<std::string> &headers);

/**
 * @brief Finds the value in a given string based on a comparator.
 *
 * @param str The string to search for the value.
 * @param comparator The comparator used to find the value.
 * @return The value found in the string, or an empty string if no value is found.
 */
std::string find_value(const std::string &str, std::string comparator);

/**
 * @brief Prints the values in vecString at the indices specified in vecInt.
 *
 * @param vecInt A vector of indices to print.
 * @param vecString A vector of strings to print values from.
 */
void printVector(std::vector<int> vecInt, std::vector<std::string> vecString);
