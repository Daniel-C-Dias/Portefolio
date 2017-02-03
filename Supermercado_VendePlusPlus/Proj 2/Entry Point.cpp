//==================================================================================================
// ===== Project 2 - Vende++ =====
//==================================================================================================
/*
	Authors: Daniel Dias
			 Ricardo Pereira
	Creation: 30/04/2016
	Version: 1.00
*/
//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Interface.hpp"

//====================================================================================================
// ========== Entry Point ==========
//====================================================================================================

int main()
{
	Variables V; // Will be used across all Interface-named cpp files, carrying the most important variables

	// ========== Variables Settings ==========

	
	V.IN_HANDLE = GetStdHandle(STD_INPUT_HANDLE);
	V.OUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	V.IN_BUFFER = new INPUT_RECORD[1]; // For interaction with mouse and keyboard
	GetConsoleScreenBufferInfo(V.OUT_HANDLE, &V.OUT_BUFFER); // Screen buffer (output) info
	GetConsoleCursorInfo(V.OUT_HANDLE, &V.CURSOR_INFO); // Cursor info
	V.OUT_BUFFER_SIZE = V.OUT_BUFFER.dwSize.X * V.OUT_BUFFER.dwSize.Y; // Get size of screen buffer
	V.FOOBAR = new DWORD[1]; // Foobar is foobar :P (No practical purpose)

	V.input = ""; // Used for any and all user keyboard (only chars, not control keys) input, when prompted
	V.page = 0; // Used for viewing clients and transactions functions

	// ========== Output Settings ==========

	SetConsoleTitle("Vende++"); // This becomes somewhat pointless (more than it already is) if fullscreen is on

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); // Not a console function, instead changes the console's window
	
		// ========== Fullscreen Mode ==========
	    //
	    // Type backslash to activate it --> 
	    /*
	    SetConsoleDisplayMode(V.OUT_HANDLE, CONSOLE_FULLSCREEN_MODE, 0);
	    // */
	    // ========== *************** ==========

	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	// Code page that supports Western Europe special characters
	
	V.CURSOR_INFO.dwSize = 10; // Set cursor size (to something more... elegant)
	V.CURSOR_INFO.bVisible = false; // Set cursor visibility (only set to true when Input() function is called)
	SetConsoleCursorInfo(V.OUT_HANDLE, &V.CURSOR_INFO); // Set cursor info
	V.OUT_BUFFER.wAttributes &= 0xFF00; // Reset screen buffer color attributes
	V.OUT_BUFFER.wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY; // Set character color attributes
	V.EVENT_OUT_BUFFER = V.OUT_BUFFER;
	V.EVENT_OUT_BUFFER.wAttributes |= BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY; // Set screen buffer color attributes (only used in Event() function)
	FillConsoleOutputAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes, V.OUT_BUFFER_SIZE, {0, 0}, V.FOOBAR); // Set screen buffer info
	SetConsoleTextAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes); // Set character info

	std::cout << std::fixed << std::showpoint; // The fractional part of double-type values will always be represented, even if it's 0
	std::cout.precision(2); // The fractional part of double-type values will always be represented with 2 digits
	// (Yay, no #include <iomanip>)

	// ========== ****** ******** ==========

	unsigned option;
	std::vector<unsigned> ACTIVE_BUTTONS; // Contains the active buttons position in the array of BUTTONs
	BUTTON * BUTTONS = new BUTTON[3];

	// Structure that defines a BUTTON position in the screen buffer, text, and state
	// These appear at the start of all the functions in Interface-named cpps
	BUTTONS[0].Left = 55;
	BUTTONS[0].Top = 26;
	BUTTONS[0].Right = 69;
	BUTTONS[0].Bottom = 28;
	BUTTONS[0].TextLines = 1;
	BUTTONS[0].TextPos = new COORD[1];
	BUTTONS[0].TextPos[0] = {55, 27};
	BUTTONS[0].Text = new std::string[1];
	BUTTONS[0].Text[0] = "   Português   ";
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 90;
	BUTTONS[1].Top = 26;
	BUTTONS[1].Right = 104;
	BUTTONS[1].Bottom = 28;
	BUTTONS[1].TextLines = 1;
	BUTTONS[1].TextPos = new COORD[1];
	BUTTONS[1].TextPos[0] = {90, 27};
	BUTTONS[1].Text = new std::string[1];
	BUTTONS[1].Text[0] = "    English    ";
	ACTIVE_BUTTONS.push_back(1);

	std::cout << "           _____                    _____                    _____                    _____                  _____" << std::endl;
	std::cout << "          /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                /\\    \\" << std::endl;
	std::cout << "         /  \\____\\                /  \\    \\                /  \\____\\                /  \\    \\              /  \\    \\" << std::endl;
	std::cout << "        /   /    /               /    \\    \\              /   |    |               /    \\    \\            /    \\    \\" << std::endl;
	std::cout << "       /   /    /               /      \\    \\            /    |    |              /      \\    \\          /      \\    \\         _____   _____     _____   _____" << std::endl;
	std::cout << "      /   /    /               /   /\\   \\    \\          /     |    |             /   /\\   \\    \\        /   /\\   \\    \\       /\\    \\ /\\    \\   /\\    \\ /\\    \\" << std::endl;
	std::cout << "     /   /____/               /   /__\\   \\    \\        /   /  |    |            /   /  \\   \\    \\      /   /__\\   \\    \\     /  \\    /  \\____\\ /  \\    /  \\____\\" << std::endl;
	std::cout << "     |  |    |               /    \\   \\   \\    \\      /   /|  |    |           /   /    \\   \\    \\    /    \\   \\   \\    \\    \\   \\  /   /    / \\   \\  /   /    /" << std::endl;
	std::cout << "     |  |    |     _____    /      \\   \\   \\    \\    /   / |  |    | _____    /   /    / \\   \\____\\  /      \\   \\   \\    \\    \\   \\/   /    /   \\   \\/   /    /" << std::endl;
	std::cout << "     |  |    |    /\\    \\  /   /\\   \\   \\   \\    \\  /   /  |  |    |/\\    \\  /   /    /   \\  |    | /   /\\   \\   \\   \\    \\    \\      /    /     \\      /    /" << std::endl;
	std::cout << "     |  |    |   /  \\____\\/   /__\\   \\   \\   \\____\\/   /   |  |    /  \\____\\/   /____/    |  |    |/   /__\\   \\   \\   \\____\\    \\    /____/       \\    /____/" << std::endl;
	std::cout << "     |  |    |  /   /    /\\   \\   \\   \\   \\  /    /\\  /    |  |   /   /    /\\   \\    \\    |  |    |\\   \\   \\   \\   \\  /    /    /    \\    \\       /    \\    \\" << std::endl;
	std::cout << "     |  |    | /   /    /  \\   \\   \\   \\   \\/____/  \\/____/|  |  /   /    /  \\   \\    \\   /  |____| \\   \\   \\   \\   \\/____/    /      \\    \\     /      \\    \\" << std::endl;
	std::cout << "     |  |____|/   /    /    \\   \\   \\   \\    \\             |  | /   /    /    \\   \\    \\ /   /    /  \\   \\   \\   \\    \\       /   /\\   \\    \\   /   /\\   \\    \\" << std::endl;
	std::cout << "     |           /    /      \\   \\   \\   \\____\\            |  |/   /    /      \\   \\    /   /    /    \\   \\   \\   \\____\\     /   /  \\   \\____\\ /   /  \\   \\____\\" << std::endl;
	std::cout << "      \\_________/____/        \\   \\   \\  /    /            |  /   /    /        \\   \\__/   /    /      \\   \\   \\  /    /     \\  /    \\  /    / \\  /    \\  /    /" << std::endl;
	std::cout << "                               \\   \\   \\/____/             |     /    /          \\        /    /        \\   \\   \\/____/       \\/____/ \\/____/   \\/____/ \\/____/" << std::endl;
	std::cout << "                                \\   \\    \\                 |    /    /            \\      /    /          \\   \\    \\" << std::endl;
	std::cout << "                                 \\   \\____\\                |   /    /              \\____/____/            \\   \\____\\" << std::endl;
	std::cout << "                                  \\  /    /                \\  /    /                                       \\  /    /" << std::endl;
	std::cout << "                                   \\/____/                  \\/____/                                         \\/____/" << std::endl;

	Sleep(1000);

	// Instruction that defines the position of the cursor
	// These appear before almost all std::cout instructions
	SetConsoleCursorPosition(V.OUT_HANDLE, {50, 23}); 
	std::cout << "Por favor selecione a linguagem / Please select the language";

	// Structure that defines a buttons aspect
	// These may appear in several places, depending on the function, and are typically preceded by a Sleep instruction
	SetConsoleCursorPosition(V.OUT_HANDLE, {54, 25});
	std::cout << "o---------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {54, 26});
	std::cout << "|               |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {54, 27});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {54, 28});
	std::cout << "|               |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {54, 29});
	std::cout << "o---------------o";

	SetConsoleCursorPosition(V.OUT_HANDLE, {89, 25});
	std::cout << "o---------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {89, 26});
	std::cout << "|               |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {89, 27});
	std::cout << "|" << BUTTONS[1].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {89, 28});
	std::cout << "|               |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {89, 29});
	std::cout << "o---------------o";

	V.language = ACTIVE_BUTTONS[Event(V, BUTTONS, ACTIVE_BUTTONS)];

	for (unsigned i = 0; i < 2; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}

	SetConsoleTitleW((V.language ? L"Vende++  //  Smart Market Application" : L"Vende++  //  Aplicação de Supermercado Inteligente"));

	// ========== Files loading ==========

	ClearScreen(V);

	ACTIVE_BUTTONS.resize(0);

	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 6;
	BUTTONS[0].Right = 27;
	BUTTONS[0].Bottom = 6;
	BUTTONS[0].TextLines = 0;
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 40;
	BUTTONS[1].Top = 6;
	BUTTONS[1].Right = 61;
	BUTTONS[1].Bottom = 6;
	BUTTONS[1].TextLines = 0;
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 74;
	BUTTONS[2].Top = 6;
	BUTTONS[2].Right = 95;
	BUTTONS[2].Bottom = 6;
	BUTTONS[2].TextLines = 0;
	ACTIVE_BUTTONS.push_back(2);

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 45 : 41), 1});
	std::cout << (V.language ? "Data Manager" : "Gestor de Informação");

	SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
	std::cout << (V.language ? "Clients" : "Ficheiro");
	SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
	std::cout << (V.language ? "file" : "de clientes");

	SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
	std::cout << (V.language ? "Products" : "Ficheiro");
	SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
	std::cout << (V.language ? "file" : "de produtos");

	SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
	std::cout << (V.language ? "Transactions" : "Ficheiro");
	SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
	std::cout << (V.language ? "file" : "de transações");

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
	std::cout << "o----------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
	std::cout << "|                      |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 7});
	std::cout << "o----------------------o";

	SetConsoleCursorPosition(V.OUT_HANDLE, {39, 5});
	std::cout << "o----------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {39, 6});
	std::cout << "|                      |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {39, 7});
	std::cout << "o----------------------o";

	SetConsoleCursorPosition(V.OUT_HANDLE, {73, 5});
	std::cout << "o----------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {73, 6});
	std::cout << "|                      |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {73, 7});
	std::cout << "o----------------------o";

	while (true)
	{
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
		std::cout << (V.language ? "Clients" : "Ficheiro");
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
		std::cout << (V.language ? "file" : "de clientes");

		SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
		std::cout << (V.language ? "Products" : "Ficheiro");
		SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
		std::cout << (V.language ? "file" : "de produtos");

		SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
		std::cout << (V.language ? "Transactions" : "Ficheiro");
		SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
		std::cout << (V.language ? "file" : "de transações");

		for (unsigned i = 0; i < 3; ++i)
		{
			if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 0) // If button 0 is active
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
				std::cout << "|                      |"; // Reset button
			}

			if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 1) // If button 1 is active
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {39, 6});
				std::cout << "|                      |"; // Reset button
			}

			if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 2) // If button 2 is active
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {73, 6});
				std::cout << "|                      |"; // Reset button
			}
		}

		if (V.clients_file.is_open())
		{
			V.clients_file.close();
		}

		if (V.products_file.is_open())
		{
			V.products_file.close();
		}

		if (V.transactions_file.is_open())
		{
			V.transactions_file.close();
		}

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);

		switch (option) // Sets the position of the cursor
		{
			case 0:
				SetConsoleCursorPosition(V.OUT_HANDLE, {7, 6});
				V.OUT_BUFFER.dwCursorPosition = {7, 6};
				break;
			case 1:
				SetConsoleCursorPosition(V.OUT_HANDLE, {41, 6});
				V.OUT_BUFFER.dwCursorPosition = {41, 6};
				break;
			case 2:
				SetConsoleCursorPosition(V.OUT_HANDLE, {75, 6});
				V.OUT_BUFFER.dwCursorPosition = {75, 6};
				break;
		}
		V.input = Input(V, 16);

		switch (option)
		{
			case 0:
				try
				{
					if (V.input == "") // If string is empty
						continue;
					V.clients_file_name = V.input;
					if (V.clients_file_name.find(".txt") == std::string::npos || V.clients_file_name.find(".txt") != V.clients_file_name.length() - 4) // If file extension isn't written, appends it to the name
					{
						V.clients_file_name += ".txt";
						std::cout << ".txt";
					}
					V.clients_file.open(V.clients_file_name, std::ios::in | std::ios::out);
					if (V.clients_file.is_open()) // Checks for status
					{
						if (V.clients_file.peek() == std::ifstream::traits_type::eof()) // Checks for content
							throw 2;
						if (!CheckClientsFile(V.clients_file)) // Checks for file validity
							throw 3;
						if (!CheckClientsData(V.clients_file, V.clients_file_com, V.clients_data)) // Checks for data validity
							throw 4;
					}
					else throw 1;
				}
				catch (int i) // If checks fail
				{
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Clients" : "Ficheiro").length(), {6, 3}, V.FOOBAR);
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "file" : "de clientes").length(), {6, 4}, V.FOOBAR);

					switch (i)
					{
						case 1:
						case 2:
							while (true)
							{
								switch (i)
								{
									case 1: // If file not open
										SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
										std::cerr << (V.language ? "File not found!" : "Ficheiro não encontrado!");
										SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
										std::cout << (V.language ? "Do you wish to create one?" : "Deseja criar um?");

										break;
									case 2: // If file empty
										SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
										std::cerr << (V.language ? "File is empty!" : "Ficheiro está vazio!");
										SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
										std::cout << (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?");

										break;
								}

								SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
								std::cout << "|                      |";
								SetConsoleCursorPosition(V.OUT_HANDLE, {7, 6});
								V.OUT_BUFFER.dwCursorPosition = {7, 6};
								V.input = Input(V, 1); // Asks for confirmation

								try
								{
									if (V.input == "")
										continue;
									if (tolower(V.input.front()) != (V.language ? 'y' : 's') && tolower(V.input.front()) != 'n')
										throw std::exception();
								}
								catch (...) // Structure that defines output if invalid option, many of these will appear
								{
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "File not found!" : "Ficheiro não encontrado!") : (V.language ? "File is empty!" : "Ficheiro está vazio!")).length(), {6, 3}, V.FOOBAR);
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "Do you wish to create one?" : "Deseja criar um?") : (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?")).length(), {6, 4}, V.FOOBAR);

									SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
									std::cerr << (V.language ? "Invalid " : "Entrada ");
									SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
									std::cerr << (V.language ? "input!" : "inválida!");

									Sleep(1000);

									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {6, 3}, V.FOOBAR);
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {6, 4}, V.FOOBAR);

									continue;
								}

								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "File not found!" : "Ficheiro não encontrado!") : (V.language ? "File is empty!" : "Ficheiro está vazio!")).length(), {6, 3}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "Do you wish to create one?" : "Deseja criar um?") : (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?")).length(), {6, 4}, V.FOOBAR);

								if (tolower(V.input.front()) == (V.language ? 'y' : 's')) // If affirmative
								{
									SetConsoleCursorPosition(V.OUT_HANDLE, {7, 6});
									std::cout << V.clients_file_name;

									CreateClientsFile(V.clients_file, V.clients_file_name); // Creates file and formats it
									CheckClientsData(V.clients_file, V.clients_file_com, V.clients_data); // Copies file into appropriate string
								}

								break;
							}

							if (tolower(V.input.front()) == 'n') continue; // If negative
							break;
						case 3:
							SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
							std::cerr << (V.language ? "File with " : "Ficheiro com ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
							std::cerr << (V.language ? "wrong format!" : "formato errado!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "File with " : "Ficheiro com ").length(), {6, 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "wrong format!" : "formato errado!").length(), {6, 4}, V.FOOBAR);

							continue;
						case 4:
							SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
							std::cerr << (V.language ? "Data possibly " : "Informação possivelmente ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
							std::cerr << (V.language ? "corrupted!" : "corrompida!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Data possibly " : "Informação possivelmente ").length(), {6, 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "corrupted!" : "corrompida!").length(), {6, 4}, V.FOOBAR);

							continue;
					}
				}

				if (V.clients_data.size() > 0)
				{
					if (!ReadClientsData(V.clients_file, V.clients_data)) // Checks for data validity
					{
						V.clients_data.resize(0);

						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Clients" : "Ficheiro").length(), {6, 3}, V.FOOBAR);
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "file" : "de clientes").length(), {6, 4}, V.FOOBAR);

						SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
						std::cerr << (V.language ? "Data " : "Informação ");
						SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
						std::cerr << (V.language ? "corrupted!" : "corrompida!");

						Sleep(1000);

						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Data " : "Informação ").length(), {6, 3}, V.FOOBAR);
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "corrupted!" : "corrompida!").length(), {6, 4}, V.FOOBAR);

						continue;
					}

					std::stable_sort(V.clients_data.begin(), V.clients_data.end(), Sort());
				}

				V.clients_file.close();

				for (unsigned i = 0; i < 3; ++i) // Deactivates button if successful
				{
					if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 0)
					{
						ACTIVE_BUTTONS.erase(ACTIVE_BUTTONS.begin() + i);
						break;
					}
				}

				break;
			case 1: // Same as clients file
				try
				{
					if (V.input == "")
						continue;
					V.products_file_name = V.input;
					if (V.products_file_name.find(".txt") == std::string::npos || V.products_file_name.find(".txt") != V.products_file_name.length() - 4)
					{
						V.products_file_name += ".txt";
						std::cout << ".txt";
					}
					V.products_file.open(V.products_file_name, std::ios::in | std::ios::out);
					if (V.products_file.is_open())
					{
						if (V.products_file.peek() == std::ifstream::traits_type::eof())
							throw 2;
						if (!CheckProductsFile(V.products_file))
							throw 3;
						if (!CheckProductsData(V.products_file, V.products_file_com, V.products_data))
							throw 4;
					}
					else throw 1;
				}
				catch (int i)
				{
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Products" : "Ficheiro").length(), {40, 3}, V.FOOBAR);
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "file" : "de produtos").length(), {40, 4}, V.FOOBAR);

					switch (i)
					{
						case 1:
						case 2:
							while (true)
							{
								switch (i)
								{
									case 1:
										SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
										std::cerr << (V.language ? "File not found!" : "Ficheiro não encontrado!");
										SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
										std::cout << (V.language ? "Do you wish to create one?" : "Deseja criar um?");

										break;
									case 2:
										SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
										std::cerr << (V.language ? "File is empty!" : "Ficheiro está vazio!");
										SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
										std::cout << (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?");

										break;
								}

								SetConsoleCursorPosition(V.OUT_HANDLE, {39, 6});
								std::cout << "|                      |";
								SetConsoleCursorPosition(V.OUT_HANDLE, {41, 6});
								V.OUT_BUFFER.dwCursorPosition = {41, 6};
								V.input = Input(V, 1);

								try
								{
									if (V.input == "")
										continue;
									if (V.input.length() > 1 || (tolower(V.input.front()) != (V.language ? 'y' : 's') && tolower(V.input.front()) != 'n'))
										throw std::exception();
								}
								catch (...)
								{
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "File not found!" : "Ficheiro não encontrado!") : (V.language ? "File is empty!" : "Ficheiro está vazio!")).length(), {40, 3}, V.FOOBAR);
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "Do you wish to create one?" : "Deseja criar um?") : (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?")).length(), {40, 4}, V.FOOBAR);

									SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
									std::cerr << (V.language ? "Invalid " : "Entrada ");
									SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
									std::cerr << (V.language ? "input!" : "inválida!");

									Sleep(1000);

									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {40, 3}, V.FOOBAR);
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {40, 4}, V.FOOBAR);

									continue;
								}

								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "File not found!" : "Ficheiro não encontrado!") : (V.language ? "File is empty!" : "Ficheiro está vazio!")).length(), {40, 3}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "Do you wish to create one?" : "Deseja criar um?") : (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?")).length(), {40, 4}, V.FOOBAR);

								if (tolower(V.input.front()) == (V.language ? 'y' : 's'))
								{
									SetConsoleCursorPosition(V.OUT_HANDLE, {41, 6});
									std::cout << V.products_file_name;

									CreateProductsFile(V.products_file, V.products_file_name);
									CheckProductsData(V.products_file, V.products_file_com, V.products_data);
								}

								break;
							}

							if (tolower(V.input.front()) == 'n') continue;
							break;
						case 3:
							SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
							std::cerr << (V.language ? "File with " : "Ficheiro com ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
							std::cerr << (V.language ? "wrong format!" : "formato errado!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "File with " : "Ficheiro com ").length(), {40, 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "wrong format!" : "formato errado!").length(), {40, 4}, V.FOOBAR);

							continue;
						case 4:
							SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
							std::cerr << (V.language ? "Data possibly " : "Informação possivelmente ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
							std::cerr << (V.language ? "corrupted!" : "corrompida!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Data possibly " : "Informação possivelmente ").length(), {40, 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "corrupted!" : "corrompida!").length(), {40, 4}, V.FOOBAR);

							continue;
					}
				}

				if (V.products_data.size() > 0)
				{
					if (!ReadProductsData(V.products_file, V.products_data))
					{
						V.products_data.resize(0);

						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Products" : "Ficheiro").length(), {40, 3}, V.FOOBAR);
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "file" : "de produtos").length(), {40, 4}, V.FOOBAR);

						SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
						std::cerr << (V.language ? "Data " : "Informação ");
						SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
						std::cerr << (V.language ? "corrupted!" : "corrompida!");

						Sleep(1000);

						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Data " : "Informação ").length(), {40, 3}, V.FOOBAR);
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "corrupted!" : "corrompida!").length(), {40, 4}, V.FOOBAR);

						continue;
					}
				}
				
				V.products_file.close();

				for (unsigned i = 0; i < 3; ++i)
				{
					if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 1)
					{
						ACTIVE_BUTTONS.erase(ACTIVE_BUTTONS.begin() + i);
						break;
					}
				}

				break;
			case 2: // Same as clients file
				try
				{
					if (V.input == "")
						continue;
					V.transactions_file_name = V.input;
					if (V.transactions_file_name.find(".txt") == std::string::npos || V.transactions_file_name.find(".txt") != V.transactions_file_name.length() - 4)
					{
						V.transactions_file_name += ".txt";
						std::cout << ".txt";
					}
					V.transactions_file.open(V.transactions_file_name, std::ios::in | std::ios::out);
					if (V.transactions_file.is_open())
					{
						if (V.transactions_file.peek() == std::ifstream::traits_type::eof())
							throw 2;
						if (!CheckTransactionsFile(V.transactions_file))
							throw 3;
						if (!CheckTransactionsData(V.transactions_file, V.transactions_file_com, V.transactions_data))
							throw 4;
					}
					else throw 1;
				}
				catch (int i)
				{
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Transactions" : "Ficheiro").length(), {74, 3}, V.FOOBAR);
					FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "file" : "de transações").length(), {74, 4}, V.FOOBAR);

					switch (i)
					{
						case 1:
						case 2:
							while (true)
							{
								switch (i)
								{
									case 1:
										SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
										std::cerr << (V.language ? "File not found!" : "Ficheiro não encontrado!");
										SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
										std::cout << (V.language ? "Do you wish to create one?" : "Deseja criar um?");

										break;
									case 2:
										SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
										std::cerr << (V.language ? "File is empty!" : "Ficheiro está vazio!");
										SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
										std::cout << (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?");

										break;
								}

								SetConsoleCursorPosition(V.OUT_HANDLE, {73, 6});
								std::cout << "|                      |";
								SetConsoleCursorPosition(V.OUT_HANDLE, {75, 6});
								V.OUT_BUFFER.dwCursorPosition = {75, 6};
								V.input = Input(V, 1);

								try
								{
									if (V.input == "")
										continue;
									if (V.input.length() > 1 || (tolower(V.input.front()) != (V.language ? 'y' : 's') && tolower(V.input.front()) != 'n'))
										throw std::exception();
								}
								catch (...)
								{
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "File not found!" : "Ficheiro não encontrado!") : (V.language ? "File is empty!" : "Ficheiro está vazio!")).length(), {74, 3}, V.FOOBAR);
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "Do you wish to create one?" : "Deseja criar um?") : (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?")).length(), {74, 4}, V.FOOBAR);

									SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
									std::cerr << (V.language ? "Invalid " : "Entrada ");
									SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
									std::cerr << (V.language ? "input!" : "inválida!");

									Sleep(1000);

									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {74, 3}, V.FOOBAR);
									FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {74, 4}, V.FOOBAR);

									continue;
								}

								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "File not found!" : "Ficheiro não encontrado!") : (V.language ? "File is empty!" : "Ficheiro está vazio!")).length(), {74, 3}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(i == 1 ? (V.language ? "Do you wish to create one?" : "Deseja criar um?") : (V.language ? "Do you wish to format it?" : "Deseja formatá-lo?")).length(), {74, 4}, V.FOOBAR);

								if (tolower(V.input.front()) == (V.language ? 'y' : 's'))
								{
									SetConsoleCursorPosition(V.OUT_HANDLE, {75, 6});
									std::cout << V.transactions_file_name;

									CreateTransactionsFile(V.transactions_file, V.transactions_file_name);
									CheckTransactionsData(V.transactions_file, V.transactions_file_com, V.transactions_data);
								}
								break;
							}

							if (tolower(V.input.front()) == 'n') continue;
							break;
						case 3:
							SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
							std::cerr << (V.language ? "File with " : "Ficheiro com ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
							std::cerr << (V.language ? "wrong format!" : "formato errado!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "File with " : "Ficheiro com ").length(), {74, 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "wrong format!" : "formato errado!").length(), {74, 4}, V.FOOBAR);

							continue;
						case 4:
							SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
							std::cerr << (V.language ? "Data possibly " : "Informação possivelmente ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
							std::cerr << (V.language ? "corrupted!" : "corrompida!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Data possibly " : "Informação possivelmente ").length(), {74, 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "corrupted!" : "corrompida!").length(), {74, 4}, V.FOOBAR);

							continue;
					}
				}

				if (V.transactions_data.size() > 0)
				{
					if (!ReadTransactionsData(V.transactions_file, V.transactions_data))
					{
						V.transactions_file.close();
						V.transactions_data.resize(0);

						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Transactions" : "Ficheiro").length(), {74, 3}, V.FOOBAR);
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "file" : "de transações").length(), {74, 4}, V.FOOBAR);

						SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
						std::cerr << (V.language ? "Data " : "Informação ");
						SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
						std::cerr << (V.language ? "corrupted!" : "corrompida!");

						Sleep(1000);

						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Data " : "Informação ").length(), {74, 3}, V.FOOBAR);
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "corrupted!" : "corrompida!").length(), {74, 4}, V.FOOBAR);

						continue;
					}

					std::stable_sort(V.transactions_data.begin(), V.transactions_data.end(), Sort());
				}

				V.transactions_file.close();

				for (unsigned i = 0; i < 3; ++i)
				{
					if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 2)
					{
						ACTIVE_BUTTONS.erase(ACTIVE_BUTTONS.begin() + i);
						break;
					}
				}
				break;
		}

		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
		std::cout << (V.language ? "Clients" : "Ficheiro");
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
		std::cout << (V.language ? "file" : "de clientes");

		SetConsoleCursorPosition(V.OUT_HANDLE, {40, 3});
		std::cout << (V.language ? "Products" : "Ficheiro");
		SetConsoleCursorPosition(V.OUT_HANDLE, {40, 4});
		std::cout << (V.language ? "file" : "de produtos");

		SetConsoleCursorPosition(V.OUT_HANDLE, {74, 3});
		std::cout << (V.language ? "Transactions" : "Ficheiro");
		SetConsoleCursorPosition(V.OUT_HANDLE, {74, 4});
		std::cout << (V.language ? "file" : "de transações");

		if (ACTIVE_BUTTONS.size() > 0) continue;
		break;
	}

	Sleep(1000);

	// ========== ***** ******* ==========

	delete[] BUTTONS;

	while (Interface(V)) // Definition in Interface.cpp
		continue;

	delete[] V.FOOBAR;
	delete[] V.IN_BUFFER;

	WriteClientsData(V.clients_file, V.clients_file_com, V.clients_file_name, V.clients_data);
	WriteProductsData(V.products_file, V.products_file_com, V.products_file_name, V.products_data);
	WriteTransactionsData(V.transactions_file, V.transactions_file_com, V.transactions_file_name, V.transactions_data); // Saves all changes made (clients, products, transactions) to the files

	return 0;
}

//====================================================================================================
// ========== Notes ==========
//====================================================================================================
/*
	The console must use the "Consolas" font (or any monosized font that supports characters from code
		page Windows-1252)
	The console must have quick-insert mode disabled (program must be restarted when disabled)
	We recommend using a somewhat big screen buffer size

	On another note, all the functions in the Interface-named cpp files are based and depend on the
		Clients, Products and Transactions implementations, even though these are fully independent
*/
//====================================================================================================
// ========== End of File ==========
//====================================================================================================