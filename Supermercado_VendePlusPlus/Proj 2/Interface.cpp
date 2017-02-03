//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Interface.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

bool Interface(Variables &V)
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[5];

	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 18;
	BUTTONS[0].Right = 25;
	BUTTONS[0].Bottom = 21;
	BUTTONS[0].TextLines = 2;
	BUTTONS[0].TextPos = new COORD[2];
	BUTTONS[0].TextPos[0] = {6, 19};
	BUTTONS[0].TextPos[1] = {6, 20};
	BUTTONS[0].Text = new std::string[2];
	BUTTONS[0].Text[0] = (V.language ? "     Clients        " : "      Gestão de     ");
	BUTTONS[0].Text[1] = (V.language ? "     Management     " : "      Clientes      ");
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 38;
	BUTTONS[1].Top = 18;
	BUTTONS[1].Right = 57;
	BUTTONS[1].Bottom = 21;
	BUTTONS[1].TextLines = 2;
	BUTTONS[1].TextPos = new COORD[2];
	BUTTONS[1].TextPos[0] = {38, 19};
	BUTTONS[1].TextPos[1] = {38, 20};
	BUTTONS[1].Text = new std::string[2];
	BUTTONS[1].Text[0] = (V.language ? "     Products       " : "      Gestão de     ");
	BUTTONS[1].Text[1] = (V.language ? "     Management     " : "      Produtos      ");
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 70;
	BUTTONS[2].Top = 18;
	BUTTONS[2].Right = 89;
	BUTTONS[2].Bottom = 21;
	BUTTONS[2].TextLines = 2;
	BUTTONS[2].TextPos = new COORD[2];
	BUTTONS[2].TextPos[0] = {70, 19};
	BUTTONS[2].TextPos[1] = {70, 20};
	BUTTONS[2].Text = new std::string[2];
	BUTTONS[2].Text[0] = (V.language ? "    Transactions    " : "     Gestão de      ");
	BUTTONS[2].Text[1] = (V.language ? "    Management      " : "     Transações     ");
	ACTIVE_BUTTONS.push_back(2);

	BUTTONS[3].Left = 22;
	BUTTONS[3].Top = 25;
	BUTTONS[3].Right = 41;
	BUTTONS[3].Bottom = 28;
	BUTTONS[3].TextLines = 2;
	BUTTONS[3].TextPos = new COORD[2];
	BUTTONS[3].TextPos[0] = {22, 26};
	BUTTONS[3].TextPos[1] = {22, 27};
	BUTTONS[3].Text = new std::string[2];
	BUTTONS[3].Text[0] = (V.language ? "   Recommendations  " : "    Gestão de       ");
	BUTTONS[3].Text[1] = (V.language ? "   Management       " : "    Recomendações   ");
	ACTIVE_BUTTONS.push_back(3);

	BUTTONS[4].Left = 54;
	BUTTONS[4].Top = 25;
	BUTTONS[4].Right = 73;
	BUTTONS[4].Bottom = 28;
	BUTTONS[4].TextLines = 2;
	BUTTONS[4].TextPos = new COORD[2];
	BUTTONS[4].TextPos[0] = {54, 26};
	BUTTONS[4].TextPos[1] = {54, 27};
	BUTTONS[4].Text = new std::string[2];
	BUTTONS[4].Text[0] = (V.language ? "         End        " : "      Terminar      ");
	BUTTONS[4].Text[1] = (V.language ? "       Session      " : "       Sessão       ");
	ACTIVE_BUTTONS.push_back(4);

	std::cout << "        ___           ___          ___           ___          ___" << std::endl;
	std::cout << "       /\\__\\         /\\  \\        /\\__\\         /\\  \\        /\\  \\" << std::endl;
	std::cout << "      / /  /        /  \\  \\      /  | |        /  \\  \\      /  \\  \\     __  __    __  __" << std::endl;
	std::cout << "     / /__/        / /\\ \\  \\    / / | |       / /\\ \\  \\    / /\\ \\  \\   /\\ \\/\\_\\  /\\ \\/\\_\\" << std::endl;
	std::cout << "     | |  |  ___  /  \\ \\ \\  \\  / /| | | ___  / /  \\ \\  \\  /  \\ \\ \\  \\  \\ \\/ / /  \\ \\/ / /" << std::endl;
	std::cout << "     | |  | /\\__\\/ /\\ \\ \\ \\__\\/ / | | |/\\__\\/ /__/ \\ \\__\\/ /\\ \\ \\ \\__\\  \\  /_/    \\  /_/" << std::endl;
	std::cout << "     | |__|/ /  /\\ \\ \\ \\ \\/__/\\/_/| | / /  /\\ \\  \\ | |__|\\ \\ \\ \\ \\/__/  /  \\ \\    /  \\ \\" << std::endl;
	std::cout << "      \\_____/__/  \\ \\ \\ \\__\\      | |/ /  /  \\ \\  \\/ /  / \\ \\ \\ \\__\\   / /\\ \\_\\  / /\\ \\_\\" << std::endl;
	std::cout << "                   \\ \\ \\/__/      | / /  /    \\ \\_/ /  /   \\ \\ \\/__/   \\/_/\\/_/  \\/_/\\/_/" << std::endl;
	std::cout << "                    \\ \\__\\        |  /  /      \\___/__/     \\ \\__\\" << std::endl;
	std::cout << "                     \\/__/         \\/__/                     \\/__/" << std::endl;

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 42 : 38), 13});
	std::cout << (V.language ? "Data Manager" : "Gestor de Informação");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 34), 15});
	std::cout << (V.language ? "Please select an option" : "Por favor selecione uma opção");

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 19});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 20});
	std::cout << "|" << BUTTONS[0].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 19});
	std::cout << "|" << BUTTONS[1].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 20});
	std::cout << "|" << BUTTONS[1].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 19});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 20});
	std::cout << "|" << BUTTONS[2].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 24});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 25});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 26});
	std::cout << "|" << BUTTONS[3].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 27});
	std::cout << "|" << BUTTONS[3].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 28});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 29});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 24});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 25});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 26});
	std::cout << "|" << BUTTONS[4].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 27});
	std::cout << "|" << BUTTONS[4].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 28});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 29});
	std::cout << "o--------------------o";

	option = Event(V, BUTTONS, ACTIVE_BUTTONS);

	for (unsigned i = 0; i < 5; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	switch (option)
	{
		case 0:
			while (ClientsInterface(V))
				continue;
			break;
		case 1:
			while (ProductsInterface(V))
				continue;
			break;
		case 2:
			while (TransactionsInterface(V))
				continue;
			break;
		case 3:
			if (V.clients_data.size() == 0 || V.products_data.size() == 0 || V.transactions_data.size() == 0)
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 31});
				std::cout << (V.language ? "File(s) empty!" : "Ficheiro(s) vazio!");

				Sleep(1000);

				break;
			}
			LoadMatrix(V);
			while (RecommendationsInterface(V))
				continue;
			break;
		case 4:
			return false;
	}
	return true;
}

bool ClientsInterface(Variables &V)
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[5];

	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 18;
	BUTTONS[0].Right = 25;
	BUTTONS[0].Bottom = 21;
	BUTTONS[0].TextLines = 2;
	BUTTONS[0].TextPos = new COORD[2];
	BUTTONS[0].TextPos[0] = {6, 19};
	BUTTONS[0].TextPos[1] = {6, 20};
	BUTTONS[0].Text = new std::string[2];
	BUTTONS[0].Text[0] = (V.language ? "       View         " : "      Ver           ");
	BUTTONS[0].Text[1] = (V.language ? "       clients      " : "      clientes      ");
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 38;
	BUTTONS[1].Top = 18;
	BUTTONS[1].Right = 57;
	BUTTONS[1].Bottom = 21;
	BUTTONS[1].TextLines = 2;
	BUTTONS[1].TextPos = new COORD[2];
	BUTTONS[1].TextPos[0] = {38, 19};
	BUTTONS[1].TextPos[1] = {38, 20};
	BUTTONS[1].Text = new std::string[2];
	BUTTONS[1].Text[0] = (V.language ? "       Edit         " : "       Editar       ");
	BUTTONS[1].Text[1] = (V.language ? "       client       " : "       cliente      ");
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 70;
	BUTTONS[2].Top = 18;
	BUTTONS[2].Right = 89;
	BUTTONS[2].Bottom = 21;
	BUTTONS[2].TextLines = 2;
	BUTTONS[2].TextPos = new COORD[2];
	BUTTONS[2].TextPos[0] = {70, 19};
	BUTTONS[2].TextPos[1] = {70, 20};
	BUTTONS[2].Text = new std::string[2];
	BUTTONS[2].Text[0] = (V.language ? "       Add          " : "      Adicionar     ");
	BUTTONS[2].Text[1] = (V.language ? "       client       " : "      cliente       ");
	ACTIVE_BUTTONS.push_back(2);

	BUTTONS[3].Left = 22;
	BUTTONS[3].Top = 25;
	BUTTONS[3].Right = 41;
	BUTTONS[3].Bottom = 28;
	BUTTONS[3].TextLines = 2;
	BUTTONS[3].TextPos = new COORD[2];
	BUTTONS[3].TextPos[0] = {22, 26};
	BUTTONS[3].TextPos[1] = {22, 27};
	BUTTONS[3].Text = new std::string[2];
	BUTTONS[3].Text[0] = (V.language ? "       Remove       " : "       Remover      ");
	BUTTONS[3].Text[1] = (V.language ? "       client       " : "       cliente      ");
	ACTIVE_BUTTONS.push_back(3);

	BUTTONS[4].Left = 54;
	BUTTONS[4].Top = 25;
	BUTTONS[4].Right = 73;
	BUTTONS[4].Bottom = 28;
	BUTTONS[4].TextLines = 1;
	BUTTONS[4].TextPos = new COORD[1];
	BUTTONS[4].TextPos[0] = {54, 26};
	BUTTONS[4].Text = new std::string[1];
	BUTTONS[4].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(4);

	std::cout << "        ___           ___          ___           ___          ___" << std::endl;
	std::cout << "       /\\__\\         /\\  \\        /\\__\\         /\\  \\        /\\  \\" << std::endl;
	std::cout << "      / /  /        /  \\  \\      /  | |        /  \\  \\      /  \\  \\     __  __    __  __" << std::endl;
	std::cout << "     / /__/        / /\\ \\  \\    / / | |       / /\\ \\  \\    / /\\ \\  \\   /\\ \\/\\_\\  /\\ \\/\\_\\" << std::endl;
	std::cout << "     | |  |  ___  /  \\ \\ \\  \\  / /| | | ___  / /  \\ \\  \\  /  \\ \\ \\  \\  \\ \\/ / /  \\ \\/ / /" << std::endl;
	std::cout << "     | |  | /\\__\\/ /\\ \\ \\ \\__\\/ / | | |/\\__\\/ /__/ \\ \\__\\/ /\\ \\ \\ \\__\\  \\  /_/    \\  /_/" << std::endl;
	std::cout << "     | |__|/ /  /\\ \\ \\ \\ \\/__/\\/_/| | / /  /\\ \\  \\ | |__|\\ \\ \\ \\ \\/__/  /  \\ \\    /  \\ \\" << std::endl;
	std::cout << "      \\_____/__/  \\ \\ \\ \\__\\      | |/ /  /  \\ \\  \\/ /  / \\ \\ \\ \\__\\   / /\\ \\_\\  / /\\ \\_\\" << std::endl;
	std::cout << "                   \\ \\ \\/__/      | / /  /    \\ \\_/ /  /   \\ \\ \\/__/   \\/_/\\/_/  \\/_/\\/_/" << std::endl;
	std::cout << "                    \\ \\__\\        |  /  /      \\___/__/     \\ \\__\\" << std::endl;
	std::cout << "                     \\/__/         \\/__/                     \\/__/" << std::endl;

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 13});
	std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 34), 15});
	std::cout << (V.language ? "Please select an option" : "Por favor selecione uma opção");

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 19});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 20});
	std::cout << "|" << BUTTONS[0].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 19});
	std::cout << "|" << BUTTONS[1].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 20});
	std::cout << "|" << BUTTONS[1].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 19});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 20});
	std::cout << "|" << BUTTONS[2].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 24});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 25});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 26});
	std::cout << "|" << BUTTONS[3].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 27});
	std::cout << "|" << BUTTONS[3].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 28});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {21, 29});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 24});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 25});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 26});
	std::cout << "|" << BUTTONS[4].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 27});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 28});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {53, 29});
	std::cout << "o--------------------o";

	option = Event(V, BUTTONS, ACTIVE_BUTTONS);

	for (unsigned i = 0; i < 5; ++i)
	{
		delete[] BUTTONS[i].Text;
		delete[] BUTTONS[i].TextPos;
	}
	delete[] BUTTONS;

	switch (option)
	{
		case 0:
			while (ViewClientsInterface(V))
				continue;
			break;
		case 1:
			while (EditClients(V)) // Definition in Clients Interface.cpp
				continue;
			break;
		case 2:
			while (AddClients(V)) // Definition in Clients Interface.cpp
				continue;
			break;
		case 3:
			while (RemoveClients(V)) // Definition in Clients Interface.cpp
				continue;
			break;
		case 4:
			return false;
	}
	return true;
}

bool ProductsInterface(Variables &V)
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 18;
	BUTTONS[0].Right = 25;
	BUTTONS[0].Bottom = 21;
	BUTTONS[0].TextLines = 2;
	BUTTONS[0].TextPos = new COORD[2];
	BUTTONS[0].TextPos[0] = {6, 19};
	BUTTONS[0].TextPos[1] = {6, 20};
	BUTTONS[0].Text = new std::string[2];
	BUTTONS[0].Text[0] = (V.language ? "      View          " : "      Ver           ");
	BUTTONS[0].Text[1] = (V.language ? "      products      " : "      produtos      ");
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 38;
	BUTTONS[1].Top = 18;
	BUTTONS[1].Right = 57;
	BUTTONS[1].Bottom = 21;
	BUTTONS[1].TextLines = 2;
	BUTTONS[1].TextPos = new COORD[2];
	BUTTONS[1].TextPos[0] = {38, 19};
	BUTTONS[1].TextPos[1] = {38, 20};
	BUTTONS[1].Text = new std::string[2];
	BUTTONS[1].Text[0] = (V.language ? "      Add           " : "      Adicionar     ");
	BUTTONS[1].Text[1] = (V.language ? "      products      " : "      produtos      ");
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 70;
	BUTTONS[2].Top = 18;
	BUTTONS[2].Right = 89;
	BUTTONS[2].Bottom = 21;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {70, 19};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	std::cout << "        ___           ___          ___           ___          ___" << std::endl;
	std::cout << "       /\\__\\         /\\  \\        /\\__\\         /\\  \\        /\\  \\" << std::endl;
	std::cout << "      / /  /        /  \\  \\      /  | |        /  \\  \\      /  \\  \\     __  __    __  __" << std::endl;
	std::cout << "     / /__/        / /\\ \\  \\    / / | |       / /\\ \\  \\    / /\\ \\  \\   /\\ \\/\\_\\  /\\ \\/\\_\\" << std::endl;
	std::cout << "     | |  |  ___  /  \\ \\ \\  \\  / /| | | ___  / /  \\ \\  \\  /  \\ \\ \\  \\  \\ \\/ / /  \\ \\/ / /" << std::endl;
	std::cout << "     | |  | /\\__\\/ /\\ \\ \\ \\__\\/ / | | |/\\__\\/ /__/ \\ \\__\\/ /\\ \\ \\ \\__\\  \\  /_/    \\  /_/" << std::endl;
	std::cout << "     | |__|/ /  /\\ \\ \\ \\ \\/__/\\/_/| | / /  /\\ \\  \\ | |__|\\ \\ \\ \\ \\/__/  /  \\ \\    /  \\ \\" << std::endl;
	std::cout << "      \\_____/__/  \\ \\ \\ \\__\\      | |/ /  /  \\ \\  \\/ /  / \\ \\ \\ \\__\\   / /\\ \\_\\  / /\\ \\_\\" << std::endl;
	std::cout << "                   \\ \\ \\/__/      | / /  /    \\ \\_/ /  /   \\ \\ \\/__/   \\/_/\\/_/  \\/_/\\/_/" << std::endl;
	std::cout << "                    \\ \\__\\        |  /  /      \\___/__/     \\ \\__\\" << std::endl;
	std::cout << "                     \\/__/         \\/__/                     \\/__/" << std::endl;

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 40 : 39), 13});
	std::cout << (V.language ? "Products Manager" : "Gestor de Produtos");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 34), 15});
	std::cout << (V.language ? "Please select an option" : "Por favor selecione uma opção");

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 19});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 20});
	std::cout << "|" << BUTTONS[0].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 19});
	std::cout << "|" << BUTTONS[1].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 20});
	std::cout << "|" << BUTTONS[1].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 19});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 20});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 22});
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
			while (ViewAllProducts(V)) // Definition in Products Interface.cpp
				continue;
			break;
		case 1:
			while (AddProducts(V)) // Definition in Products Interface.cpp
				continue;
			break;
		case 2:
			return false;
	}
	return true;
}

bool TransactionsInterface(Variables &V)
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 18;
	BUTTONS[0].Right = 25;
	BUTTONS[0].Bottom = 21;
	BUTTONS[0].TextLines = 2;
	BUTTONS[0].TextPos = new COORD[2];
	BUTTONS[0].TextPos[0] = {6, 19};
	BUTTONS[0].TextPos[1] = {6, 20};
	BUTTONS[0].Text = new std::string[2];
	BUTTONS[0].Text[0] = (V.language ? "    View            " : "     Ver            ");
	BUTTONS[0].Text[1] = (V.language ? "    transactions    " : "     transações     ");
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 38;
	BUTTONS[1].Top = 18;
	BUTTONS[1].Right = 57;
	BUTTONS[1].Bottom = 21;
	BUTTONS[1].TextLines = 2;
	BUTTONS[1].TextPos = new COORD[2];
	BUTTONS[1].TextPos[0] = {38, 19};
	BUTTONS[1].TextPos[1] = {38, 20};
	BUTTONS[1].Text = new std::string[2];
	BUTTONS[1].Text[0] = (V.language ? "    Add             " : "     Adicionar      ");
	BUTTONS[1].Text[1] = (V.language ? "    transactions    " : "     transações     ");
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 70;
	BUTTONS[2].Top = 18;
	BUTTONS[2].Right = 89;
	BUTTONS[2].Bottom = 21;
	BUTTONS[2].TextLines = 2;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {70, 19};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	std::cout << "        ___           ___          ___           ___          ___" << std::endl;
	std::cout << "       /\\__\\         /\\  \\        /\\__\\         /\\  \\        /\\  \\" << std::endl;
	std::cout << "      / /  /        /  \\  \\      /  | |        /  \\  \\      /  \\  \\     __  __    __  __" << std::endl;
	std::cout << "     / /__/        / /\\ \\  \\    / / | |       / /\\ \\  \\    / /\\ \\  \\   /\\ \\/\\_\\  /\\ \\/\\_\\" << std::endl;
	std::cout << "     | |  |  ___  /  \\ \\ \\  \\  / /| | | ___  / /  \\ \\  \\  /  \\ \\ \\  \\  \\ \\/ / /  \\ \\/ / /" << std::endl;
	std::cout << "     | |  | /\\__\\/ /\\ \\ \\ \\__\\/ / | | |/\\__\\/ /__/ \\ \\__\\/ /\\ \\ \\ \\__\\  \\  /_/    \\  /_/" << std::endl;
	std::cout << "     | |__|/ /  /\\ \\ \\ \\ \\/__/\\/_/| | / /  /\\ \\  \\ | |__|\\ \\ \\ \\ \\/__/  /  \\ \\    /  \\ \\" << std::endl;
	std::cout << "      \\_____/__/  \\ \\ \\ \\__\\      | |/ /  /  \\ \\  \\/ /  / \\ \\ \\ \\__\\   / /\\ \\_\\  / /\\ \\_\\" << std::endl;
	std::cout << "                   \\ \\ \\/__/      | / /  /    \\ \\_/ /  /   \\ \\ \\/__/   \\/_/\\/_/  \\/_/\\/_/" << std::endl;
	std::cout << "                    \\ \\__\\        |  /  /      \\___/__/     \\ \\__\\" << std::endl;
	std::cout << "                     \\/__/         \\/__/                     \\/__/" << std::endl;

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 38 : 38), 13});
	std::cout << (V.language ? "Transactions Manager" : "Gestor de Transações");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 34), 15});
	std::cout << (V.language ? "Please select an option" : "Por favor selecione uma opção");

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 19});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 20});
	std::cout << "|" << BUTTONS[0].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 19});
	std::cout << "|" << BUTTONS[1].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 20});
	std::cout << "|" << BUTTONS[1].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 19});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 20});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 22});
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
			while (ViewTransactionsInterface(V))
				continue;
			break;
		case 1:
			while (AddTransactions(V)) // Definition in Transactions Interface.cpp
				continue;
			break;
		case 2:
			return false;
	}
	return true;
}

bool RecommendationsInterface(Variables &V)
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 18;
	BUTTONS[0].Right = 25;
	BUTTONS[0].Bottom = 21;
	BUTTONS[0].TextLines = 2;
	BUTTONS[0].TextPos = new COORD[2];
	BUTTONS[0].TextPos[0] = {6, 19};
	BUTTONS[0].TextPos[1] = {6, 20};
	BUTTONS[0].Text = new std::string[2];
	BUTTONS[0].Text[0] = (V.language ? "   Personal         " : "    Recomendação    ");
	BUTTONS[0].Text[1] = (V.language ? "   recommendation   " : "    pessoal         ");
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 38;
	BUTTONS[1].Top = 18;
	BUTTONS[1].Right = 57;
	BUTTONS[1].Bottom = 21;
	BUTTONS[1].TextLines = 2;
	BUTTONS[1].TextPos = new COORD[2];
	BUTTONS[1].TextPos[0] = {38, 19};
	BUTTONS[1].TextPos[1] = {38, 20};
	BUTTONS[1].Text = new std::string[2];
	BUTTONS[1].Text[0] = (V.language ? "      Bottom10      " : "      Campanha      ");
	BUTTONS[1].Text[1] = (V.language ? "      campaign      " : "      Bottom10      ");
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 70;
	BUTTONS[2].Top = 18;
	BUTTONS[2].Right = 89;
	BUTTONS[2].Bottom = 21;
	BUTTONS[2].TextLines = 2;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {70, 19};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	std::cout << "        ___           ___          ___           ___          ___" << std::endl;
	std::cout << "       /\\__\\         /\\  \\        /\\__\\         /\\  \\        /\\  \\" << std::endl;
	std::cout << "      / /  /        /  \\  \\      /  | |        /  \\  \\      /  \\  \\     __  __    __  __" << std::endl;
	std::cout << "     / /__/        / /\\ \\  \\    / / | |       / /\\ \\  \\    / /\\ \\  \\   /\\ \\/\\_\\  /\\ \\/\\_\\" << std::endl;
	std::cout << "     | |  |  ___  /  \\ \\ \\  \\  / /| | | ___  / /  \\ \\  \\  /  \\ \\ \\  \\  \\ \\/ / /  \\ \\/ / /" << std::endl;
	std::cout << "     | |  | /\\__\\/ /\\ \\ \\ \\__\\/ / | | |/\\__\\/ /__/ \\ \\__\\/ /\\ \\ \\ \\__\\  \\  /_/    \\  /_/" << std::endl;
	std::cout << "     | |__|/ /  /\\ \\ \\ \\ \\/__/\\/_/| | / /  /\\ \\  \\ | |__|\\ \\ \\ \\ \\/__/  /  \\ \\    /  \\ \\" << std::endl;
	std::cout << "      \\_____/__/  \\ \\ \\ \\__\\      | |/ /  /  \\ \\  \\/ /  / \\ \\ \\ \\__\\   / /\\ \\_\\  / /\\ \\_\\" << std::endl;
	std::cout << "                   \\ \\ \\/__/      | / /  /    \\ \\_/ /  /   \\ \\ \\/__/   \\/_/\\/_/  \\/_/\\/_/" << std::endl;
	std::cout << "                    \\ \\__\\        |  /  /      \\___/__/     \\ \\__\\" << std::endl;
	std::cout << "                     \\/__/         \\/__/                     \\/__/" << std::endl;

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 37), 13});
	std::cout << (V.language ? "Recommendations Manager" : "Gestor de Recomendações");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 34), 15});
	std::cout << (V.language ? "Please select an option" : "Por favor selecione uma opção");

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 19});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 20});
	std::cout << "|" << BUTTONS[0].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 19});
	std::cout << "|" << BUTTONS[1].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 20});
	std::cout << "|" << BUTTONS[1].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 19});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 20});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 22});
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
			while (PersonalRecommendations(V)) // Definition in Recommendations Interface.cpp
				continue;
			break;
		case 1:
			if (V.clients_data.size() <= 10)
			{
				SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 29 : 24), 24});
				std::cout << (V.language ? "Not enough clients to create campaign!" : "Não há clientes suficientes para criar campanha!");

				Sleep(1000);

				break;
			}
			while (BottomTenCampaign(V)) // Definition in Recommendations Interface.cpp
				continue;
			break;
		case 2:
			return false;
	}
	return true;
}

// ========== View Functions Definitions ==========

bool ViewClientsInterface(Variables &V)
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 18;
	BUTTONS[0].Right = 25;
	BUTTONS[0].Bottom = 21;
	BUTTONS[0].TextLines = 2;
	BUTTONS[0].TextPos = new COORD[2];
	BUTTONS[0].TextPos[0] = {6, 19};
	BUTTONS[0].TextPos[1] = {6, 20};
	BUTTONS[0].Text = new std::string[2];
	BUTTONS[0].Text[0] = (V.language ? "     View list      " : "     Ver lista      ");
	BUTTONS[0].Text[1] = (V.language ? "     of clients     " : "     de clientes    ");
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 38;
	BUTTONS[1].Top = 18;
	BUTTONS[1].Right = 57;
	BUTTONS[1].Bottom = 21;
	BUTTONS[1].TextLines = 2;
	BUTTONS[1].TextPos = new COORD[2];
	BUTTONS[1].TextPos[0] = {38, 19};
	BUTTONS[1].TextPos[1] = {38, 20};
	BUTTONS[1].Text = new std::string[2];
	BUTTONS[1].Text[0] = (V.language ? "    View specific   " : "     Ver cliente    ");
	BUTTONS[1].Text[1] = (V.language ? "    client          " : "     específico     ");
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 70;
	BUTTONS[2].Top = 18;
	BUTTONS[2].Right = 89;
	BUTTONS[2].Bottom = 21;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {70, 19};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	std::cout << "        ___           ___          ___           ___          ___" << std::endl;
	std::cout << "       /\\__\\         /\\  \\        /\\__\\         /\\  \\        /\\  \\" << std::endl;
	std::cout << "      / /  /        /  \\  \\      /  | |        /  \\  \\      /  \\  \\     __  __    __  __" << std::endl;
	std::cout << "     / /__/        / /\\ \\  \\    / / | |       / /\\ \\  \\    / /\\ \\  \\   /\\ \\/\\_\\  /\\ \\/\\_\\" << std::endl;
	std::cout << "     | |  |  ___  /  \\ \\ \\  \\  / /| | | ___  / /  \\ \\  \\  /  \\ \\ \\  \\  \\ \\/ / /  \\ \\/ / /" << std::endl;
	std::cout << "     | |  | /\\__\\/ /\\ \\ \\ \\__\\/ / | | |/\\__\\/ /__/ \\ \\__\\/ /\\ \\ \\ \\__\\  \\  /_/    \\  /_/" << std::endl;
	std::cout << "     | |__|/ /  /\\ \\ \\ \\ \\/__/\\/_/| | / /  /\\ \\  \\ | |__|\\ \\ \\ \\ \\/__/  /  \\ \\    /  \\ \\" << std::endl;
	std::cout << "      \\_____/__/  \\ \\ \\ \\__\\      | |/ /  /  \\ \\  \\/ /  / \\ \\ \\ \\__\\   / /\\ \\_\\  / /\\ \\_\\" << std::endl;
	std::cout << "                   \\ \\ \\/__/      | / /  /    \\ \\_/ /  /   \\ \\ \\/__/   \\/_/\\/_/  \\/_/\\/_/" << std::endl;
	std::cout << "                    \\ \\__\\        |  /  /      \\___/__/     \\ \\__\\" << std::endl;
	std::cout << "                     \\/__/         \\/__/                     \\/__/" << std::endl;

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 41 : 39), 13});
	std::cout << (V.language ? "Clients Manager" : "Gestor de Clientes");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 34), 15});
	std::cout << (V.language ? "Please select an option" : "Por favor selecione uma opção");

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 19});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 20});
	std::cout << "|" << BUTTONS[0].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 19});
	std::cout << "|" << BUTTONS[1].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 20});
	std::cout << "|" << BUTTONS[1].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 19});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 20});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 22});
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
			while (ViewAllClients(V)) // Definition in Clients Interface.cpp
				continue;
			break;
		case 1:
			while (ViewSpecificClient(V)) // Definition in Clients Interface.cpp
				continue;
			break;
		case 2:
			return false;
	}
	return true;
}

bool ViewTransactionsInterface(Variables &V)
{
	ClearScreen(V);
	V.input = "";
	V.page = 0;

	unsigned option;
	std::vector<unsigned> ACTIVE_BUTTONS;
	BUTTON * BUTTONS = new BUTTON[3];

	BUTTONS[0].Left = 6;
	BUTTONS[0].Top = 18;
	BUTTONS[0].Right = 25;
	BUTTONS[0].Bottom = 21;
	BUTTONS[0].TextLines = 2;
	BUTTONS[0].TextPos = new COORD[2];
	BUTTONS[0].TextPos[0] = {6, 19};
	BUTTONS[0].TextPos[1] = {6, 20};
	BUTTONS[0].Text = new std::string[2];
	BUTTONS[0].Text[0] = (V.language ? "   View list        " : "    Ver lista       ");
	BUTTONS[0].Text[1] = (V.language ? "   of transactions  " : "    de transações   ");
	ACTIVE_BUTTONS.push_back(0);

	BUTTONS[1].Left = 38;
	BUTTONS[1].Top = 18;
	BUTTONS[1].Right = 57;
	BUTTONS[1].Bottom = 21;
	BUTTONS[1].TextLines = 2;
	BUTTONS[1].TextPos = new COORD[2];
	BUTTONS[1].TextPos[0] = {38, 19};
	BUTTONS[1].TextPos[1] = {38, 20};
	BUTTONS[1].Text = new std::string[2];
	BUTTONS[1].Text[0] = (V.language ? "    View specific   " : "   Ver transações   ");
	BUTTONS[1].Text[1] = (V.language ? "    transactions    " : "   específicas      ");
	ACTIVE_BUTTONS.push_back(1);

	BUTTONS[2].Left = 70;
	BUTTONS[2].Top = 18;
	BUTTONS[2].Right = 89;
	BUTTONS[2].Bottom = 21;
	BUTTONS[2].TextLines = 1;
	BUTTONS[2].TextPos = new COORD[1];
	BUTTONS[2].TextPos[0] = {70, 19};
	BUTTONS[2].Text = new std::string[1];
	BUTTONS[2].Text[0] = (V.language ? "       Return       " : "     Retroceder     ");
	ACTIVE_BUTTONS.push_back(2);

	std::cout << "        ___           ___          ___           ___          ___" << std::endl;
	std::cout << "       /\\__\\         /\\  \\        /\\__\\         /\\  \\        /\\  \\" << std::endl;
	std::cout << "      / /  /        /  \\  \\      /  | |        /  \\  \\      /  \\  \\     __  __    __  __" << std::endl;
	std::cout << "     / /__/        / /\\ \\  \\    / / | |       / /\\ \\  \\    / /\\ \\  \\   /\\ \\/\\_\\  /\\ \\/\\_\\" << std::endl;
	std::cout << "     | |  |  ___  /  \\ \\ \\  \\  / /| | | ___  / /  \\ \\  \\  /  \\ \\ \\  \\  \\ \\/ / /  \\ \\/ / /" << std::endl;
	std::cout << "     | |  | /\\__\\/ /\\ \\ \\ \\__\\/ / | | |/\\__\\/ /__/ \\ \\__\\/ /\\ \\ \\ \\__\\  \\  /_/    \\  /_/" << std::endl;
	std::cout << "     | |__|/ /  /\\ \\ \\ \\ \\/__/\\/_/| | / /  /\\ \\  \\ | |__|\\ \\ \\ \\ \\/__/  /  \\ \\    /  \\ \\" << std::endl;
	std::cout << "      \\_____/__/  \\ \\ \\ \\__\\      | |/ /  /  \\ \\  \\/ /  / \\ \\ \\ \\__\\   / /\\ \\_\\  / /\\ \\_\\" << std::endl;
	std::cout << "                   \\ \\ \\/__/      | / /  /    \\ \\_/ /  /   \\ \\ \\/__/   \\/_/\\/_/  \\/_/\\/_/" << std::endl;
	std::cout << "                    \\ \\__\\        |  /  /      \\___/__/     \\ \\__\\" << std::endl;
	std::cout << "                     \\/__/         \\/__/                     \\/__/" << std::endl;

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 38 : 38), 13});
	std::cout << (V.language ? "Transactions Manager" : "Gestor de Transações");

	SetConsoleCursorPosition(V.OUT_HANDLE, {(V.language ? 37 : 34), 15});
	std::cout << (V.language ? "Please select an option" : "Por favor selecione uma opção");

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 19});
	std::cout << "|" << BUTTONS[0].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 20});
	std::cout << "|" << BUTTONS[0].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {5, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 19});
	std::cout << "|" << BUTTONS[1].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 20});
	std::cout << "|" << BUTTONS[1].Text[1] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {37, 22});
	std::cout << "o--------------------o";

	Sleep(200);

	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 17});
	std::cout << "o--------------------o";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 18});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 19});
	std::cout << "|" << BUTTONS[2].Text[0] << "|";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 20});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 21});
	std::cout << "|                    |";
	SetConsoleCursorPosition(V.OUT_HANDLE, {69, 22});
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
			while (ViewAllTransactions(V)) // Definition in Transactions Interface.cpp
				continue;
			break;
		case 1:
			while (ViewSpecificTransactions(V)) // Definition in Transactions Interface.cpp
				continue;
			break;
		case 2:
			return false;
	}
	return true;
}

//====================================================================================================
// ========== End of File ==========
//====================================================================================================