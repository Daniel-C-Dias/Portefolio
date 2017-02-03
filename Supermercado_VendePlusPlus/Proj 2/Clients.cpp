//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Clients.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

// Default constructor, since it's never used, it only returns invalid values for each parameter
Clients::Clients()
{
	id = 0;
	name = "\0";
	date = "00/00/0000";
	value = -1;
}

// Interface-oriented constructor, takes specific parameters and creates a client; spent value always defaults to 0 in this case
Clients::Clients(const unsigned &id, const std::string &name, const std::string &date)
{
	this->id = id;
	this->name = name;
	this->date = date;
	value = 0;
}

// Implementation-oriented constructor, receives a line from the file contained in a stringstream, and extracts the information; assumes it's in the correct format (if not, may return invalid data)
Clients::Clients(std::stringstream &stream)
{
	try
	{
		stream >> id;
		stream.seekg(3, std::ios::cur);

		getline(stream, name, ';');
		name.pop_back();
		stream.seekg(1, std::ios::cur);

		getline(stream, date, ';');
		date.pop_back();

		stream >> value;

		if (stream.bad())
			throw std::exception();
	}
	catch (...)
	{
		id = 0;
		name = "\0";
		date = "00/00/0000";
		value = -1;
	}
}

// Used to change name of an already existing client
void Clients::SetName(const std::string &name)
{
	this->name = name;
	return;
}

// Used to change the value spent by an already existing client, adding to the previous amount
void Clients::SetValue(const double &value)
{
	this->value += value;
	return;
}

// Access to client's ID
unsigned Clients::GetId() const
{
	return id;
}

// Access to client's name
std::string Clients::GetName() const
{
	return name;
}

// Access to client's date
std::string Clients::GetDate() const
{
	return date;
}

// Access to client's spent value
double Clients::GetValue() const
{
	return value;
}

// Creates a clients file, pre-formatted
void CreateClientsFile(std::fstream &clients_file, const std::string &clients_file_name)
{
	clients_file.open(clients_file_name.c_str(), std::ios::out | std::ios::trunc);
	clients_file.close();
	clients_file.open(clients_file_name.c_str(), std::ios::in | std::ios::out);

	clients_file << ": Ficheiro de clientes" << std::endl << std::endl;
	clients_file << ": A LINHA ABAIXO NÃO DEVE SER ALTERADA OU APAGADA" << std::endl;
	clients_file << ". c" << std::endl << std::endl;
	clients_file << ": Linhas de comentários são indicadas por um \":\" no início da linha" << std::endl;
	clients_file << ": Linhas de controlo são indicadas por um \".\" no início da linha" << std::endl << std::endl;
	clients_file << ": Todas as linhas de comentários e de controlo acima da linha # serão preservadas pelo programa" << std::endl;
	clients_file << ": Todas as linhas de comentários e de controlo abaixo da linha # serão APAGADAS pelo programa" << std::endl << std::endl;
	clients_file << ": Exemplo de uma linha de informação: 1 ; Daniel Dias ; 01/01/2016 ; 4.99" << std::endl << std::endl;
	clients_file << ": AS LINHAS ABAIXO NÃO DEVEM SER ALTERADAS OU APAGADAS" << std::endl;
	clients_file << "# 0" << std::endl << std::endl;

	clients_file.seekp(0, std::ios::beg);
	clients_file.clear();

	return;
}

// Checks a file to see if it is a clients file (contains clients' information)
bool CheckClientsFile(std::fstream &clients_file)
{
	for (clients_file.peek(); !clients_file.eof(); clients_file.peek())
	{
		std::string stream;
		getline(clients_file, stream, '\n');

		if (stream.size() > 0 && stream.front() == '.') // It does so by first searching for "control lines" (preceded by a dot)
		{
			if (stream.size() > 2 && stream.at(2) == 'c') // Then checks to see if it contains a character specific to clients files (c)
			{
				clients_file.seekg(0, std::ios::beg);
				clients_file.clear();

				return true;
			}
		}
	}
	return false; // Otherwise it is not a clients file
}

// Checks a clients file to see if it contains valid data (this assumes that the function above was used first to determine if the file was valid)
bool CheckClientsData(std::fstream &clients_file, std::string &clients_file_com, std::vector<Clients> &clients_data)
{
	for (clients_file.peek(); !clients_file.eof(); clients_file.peek())
	{
		std::string stream;
		getline(clients_file, stream, '\n');

		if (stream.size() == 0) // Ignores empty lines, saving them in a string
		{
			clients_file_com += '\n';
		}
		else if (stream.front() == ':' || stream.front() == '.') // Ignores "comment lines" and "control lines", saving them in a string
		{
			clients_file_com += stream + '\n';
		}
		else if (stream.front() == '#') // Detects number line
		{
			try
			{
				if (std::to_string(std::stoi(stream.substr(2, std::string::npos))).size() < stream.substr(2, std::string::npos).size()) // Checks if it is a single integer (that represents the number of clients)
					throw std::exception();
			}
			catch (...)
			{
				return false; // Assumes the data is corrupted otherwise
			}

			clients_data.resize(std::stoi(stream.substr(2, std::string::npos))); // If it is a integer, changes the size of the clients vector to match that integer, since the read function works with iterators

			clients_file.seekg(0, std::ios::beg);
			clients_file.clear();

			return true;
		}
	}
	return false;
}

// Reads clients' data from the file and inserts it in the clients vector
bool ReadClientsData(std::fstream &clients_file, std::vector<Clients> &clients_data)
{
	for (std::vector<Clients>::iterator it = clients_data.begin(); it != clients_data.end();)
	{
		std::string stream;
		getline(clients_file, stream, '\n');

		if (stream.size() > 0 && stream.front() != ':' && stream.front() != '.' && stream.front() != '#')
		{
			std::stringstream sstream(stream);
			Clients Client = Clients(sstream);
			if (Client.GetId() == 0)
			{
				return false; // Fails if information retrieved from the constructor is invalid
			}
			*it = Client;
			++it;
		}
	}

	clients_file.seekg(0, std::ios::beg);
	clients_file.clear();

	return true;
}

// Writes clients' data from vector to file
void WriteClientsData(std::fstream &clients_file, const std::string &clients_file_com, const std::string &clients_file_name, std::vector<Clients> &clients_data)
{
	clients_file.open("clients.temp.txt", std::ios::out | std::ios::trunc); // Starts by creating a new file, for safety

	clients_file << std::fixed << std::showpoint;
	clients_file.precision(2);

	clients_file << clients_file_com; // Writes the "comment lines" and the "control lines" to the file

	clients_file << "# " << clients_data.size() << std::endl; // Writes the current number of clients

	for (std::vector<Clients>::iterator it = clients_data.begin(); it != clients_data.end(); ++it) // Writes the clients' data
	{
		Clients Client = *it;
		clients_file << Client.GetId() << " ; " << Client.GetName() << " ; " << Client.GetDate() << " ; " << Client.GetValue() << std::endl;
	}

	clients_file.close();

	remove(clients_file_name.c_str()); // Replaces old file
	rename("clients.temp.txt", clients_file_name.c_str());

	return;
}

//====================================================================================================
// ========== Notes ==========
//====================================================================================================
/*
	This implementation works on the following premises:
		- A container of type std::vector with elements of the type <Clients> is used to load the
			clients information in the file, allowing it (or the vector itself) to be modified
		- A text file of the type std::fstream contains the clients information, and is formatted in a
			specific way
*/
//====================================================================================================
// ========== End of File ==========
//====================================================================================================