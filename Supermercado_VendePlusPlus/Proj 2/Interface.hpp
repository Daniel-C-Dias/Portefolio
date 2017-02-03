//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Clients.hpp"
#include "Products.hpp"
#include "Transactions.hpp"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#undef max // For std::numeric_limits

//====================================================================================================
// ========== Objects and Functions Declarations ==========
//====================================================================================================

// Functor to use in std::stable_sort
struct Sort
{
	bool operator()(const Clients &c1, const Clients &c2) // Given two Clients type elements, compares names and orders them alphabetically
	{
		return c1.GetName() < c2.GetName();
	}

	bool operator()(const Transactions &t1, const Transactions &t2) // Given two Transactions type elements, compares dates and orders them chronologically
	{
		return std::stoi(t1.GetDate().substr(6, 4) + t1.GetDate().substr(3, 2) + t1.GetDate().substr(0, 2)) < std::stoi(t2.GetDate().substr(6, 4) + t2.GetDate().substr(3, 2) + t2.GetDate().substr(0, 2));
	}
};

// Functor to use in std::stable_sort
struct Compare
{
	bool operator()(const Clients &c1, const Clients &c2) // Given two Clients type elements, compares ids and orders them numerically
	{
		return c1.GetId() < c2.GetId();
	}

	bool operator()(const std::pair<unsigned, double> &p1, const std::pair<unsigned, double> &p2) // Given two pair<unsigned, double> type elements, compares the double and orders them numerically
	{
		return p1.second < p2.second;
	}
};

struct Variables
{
	HANDLE IN_HANDLE;
	HANDLE OUT_HANDLE;
	PINPUT_RECORD IN_BUFFER;
	CONSOLE_SCREEN_BUFFER_INFO OUT_BUFFER;
	CONSOLE_SCREEN_BUFFER_INFO EVENT_OUT_BUFFER;
	CONSOLE_CURSOR_INFO CURSOR_INFO;
	DWORD OUT_BUFFER_SIZE;
	PDWORD FOOBAR;

	unsigned language;
	unsigned page;
	std::string input;
	std::vector<std::vector<bool>> matrix;

	// Clients implementation specific
	std::fstream clients_file;
	std::string clients_file_com;
	std::string clients_file_name;
	std::vector<Clients> clients_data;

	// Products implementation specific
	std::fstream products_file;
	std::string products_file_com;
	std::string products_file_name;
	std::vector<Products> products_data;

	// Transactions implementation specific
	std::fstream transactions_file;
	std::string transactions_file_com;
	std::string transactions_file_name;
	std::vector<Transactions> transactions_data;
};

struct BUTTON
{
	SHORT Left;
	SHORT Top;
	SHORT Bottom;
	SHORT Right;
	unsigned TextLines;
	COORD * TextPos;
	std::string * Text;
};

// Definition in "Utilities.cpp"

void ClearScreen(Variables &V);

unsigned ValidDate(Variables &V);

void LoadMatrix(Variables &V);

std::string Input(Variables &V, const unsigned &limit);

unsigned Event(Variables &V, BUTTON BUTTON[], const std::vector<unsigned> &ACTIVE_BUTTONS);

// Definition in "Interface.cpp"

bool Interface(Variables &V);

bool ClientsInterface(Variables &V);

bool ProductsInterface(Variables &V);

bool TransactionsInterface(Variables &V);

bool RecommendationsInterface(Variables &V);

bool ViewClientsInterface(Variables &V);

bool ViewTransactionsInterface(Variables &V);

// Definition in "Clients Interface.cpp"

bool ViewAllClients(Variables &V);

bool ViewSpecificClient(Variables &V);

bool EditClients(Variables &V);

bool AddClients(Variables &V);

bool RemoveClients(Variables &V);

// Definition in "Products Interface.cpp"

bool ViewAllProducts(Variables &V);

bool AddProducts(Variables &V);

// Definition in "Transactions Interface.cpp"

bool ViewAllTransactions(Variables &V);

bool ViewSpecificTransactions(Variables &V);

bool AddTransactions(Variables &V);

// Definition in "Recommendations Interface.cpp"

bool PersonalRecommendations(Variables &V);

bool BottomTenCampaign(Variables &V);

#endif

//====================================================================================================
// ========== End of File ==========
//====================================================================================================