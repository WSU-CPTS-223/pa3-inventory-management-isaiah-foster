#pragma once
#include <sstream>
#include <fstream>
#include "hash_table.hpp"

std::vector<std::string> parseCSVLine(const std::string &line);

void populate_tables(HashTable<string,Product> &lookupTable, HashTable<string,Product> &categoryTable);