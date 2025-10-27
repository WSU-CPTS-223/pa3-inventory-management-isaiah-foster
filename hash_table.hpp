#pragma once
#include <vector>
#include <list>
#include "product.hpp"

template<typename Key, typename Value>
class HashTable
{
public:
    HashTable();
    ~HashTable() = default;
    void insert(const std::string& key, const Value& product);
    bool find(const std::string& key) const;

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
void HashTable<Key, Value>::insert(const std::string& key, const Value& product)
{
    size_t index = hash(key);
    for (auto& node : table[index])
    {
        if (node.key == key)
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
    std::cout << "Product not found for key: " << key << std::endl;
    return false;
}
