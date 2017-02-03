//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#ifndef TRANSACTIONS_HPP
#define TRANSACTIONS_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//====================================================================================================
// ========== Objects and Functions Declarations ==========
//====================================================================================================

class Transactions
{
private:
	unsigned id;
	std::string date;
	std::vector<std::string> purchases;
public:
	Transactions();
	Transactions(const unsigned &id, const std::string &date, const std::vector<std::string> &purchases);
	Transactions(std::stringstream &stream);

	unsigned GetId() const;
	std::string GetDate() const;
	std::vector<std::string> GetPurchases() const;
};

void CreateTransactionsFile(std::fstream &transactions_file, const std::string &transactions_file_name);

bool CheckTransactionsFile(std::fstream &transactions_file);

bool CheckTransactionsData(std::fstream &transactions_file, std::string &transactions_file_com, std::vector<Transactions> &transactions_data);

bool ReadTransactionsData(std::fstream &transactions_file, std::vector<Transactions> &transactions_data);

void WriteTransactionsData(std::fstream &transactions_file, const std::string &transactions_file_com, const std::string &transactions_file_name, std::vector<Transactions> &transactions_data);

#endif

//====================================================================================================
// ========== End of File ==========
//====================================================================================================