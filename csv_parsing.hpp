#pragma once
#include "hash_table.hpp"
#include <sstream>
#include <fstream>

void parseCSV(HashTable<string,Product> &hashTable) {
    std::ifstream file("products.csv");
    std::string line;
    // Skip the header line
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;

        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 27) {
            continue; // Skip malformed lines
        }
         
//construct Product object
        Product product(
            tokens[0],  // uniqId
            tokens[1], // productName
            tokens[2], // brandName
            tokens[3], // asin
            tokens[4], // category
            tokens[5], // upcEanCode
            std::stoi(tokens[6]), // listPrice
            std::stoi(tokens[7]), // sellingPrice
            std::stoi(tokens[8]), // quantity
            tokens[9], // modelNumber
            tokens[10], // aboutProduct
            tokens[11], // productSpecification
            tokens[12], // technicalDetails
            std::stoi(tokens[13]), // shippingWeight
            tokens[14], // productDimensions
            tokens[15], // image
            tokens[16], // variants
            tokens[17], // sku
            tokens[18], // productUrl
            tokens[19], // stock
            tokens[20], // productDetails
            tokens[21], // dimensions
            tokens[22], // color
            tokens[23], // ingredients
            tokens[24], // directionToUse
            tokens[25] == "true", // isAmazonSeller
            tokens[26], // sizeQuantityVariant
            tokens[27]  // productDescription
        );

        hashTable.insert(product.uniqId, product);
    }
}