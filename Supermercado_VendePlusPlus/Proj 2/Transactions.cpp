//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Transactions.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

// Default constructor, since it's never used, it only returns invalid values for each parameter
Transactions::Transactions()
{
	id = 0;
	date = "00/00/0000";
}

// Interface-oriented constructor, takes specific parameters and creates a transaction
Transactions::Transactions(const unsigned &id, const std::string &date, const std::vector<std::string> &purchases)
{
	this->id = id;
	this->date = date;
	this->purchases = purchases;
}

// Implementation-oriented constructor, receives a line from the file contained in a stringstream, and extracts the information; assumes it's in the correct format (if not, may return invalid data)
Transactions::Transactions(std::stringstream &stream)
{
	try
	{
		stream >> id;
		stream.seekg(3, std::ios::cur);

		getline(stream, date, ';');
		date.pop_back();

		std::string spurchases;
		std::stringstream sspurchases;
		getline(stream, spurchases);
		sspurchases << spurchases;
		for (sspurchases.peek(); sspurchases.good(); sspurchases.peek())
		{
			getline(sspurchases, spurchases, ',');
			spurchases = spurchases.substr(1, spurchases.length());
			purchases.push_back(spurchases);
		}

		if (stream.bad())
			throw std::exception();
	}
	catch (...)
	{
		id = 0;
		date = "00/00/0000";
	}
}

// Access to transaction's ID (belonging to the client who made the transaction)
unsigned Transactions::GetId() const
{
	return id;
}

// Access to transaction's date
std::string Transactions::GetDate() const
{
	return date;
}

// Access to transaction's vector of purchases (products)
std::vector<std::string> Transactions::GetPurchases() const
{
	return purchases;
}

// Creates a transactions file, pre-formatted
void CreateTransactionsFile(std::fstream &transactions_file, const std::string &transactions_file_name)
{
	transactions_file.open(transactions_file_name.c_str(), std::ios::out | std::ios::trunc);
	transactions_file.close();
	transactions_file.open(transactions_file_name.c_str(), std::ios::in | std::ios::out);

	transactions_file << ": Ficheiro de transações" << std::endl << std::endl;
	transactions_file << ": A LINHA ABAIXO NÃO DEVE SER ALTERADA OU APAGADA" << std::endl;
	transactions_file << ". t" << std::endl << std::endl;
	transactions_file << ": Linhas de comentários são indicadas por um \":\" no início da linha" << std::endl;
	transactions_file << ": Linhas de controlo são indicadas por um \".\" no início da linha" << std::endl << std::endl;
	transactions_file << ": Todas as linhas de comentários e de controlo acima da linha # serão preservadas pelo programa" << std::endl;
	transactions_file << ": Todas as linhas de comentários e de controlo abaixo da linha # serão APAGADAS pelo programa" << std::endl << std::endl;
	transactions_file << ": Exemplo de uma linha de informação: 1 ; 01/01/2016 ; pão, água" << std::endl << std::endl;
	transactions_file << ": AS LINHAS ABAIXO NÃO DEVEM SER ALTERADAS OU APAGADAS" << std::endl;
	transactions_file << "# 0" << std::endl << std::endl;

	transactions_file.seekp(0, std::ios::beg);
	transactions_file.clear();

	return;
}

// Checks a file to see if it is a transactions file (contains transactions' information)
bool CheckTransactionsFile(std::fstream &transactions_file)
{
	for (transactions_file.peek(); !transactions_file.eof(); transactions_file.peek())
	{
		std::string stream;
		getline(transactions_file, stream, '\n');

		if (stream.size() > 0 && stream.front() == '.') // It does so by first searching for "control lines" (preceded by a dot)
		{
			if (stream.size() > 2 && stream.at(2) == 't') // Then checks to see if it contains a character specific to transactions files (t)
			{
				transactions_file.seekg(0, std::ios::beg);
				transactions_file.clear();

				return true;
			}
		}
	}
	return false; // Otherwise it is not a transactions file
}

// Checks a transactions file to see if it contains valid data (this assumes that the function above was used first to determine if the file was valid)
bool CheckTransactionsData(std::fstream &transactions_file, std::string &transactions_file_com, std::vector<Transactions> &transactions_data)
{
	for (transactions_file.peek(); !transactions_file.eof(); transactions_file.peek())
	{
		std::string stream = "";
		getline(transactions_file, stream, '\n');

		if (stream.size() == 0) // Ignores empty lines, saving them in a string
		{
			transactions_file_com += '\n';
		}
		else if (stream.front() == ':' || stream.front() == '.') // Ignores "comment lines" and "control lines", saving them in a string
		{
			transactions_file_com += stream + '\n';
		}
		else if (stream.front() == '#') // Detects number line
		{
			try
			{
				if (std::to_string(std::stoi(stream.substr(2, std::string::npos))).size() < stream.substr(2, std::string::npos).size()) // Checks if it is a single integer (that represents the number of transactions)
					throw std::exception();
			}
			catch (...)
			{
				return false; // Assumes the data is corrupted otherwise
			}

			transactions_data.resize(std::stoi(stream.substr(2, std::string::npos))); // If it is a integer, changes the size of the transactions vector to match that integer, since the read function works with iterators

			transactions_file.seekg(0, std::ios::beg);
			transactions_file.clear();

			return true;
		}
	}
	return false;
}

// Reads transactions' data from the file and inserts it in the transactions vector
bool ReadTransactionsData(std::fstream &transactions_file, std::vector<Transactions> &transactions_data)
{
	for (std::vector<Transactions>::iterator it = transactions_data.begin(); it != transactions_data.end();)
	{
		std::string stream;
		getline(transactions_file, stream, '\n');

		if (stream.size() > 0 && stream.front() != ':' && stream.front() != '.' && stream.front() != '#')
		{
			std::stringstream sstream(stream);
			Transactions Transaction = Transactions(sstream);
			if (Transaction.GetId() == 0) // Fails if information retrieved from the constructor is invalid
			{
				return false;
			}
			*it = Transaction;
			++it;
		}
	}
	return true;
}

// Writes transactions' data from vector to file
void WriteTransactionsData(std::fstream &transactions_file, const std::string &transactions_file_com, const std::string &transactions_file_name, std::vector<Transactions> &transactions_data)
{
	transactions_file.open("transactions.temp.txt", std::ios::out | std::ios::trunc); // Starts by creating a new file, for safety

	transactions_file << std::fixed << std::showpoint;
	transactions_file.precision(2);

	transactions_file << transactions_file_com; // Writes the "comment lines" and the "control lines" to the file

	transactions_file << "# " << transactions_data.size() << std::endl; // Writes the current number of transactions

	for (std::vector<Transactions>::iterator it = transactions_data.begin(); it != transactions_data.end(); ++it) // Writes the transactions' data
	{
		Transactions Transaction = *it;
		transactions_file << Transaction.GetId() << " ; " << Transaction.GetDate() << " ; " << Transaction.GetPurchases()[0];
		for (unsigned i = 1; i < Transaction.GetPurchases().size(); ++i)
			transactions_file << ", " << Transaction.GetPurchases()[i];
		transactions_file << std::endl;
	}

	transactions_file.close();

	remove(transactions_file_name.c_str()); // Replaces old file
	rename("transactions.temp.txt", transactions_file_name.c_str());

	return;
}

//====================================================================================================
// ========== Notes ==========
//====================================================================================================
/*
	This implementation works on the following premises:
		- A container of type std::vector with elements of the type <Transactions> is used to load the
			transactions information in the file, allowing it (or the vector itself) to be modified
		- A text file of the type std::fstream contains the transactions information, and is formatted
			in a specific way
*/
//====================================================================================================
// ========== End of File ==========
//====================================================================================================