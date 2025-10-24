#pragma once
#include <vector>
#include "product.hpp"

template<typename Key, typename Value>
class HashTable
{
public:
    HashTable();
    ~HashTable();
    void insert(const std::string& key, const Value& product);
    bool find(const std::string& key) const;
    std::vector<Value> listByCategory(const std::string& category) const;

private:
    struct HashNode
    {
        std::string key;
        Value product;
        HashNode* next;
    };

    std::vector<HashNode*> table;
    size_t hash(const std::string& key) const;
};

template<typename Key, typename Value>
size_t HashTable<Key, Value>::hash(const std::string& key) const
{
    std::hash<std::string> hasher;
    return hasher(key) % table.size();
}
template<typename Key, typename Value>
HashTable<Key, Value>::HashTable() : table(1000, nullptr) {}