//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Interface.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

bool ViewAllTransactions(Variables &V) //function that allows the user to view all of the transaction saves on the transaction txt file
{                                      // similar to the ViewAllClients function
	ClearScreen(V);
	V.input = "";

	unsigned option;
	SHORT h = 6;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	//settings for the buttons to be displayed on screen
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
	if (20 + 20 * V.page < V.transactions_data.size())
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

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 38 : 38), 1});
	std::cout << (V.language ? "Transactions Manager" : "Gestor de Transações");

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 3});
	std::cout << "o" << "------------" << "o" << "------------" << "o" << "-------------------------------------------------------------------" << "o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 4});
	std::cout << "|" << "     ID     " << "|" << (V.language ? "    Date    " : "    Data    ") << "|" << (V.language ? "                         List of purchases                         " : "                          Lista de compras                         ") << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
	std::cout << "o" << "------------" << "o" << "------------" << "o" << "-------------------------------------------------------------------" << "o";
	
	for (unsigned i = 0; i < 20; ++i, ++h)//only 20 transaction will be displayed on screen at a time
	{
		if (i + 20 * V.page < V.transactions_data.size())
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, h});
			std::cout << "| " << V.transactions_data[i + 20 * V.page].Transactions::GetId();
			SetConsoleCursorPosition(V.OUT_HANDLE, {18, h});
			std::cout << "| " << V.transactions_data[i + 20 * V.page].Transactions::GetDate();
			SetConsoleCursorPosition(V.OUT_HANDLE, {31, h});
			std::cout << "| ";
			for (unsigned j = 0, k = 0; j < V.transactions_data[i + 20 * V.page].Transactions::GetPurchases().size(); ++j)
			{
				k += V.transactions_data[i + 20 * V.page].Transactions::GetPurchases()[j].length() + 1;
				if (k <= 65)
				{
					std::cout << V.transactions_data[i + 20 * V.page].Transactions::GetPurchases()[j];
				}
				else
				{
					SetConsoleCursorPosition(V.OUT_HANDLE, {99, h});
					std::cout << "|";
					SetConsoleCursorPosition(V.OUT_HANDLE, {5, ++h});
					std::cout << "|" << "            " << "|" << "            " << "| " << V.transactions_data[i + 20 * V.page].Transactions::GetPurchases()[j];
					k = V.transactions_data[i + 20 * V.page].Transactions::GetPurchases()[j].length() + 1;
				}
				if (j != V.transactions_data[i + 20 * V.page].Transactions::GetPurchases().size() - 1)
				{
					std::cout << ", ";
					++k;
				}
			}
			SetConsoleCursorPosition(V.OUT_HANDLE, {99, h});
			std::cout << "|";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, ++h});
			std::cout << "o" << "------------" << "o" << "------------" << "o" << "-------------------------------------------------------------------" << "o";
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

	if (20 + 20 * V.page < V.transactions_data.size())
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

bool ViewSpecificTransactions(Variables &V) //function that allows the user to search for specific transactions, either by and client ID or date of said transaction
{
	ClearScreen(V);
	V.input = "";

	unsigned option;
	bool alt = false, display = false;
	bool by_id = false, by_dates_first = false, by_dates_second = false;
	std::vector<unsigned> positions(0), positions_one(0), positions_two(0), positions_high(0), positions_low(0);
	SHORT h = 6;// defines the postion for the transction line
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[8];

	//settings for the buttons to by displayed on screen
	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 6;
	BUTTONS[0].Right = 17;
	BUTTONS[0].Bottom = 6;
	BUTTONS[0].TextLines = 0;
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 19;
	BUTTONS[1].Top = 6;
	BUTTONS[1].Right = 30;
	BUTTONS[1].Bottom = 6;
	BUTTONS[1].TextLines = 0;
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 13;
	BUTTONS[2].Top = 12;
	BUTTONS[2].Right = 24;
	BUTTONS[2].Bottom = 12;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {13, 12};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "   Distant  " : "  Distante  ");
	ACTIVE_BUTTONS.push_back(2);

	BUTTONS[3].Left = 26;
	BUTTONS[3].Top = 12;
	BUTTONS[3].Right = 37;
	BUTTONS[3].Bottom = 12;
	BUTTONS[3].TextLines = 1;
	BUTTONS[3].TextPos = new COORD[1];
	BUTTONS[3].TextPos[0] = {26, 12};
	BUTTONS[3].Text = new std::string[1];
	BUTTONS[3].Text[0] = (V.language ? "   Recent   " : "   Recente  ");
	ACTIVE_BUTTONS.push_back(3);

	BUTTONS[4].Left = 105;
	BUTTONS[4].Top = 4;
	BUTTONS[4].Right = 124;
	BUTTONS[4].Bottom = 6;
	BUTTONS[4].TextLines = 1;
	BUTTONS[4].TextPos = new COORD[1];
	BUTTONS[4].TextPos[0] = {105, 5};
	BUTTONS[4].Text = new std::string[1];
	BUTTONS[4].Text[0] = (V.language ? "  <- Previous page  " : " <- Página anterior ");

	BUTTONS[5].Left = 105;
	BUTTONS[5].Top = 10;
	BUTTONS[5].Right = 124;
	BUTTONS[5].Bottom = 12;
	BUTTONS[5].TextLines = 1;
	BUTTONS[5].TextPos = new COORD[1];
	BUTTONS[5].TextPos[0] = {105, 11};
	BUTTONS[5].Text = new std::string[1];
	BUTTONS[5].Text[0] = (V.language ? "    Next page ->    " : " Página seguinte -> ");

	BUTTONS[6].Left = 105;
	BUTTONS[6].Top = 16;
	BUTTONS[6].Right = 124;
	BUTTONS[6].Bottom = 18;
	BUTTONS[6].TextLines = 1;
	BUTTONS[6].TextPos = new COORD[1];
	BUTTONS[6].TextPos[0] = {105, 17};
	BUTTONS[6].Text = new std::string[1];
	BUTTONS[6].Text[0] = (V.language ? "     New search     " : "    Nova procura    ");

	BUTTONS[7].Left = 105;
	BUTTONS[7].Top = 22;
	BUTTONS[7].Right = 124;
	BUTTONS[7].Bottom = 24;
	BUTTONS[7].TextLines = 1;
	BUTTONS[7].TextPos = new COORD[1];
	BUTTONS[7].TextPos[0] = {105, 23};
	BUTTONS[7].Text = new std::string[1];
	BUTTONS[7].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");

	for (unsigned i = 0; i < V.transactions_data.size(); ++i)
	{
		positions_one.push_back(i);
	}

	while (true) 
	{
		if (V.page > 0) //activates the previous page button
		{
			ACTIVE_BUTTONS.push_back(4);
		}

		if (20 + 20 * V.page < positions.size()) //activates the next page button
		{
			ACTIVE_BUTTONS.push_back(5);
		}

		if (by_id || by_dates_first || by_dates_second) //in case any research has been made ir activates the New Search button
		{
			ACTIVE_BUTTONS.push_back(6);
		}

		if (ACTIVE_BUTTONS.back() != 7) //allows the Return button to be active only once
		{
			ACTIVE_BUTTONS.push_back(7);
		}

		if (display)
		{
			ClearScreen(V);

			h = 6;
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, 3});
			std::cout << "o" << "------------" << "o" << "------------" << "o" << "-------------------------------------------------------------------" << "o";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, 4});
			std::cout << "|" << "     ID     " << "|" << (V.language ? "    Date    " : "    Data    ") << "|" << (V.language ? "                         List of purchases                         " : "                          Lista de compras                         ") << "|";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, 5});
			std::cout << "o" << "------------" << "o" << "------------" << "o" << "-------------------------------------------------------------------" << "o";
			
			for (unsigned i = 0; i < 20; ++i, ++h) // only 20 transction are displayed on screen at a time
			{
				if (i + 20 * V.page < positions.size())
				{
					SetConsoleCursorPosition(V.OUT_HANDLE, {5, h});
					std::cout << "| " << V.transactions_data[positions[i + 20 * V.page]].Transactions::GetId();
					SetConsoleCursorPosition(V.OUT_HANDLE, {18, h});
					std::cout << "| " << V.transactions_data[positions[i + 20 * V.page]].Transactions::GetDate();
					SetConsoleCursorPosition(V.OUT_HANDLE, {31, h});
					std::cout << "| ";
					
					for (unsigned j = 0, k = 0; j < V.transactions_data[positions[i + 20 * V.page]].Transactions::GetPurchases().size(); ++j)
					{
						k += V.transactions_data[positions[i + 20 * V.page]].Transactions::GetPurchases()[j].length() + 1;
						if (k <= 65)
						{
							std::cout << V.transactions_data[positions[i + 20 * V.page]].Transactions::GetPurchases()[j];
						}
						else
						{
							SetConsoleCursorPosition(V.OUT_HANDLE, {99, h});
							std::cout << "|";
							SetConsoleCursorPosition(V.OUT_HANDLE, {5, ++h});
							std::cout << "|" << "            " << "|" << "            " << "| " << V.transactions_data[positions[i + 20 * V.page]].Transactions::GetPurchases()[j];
							k = V.transactions_data[positions[i + 20 * V.page]].Transactions::GetPurchases()[j].length() + 1;
						}
						if (j != V.transactions_data[positions[i + 20 * V.page]].Transactions::GetPurchases().size() - 1)
						{
							std::cout << ", ";
							++k;
						}
					}
					SetConsoleCursorPosition(V.OUT_HANDLE, {99, h});
					std::cout << "|";
					SetConsoleCursorPosition(V.OUT_HANDLE, {5, ++h});
					std::cout << "o" << "------------" << "o" << "------------" << "o" << "-------------------------------------------------------------------" << "o";
				}
				else break;
			}
			h += 4;
			display = false;
		}

		SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 38 : 38), 1});
		std::cout << (V.language ? "Transactions Manager" : "Gestor de Transações");

		if (!by_id && !by_dates_first) //in case the search is only being made by one date represents the Search by ID button
		{
	
			SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), h - 3});
			std::cout << (V.language ? "Search" : "Procurar");
			SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 8 : 7), h - 2});
			std::cout << (V.language ? "by ID" : "por ID");

			BUTTONS[0].Top = h;
			BUTTONS[0].Bottom = h;

			SetConsoleCursorPosition(V.OUT_HANDLE, {5, h - 1});
			std::cout << "o------------o";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, h});
			std::cout << "|            |";
			SetConsoleCursorPosition(V.OUT_HANDLE, {5, h + 1});
			std::cout << "o------------o";
		}

		if (!by_dates_second && !by_dates_first) // in case the search is only being made by ID it represents the Search by Date button
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 20 : 19), h - 3});
			std::cout << (V.language ? "Search" : "Procurar");
			SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 20 : 19), h - 2});
			std::cout << (V.language ? "by Date" : "por Data");

			BUTTONS[1].Top = h;
			BUTTONS[1].Bottom = h;

			SetConsoleCursorPosition(V.OUT_HANDLE, {18, h - 1});
			std::cout << "o------------o";
			SetConsoleCursorPosition(V.OUT_HANDLE, {18, h});
			std::cout << "|            |";
			SetConsoleCursorPosition(V.OUT_HANDLE, {18, h + 1});
			std::cout << "o------------o";
		}

		if (!by_dates_second) // in case the search is only being made by ID it represents the Search Between Dates buttons
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 15 : 17), h + 3});
			std::cout << (V.language ? "Search" : "Procurar");
			SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 15 : 17), h + 4});
			std::cout << (V.language ? "between Dates" : "entre Datas");

			for (unsigned i = 0; i < ACTIVE_BUTTONS.size(); ++i) //to show the boxes of the specific buttons acording to the search conditons
			{
				if (ACTIVE_BUTTONS[i] == 2)
				{
					BUTTONS[2].Top = h + 6;
					BUTTONS[2].Bottom = h + 6;
					BUTTONS[2].TextPos[0].Y = h + 6;

					SetConsoleCursorPosition(V.OUT_HANDLE, {12, h + 5});
					std::cout << "o------------o";
					SetConsoleCursorPosition(V.OUT_HANDLE, {12, h + 6});
					std::cout << "|" << BUTTONS[2].Text[0] << "|";
					SetConsoleCursorPosition(V.OUT_HANDLE, {12, h + 7});
					std::cout << "o------------o";
				}

				if (ACTIVE_BUTTONS[i] == 3)
				{
					BUTTONS[3].Top = h + 6;
					BUTTONS[3].Bottom = h + 6;
					BUTTONS[3].TextPos[0].Y = h + 6;

					SetConsoleCursorPosition(V.OUT_HANDLE, {25, h + 5});
					std::cout << "o------------o";
					SetConsoleCursorPosition(V.OUT_HANDLE, {25, h + 6});
					std::cout << "|" << BUTTONS[3].Text[0] << "|";
					SetConsoleCursorPosition(V.OUT_HANDLE, {25, h + 7});
					std::cout << "o------------o";
				}
			}
		}

		if (by_id || by_dates_second)// limits the pages after a search of any kind is made
		{
			if (V.page > 0)
			{
				Sleep(200);

				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 3});
				std::cout << "o--------------------o";
				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 4});
				std::cout << "|                    |";
				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 5});
				std::cout << "|" << BUTTONS[4].Text[0] << "|";
				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 6});
				std::cout << "|                    |";
				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 7});
				std::cout << "o--------------------o";
			}

			if (20 + 20 * V.page < positions.size())
			{
				Sleep(200);

				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 9});
				std::cout << "o--------------------o";
				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 10});
				std::cout << "|                    |";
				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 11});
				std::cout << "|" << BUTTONS[5].Text[0] << "|";
				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 12});
				std::cout << "|                    |";
				SetConsoleCursorPosition(V.OUT_HANDLE, {104, 13});
				std::cout << "o--------------------o";
			}
		}

		if (by_id || by_dates_first || by_dates_second) //activates the New Search button
		{
			Sleep(200);

			SetConsoleCursorPosition(V.OUT_HANDLE, {104, 15});
			std::cout << "o--------------------o";
			SetConsoleCursorPosition(V.OUT_HANDLE, {104, 16});
			std::cout << "|                    |";
			SetConsoleCursorPosition(V.OUT_HANDLE, {104, 17});
			std::cout << "|" << BUTTONS[6].Text[0] << "|";
			SetConsoleCursorPosition(V.OUT_HANDLE, {104, 18});
			std::cout << "|                    |";
			SetConsoleCursorPosition(V.OUT_HANDLE, {104, 19});
			std::cout << "o--------------------o";
		}

		Sleep(200);

		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 21});
		std::cout << "o--------------------o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 22});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 23});
		std::cout << "|" << BUTTONS[7].Text[0] << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 24});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 25});
		std::cout << "o--------------------o";

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);

		switch (option)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				switch (option) // sets the positon of the cursor on screnn acording to the kind of search being made
				{
					case 0:
						SetConsoleCursorPosition(V.OUT_HANDLE, {7, h});
						V.OUT_BUFFER.dwCursorPosition = {7, h};
						break;
					case 1:
						SetConsoleCursorPosition(V.OUT_HANDLE, {20, h});
						V.OUT_BUFFER.dwCursorPosition = {20, h};
						break;
					case 2:
						SetConsoleCursorPosition(V.OUT_HANDLE, {12, h + 6});
						std::cout << "|            |";
						SetConsoleCursorPosition(V.OUT_HANDLE, {14, h + 6});
						V.OUT_BUFFER.dwCursorPosition = {14, h + 6};
						break;
					case 3:
						SetConsoleCursorPosition(V.OUT_HANDLE, {25, h + 6});
						std::cout << "|            |";
						SetConsoleCursorPosition(V.OUT_HANDLE, {27, h + 6});
						V.OUT_BUFFER.dwCursorPosition = {27, h + 6};
						break;
				}

				V.input = Input(V, 10);

				switch (option)
				{
					case 0: //after and ID has been inputed
						try //test the validation of the ID
						{
							if (V.input == "") //in case the entry is empty
								continue;
							if (std::to_string(std::stol(V.input)).size() < V.input.size() || std::stol(V.input) < 0 || std::stol(V.input) > std::numeric_limits<int>::max())
								throw std::exception(); // in case the entry has an invalid charecter
						}
						catch (...)
						{
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Search" : "Procurar").length(), {(V.language ? 8 : 7), h - 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "by ID" : "por ID").length(), {(V.language ? 8 : 7), h - 2}, V.FOOBAR);

							SetConsoleCursorPosition(V.OUT_HANDLE, {6, h - 3});
							std::cerr << (V.language ? "Invalid " : "Entrada ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {6, h - 2});
							std::cerr << (V.language ? "input!" : "inválida!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {6, h - 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {6, h - 2}, V.FOOBAR);

							continue;
						}


						// to re-use the information that has already been searched in case a search within a search is being
						for (unsigned i = 0; i < (alt ? positions_two : positions_one).size(); ++i)
						{
							if (V.transactions_data[(alt ? positions_two : positions_one)[i]].GetId() == std::stoi(V.input))
							{
								(alt ? positions_one : positions_two).push_back((alt ? positions_two : positions_one)[i]);
							}
						}

						if ((alt ? positions_one : positions_two).size() == 0)
						{
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Search" : "Procurar").length(), {(V.language ? 8 : 7), h - 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "by ID" : "por ID").length(), {(V.language ? 8 : 7), h - 2}, V.FOOBAR);

							SetConsoleCursorPosition(V.OUT_HANDLE, {6, h - 3});
							std::cerr << (V.language ? "Transactions " : "Transações ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {6, h - 2});
							std::cerr << (V.language ? "not found!" : "não encontradas!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {6, h - 3}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {6, h - 2}, V.FOOBAR);

							continue;
						}

						by_id = true;
						break;
					case 1:
					case 2:
					case 3:
						switch (ValidDate(V)) //check if the date is in a valid format
						{
							case 1:
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Search" : "Procurar").length(), {(option == 1 ? (V.language ? 20 : 19) : (V.language ? 15 : 17)), (option == 1 ? h - 3 : h + 3)}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(option == 1 ? (V.language ? "by Date" : "por Data") : (V.language ? "between Dates" : "entre Datas")).length(), {(option == 1 ? (V.language ? 20 : 19) : (V.language ? 15 : 17)), (option == 1 ? h - 2 : h + 4)}, V.FOOBAR);

								SetConsoleCursorPosition(V.OUT_HANDLE, {(option == 1 ? 19 : 13), (option == 1 ? h - 3 : h + 3)});
								std::cerr << (V.language ? "Invalid " : "Entrada ");
								SetConsoleCursorPosition(V.OUT_HANDLE, {(option == 1 ? 19 : 13), (option == 1 ? h - 2 : h + 4)});
								std::cerr << (V.language ? "input!" : "inválida!");

								Sleep(1000);

								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {(option == 1 ? 19 : 13), (option == 1 ? h - 3 : h + 3)}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {(option == 1 ? 19 : 13), (option == 1 ? h - 2 : h + 4)}, V.FOOBAR);
							case 2:
								continue;
						}

						unsigned date_limit = std::stoi(V.input.substr(6, 4) + V.input.substr(3, 2) + V.input.substr(0, 2));

						switch (option) // in case the search if being made by dates
						{
							case 1: // just by one date
								for (unsigned i = 0; i < (alt ? positions_two : positions_one).size(); ++i)
								{
									if (V.transactions_data[(alt ? positions_two : positions_one)[i]].GetDate() == V.input)
									{
										(alt ? positions_one : positions_two).push_back((alt ? positions_two : positions_one)[i]);
									}
								}
								break;
							case 2: // by the a distant date
								for (unsigned i = 0; i < (alt ? positions_two : positions_one).size(); ++i)
								{
									unsigned date = std::stoi(V.transactions_data[(alt ? positions_two : positions_one)[i]].GetDate().substr(6, 4) +
															  V.transactions_data[(alt ? positions_two : positions_one)[i]].GetDate().substr(3, 2) +
															  V.transactions_data[(alt ? positions_two : positions_one)[i]].GetDate().substr(0, 2));
									if (date >= date_limit)
									{
										positions_high.push_back((alt ? positions_two : positions_one)[i]);
									}
								}
								break;
							case 3: // by the recent date
								for (unsigned i = 0; i < (alt ? positions_two : positions_one).size(); ++i)
								{
									unsigned date = std::stoi(V.transactions_data[(alt ? positions_two : positions_one)[i]].GetDate().substr(6, 4) +
															  V.transactions_data[(alt ? positions_two : positions_one)[i]].GetDate().substr(3, 2) +
															  V.transactions_data[(alt ? positions_two : positions_one)[i]].GetDate().substr(0, 2));
									if (date <= date_limit)
									{
										positions_low.push_back((alt ? positions_two : positions_one)[i]);
									}
								}
								break;
						}

						// in case a search by date is not found
						if ((option == 1 && (alt ? positions_one : positions_two).size() == 0) || (option == 2 && positions_high.size() == 0) || (option == 3 && positions_low.size() == 0))
						{
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Search" : "Procurar").length(), {(option == 1 ? (V.language ? 20 : 19) : (V.language ? 15 : 17)), (option == 1 ? h - 3 : h + 3)}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(option == 1 ? (V.language ? "by Date" : "por Data") : (V.language ? "between Dates" : "entre Datas")).length(), {(option == 1 ? (V.language ? 20 : 19) : (V.language ? 15 : 17)), (option == 1 ? h - 2 : h + 4)}, V.FOOBAR);

							SetConsoleCursorPosition(V.OUT_HANDLE, {(option == 1 ? 19 : 13), (option == 1 ? h - 3 : h + 3)});
							std::cerr << (V.language ? "Transactions " : "Transações ");
							SetConsoleCursorPosition(V.OUT_HANDLE, {(option == 1 ? 19 : 13), (option == 1 ? h - 2 : h + 4)});
							std::cerr << (V.language ? "not found!" : "não encontradas!");

							Sleep(1000);

							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Transactions " : "Transações ").length(), {(option == 1 ? 19 : 13), (option == 1 ? h - 3 : h + 3)}, V.FOOBAR);
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "not found!" : "não encontradas!").length(), {(option == 1 ? 19 : 13), (option == 1 ? h - 2 : h + 4)}, V.FOOBAR);

							continue;
						}

						switch (option)
						{
							case 1: // in case a search by date is made it allows a search by ID
								by_dates_second = true;
								break;
							case 2:
							case 3:
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Search" : "Procurar").length(), {(V.language ? 8 : 7), h - 3}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "by ID" : "por ID").length(), {(V.language ? 8 : 7), h - 2}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Search" : "Procurar").length(), {(V.language ? 20 : 19), h - 3}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "by Date" : "por Data").length(), {(V.language ? 20 : 19), h - 2}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', 27, {5, h - 1}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', 27, {5, h}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', 27, {5, h + 1}, V.FOOBAR);

								ACTIVE_BUTTONS.resize(0);
								switch (option) // to choose which date button is to be active after another one has been pressed
								{
									case 2: //if the distance date has been inputed
										ACTIVE_BUTTONS.push_back(3);
										break;
									case 3://if the recent date has been inputed
										ACTIVE_BUTTONS.push_back(2);
										break;
								}

								if (!by_dates_first) //limits the search to only one follow up search if search between dates is chosen 
								{
									by_dates_first = true;
									continue;
								}
								break;
						}
						break;
				}

				if (by_dates_first) // algothrim to execute only if a search between dates is made
				{                  
					for (unsigned i = 0; i < positions_high.size(); ++i)
					{
						for (unsigned j = 0; j < positions_low.size(); ++j)
						{
							if (positions_high[i] == positions_low[j])
							{
								(alt ? positions_one : positions_two).push_back(positions_high[i]);
								break;
							}
						}
					}
				}

				positions = (alt ? positions_one : positions_two); //keeps the postion of V.transactions_data obtained in the search
				(alt ? positions_two : positions_one).resize(0);
				alt = !alt;

				if (by_dates_first) //switchs the bool value of the variables by_date_first and by_date_second
				{
					by_dates_first = !(by_dates_second = by_dates_first);
				}

				V.page = 0;
			case 4:
			case 5:
				ACTIVE_BUTTONS.resize(0);

				if (!by_id)
				{
					ACTIVE_BUTTONS.push_back(0);
				}

				if (!by_dates_second)
				{
					for (unsigned i = 1; i < 4; ++i)
					{
						ACTIVE_BUTTONS.push_back(i);
					}
				}

				switch (option)
				{
					case 4:
						--V.page;
						break;
					case 5:
						++V.page;
						break;
				}

				display = true;
				continue;
		}
		break;
	}

	for (unsigned i = 2; i < 8; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	if (option == 7) return false;
	return true;
}

bool AddTransactions(Variables &V) //function that allows the user to add a transaction made by a client
{                                  // similar to the AddClients function
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	unsigned n = -1;
	bool invalid = false;
	double value = 0;
	std::string date;
	std::vector <std::string> purchases;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[5];

	//settings for the buttons to be displayed on screen
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

	BUTTONS[2].Left = 6;
	BUTTONS[2].Top = 18;
	BUTTONS[2].Right = 17;
	BUTTONS[2].Bottom = 18;
	BUTTONS[2].TextLines = 0;

	BUTTONS[3].Left = 105;
	BUTTONS[3].Top = 4;
	BUTTONS[3].Right = 124;
	BUTTONS[3].Bottom = 6;
	BUTTONS[3].TextLines = 1;
	BUTTONS[3].TextPos = new COORD[1];
	BUTTONS[3].TextPos[0] = {105, 5};
	BUTTONS[3].Text = new std::string[1];
	BUTTONS[3].Text[0] = (V.language ? "     New search     " : "    Nova procura    ");

	BUTTONS[4].Left = 105;
	BUTTONS[4].Top = 10;
	BUTTONS[4].Right = 124;
	BUTTONS[4].Bottom = 12;
	BUTTONS[4].TextLines = 1;
	BUTTONS[4].TextPos = new COORD[1];
	BUTTONS[4].TextPos[0] = {105, 11};
	BUTTONS[4].Text = new std::string[1];
	BUTTONS[4].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(4);

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 38 : 38), 1});
	std::cout << (V.language ? "Transactions Manager" : "Gestor de Transações");

	SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
	std::cout << (V.language ? "Insert" : "Inserir");
	SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
	std::cout << (V.language ? "ID" : "ID");

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
	std::cout << "|" << BUTTONS[4].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 12});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {104, 13});
	std::cout << "o--------------------o";

	while (true)
	{
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 3});
		std::cout << (V.language ? "Insert" : "Inserir");
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 4});
		std::cout << (V.language ? "ID" : "ID");

		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 6});
		std::cout << "|            |";

		option = Event(V, BUTTONS, ACTIVE_BUTTONS);

		if (option == 0)
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {7, 6});
			V.OUT_BUFFER.dwCursorPosition = {7, 6};
			V.input = Input(V, 10);

			try // test if the ID inputed is valid
			{
				if (V.input == "")
					continue;
				if (std::to_string(std::stol(V.input)).size() < V.input.size() || std::stol(V.input) < 0 || std::stol(V.input) > std::numeric_limits<int>::max())
					throw std::exception();
			}
			catch (...)
			{
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Insert" : "Inserir").length(), {6, 3}, V.FOOBAR);
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "ID" : "ID").length(), {6, 4}, V.FOOBAR);

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
					n = i; //saves the postion of the client founded
					break;
				}
			}

			if (n == -1)//shows error message if the client is not found
			{
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Insert" : "Inserir").length(), {6, 3}, V.FOOBAR);
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "ID" : "ID").length(), {6, 4}, V.FOOBAR);

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

	if (n != -1) // shows data of the found client
	{
		ACTIVE_BUTTONS.resize(0);
		for (unsigned i = 1; i < 5; ++i)
		{
			ACTIVE_BUTTONS.push_back(i);
		}

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

		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 15});
		std::cout << (V.language ? "Insert" : "Inserir");
		SetConsoleCursorPosition(V.OUT_HANDLE, {6, 16});
		std::cout << (V.language ? "Products" : "Produtos");

		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 17});
		std::cout << "o--o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
		std::cout << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {5, 19});
		std::cout << "o--o";

		Sleep(200);

		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 3});
		std::cout << "o--------------------o";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 4});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 5});
		std::cout << "|" << BUTTONS[3].Text[0] << "|";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 6});
		std::cout << "|                    |";
		SetConsoleCursorPosition(V.OUT_HANDLE, {104, 7});
		std::cout << "o--------------------o";

		while (true) //activates the Insert Date button
		{
			SetConsoleCursorPosition(V.OUT_HANDLE, {6, 9});
			std::cout << (V.language ? "Insert" : "Inserir");
			SetConsoleCursorPosition(V.OUT_HANDLE, {6, 10});
			std::cout << (V.language ? "Date" : "Data");

			SetConsoleCursorPosition(V.OUT_HANDLE, {6, 15});
			std::cout << (V.language ? "Insert" : "Inserir");
			SetConsoleCursorPosition(V.OUT_HANDLE, {6, 16});
			std::cout << (V.language ? "Products" : "Produtos");

			if (ACTIVE_BUTTONS.front() == 1)
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {5, 12});
				std::cout << "|            |";
			}

			if (invalid) // in case the products inputed have an invalid value
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
				FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', V.input.length(), {7, 18}, V.FOOBAR);

				invalid = false;
				purchases.resize(0);
			}

			option = Event(V, BUTTONS, ACTIVE_BUTTONS);

			switch (option)
			{
				case 1:
				case 2:
					switch (option)
					{
						case 1:
							SetConsoleCursorPosition(V.OUT_HANDLE, {7, 12});
							V.OUT_BUFFER.dwCursorPosition = {7, 12};
							V.input = Input(V, 10);

							switch (ValidDate(V)) //check the date format
							{
								case 0:
									if (std::stoi(V.input.substr(6, 4) + V.input.substr(3, 2) + V.input.substr(0, 2)) >=
										std::stoi(V.clients_data[n].GetDate().substr(6, 4) + V.clients_data[n].GetDate().substr(3, 2) + V.clients_data[n].GetDate().substr(0, 2)))
									{
										date = V.input;
										break;
									}
								case 1:
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

							for (unsigned i = 0; i < 5; ++i)
							{
								if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 1)
								{
									ACTIVE_BUTTONS.erase(ACTIVE_BUTTONS.begin() + i);
									break;
								}
							}

							if (ACTIVE_BUTTONS.size() > 2) continue;
							break;
						case 2: //to save the products made in the transaction
							std::stringstream stream;

							SetConsoleCursorPosition(V.OUT_HANDLE, {7, 18});
							V.OUT_BUFFER.dwCursorPosition = {7, 18};
							V.input = Input(V, std::numeric_limits<short>::max());

							if (V.input == "") continue;
							stream << " " << V.input;

							for (stream.peek(); stream.good(); stream.peek())
							{
								purchases.push_back(std::string());
								getline(stream, purchases.back(), ',');
								purchases.back() = purchases.back().substr(1, purchases.back().length());
							}

							for (unsigned i = 0; i < purchases.size(); ++i)
							{
								for (unsigned j = 0; j < V.products_data.size(); ++j)
								{
									if (purchases[i] == V.products_data[j].GetName())
									{
										value += V.products_data[j].GetPrice(); //sums the total of the prices of the products bought
										break;
									}

									if (j == V.products_data.size() - 1)
									{
										invalid = true;
									}
								}
								if (invalid) break;
							}

							if (invalid)
							{
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Insert" : "Inserir").length(), {6, 15}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Products" : "Produtos").length(), {6, 16}, V.FOOBAR);

								SetConsoleCursorPosition(V.OUT_HANDLE, {6, 15});
								std::cerr << (V.language ? "Invalid " : "Entrada ");
								SetConsoleCursorPosition(V.OUT_HANDLE, {6, 16});
								std::cerr << (V.language ? "input!" : "inválida!");

								Sleep(1000);

								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "Invalid " : "Entrada ").length(), {6, 15}, V.FOOBAR);
								FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', std::string(V.language ? "input!" : "inválida!").length(), {6, 16}, V.FOOBAR);

								continue;
							}

							for (unsigned i = 0; i < 5; ++i)
							{
								if (ACTIVE_BUTTONS.size() > i && ACTIVE_BUTTONS[i] == 2)
								{
									ACTIVE_BUTTONS.erase(ACTIVE_BUTTONS.begin() + i);
									break;
								}
							}

							if (ACTIVE_BUTTONS.size() > 2) continue;
							break;
					}

					V.clients_data[n].SetValue(value); //saves the value into the specific client total purchases
					V.transactions_data.push_back(Transactions::Transactions(V.clients_data[n].GetId(), date, purchases));// saves the new transaction in the vector
					std::stable_sort(V.transactions_data.begin(), V.transactions_data.end(), Sort());

					ClearScreen(V);

					SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 38 : 38), 1});
					std::cout << (V.language ? "Transactions Manager" : "Gestor de Transações");

					//shows success message
					SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 33 : 32), 3});
					std::cout << (V.language ? "Transaction successfully added!" : "Transação adicionada com sucesso!");

					Sleep(2000);
			}
			break;
		}
	}

	for (unsigned i = 3; i < 5; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	if (option == 4) return false;
	return true;
}

//====================================================================================================
// ========== End of File ==========
//====================================================================================================