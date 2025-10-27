#include "testing.hpp"


void test_csv_parse(void)
{
    HashTable<string, Product> test_table;
    parseCSV(test_table);
    test_table.find("4c69b61db1fc16e7013b43fc926e502d");
}