#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include "product.hpp"

template<typename Key, typename Value>
class HashTable
{
public:
    HashTable();
    ~HashTable() = default;
    void insert(const std::string& key, const Value& product, bool isCategoryKey);
    bool find(const std::string& key) const;
    bool listByCategory(const std::string& category) const;

private:
    struct HashNode
    {
        std::string key;
        Value product;
    };

    std::vector<std::list<HashNode>> table;
    size_t hash(const std::string& key) const;
};

//hash function
template<typename Key, typename Value>
size_t HashTable<Key, Value>::hash(const std::string& key) const
{
    std::hash<std::string> hasher;
    return hasher(key) % table.size();
}

//constructor
template<typename Key, typename Value>
HashTable<Key, Value>::HashTable() : table(1000) {}

//insert function
template<typename Key, typename Value>
void HashTable<Key, Value>::insert(const std::string& key, const Value& product, bool isCategoryKey)
{
    size_t index = hash(key);
    for (auto& node : table[index])
    {
        if (node.key == key && !isCategoryKey)
        {

            node.product = product; // update existing
            return;
        }
    }
    table[index].push_back({key, product}); // add new
}

//find function
template<typename Key, typename Value>
bool HashTable<Key, Value>::find(const std::string& key) const
{
    size_t index = hash(key);
    for (const auto& node : table[index])
    {
        if (node.key == key)
        {
            std::cout << "Product found: " << node.product.productName << std::endl;
            return true;
        }
    }
    std::cout << "Inventory not found" << std::endl;
    return false;
}

//listByCategory function by hashing category. tell user if category found or not
template<typename Key, typename Value>
bool HashTable<Key, Value>::listByCategory(const std::string& category) const
{
    bool found = false;
    std::cout << "Listing products in category: " << category << std::endl;
    size_t index = hash(category);
    int i = 0;
    for (const auto& node : table[index])
    {
        //check that the category argument is in the product's category list
        if (std::find(node.product.categories.begin(), node.product.categories.end(), category) != node.product.categories.end())
        {
            i++;
            std::cout << i << ". "<< node.product.uniqId << " - " << node.product.productName << std::endl;
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "Invalid Category" << std::endl;
    }
    return found;
}