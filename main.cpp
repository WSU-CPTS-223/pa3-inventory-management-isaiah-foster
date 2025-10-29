#include "testing.hpp"

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, HashTable<string, Product>& inventory_table, HashTable<string, Product>& category_table)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
        line = line.substr(line.find(" ") + 1);
        cout << inventory_table.find(line) << endl;
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        string category = line.substr(line.find(" ") + 1);
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        category_table.listByCategory(category);
    }
}

vector<HashTable<string, Product>*> bootStrap(void)
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
 
    HashTable<string, Product>* inventory_table = new HashTable<string, Product>;
    HashTable<string, Product>* category_table = new HashTable<string, Product>;
    populate_tables(*inventory_table, *category_table);

    return {inventory_table, category_table};
}

int main(int argc, char const *argv[])
{
    testall();
    string line;
    auto inventorys = bootStrap();
    auto inventory_table = inventorys[0];
    auto category_table = inventorys[1];
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line, *inventory_table, *category_table);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
