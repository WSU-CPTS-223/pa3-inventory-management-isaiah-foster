//Uniq Id,Product Name,Brand Name,Asin,Category,Upc Ean Code,List Price,Selling Price,Quantity,Model Number,About Product,Product Specification,Technical Details,Shipping Weight,Product Dimensions,Image,Variants,Sku,Product Url,Stock,Product Details,Dimensions,Color,Ingredients,Direction To Use,Is Amazon Seller,Size Quantity Variant,Product Description
#include <iostream>
#include <string>
using namespace std;

class Product{
public:
    string uniqId;
    string productName;
    string brandName;
    string asin;
    vector<string> categories;
    string upcEanCode;
    string listPrice;
    string sellingPrice;
    string quantity;
    string modelNumber;
    string aboutProduct;
    string productSpecification;
    string technicalDetails;
    string shippingWeight;
    string productDimensions;
    string image;
    string variants;
    string sku;
    string productUrl;
    string stock;
    string productDetails;
    string dimensions;
    string color;
    string ingredients;
    string directionToUse;
    bool isAmazonSeller;
    string sizeQuantityVariant;
    string productDescription;

    Product() {}

    Product(const string& uid, const string& pname, const string& bname, const string& a, const vector<string>& cats,
            const string& upc, string lprice, string sprice, string qty, const string& mnumber,
            const string& about, const string& pspec, const string& tdetails, string sweight,
            const string& pdim, const string& img, const string& var, const string& sk,
            const string& purl, const string& stk, const string& pdetails, const string& dim,
            const string& col, const string& ingred, const string& dtu, bool isAmazon,
            const string& sqv, const string& pdesc)
        : uniqId(uid), productName(pname), brandName(bname), asin(a), categories(cats),
          upcEanCode(upc), listPrice(lprice), sellingPrice(sprice), quantity(qty),
          modelNumber(mnumber), aboutProduct(about), productSpecification(pspec),
          technicalDetails(tdetails), shippingWeight(sweight), productDimensions(pdim),
          image(img), variants(var), sku(sk), productUrl(purl), stock(stk),
          productDetails(pdetails), dimensions(dim), color(col), ingredients(ingred),
          directionToUse(dtu), isAmazonSeller(isAmazon), sizeQuantityVariant(sqv),
          productDescription(pdesc) {}
};