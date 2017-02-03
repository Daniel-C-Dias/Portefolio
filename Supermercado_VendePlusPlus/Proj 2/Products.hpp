//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#ifndef PRODUCTS_HPP
#define PRODUCTS_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//====================================================================================================
// ========== Objects and Functions Declarations ==========
//====================================================================================================

class Products
{
private:
	std::string name;
	double price;
public:
	Products();
	Products(const std::string &name, const double &price);
	Products(std::stringstream &stream);

	std::string GetName() const;
	double GetPrice() const;
};

void CreateProductsFile(std::fstream &products_file, const std::string &products_file_name);

bool CheckProductsFile(std::fstream &products_file);

bool CheckProductsData(std::fstream &products_file, std::string &products_file_com, std::vector<Products> &products_data);

bool ReadProductsData(std::fstream &products_file, std::vector<Products> &products_data);

void WriteProductsData(std::fstream &products_file, const std::string &products_file_com, const std::string &products_file_name, std::vector<Products> &products_data);

#endif

//====================================================================================================
// ========== End of File ==========
//====================================================================================================