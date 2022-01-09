#include <string>
#include <list>
#include <map>
#include <iostream>

/*
 * Author: Jared Dyreson
*/

// NOTE: Forward declare this so the compliler doesn't freak out

class ProductCatalog;
class ProductDescription;
class Register;
class Sale;
class SalesLineItem;

/*
 * Class Headers "implementation"
*/

class ProductDescription {
  private:
    std::string description; // Text
    float price; // Money
    int itemID; // ItemID
    // I was previously scolded for using define statements instead of constexpr
    // However I was just abusing the preprocessor to fill in types, where constexpr just seems to only be used for constant integers which was not the case for me
    // I know it's very bad, I just wanted to keep true to the diagram
};

class ProductCatalog {
  public:
    ProductDescription productDesc(int);
  private:
    // below int is supposed to be ItemID, please see ProductDescription class definition for more information
    std::map<int, ProductDescription> catalog; // get(id) function is an expected interface, make wrapper around std::map<int, ProductDescription> ?

};

class SalesLineItem {
  public:
    SalesLineItem(const ProductDescription&, int);
  private:
    int quantity;
};

class Sale {
  public:
    void makeLineItem(const ProductDescription&, int);
  private:
    bool isComplete;
    std::string _time; /* time is a C++ keyword */
    std::list<SalesLineItem> lineItems;
};

class Register {
  public:
    void enterItem(int, int);
  private:
    ProductCatalog catalog;
    Sale currentSale;
};

void Sale::makeLineItem(const ProductDescription& description, int quantity) {
  this->lineItems.emplace_back(SalesLineItem(description, quantity));
}

int main() {
  Register reg = Register();
  Sale s = Sale();
  ProductDescription desc = ProductDescription();
  s.makeLineItem(desc, 100);
  return 0;
}
