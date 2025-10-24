#pragma once
#include "csv_parsing.hpp"


void test_csv_parse(void)
{
    HashTable<string, Product> test_table;
    parseCSV(test_table);
    test_table.find("875a5a1374880f0c30bce7429ff4e411");
}