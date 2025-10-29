#include "csv_parsing.hpp"

std::vector<std::string> parseCSVLine(const std::string &line) {
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"') {
            //signal that current position in string stream is inside quotes. add quote to the token if the next char is a quote and skip
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                token += '"';
                ++i; // skip the next quote
            } else {
                inQuotes = !inQuotes;
            }
            //delimit if a comma is found and we are not inside quotes
        } else if (c == ',' && !inQuotes) {
            //put NA if quote is empty
            if (token.empty()) token = "NA";
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }

    //push the final token to the vector
    if (token.empty()) token = "NA";
    tokens.push_back(token);

    return tokens;
}

void populate_tables(HashTable<std::string, Product> &lookupTable, HashTable<std::string, Product> &categoryTable) {
    std::ifstream file("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open CSV file.\n";
        return;
    }

    std::string line;
    //skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = parseCSVLine(line);

        if (tokens.size() != 28) {
            //skip bad lines from csv
            continue;
        }

        //parse each category list (delimit with '|' and remove spaces for proper lookups by user)
        std::vector<std::string> categories;
        std::istringstream catStream(tokens[4]);
        std::string category;
        while (std::getline(catStream, category, '|')) {
            // Remove leading and trailing whitespace
            category.erase(0, category.find_first_not_of(" \t"));
            category.erase(category.find_last_not_of(" \t") + 1);
            categories.push_back(category);
        }

        Product product(
            tokens[0],   // uniqId
            tokens[1],   // productName
            tokens[2],   // brandName
            tokens[3],   // asin
            categories,  // category
            tokens[5],   // upcEanCode
            tokens[6],   // listPrice
            tokens[7],   // sellingPrice
            tokens[8],   // quantity
            tokens[9],   // modelNumber
            tokens[10],  // aboutProduct
            tokens[11],  // productSpecification
            tokens[12],  // technicalDetails
            tokens[13],  // shippingWeight
            tokens[14],  // productDimensions
            tokens[15],  // image
            tokens[16],  // variants
            tokens[17],  // sku
            tokens[18],  // productUrl
            tokens[19],  // stock
            tokens[20],  // productDetails
            tokens[21],  // dimensions
            tokens[22],  // color
            tokens[23],  // ingredients
            tokens[24],  // directionToUse
            tokens[25] == "Y", // isAmazonSeller
            tokens[26],  // sizeQuantityVariant
            tokens[27]   // productDescription
        );

        //populate the hash table for lookups by uniqId
        lookupTable.insert(product.uniqId, product, false);

        //populate the hash table for lookups by category
        for(auto& cat : categories) {
            if(cat!= "NA") //skip NA categories
                categoryTable.insert(cat, product, true);
        }
    }
    file.close();
}