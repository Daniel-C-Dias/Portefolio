//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#ifndef CLIENTS_HPP
#define CLIENTS_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//====================================================================================================
// ========== Objects and Functions Declarations ==========
//====================================================================================================

class Clients
{
private:
	unsigned id;
	std::string name;
	std::string date;
	double value;
public:
	Clients();
	Clients(const unsigned &id, const std::string &name, const std::string &date);
	Clients(std::stringstream &stream);

	void SetName(const std::string &name);
	void SetValue(const double &value);

	unsigned GetId() const;
	std::string GetName() const;
	std::string GetDate() const;
	double GetValue() const;
};

void CreateClientsFile(std::fstream &clients_file, const std::string &clients_file_name);

bool CheckClientsFile(std::fstream &clients_file);

bool CheckClientsData(std::fstream &clients_file, std::string &clients_file_com, std::vector<Clients> &clients_data);

bool ReadClientsData(std::fstream &clients_file, std::vector<Clients> &clients_data);

void WriteClientsData(std::fstream &clients_file, const std::string &clients_file_com, const std::string &clients_file_name, std::vector<Clients> &clients_data);

#endif

//====================================================================================================
// ========== End of File ==========
//====================================================================================================