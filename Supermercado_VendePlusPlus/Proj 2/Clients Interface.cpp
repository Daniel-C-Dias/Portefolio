//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Interface.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

bool ViewAllClients(Variables &V) // function that allows the user to see all the clients in the txt file, showing only 20 per page
{
	ClearScreen(V);
	V.input = "";

	unsigned option; //option relates to the number of the button/box displayed on screen
	SHORT h = 6;
	std::vector<unsigned> ACTIVE_BUTTONS; //this vector controls which button/box is displayed on screen
	BUTTON * BUTTONS = new BUTTON[3];

	// setting for the button positon that allows the user to move to the previous 20 clients of the list
	BUTTONS[0].Left = 105;
	BUTTONS[0].Top = 4;
	BUTTONS[0].Right = 124;
	BUTTONS[0].Bottom = 6;
	BUTTONS[0].TextLines = 1;
	BUTTONS[0].TextPos = new COORD[1];
	BUTTONS[0].TextPos[0] = {105, 5};
	BUTTONS[0].Text = new std::string[1];
	BUTTONS[0].Text[0] = (V.language ? "  <- Previous page  " : " <- Página anterior ");
	if (V.page > 0) // assessing if the list has a page to return to
	{
		ACTIVE_BUTTONS.push_back(0);
	}

	// setting for the button positon that allows the user to move to the next 20 clients of the list
	BUTTONS[1].Left = 105;
	BUTTONS[1].Top = 10;
	BUTTONS[1].Right = 124;
	BUTTONS[1].Bottom = 12;
	BUTTONS[1].TextLines = 1;
	BUTTONS[1].TextPos = new COORD[1];
	BUTTONS[1].TextPos[0] = {105, 11};
	BUTTONS[1].Text = new std::string[1];
	BUTTONS[1].Text[0] = (V.language ? "    Next page ->    " : " Página seguinte -> ");
	if (20 + 20 * V.page < V.clients_data.size()) // assessing if the list has a page to move to
	{
		ACTIVE_BUTTONS.push_back(1);
	}
	// setting for the button positon that allows the user to return to the previews menu
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

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 1}); //settings for the title of the page interface
	std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

	// settings for the box that house the date of all the clients in the txt file
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 3});
	std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 4});
	std::cout << "|" << "     ID     " << "|" << (V.language ? "                  Name of clients                 " : "                 Nome dos clientes                ") << "|" << (V.language ? "    Date    " : "    Data    ") << "|" << (V.language ? " Value spent(€) " : " Valor gasto(€) ") << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
	std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
	
	for (unsigned i = 0; i < 20; ++i, ++h) // using this for cycle the number of clients shown is restricted to 20 per page
	{
		if (i + 20 * V.page < V.clients_data.size())
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, h});
			std::cout << "| " << V.clients_data[i + 20 * V.page].Clients::GetId();
			SetConsoleCursorPosition(V.OUT_HANDLE, {18, h});
			std::cout << "| " << V.clients_data[i + 20 * V.page].Clients::GetName();
			SetConsoleCursorPosition(V.OUT_HANDLE, {69, h});
			std::cout << "| " << V.clients_data[i + 20 * V.page].Clients::GetDate();
			SetConsoleCursorPosition(V.OUT_HANDLE, {82, h});
			std::cout << "| " << V.clients_data[i + 20 * V.page].Clients::GetValue() << "€";
			SetConsoleCursorPosition(V.OUT_HANDLE, {99, h});
			std::cout << "|";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, ++h});
			std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
		}
		else break;
	}

	if (V.page > 0) // retricts the appearence of the button "Previous Page"
	{
		Sleep(200); // pauses the screen for 0,2 seconds

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

	if (20 + 20 * V.page < V.clients_data.size()) //retricts the appearence of the button "Next Page"
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

	for (unsigned i = 0; i < 3; ++i) // to delete any text that might appear in a box
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	switch (option) // switch to change page when the user presses the specifc button
	{
		case 0: // goes down a page
			--V.page;
			break;
		case 1: // goes up a page
			++V.page;
			break;
		case 2: //return to previews menu
			return false;
	}
	return true;
}

bool ViewSpecificClient(Variables &V) // allows the user to search for client by his ID
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	unsigned n = -1;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	//settings for the positon of the box where the user will input the ID he wishes to search
	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 6;
	BUTTONS[0].Right = 17;
	BUTTONS[0].Bottom = 6;
	BUTTONS[0].TextLines = 0;
	ACTIVE_BUTTONS.push_back(0);

	//settings for the positon of the button to reset the page and allow the user to make a new search without changing menu
	BUTTONS[1].Left = 105;
	BUTTONS[1].Top = 4;
	BUTTONS[1].Right = 124;
	BUTTONS[1].Bottom = 6;
	BUTTONS[1].TextLines = 1;
	BUTTONS[1].TextPos = new COORD[1];
	BUTTONS[1].TextPos[0] = {105, 5};
	BUTTONS[1].Text = new std::string[1];
	BUTTONS[1].Text[0] = (V.language ? "     New search     " : "    Nova procura    ");

	//settings for the positon of the button that allows the user to retun to the previous menu
	BUTTONS[2].Left = 105;
	BUTTONS[2].Top = 10;
	BUTTONS[2].Right = 124;
	BUTTONS[2].Bottom = 12;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {105, 11};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	// setting the title of the menu
	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 1});
	std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

	//setting the title above the box to input the ID to search for
	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), 3});
	std::cout << (V.language ? "Search" : "Procurar");
	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), 4});
	std::cout << (V.language ? "by ID" : "por ID");

	// configuration of the ID input box
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
	std::cout << "o------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
	std::cout << "|            |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 7});
	std::cout << "o------------o";

	Sleep(200);

	//configuration of the box that involves the return button
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 9});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 10});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 11});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 12});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 13});
	std::cout << "o--------------------o";

	while (true)
	{
		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), 3});
		std::cout << (V.language ? "Search" : "Procurar");
		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), 4});
		std::cout << (V.language ? "by ID" : "por ID");

		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
		std::cout << "|            |";

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);

		if (option == 0) // analysing the input introduced by the user
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {7, 6});
			V.OUT_BUFFER.dwCursorPosition = {7, 6};
			V.input = Input(V, 10);

			try
			{
				if (V.input == "") //if the input is empty nothing will happen and the user can try to insert something again
					continue;
				
				// in case the user introduces a charecter that isn't allow 
				if (std::to_string(std::stol(V.input)).size() < V.input.size() || std::stol(V.input) < 0 || std::stol(V.input) > std::numeric_limits<int>::max())
					throw std::exception();
			}
			catch (...)// the text above the box will be replaced by an error message and the previous input will be deleted
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

			for (unsigned i = 0; i < V.clients_data.size(); ++i) // cycles that searches for the specifc client ID
			{
				if (V.clients_data[i].GetId() == std::stoi(V.input)) 
				{
					n = i; //saves the position of the searched client
					break;
				}
			}

			if (n == -1) // in case the client ID is not found it will inform the user and then delete said message
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

	if (n != -1) // meaning the client was found
	{
		ACTIVE_BUTTONS.front() = 1; // activates the "New Search Button"

		//defines the boxes that surronds the found client information
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

	for (unsigned i = 1; i < 3; ++i) // deletes the inputs on the boxes of the buttons
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	if (option == 2) return false;
	return true;
}

bool EditClients(Variables &V) // function to edit the client name by given an specific ID
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	unsigned n = -1;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[4];
	
	//settings for the postion of all the diferent buttons presented on screen
	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 6;
	BUTTONS[0].Right = 17;
	BUTTONS[0].Bottom = 6;
	BUTTONS[0].TextLines = 0;
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 19;
	BUTTONS[1].Top = 6;
	BUTTONS[1].Right = 68;
	BUTTONS[1].Bottom = 6;
	BUTTONS[1].TextLines = 0;

	BUTTONS[2].Left = 105;
	BUTTONS[2].Top = 4;
	BUTTONS[2].Right = 124;
	BUTTONS[2].Bottom = 6;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {105, 5};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "     New search     " : "    Nova procura    ");

	BUTTONS[3].Left = 105;
	BUTTONS[3].Top = 10;
	BUTTONS[3].Right = 124;
	BUTTONS[3].Bottom = 12;
	BUTTONS[3].TextLines = 1;
	BUTTONS[3].TextPos = new COORD[1];
	BUTTONS[3].TextPos[0] = {105, 11};
	BUTTONS[3].Text = new std::string[1];
	BUTTONS[3].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(3);

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 1});
	std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

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

	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 9});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 10});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 11});
	std::cout << "|" << BUTTONS[3].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 12});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 13});
	std::cout << "o--------------------o";

	//==============================================================
	// same code used to search for a specific client by ID
	//==============================================================
	while (true)
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

			try
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
					n = i;
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

	//==============================================================

	if (n != -1) // the client was found, his information is displayed on screen and the user is allowed to edit the name
	{
		//settings to display de found client info
		ACTIVE_BUTTONS.resize(0);
		for (unsigned i = 1; i < 4; ++i)
		{
			ACTIVE_BUTTONS.push_back(i);
		}

		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 3});
		std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 4});
		std::cout << "|" << "     ID     " << "|" << (V.language ? "                  Insert new name                 " : "                 Inserir novo nome                ") << "|" << (V.language ? "    Date    " : "    Data    ") << "|" << (V.language ? " Value spent(€) " : " Valor gasto(€) ") << "|";
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
			SetConsoleCursorPosition(V.OUT_HANDLE, {18, 6});
			std::cout << "| " << V.clients_data[n].Clients::GetName();

			option = Event(V, BUTTONS, ACTIVE_BUTTONS);

			if (option == 1)
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {18, 6});
				std::cout << "|                                                  |";
				SetConsoleCursorPosition(V.OUT_HANDLE, {20, 6});
				V.OUT_BUFFER.dwCursorPosition = {20, 6};
				V.input = Input(V, 48);

				if (V.input == "") continue; 

				V.clients_data[n].SetName(V.input); // saves the new name with the SetName function of the client class

				std::stable_sort(V.clients_data.begin(), V.clients_data.end(), Sort());

				ClearScreen(V);

				SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 1});
				std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

				// shows a the user a message indicating the sucess of the edit
				SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 35 : 34), 3});
				std::cout << (V.language ? "Client successfully edited!" : "Cliente editado com sucesso!");

				Sleep(2000);
			}
			break;
		}
	}

	for (unsigned i = 2; i < 4; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	if (option == 3) return false;
	return true;
}

bool AddClients(Variables &V) // function that allows the user to add a new client to the list
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	unsigned id = 0;
	std::string name;
	std::string date;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];
	
	//setting for the buttons and general display
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

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 1});
	std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

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
	std::cout << (V.language ? "Date" : "Data");

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 11});
	std::cout << "o------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 12});
	std::cout << "|            |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 13});
	std::cout << "o------------o";

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
		std::cout << (V.language ? "Date" : "Data");

		for (unsigned i = 0; i < 3; ++i)
		{
			if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 1)
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {5, 12});
				std::cout << "|            |";
			}
		}

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);

		switch (option)
		{
			case 0:// saves the name of the new client
				SetConsoleCursorPosition(V.OUT_HANDLE, {7, 6});
				V.OUT_BUFFER.dwCursorPosition = {7, 6};
				V.input = Input(V, 48);

				if (V.input == "") continue;

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
			case 1: //saves the date in which the client was added
				SetConsoleCursorPosition(V.OUT_HANDLE, {7, 12});
				V.OUT_BUFFER.dwCursorPosition = {7, 12};
				V.input = Input(V, 10);

				switch (ValidDate(V)) //call a function that will validate the date format
				{
					case 0: // date was correctly inputed
						date = V.input;
						break;
					case 1: //date was wrong
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Insert" : "Inserir").length(), {6, 9}, V.FOOBAR);
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Date" : "Data").length(), {6, 10}, V.FOOBAR);

						SetConsoleCursorPosition(V.OUT_HANDLE, {6, 9});
						std::cerr << (V.language ? "Invalid " : "Entrada ");
						SetConsoleCursorPosition(V.OUT_HANDLE, {6, 10});
						std::cerr << (V.language ? "input!" : "inválida!");

						Sleep(1000);

						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {6, 9}, V.FOOBAR);
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {6, 10}, V.FOOBAR);
					case 2:
						continue;
				}

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

	if (option != 2) // searches for existing client ID in the client file and the transaction file and gives the added client the bigger number found + 1
	{
		if (V.clients_data.size() > 0)
		{
			std::stable_sort(V.clients_data.begin(), V.clients_data.end(), Compare());

			id = V.clients_data.back().GetId();

			std::stable_sort(V.clients_data.begin(), V.clients_data.end(), Sort());
		}

		++id;

		for (unsigned i = 0; i < V.transactions_data.size(); ++i)
		{
			if (V.transactions_data[i].GetId() == id)
			{
				++id;
				i = -1;
			}
		}

		V.clients_data.push_back(Clients::Clients(id, name, date)); //saves the new date in the vector
		std::stable_sort(V.clients_data.begin(), V.clients_data.end(), Sort());

		ClearScreen(V);

		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 1});
		std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

		//shows user success message
		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 36 : 33), 3});
		std::cout << (V.language ? "Client successfully added!" : "Cliente adicionado com sucesso!");

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

bool RemoveClients(Variables &V)//function that allows the user to  remove a specif client by inputting an ID
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	unsigned n = -1;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[4];

	//setting for the buttons displayed on screen
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
	BUTTONS[1].Text[0] = (V.language ? "    Remove client   " : "   Remover cliente  ");

	BUTTONS[2].Left = 105;
	BUTTONS[2].Top = 10;
	BUTTONS[2].Right = 124;
	BUTTONS[2].Bottom = 12;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {105, 11};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "     New search     " : "    Nova procura    ");

	BUTTONS[3].Left = 105;
	BUTTONS[3].Top = 16;
	BUTTONS[3].Right = 124;
	BUTTONS[3].Bottom = 18;
	BUTTONS[3].TextLines = 1;
	BUTTONS[3].TextPos = new COORD[1];
	BUTTONS[3].TextPos[0] = {105, 17};
	BUTTONS[3].Text = new std::string[1];
	BUTTONS[3].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(3);

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 1});
	std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

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

	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 15});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 16});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 17});
	std::cout << "|" << BUTTONS[3].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 19});
	std::cout << "o--------------------o";

	while (true) // code similiar to the function to search a client by a specific ID
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

			try
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
					n = i;
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

	if (n != -1) // shows data on screen if client is found
	{
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 3});
		std::cout << "o" << "------------" << "o" << "--------------------------------------------------" << "o" << "------------" << "o" << "----------------" << "o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 4});
		std::cout << "|" << "     ID     " << "|" << (V.language ? "                  Name of clients                 " : "                  Nome do cliente                 ") << "|" << (V.language ? "    Date    " : "    Data    ") << "|" << (V.language ? " Value spent(€) " : " Valor gasto(€) ") << "|";
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

		ACTIVE_BUTTONS.resize(0);
		for (unsigned i = 1; i < 4; ++i)
		{
			ACTIVE_BUTTONS.push_back(i);
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

		Sleep(200);

		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 9});
		std::cout << "o--------------------o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 10});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 11});
		std::cout << "|" << BUTTONS[2].Text[0] << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 12});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 13});
		std::cout << "o--------------------o";

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);

		if (option == 1) // if the remove client button is pressed
		{
			ClearScreen(V);

			SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 1});
			std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

			//shows a success message
			SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 35 : 34), 3});
			std::cout << (V.language ? "Client successfully removed!" : "Cliente removido com sucesso!");

			V.clients_data.erase(V.clients_data.begin() + n); // deletes the client from the vector

			Sleep(2000);
		}
	}

	for (unsigned i = 1; i < 4; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	if (option == 3) return false;
	return true;
}

//====================================================================================================
// ========== End of File ==========
//====================================================================================================