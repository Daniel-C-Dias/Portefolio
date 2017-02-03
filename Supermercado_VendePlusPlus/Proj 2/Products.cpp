//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Products.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

// Default constructor, since it's never used, it only returns invalid values for each parameter
Products::Products()
{
	name = "\0";
	price = -1;
}

// Interface-oriented constructor, takes specific parameters and creates a product
Products::Products(const std::string &name, const double &price)
{
	this->name = name;
	this->price = price;
}

// Implementation-oriented constructor, receives a line from the file contained in a stringstream, and extracts the information; assumes it's in the correct format (if not, may return invalid data)
Products::Products(std::stringstream &stream)
{
	try
	{
		getline(stream, name, ';');
		name.pop_back();

		stream >> price;

		if (stream.bad())
			throw std::exception();
	}
	catch (...)
	{
		name = "\0";
		price = -1;
	}
}

// Access to product's name
std::string Products::GetName() const
{
	return name;
}

// Access to product's price
double Products::GetPrice() const
{
	return price;
}

// Creates a products file, pre-formatted
void CreateProductsFile(std::fstream &products_file, const std::string &products_file_name)
{
	products_file.open(products_file_name.c_str(), std::ios::out | std::ios::trunc);
	products_file.close();
	products_file.open(products_file_name.c_str(), std::ios::in | std::ios::out);

	products_file << ": Ficheiro de produtos" << std::endl << std::endl;
	products_file << ": A LINHA ABAIXO NÃO DEVE SER ALTERADA OU APAGADA" << std::endl;
	products_file << ". p" << std::endl << std::endl;
	products_file << ": Linhas de comentários são indicadas por um \":\" no início da linha" << std::endl;
	products_file << ": Linhas de controlo são indicadas por um \".\" no início da linha" << std::endl << std::endl;
	products_file << ": Todas as linhas de comentários e de controlo acima da linha # serão preservadas pelo programa" << std::endl;
	products_file << ": Todas as linhas de comentários e de controlo abaixo da linha # serão APAGADAS pelo programa" << std::endl << std::endl;
	products_file << ": Exemplo de uma linha de informação: pão ; 0.99" << std::endl << std::endl;
	products_file << ": AS LINHAS ABAIXO NÃO DEVEM SER ALTERADAS OU APAGADAS" << std::endl;
	products_file << "# 0" << std::endl << std::endl;

	products_file.seekp(0, std::ios::beg);
	products_file.clear();
}

// Checks a file to see if it's a products file (contains products information)
bool CheckProductsFile(std::fstream &products_file)
{
	for (products_file.peek(); !products_file.eof(); products_file.peek())
	{
		std::string stream;
		getline(products_file, stream, '\n');

		if (stream.size() > 0 && stream.front() == '.') // It does so by first searching for "control lines" (preceded by a dot)
		{
			if (stream.size() > 2 && stream.at(2) == 'p') // Then checks to see if it contains a character specific to products files (p)
			{
				products_file.seekg(0, std::ios::beg);
				products_file.clear();

				return true;
			}
		}
	}
	return false; // Otherwise it is not a products file
}

// Checks a products file to see if it contains valid data (this assumes that the function above was used first to determine if the file was valid)
bool CheckProductsData(std::fstream &products_file, std::string &products_file_com, std::vector<Products> &products_data)
{
	for (products_file.peek(); !products_file.eof(); products_file.peek())
	{
		std::string stream;
		getline(products_file, stream, '\n');

		if (stream.size() == 0) // Ignores empty lines, saving them in a string
		{
			products_file_com += '\n'; 
		}
		else if (stream.front() == ':' || stream.front() == '.') // Ignores "comment lines" and "control lines", saving them in a string
		{
			products_file_com += stream + '\n';
		}
		else if (stream.front() == '#') // Detects number line
		{
			try
			{
				if (std::to_string(std::stoi(stream.substr(2, std::string::npos))).size() < stream.substr(2, std::string::npos).size()) // Checks if it is a single integer (that represents the number of products)
					throw std::exception();
			}
			catch (...)
			{
				return false; // Assumes the data is corrupted otherwise
			}

			products_data.resize(std::stoi(stream.substr(2, std::string::npos))); // If it is a integer, changes the size of the products vector to match that integer, since the read function works with iterators

			products_file.seekg(0, std::ios::beg);
			products_file.clear();

			return true;
		}
	}
	return false;
}

// Reads products' data from the file and inserts it in the products vector
bool ReadProductsData(std::fstream &products_file, std::vector<Products> &products_data)
{
	for (std::vector<Products>::iterator it = products_data.begin(); it != products_data.end();)
	{
		std::string stream;
		getline(products_file, stream, '\n');

		if (stream.size() > 0 && stream.front() != ':' && stream.front() != '.' && stream.front() != '#')
		{
			std::stringstream sstream(stream);
			Products Product = Products(sstream);
			if (Product.GetName() == "\0") // Fails if information retrieved from the constructor is invalid
			{
				return false;
			}
			*it = Product;
			++it;
		}
	}

	products_file.seekg(0, std::ios::beg);
	products_file.clear();

	return true;
}

// Writes products' data from vector to file
void WriteProductsData(std::fstream &products_file, const std::string &products_file_com, const std::string &products_file_name, std::vector<Products> &products_data)
{
	products_file.open("products.temp.txt", std::ios::out | std::ios::trunc); // Starts by creating a new file, for safety

	products_file << std::fixed << std::showpoint;
	products_file.precision(2);

	products_file << products_file_com; // Writes the "comment lines" and the "control lines" to the file

	products_file << "# " << products_data.size() << std::endl; // Writes the current number of products

	for (std::vector<Products>::iterator it = products_data.begin(); it != products_data.end(); ++it) // Writes the products' data
	{
		Products Product = *it;
		products_file << Product.GetName() << " ; " << Product.GetPrice() << std::endl;
	}

	products_file.close();

	remove(products_file_name.c_str()); // Replaces old file
	rename("products.temp.txt", products_file_name.c_str());

	return;
}

//====================================================================================================
// ========== Notes ==========
//====================================================================================================
/*
	This implementation works on the following premises:
		- A container of type std::vector with elements of the type <Products> is used to load the
			products information in the file, allowing it (or the vector itself) to be modified
		- A text file of the type std::fstream contains the products information, and is formatted in a
			specific way
*/
//====================================================================================================
// ========== End of File ==========
//====================================================================================================