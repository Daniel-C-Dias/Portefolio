//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Interface.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

bool PersonalRecommendations(Variables &V) // function that allows the user to recommend a specific product to a client whose ID as been given
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	unsigned n = -1;
	unsigned similar_clients_max = 0;
	unsigned different_products_max = 0;
	std::vector<unsigned> similar_clients(V.matrix.size(), 0);
	std::vector<unsigned> similar_clients_positions(1, 0);
	std::vector<unsigned> different_products(V.matrix.front().size(), 0);
	std::vector<unsigned> different_products_positions(1, 0);
	SHORT h = 15;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	//settings for the button displayed on screen
	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 6;
	BUTTONS[0].Right = 17;
	BUTTONS[0].Bottom = 6;
	BUTTONS[0].TextLines = 0;
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 105;
	BUTTONS[1].Top = 4;
	BUTTONS[1].Right = 124;
	BUTTONS[1].Bottom = 6;
	BUTTONS[1].TextLines = 1;
	BUTTONS[1].TextPos = new COORD[1];
	BUTTONS[1].TextPos[0] = {105, 5};
	BUTTONS[1].Text = new std::string[1];
	BUTTONS[1].Text[0] = (V.language ? "     New search     " : "    Nova procura    ");

	BUTTONS[2].Left = 105;
	BUTTONS[2].Top = 13;
	BUTTONS[2].Right = 124;
	BUTTONS[2].Bottom = 15;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {105, 14};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 37), 1});
	std::cout << (V.language ? "Recommendations Manager" : "Gestor de Recomendações");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), 3});
	std::cout << (V.language ? "Search" : "Procurar");
	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), 4});
	std::cout << (V.language ? "by ID" : "por ID");

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
	std::cout << "o------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
	std::cout << "|            |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 7});
	std::cout << "o------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 12});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 13});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 14});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 15});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 16});
	std::cout << "o--------------------o";

	while (true) //to search if the client exist
	{
		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), 3});
		std::cout << (V.language ? "Search" : "Procurar");
		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), 4});
		std::cout << (V.language ? "by ID" : "por ID");

		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
		std::cout << "|            |";

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);

		if (option == 0)
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {7, 6});
			V.OUT_BUFFER.dwCursorPosition = {7, 6};
			V.input = Input(V, 10);

			try //check if the ID is a valid one
			{
				if (V.input == "")
					continue;
				if (std::to_string(std::stol(V.input)).size() < V.input.size() || std::stol(V.input) < 0 || std::stol(V.input) > std::numeric_limits<int>::max())
					throw std::exception();
			}
			catch (...)
			{
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Search" : "Procurar").length(), {(V.language ? 8 : 7), 3}, V.FOOBAR);
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "by ID" : "por ID").length(), {(V.language ? 8 : 7), 4}, V.FOOBAR);

				SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
				std::cerr << (V.language ? "Invalid " : "Entrada ");
				SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
				std::cerr << (V.language ? "input!" : "inválida!");

				Sleep(1000);

				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {6, 3}, V.FOOBAR);
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {6, 4}, V.FOOBAR);

				continue;
			}

			for (unsigned i = 0; i < V.clients_data.size(); ++i)
			{
				if (V.clients_data[i].GetId() == std::stoi(V.input))
				{
					n = i; //saves the position of the client
					break;
				}
			}

			if (n == -1)
			{
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Search" : "Procurar").length(), {(V.language ? 8 : 7), 3}, V.FOOBAR);
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "by ID" : "por ID").length(), {(V.language ? 8 : 7), 4}, V.FOOBAR);

				SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
				std::cerr << (V.language ? "Client " : "Cliente ");
				SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
				std::cerr << (V.language ? "not found!" : "não encontrado!");

				Sleep(1000);

				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Client " : "Cliente ").length(), {6, 3}, V.FOOBAR);
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "not found!" : "não encontrado!").length(), {6, 4}, V.FOOBAR);

				continue;
			}
		}
		break;
	}

	if (n != -1) // displays client info on screen
	{
		ACTIVE_BUTTONS.front() = 1;

		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 3});
		std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 4});
		std::cout << "|" << "     ID     " << "|" << (V.language ? "                  Name of client                  " : "                  Nome do cliente                 ") << "|" << (V.language ? "    Date    " : "    Data    ") << "|" << (V.language ? " Value spent(€) " : " Valor gasto(€) ") << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
		std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
		std::cout << "| " << V.clients_data[n].Clients::GetId();
		SetConsoleCursorPosition(V.OUT_HANDLE, {18, 6});
		std::cout << "| " << V.clients_data[n].Clients::GetName();
		SetConsoleCursorPosition(V.OUT_HANDLE, {69, 6});
		std::cout << "| " << V.clients_data[n].Clients::GetDate();
		SetConsoleCursorPosition(V.OUT_HANDLE, {82, 6});
		std::cout << "| " << V.clients_data[n].Clients::GetValue() << "€";
		SetConsoleCursorPosition(V.OUT_HANDLE, {99, 6});
		std::cout << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 7});
		std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";

		for (unsigned i = (n == 0 ? 1 : 0); i < V.matrix.size(); (n == ++i ? ++i : i)) // This for loop checks the amount of products that each client bought that are the same that the target client bought
		{
			for (unsigned j = 0; j < V.matrix[i].size(); ++j)
			{
				if (V.matrix[n][j] == true && V.matrix[i][j] == true)
				{
					++similar_clients[i]; // The similar_clients vector has size == clients.size(), with each position associated to the respective client in the clients vector
				}
			}
		}

		similar_clients_positions.push_back(0);
		for (unsigned i = 1; i < similar_clients.size(); ++i) // This for loop checks the similar_clients vector for the highest amount of products bought by a client (or clients), saving the position of those clients in the similar_clients_positions vector
		{
			if (similar_clients[i] >= similar_clients_max)
			{
				if (similar_clients[i] > similar_clients_max)
				{
					similar_clients_max = similar_clients[i];
					similar_clients_positions.resize(0);
				}
				similar_clients_positions.push_back(i);
			}
		}

		for (unsigned i = 0; i < similar_clients_positions.size(); ++i) // This for loop checks for the amount of products that the clients from similar_clients_positions bought that the target client hasn't
		{
			for (unsigned j = 0; j < V.matrix[i].size(); ++j)
			{
				if (V.matrix[n][j] == false && V.matrix[similar_clients_positions[i]][j] == true)
				{
					++different_products[j]; // The different_products vector has size == products.size(), with each position associated to the respective product in the products vector
				}
			}
		}

		different_products_positions.push_back(0);
		for (unsigned i = 1; i < different_products.size(); ++i) // This for loop checks the different_products vector for the highest amount of times a product (or products) were bought, saving the position of those products in the different_products_positions vector
		{
			if (different_products[i] >= different_products_max)
			{
				if (different_products[i] > different_products_max)
				{
					different_products_max = different_products[i];
					different_products_positions.resize(0);
				}
				different_products_positions.push_back(i);
			}
		}

		switch (similar_clients_max)
		{
			case 0:
				SetConsoleCursorPosition(V.OUT_HANDLE, {6, 10});
				std::cout << (V.language ? "Note: No transactions in common; most popular product recommended" : "Nota: Sem transações em comum; recomendado o produto mais popular");
			default:
				SetConsoleCursorPosition(V.OUT_HANDLE, {6, 9});
				std::cout << (V.language ? "Recommendations:" : "Recomendações:");
				SetConsoleCursorPosition(V.OUT_HANDLE, {5, 12});
				std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
				SetConsoleCursorPosition(V.OUT_HANDLE, {5, 13});
				std::cout << "|" << (V.language ? "                                  Products                                  " : "                                  Produtos                                  ") << "|" << (V.language ? "    Price(€)    " : "    Preço(€)    ") << "|";
				SetConsoleCursorPosition(V.OUT_HANDLE, {5, 14});
				std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
				for (unsigned i = 0; i < different_products_positions.size(); ++i, ++h)
				{
					SetConsoleCursorPosition(V.OUT_HANDLE, {5, h});
					std::cout << "| " << V.products_data[different_products_positions[i]].Products::GetName();
					SetConsoleCursorPosition(V.OUT_HANDLE, {82, h});
					std::cout << "| " << V.products_data[different_products_positions[i]].Products::GetPrice() << "€";
					SetConsoleCursorPosition(V.OUT_HANDLE, {99, h});
					std::cout << "|";
					SetConsoleCursorPosition(V.OUT_HANDLE, {5, ++h});
					std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
				}
				break;
		}

		Sleep(200);

		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 3});
		std::cout << "o--------------------o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 4});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 5});
		std::cout << "|" << BUTTONS[1].Text[0] << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 6});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 7});
		std::cout << "o--------------------o";

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);
	}

	for (unsigned i = 1; i < 3; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	if (option == 2) return false;
	return true;
}

bool BottomTenCampaign(Variables &V) //function that defines the bottom ten campaign
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	std::vector<unsigned> n;
	std::vector<std::pair<unsigned, double>> v;
	unsigned similar_clients_max = 0;
	unsigned different_products_max = 0;
	std::vector<unsigned> similar_clients(V.matrix.size(), 0);
	std::vector<unsigned> similar_clients_positions(1, 0);
	std::vector<unsigned> different_products(V.matrix.front().size(), 0);
	std::vector<unsigned> different_products_positions(1, 0);
	SHORT h = 8;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[1];

	//settings for the buttons to be displayed on screen (which is only the Return button)
	BUTTONS[0].Left = 105;
	BUTTONS[0].Top = 33;
	BUTTONS[0].Right = 124;
	BUTTONS[0].Bottom = 35;
	BUTTONS[0].TextLines = 1;
	BUTTONS[0].TextPos = new COORD[1];
	BUTTONS[0].TextPos[0] = {105, 34};
	BUTTONS[0].Text = new std::string[1];
	BUTTONS[0].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(0);

	for (unsigned i = 0; i < V.clients_data.size(); ++i) //defines a vector of pairs (position,value)
	{
		v.push_back(std::pair<unsigned, double>(i, V.clients_data[i].GetValue()));
	}

	std::stable_sort(v.begin(), v.end(), Compare());//sorts the previous vector by the value variable
	
	for (unsigned i = 0; i < 10; ++i) // sets position of the 10 lower elements in another vector
	{
		n.push_back(v[i].first);
	}

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 37), 1});
	std::cout << (V.language ? "Recommendations Manager" : "Gestor de Recomendações");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 40 : 40), 3});
	std::cout << (V.language ? "Bottom10 Campaign" : "Campanha Bottom10");
	
	//shows the Bottom 10 clients information on screen
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
	std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
	std::cout << "|" << "     ID     " << "|" << (V.language ? "                  Name of client                  " : "                  Nome do cliente                 ") << "|" << (V.language ? "    Date    " : "    Data    ") << "|" << (V.language ? " Value spent(€) " : " Valor gasto(€) ") << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 7});
	std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
	for (unsigned i = 0; i < 10; ++i, ++h)
	{
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, h});
		std::cout << "| " << V.clients_data[n[i]].Clients::GetId();
		SetConsoleCursorPosition(V.OUT_HANDLE, {18, h});
		std::cout << "| " << V.clients_data[n[i]].Clients::GetName();
		SetConsoleCursorPosition(V.OUT_HANDLE, {69, h});
		std::cout << "| " << V.clients_data[n[i]].Clients::GetDate();
		SetConsoleCursorPosition(V.OUT_HANDLE, {82, h});
		std::cout << "| " << V.clients_data[n[i]].Clients::GetValue() << "€";
		SetConsoleCursorPosition(V.OUT_HANDLE, {99, h});
		std::cout << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, ++h});
		std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
	}

	V.matrix.push_back(std::vector<bool>(V.products_data.size(), false)); //makes an extra element at the end of the matrix, which is the template client between the bottom 10

	for (unsigned i = 0; i < V.products_data.size(); ++i) //sets the products in common between the button 10 to the template client
	{
		for (unsigned j = 0; j < 10; ++j)
		{
			if (V.matrix[n[j]][i] == false) break;
			if (j == 9)
			{
				V.matrix.back()[i] = true;
			}
		}
	}
		
	for (unsigned i = 0; i < V.matrix.size() - 1; ++i) // This for loop checks the amount of products that each client bought that are the same that the target client bought
	{
		bool next = false;
		for (unsigned j = 0; j < 10; ++j)
		{
			if (i == n[j])
			{
				next = true;
				break;
			}
		}
		if (next) continue;

		for (unsigned j = 0; j < V.matrix[i].size(); ++j)
		{
			if (V.matrix.back()[j] == true && V.matrix[i][j] == true)
			{
				++similar_clients[i]; // The similar_clients vector has size == clients.size(), with each position associated to the respective client in the clients vector
			}
		}
	}

	similar_clients_positions.push_back(0);
	for (unsigned i = 1; i < similar_clients.size(); ++i) // This for loop checks the similar_clients vector for the highest amount of products bought by a client (or clients), saving the position of those clients in the similar_clients_positions vector
	{
		if (similar_clients[i] >= similar_clients_max)
		{
			if (similar_clients[i] > similar_clients_max)
			{
				similar_clients_max = similar_clients[i];
				similar_clients_positions.resize(0);
			}
			similar_clients_positions.push_back(i);
		}
	}

	for (unsigned i = 0; i < similar_clients_positions.size(); ++i) // This for loop checks for the amount of products that the clients from similar_clients_positions bought that the target client hasn't
	{
		for (unsigned j = 0; j < V.matrix[i].size(); ++j)
		{
			if (V.matrix.back()[j] == false && V.matrix[similar_clients_positions[i]][j] == true)
			{
				++different_products[j]; // The different_products vector has size == products.size(), with each position associated to the respective product in the products vector
			}
		}
	}

	different_products_positions.push_back(0);
	for (unsigned i = 1; i < different_products.size(); ++i) // This for loop checks the different_products vector for the highest amount of times a product (or products) were bought, saving the position of those products in the different_products_positions vector
	{
		if (different_products[i] >= different_products_max)
		{
			if (different_products[i] > different_products_max)
			{
				different_products_max = different_products[i];
				different_products_positions.resize(0);
			}
			different_products_positions.push_back(i);
		}
	}

	switch (similar_clients_max)
	{
		case 0:
			SetConsoleCursorPosition(V.OUT_HANDLE, {6, 30});
			std::cout << (V.language ? "Note: No transactions in common; most popular product recommended" : "Nota: Sem transações em comum; recomendado o produto mais popular");
		default://shows the product to be recommended in the bottom 10 campaign
			SetConsoleCursorPosition(V.OUT_HANDLE, {6, 29});
			std::cout << (V.language ? "Recommendations:" : "Recomendações:");
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, 32});
			std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, 33});
			std::cout << "|" << (V.language ? "                                  Products                                  " : "                                  Produtos                                  ") << "|" << (V.language ? "    Price(€)    " : "    Preço(€)    ") << "|";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, 34});
			std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, 35});
			std::cout << "| " << V.products_data[different_products_positions.front()].Products::GetName();
			SetConsoleCursorPosition(V.OUT_HANDLE, {82, 35});
			std::cout << "| " << V.products_data[different_products_positions.front()].Products::GetPrice() << "€";
			SetConsoleCursorPosition(V.OUT_HANDLE, {99, 35});
			std::cout << "|";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, 36});
			std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
			break;
	}

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 32});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 33});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 34});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 35});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 36});
	std::cout << "o--------------------o";

	option = Event(V, BUTTONS, ACTIVE_BUTTONS);
	
	delete[] BUTTONS[0].Text;
	delete[] BUTTONS[0].TextPos;
	delete[] BUTTONS;

	return false;
}

//====================================================================================================
// ========== End of File ==========
//====================================================================================================