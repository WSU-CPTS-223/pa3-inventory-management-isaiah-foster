#include "testing.hpp"
#include "cassert"
#include <sstream>

bool validCommand(string line);
void evalCommand(string line, HashTable<string, Product>& inventory_table, HashTable<string, Product>& category_table);

static Product makeProduct(const string& id, const string& name, const vector<string>& categories)
{
    return Product(id, name, "Brand", "ASIN", categories, "UPC", "$10.00", "$8.00",
                   "10", "Model", "About", "Spec", "Tech", "1 lb", "1x1x1",
                   "image.jpg", "Variant", "SKU", "http://example.com", "In Stock",
                   "Product Details", "Dimensions", "Color", "Ingredients", "Use",
                   true, "Size", "Description");
}


void testall(void)
{
    test_csv_parse();
    test_hash_table();
    test_hash_insert_overwrite();
    test_listByCategory_multiple_hits();
    test_parseCSVLine_quotes();
    test_validCommand_variations();
    test_evalCommand_listInventory_output(); 
}

//test csv parsing and populating hash tables with given data
void test_csv_parse(void)
{
    HashTable<string, Product> lookup_table;
    HashTable<string, Product> category_table;
    populate_tables(lookup_table, category_table);
    assert(lookup_table.find("4c69b61db1fc16e7013b43fc926e502d")==true);
    cout <<"ID Lookup test PASSED"<<endl;
    assert(lookup_table.find("")==false);
    cout <<"Non-existing ID Lookup test PASSED"<<endl;
    assert(category_table.listByCategory("Wall Art")==true);
    cout <<"Category lookup test PASSED"<<endl;
    assert(category_table.listByCategory("NonExistingCategory")==false);
    cout <<"Non-existing Category lookup test PASSED"<<endl;
}

//test hash table using assertions
void test_hash_table(void)
{
    HashTable<string, Product> table;
    Product prod1("id1", "Product1", "BrandA", "ASIN1", {"Category1", "Category2"},
                  "UPC1", "$10.00", "$8.00", "100", "Model1",
                  "About Product 1", "Specs1", "Details1", "1 lb",
                  "10x5x2 in", "image1.jpg", "Variant1", "SKU1",
                  "http://product1.url", "In Stock", "Details about product 1",
                  "10x5x2 in", "Red", "Ingredients1", "Use as directed",
                  true, "Size1", "Description of Product 1");

    table.insert(prod1.uniqId, prod1, false);
    assert(table.find("id1") == true);
    cout << "Find existing product test PASSED" << endl;
    assert(table.find("nonexistent_id") == false);
    cout << "Find non-existing product test PASSED" << endl;

    Product prod2("id2", "Product2", "BrandB", "ASIN2", {"Category3"},
                  "UPC2", "$20.00", "$15.00", "50", "Model2",
                  "About Product 2", "Specs2", "Details2", "2 lb",
                  "15x10x5 in", "image2.jpg", "Variant2", "SKU2",
                  "http://product2.url", "In Stock", "Details about product 2",
                  "15x10x5 in", "Blue", "Ingredients2", "Use as directed",
                  false, "Size2", "Description of Product 2");

    table.insert(prod2.uniqId, prod2, false);
    assert(table.find("id2") == true);
    cout << "Find second existing product test PASSED" << endl;
}

//test that inserting a product with an existing key updates the product
void test_hash_insert_overwrite(void)
{
    HashTable<string, Product> table;

    Product original = makeProduct("duplicate-id", "Original Product", {"CategoryA"});
    Product updated = makeProduct("duplicate-id", "Updated Product", {"CategoryA"});

    table.insert(original.uniqId, original, false);
    table.insert(updated.uniqId, updated, false);

    std::ostringstream buffer;
    std::streambuf* originalBuf = std::cout.rdbuf(buffer.rdbuf());
    assert(table.find("duplicate-id") == true);
    std::cout.rdbuf(originalBuf);

    std::string output = buffer.str();
    assert(output.find("Updated Product") != string::npos);
    assert(output.find("Original Product") == string::npos);
    cout << "Hash insert overwrite test PASSED" << endl;
}

//test listing by category with multiple products in the same category
void test_listByCategory_multiple_hits(void)
{
    HashTable<string, Product> categoryTable;
    Product first = makeProduct("first-id", "First Item", {"SharedCategory"});
    Product second = makeProduct("second-id", "Second Item", {"SharedCategory", "OtherCategory"});

    categoryTable.insert("SharedCategory", first, true);
    categoryTable.insert("SharedCategory", second, true);

    std::ostringstream buffer;
    std::streambuf* originalBuf = std::cout.rdbuf(buffer.rdbuf());
    bool found = categoryTable.listByCategory("SharedCategory");
    std::cout.rdbuf(originalBuf);

    assert(found == true);

    std::string output = buffer.str();
    assert(output.find("First Item") != string::npos);
    assert(output.find("Second Item") != string::npos);
    cout << "List by category multiple hits test PASSED" << endl;
}

//test CSV parsing with quoted fields and escaped quotes
void test_parseCSVLine_quotes(void)
{
    std::string line = "\"alpha\",\"escaped \"\"quote\"\"\",,tail";
    std::vector<std::string> tokens = parseCSVLine(line);
    assert(tokens.size() == 4);
    assert(tokens[0] == "alpha");
    assert(tokens[1] == "escaped \"quote\"");
    assert(tokens[2] == "NA");
    assert(tokens[3] == "tail");
    cout << "CSV parsing with quotes test PASSED" << endl;
}

//test various valid and invalid command formats
void test_validCommand_variations(void)
{
    assert(validCommand(":help"));
    assert(validCommand("find 12345"));
    assert(validCommand("listInventory Home Decor"));
    assert(!validCommand("fi"));
    assert(!validCommand("list"));
    cout << "Valid command variations test PASSED" << endl;
}

//test evalCommand for listInventory output
void test_evalCommand_listInventory_output(void)
{
    HashTable<string, Product> inventoryTable;
    HashTable<string, Product> categoryTable;
    Product first = makeProduct("cat-1", "Catalog Item 1", {"TargetCategory"});
    Product second = makeProduct("cat-2", "Catalog Item 2", {"TargetCategory"});

    categoryTable.insert("TargetCategory", first, true);
    categoryTable.insert("TargetCategory", second, true);

    std::ostringstream buffer;
    std::streambuf* originalBuf = std::cout.rdbuf(buffer.rdbuf());
    evalCommand("listInventory TargetCategory", inventoryTable, categoryTable);
    std::cout.rdbuf(originalBuf);

    std::string output = buffer.str();
    assert(output.find("Listing products in category: TargetCategory") != string::npos);
    assert(output.find("Catalog Item 1") != string::npos);
    assert(output.find("Catalog Item 2") != string::npos);
    cout << "ListInventory command test PASSED" << endl;
}
