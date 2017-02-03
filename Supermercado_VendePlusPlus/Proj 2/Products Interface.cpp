//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Interface.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

bool ViewAllProducts(Variables &V) // function that allows the user to see all the existing products in the store
{                                  // the code is similar to the ViewAllClients function
	ClearScreen(V);
	V.input = "";

	unsigned option;
	SHORT h = 6;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	//setting for the buttons displayed on screen
	BUTTONS[0].Left = 105;
	BUTTONS[0].Top = 4;
	BUTTONS[0].Right = 124;
	BUTTONS[0].Bottom = 6;
	BUTTONS[0].TextLines = 1;
	BUTTONS[0].TextPos = new COORD[1];
	BUTTONS[0].TextPos[0] = {105, 5};
	BUTTONS[0].Text = new std::string[1];
	BUTTONS[0].Text[0] = (V.language ? "  <- Previous page  " : " <- Página anterior ");
	if (V.page > 0)
	{
		ACTIVE_BUTTONS.push_back(0);
	}

	BUTTONS[1].Left = 105;
	BUTTONS[1].Top = 10;
	BUTTONS[1].Right = 124;
	BUTTONS[1].Bottom = 12;
	BUTTONS[1].TextLines = 1;
	BUTTONS[1].TextPos = new COORD[1];
	BUTTONS[1].TextPos[0] = {105, 11};
	BUTTONS[1].Text = new std::string[1];
	BUTTONS[1].Text[0] = (V.language ? "    Next page ->    " : " Página seguinte -> ");
	if (20 + 20 * V.page < V.products_data.size())
	{
		ACTIVE_BUTTONS.push_back(1);
	}

	BUTTONS[2].Left = 105;
	BUTTONS[2].Top = 16;
	BUTTONS[2].Right = 124;
	BUTTONS[2].Bottom = 18;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {105, 17};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 40 : 39), 1});
	std::cout << (V.language ? "Products Manager" : "Gestor de Produtos");
	
	//structor for the table that show the products information (only 20 per page)
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 3});
	std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 4});
	std::cout << "|" << (V.language ? "                                  Products                                  " : "                                  Produtos                                  ") << "|" << (V.language ? "    Price(€)    " : "    Preço(€)    ") << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
	std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
	for (unsigned i = 0; i < 20; ++i, ++h)
	{
		if (i + 20 * V.page < V.products_data.size())
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, h});
			std::cout << "| " << V.products_data[i + 20 * V.page].Products::GetName();
			SetConsoleCursorPosition(V.OUT_HANDLE, {82, h});
			std::cout << "| " << V.products_data[i + 20 * V.page].Products::GetPrice() << "€";
			SetConsoleCursorPosition(V.OUT_HANDLE, {99, h});
			std::cout << "|";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, ++h});
			std::cout << "o" << "----------------------------------------------------------------------------" << "o" << "----------------" << "o";
		}
		else break;
	}

	if (V.page > 0)
	{
		Sleep(200);

		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 3});
		std::cout << "o--------------------o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 4});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 5});
		std::cout << "|" << BUTTONS[0].Text[0] << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 6});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 7});
		std::cout << "o--------------------o";
	}

	if (20 + 20 * V.page < V.products_data.size())
	{
		Sleep(200);

		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 9});
		std::cout << "o--------------------o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 10});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 11});
		std::cout << "|" << BUTTONS[1].Text[0] << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 12});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 13});
		std::cout << "o--------------------o";
	}

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 15});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 16});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 17});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 19});
	std::cout << "o--------------------o";

	option = Event(V, BUTTONS, ACTIVE_BUTTONS);

	for (unsigned i = 0; i < 3; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	switch (option)
	{
		case 0:
			--V.page;
			break;
		case 1:
			++V.page;
			break;
		case 2:
			return false;
	}
	return true;
}

bool AddProducts(Variables &V) //function that allows the user to add a new product to the store
{                              // similar to the AddClients function
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	double price = 0;
	std::string name;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	//setting for the buttons displayed on screen
	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 6;
	BUTTONS[0].Right = 17;
	BUTTONS[0].Bottom = 6;
	BUTTONS[0].TextLines = 0;
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 6;
	BUTTONS[1].Top = 12;
	BUTTONS[1].Right = 17;
	BUTTONS[1].Bottom = 12;
	BUTTONS[1].TextLines = 0;
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 105;
	BUTTONS[2].Top = 4;
	BUTTONS[2].Right = 124;
	BUTTONS[2].Bottom = 6;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {105, 5};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 40 : 39), 1});
	std::cout << (V.language ? "Products Manager" : "Gestor de Produtos");

	SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
	std::cout << (V.language ? "Insert" : "Inserir");
	SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
	std::cout << (V.language ? "Name" : "Nome");

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
	std::cout << "o--o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
	std::cout << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 7});
	std::cout << "o--o";

	SetConsoleCursorPosition(V.OUT_HANDLE, {6, 9});
	std::cout << (V.language ? "Insert" : "Inserir");
	SetConsoleCursorPosition(V.OUT_HANDLE, {6, 10});
	std::cout << (V.language ? "Price" : "Preço");

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 11});
	std::cout << "o-------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 12});
	std::cout << "|             |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 13});
	std::cout << "o-------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 3});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 4});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 5});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 6});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 7});
	std::cout << "o--------------------o";

	while (true)
	{
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
		std::cout << (V.language ? "Insert" : "Inserir");
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
		std::cout << (V.language ? "Name" : "Nome");

		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 9});
		std::cout << (V.language ? "Insert" : "Inserir");
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 10});
		std::cout << (V.language ? "Price" : "Preço");

		for (unsigned i = 0; i < 3; ++i)
		{
			if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 1)
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {5, 12});
				std::cout << "|             |";
			}
		}

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);

		switch (option)
		{
			case 0: //input for the product name
				SetConsoleCursorPosition(V.OUT_HANDLE, {7, 6});
				V.OUT_BUFFER.dwCursorPosition = {7, 6};
				V.input = Input(V, 64);

				if (V.input == "") continue; // in case the name is empty

				name = V.input;

				for (unsigned i = 0; i < 3; ++i)
				{
					if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 0)
					{
						ACTIVE_BUTTONS.erase(ACTIVE_BUTTONS.begin() + i);
						break;
					}
				}

				if (ACTIVE_BUTTONS.size() > 1) continue;
				break;

			case 1: //input for the product price
				SetConsoleCursorPosition(V.OUT_HANDLE, {7, 12});
				V.OUT_BUFFER.dwCursorPosition = {7, 12};
				V.input = Input(V, 10);

				try // to check if the price introduced is a valid input
				{
					if (V.input == "") // in case the input is empty
						continue;
					for (unsigned i = 0; i < V.input.size(); ++i) // in case the inputed price has a non-allowed character 
					{
						if ((V.input[i] > 57 || V.input[i] < 48) && V.input[i] != '.')
							throw std::exception();
					}
				}
				catch (...) // show an error message on screen
				{
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Insert" : "Inserir").length(), {6, 9}, V.FOOBAR);
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Price" : "Preço").length(), {6, 10}, V.FOOBAR);

					SetConsoleCursorPosition(V.OUT_HANDLE, {6, 9});
					std::cerr << (V.language ? "Invalid " : "Entrada ");
					SetConsoleCursorPosition(V.OUT_HANDLE, {6, 10});
					std::cerr << (V.language ? "input!" : "inválida!");

					Sleep(1000);

					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {6, 9}, V.FOOBAR);
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {6, 10}, V.FOOBAR);

					continue;
				}

				std::cout << "€"; // add an the euro symblol for display purposes only

				price = std::stod(V.input); //save the price in a variable

				for (unsigned i = 0; i < 3; ++i)
				{
					if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 1)
					{
						ACTIVE_BUTTONS.erase(ACTIVE_BUTTONS.begin() + i);
						break;
					}
				}

				if (ACTIVE_BUTTONS.size() > 1) continue;
				break;
		}
		break;
	}

	if (option != 2) //saves the new product 
	{
		V.products_data.push_back(Products::Products(name, price)); //adds the new product to the vector

		ClearScreen(V);

		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 40 : 39), 1});
		std::cout << (V.language ? "Products Manager" : "Gestor de Produtos");

		//shows the user a success message
		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 35 : 33), 3});
		std::cout << (V.language ? "Product successfully added!" : "Produto adicionado com sucesso!");

		Sleep(2000);
	}

	for (unsigned i = 2; i < 3; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	if (option == 2) return false;
	return true;
}

//====================================================================================================
// ========== End of File ==========
//====================================================================================================