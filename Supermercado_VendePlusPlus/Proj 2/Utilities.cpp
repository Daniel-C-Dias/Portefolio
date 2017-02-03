//====================================================================================================
// ========== Preprocessor Directives ==========
//====================================================================================================

#include "Interface.hpp"

//====================================================================================================
// ========== Functions Definitions ==========
//====================================================================================================

// Function called to clear the screen buffer
void ClearScreen(Variables &V)
{
	FillConsoleOutputAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes, V.OUT_BUFFER_SIZE, {0, 0}, V.FOOBAR); // Sets output attributes to default (defined in Entry Point.cpp)
	SetConsoleTextAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes); // Sets text attributes to default (defined in Entry Point.cpp)

	FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR)' ', V.OUT_BUFFER_SIZE, {0, 0}, V.FOOBAR); // Fills buffer with whitespace chars ' '
	SetConsoleCursorPosition(V.OUT_HANDLE, {0, 0}); // Sets cursor position to {0, 0}

	return;
}

// Matrix used in the recommendations interface
void LoadMatrix(Variables &V)
{
	std::vector<unsigned> exclients(1, 0); // Temporary vector that contains id's of clients that don't exist in the clients vector anymore (declared with one element with value 0 for easier evaluation)

	V.matrix.resize(V.clients_data.size(), std::vector<bool>(V.products_data.size(), false)); // Matrix constructor, with the number of clients in the first dimension and the number of products in the second dimension (Note that their position is the same as their respective vectors)

	for (unsigned i = 0; i < V.transactions_data.size(); ++i) // Tests if there are any transactions with id's that don't exist in the clients file anymore
	{
		for (unsigned j = 0; j < V.clients_data.size(); ++j)
		{
			if (V.transactions_data[i].GetId() == V.clients_data[j].GetId()) break;
			else if (j == V.clients_data.size() - 1) // If there are, it writes the id to the temporary vector and increases the size of the matrix in the first dimension
			{
				for (unsigned k = 0; k < exclients.size(); ++k)
				{
					if (V.transactions_data[i].GetId() == exclients[k]) break;
					else if (k == exclients.size() - 1) // Only writes to the temporary vector if it doesn't exist there yet (otherwise does nothing)
					{
						exclients.push_back(V.transactions_data[i].GetId());
						V.matrix.push_back(std::vector<bool>(V.products_data.size(), false));
					}
				}
			}
		}
	}

	exclients.erase(exclients.begin()); // Erases first element (with value 0)

	for (unsigned i = 0; i < V.transactions_data.size(); ++i) // Compares the transactions of each client (first dimension), setting to true in each product (second dimension) for the products that are found in each transaction
	{
		for (unsigned j = 0; j < V.clients_data.size() + exclients.size(); ++j)
		{
			if (V.transactions_data[i].GetId() == (j < V.clients_data.size() ? V.clients_data[j].GetId() : exclients[j - V.clients_data.size()])) // Compares ids
			{
				for (unsigned k = 0; k < V.transactions_data[i].GetPurchases().size(); ++k)
				{
					for (unsigned l = 0; l < V.products_data.size(); ++l)
					{
						if (V.transactions_data[i].GetPurchases()[k] == V.products_data[l].GetName()) // Compares purchases (products)
						{
							V.matrix[j][l] = true;
							break;
						}
					}
				}
			}
		}
	}
	return;
}

// Checks if V.input contains input in the form of a valid date
unsigned ValidDate(Variables &V)
{
	try
	{
		if (V.input == "")
			return 2; // If empty
		if (V.input.length() > 10)
			throw std::exception();
		std::string year = V.input.substr(6, 4), month = V.input.substr(3, 2), day = V.input.substr(0, 2);
		if (V.input[2] != '/' || V.input[5] != '/')
			throw std::exception();
		for (unsigned i = 0; i < 4; ++i)
		{
			if (i < 2 && (day[i] > 57 || day[i] < 48))
				throw std::exception();
			if (i < 2 && (month[i] > 57 || month[i] < 48))
				throw std::exception();
			if (year[i] > 57 || year[i] < 48)
				throw std::exception();
		}
		if (std::stoi(month) < 1 || std::stoi(month) > 12)
			throw std::exception();
		if (std::stoi(day) < 1 || std::stoi(day) >
			(std::stoi(month) == 1 || std::stoi(month) == 3 || std::stoi(month) == 5 || std::stoi(month) == 7 || std::stoi(month) == 8 || std::stoi(month) == 10 || std::stoi(month) == 12 ?
			31 :
			(std::stoi(month) != 2 ?
			30 :
			(((std::stoi(year) % 4 == 0 && std::stoi(year) % 100 != 0) || std::stoi(year) % 400 == 0) ?
			29 :
			28))))
			throw std::exception();
	}
	catch (...)
	{
		return 1; // If invalid
	}
	return 0; // If valid
}

// Function called to process user input
std::string Input(Variables &V, const unsigned &limit)
{
	std::string input; // String that contains the user input
	std::string::iterator it; // Iterator to move through string
	PSTR INPUT = new TCHAR[1]; // Pointer to a null-terminated string of 8-bit Windows (ANSI) characters
	PSTR RE_INPUT = new TCHAR[1]; // Pointer to a null-terminated string of 8-bit Windows (ANSI) characters
	
	input.reserve(std::numeric_limits<short>::max()); // Reserves as much space for the string as possible, so that the iterator remains defined
	it = input.end(); // Places iterator at the end of the string (position 0)

	V.CURSOR_INFO.bVisible = true;
	SetConsoleCursorInfo(V.OUT_HANDLE, &V.CURSOR_INFO); // Makes cursor visible

	FlushConsoleInputBuffer(V.IN_HANDLE); // Clears input buffer

	while (true) // Reads information until break
	{
		ReadConsoleInput(V.IN_HANDLE, V.IN_BUFFER, 1, V.FOOBAR); // Read user input to INPUT_RECORD V.IN_BUFFER

		if (V.IN_BUFFER[0].Event.KeyEvent.bKeyDown == TRUE) // If event was a key press
		{
			INPUT[0] = V.IN_BUFFER[0].Event.KeyEvent.uChar.AsciiChar; // Converts key information to TCHAR and moves it to INPUT[0]

			if (V.IN_BUFFER[0].Event.KeyEvent.wVirtualKeyCode == VK_RETURN) // If the key was the return key (enter)
			{
				for (; it != input.end(); ++it) // Moves cursor to the end of the string (useful for the interface)
				{
					SetConsoleCursorPosition(V.OUT_HANDLE, {++V.OUT_BUFFER.dwCursorPosition.X, V.OUT_BUFFER.dwCursorPosition.Y});
				}
				break; // Exits loop
			}
			else if (V.IN_BUFFER[0].Event.KeyEvent.wVirtualKeyCode == VK_LEFT) // If the key was the left arrow key
			{
				if (it != input.begin()) // If iterator is not at the beginning of the string
				{
					--it; // Moves iterator back
					SetConsoleCursorPosition(V.OUT_HANDLE, {--V.OUT_BUFFER.dwCursorPosition.X, V.OUT_BUFFER.dwCursorPosition.Y}); // Moves cursor back
				}
			}
			else if (V.IN_BUFFER[0].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) // If the key was the right arrow key
			{
				if (it != input.end()) // If iterator is not at the end of the string
				{
					SetConsoleCursorPosition(V.OUT_HANDLE, {++V.OUT_BUFFER.dwCursorPosition.X, V.OUT_BUFFER.dwCursorPosition.Y}); // Moves cursor forward
					++it; // Moves iterator forward
				}
			}
			else if (V.IN_BUFFER[0].Event.KeyEvent.wVirtualKeyCode == VK_BACK) // If the key was the backspace key
			{
				if (it != input.begin()) // If iterator is not at the beginning of the string
				{
					if (it != input.end()) // If iterator is not at the end of the string
					{
						--it; // Moves iterator back
						SetConsoleCursorPosition(V.OUT_HANDLE, {--V.OUT_BUFFER.dwCursorPosition.X, V.OUT_BUFFER.dwCursorPosition.Y}); // Moves cursor back

						input.erase(it); // Erases char at it
						for (std::string::iterator re_it = it; re_it != input.end(); ++re_it) // Overwrites screen buffer
						{
							RE_INPUT[0] = *re_it;

							WriteConsoleOutputCharacter(V.OUT_HANDLE, RE_INPUT, 1, {V.OUT_BUFFER.dwCursorPosition.X + (SHORT) std::distance(it, re_it), V.OUT_BUFFER.dwCursorPosition.Y}, V.FOOBAR);
							WriteConsoleOutputCharacter(V.OUT_HANDLE, " ", 1, {V.OUT_BUFFER.dwCursorPosition.X + (SHORT) std::distance(it, re_it) + 1, V.OUT_BUFFER.dwCursorPosition.Y}, V.FOOBAR);
						}
					}
					else // If iterator is at the end of the string
					{
						--it; // Moves iterator back
						SetConsoleCursorPosition(V.OUT_HANDLE, {--V.OUT_BUFFER.dwCursorPosition.X, V.OUT_BUFFER.dwCursorPosition.Y}); // Moves cursor back
						
						input.pop_back(); // Erases char at end
						WriteConsoleOutputCharacter(V.OUT_HANDLE, " ", 1, V.OUT_BUFFER.dwCursorPosition, V.FOOBAR); // Overwrites screen buffer
					}
				}
			}
			else if ((unsigned)INPUT[0] > 31 && input.size() < limit) // If the char in INPUT[0] has ASCII code superior to 31 (not a control char) and the string length is within the limit
			{
				if (it != input.end()) // If iterator is not at the end of the string
				{
					input.insert(it, INPUT[0]); // Inserts INPUT[0] in input at it
					for (std::string::iterator re_it = it; re_it != input.end(); ++re_it) // Overwrites screen buffer
					{
						RE_INPUT[0] = *re_it;

						WriteConsoleOutputCharacter(V.OUT_HANDLE, RE_INPUT, 1, {V.OUT_BUFFER.dwCursorPosition.X + (SHORT) std::distance(it, re_it), V.OUT_BUFFER.dwCursorPosition.Y}, V.FOOBAR);
					}

					SetConsoleCursorPosition(V.OUT_HANDLE, {++V.OUT_BUFFER.dwCursorPosition.X, V.OUT_BUFFER.dwCursorPosition.Y}); // Moves cursor forward
					++it; // Moves iterator forward
				}
				else
				{
					input.push_back(INPUT[0]); // Inserts INPUT[0] in string at end
					WriteConsoleOutputCharacter(V.OUT_HANDLE, INPUT, 1, V.OUT_BUFFER.dwCursorPosition, V.FOOBAR);  // Overwrites screen buffer

					SetConsoleCursorPosition(V.OUT_HANDLE, {++V.OUT_BUFFER.dwCursorPosition.X, V.OUT_BUFFER.dwCursorPosition.Y}); // Moves cursor forward
					++it; // Moves iterator forward
				}
			}
			else continue; // Any other kind of input is ignored
		}
	}

	V.CURSOR_INFO.bVisible = false;
	SetConsoleCursorInfo(V.OUT_HANDLE, &V.CURSOR_INFO); // Makes cursor invisible

	delete[] INPUT;
	delete[] RE_INPUT;

	return input;
}

// Function called to process user input
unsigned Event(Variables &V, BUTTON BUTTON[], const std::vector<unsigned> &ACTIVE_BUTTONS)
{
	int POS = -1; // Position in ACTIVE_BUTTONS of the button pressed
	unsigned ACT_BUT_NUM = ACTIVE_BUTTONS.size();

	SHORT * X_length = new SHORT[ACT_BUT_NUM]; // Width of the buttons
	SHORT * Y_length = new SHORT[ACT_BUT_NUM]; // Height of the buttons

	for (unsigned i = 0; i < ACT_BUT_NUM; ++i)
	{
		X_length[i] = BUTTON[ACTIVE_BUTTONS[i]].Right - BUTTON[ACTIVE_BUTTONS[i]].Left + 1;
		Y_length[i] = BUTTON[ACTIVE_BUTTONS[i]].Bottom - BUTTON[ACTIVE_BUTTONS[i]].Top + 1;
	}

	FlushConsoleInputBuffer(V.IN_HANDLE); // Clears input buffer

	while (true) // Reads information until break
	{
		ReadConsoleInput(V.IN_HANDLE, V.IN_BUFFER, 1, V.FOOBAR); // Read user input to INPUT_RECORD V.IN_BUFFER

		if (V.IN_BUFFER[0].Event.MouseEvent.dwEventFlags == MOUSE_MOVED) // If event was mouse movement
		{
			COORD POSITION = V.IN_BUFFER[0].Event.MouseEvent.dwMousePosition; // Creates COORD with mouse position

			if (POS != -1) // If there is a currently focused button
			{
				if (!(BUTTON[ACTIVE_BUTTONS[POS]].Left <= POSITION.X && POSITION.X <= BUTTON[ACTIVE_BUTTONS[POS]].Right && BUTTON[ACTIVE_BUTTONS[POS]].Top <= POSITION.Y && POSITION.Y <= BUTTON[ACTIVE_BUTTONS[POS]].Bottom)) // If POSITION doesn't match with the COORD of the focused button
				{					
					FillConsoleOutputAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes, V.OUT_BUFFER_SIZE, {0, 0}, V.FOOBAR); // Sets output attributes to default
					SetConsoleTextAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes); // Sets text attributes to default

					for (unsigned i = 0; i < BUTTON[ACTIVE_BUTTONS[POS]].TextLines; ++i)
					{						
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', BUTTON[ACTIVE_BUTTONS[POS]].Text[i].length(), BUTTON[ACTIVE_BUTTONS[POS]].TextPos[i], V.FOOBAR); // Changes button from focused to default
						SetConsoleCursorPosition(V.OUT_HANDLE, BUTTON[ACTIVE_BUTTONS[POS]].TextPos[i]); 
						std::cout << BUTTON[ACTIVE_BUTTONS[POS]].Text[i]; // Changes button text from focused to default
					}
				}
				else continue; // If POSITION matches then checks the next event
			}

			POS = -1; // Changes POS to no position

			for (unsigned i = 0; i < ACT_BUT_NUM; ++i) // Tests for all buttons
			{
				if (BUTTON[ACTIVE_BUTTONS[i]].Left <= POSITION.X && POSITION.X <= BUTTON[ACTIVE_BUTTONS[i]].Right && BUTTON[ACTIVE_BUTTONS[i]].Top <= POSITION.Y && POSITION.Y <= BUTTON[ACTIVE_BUTTONS[i]].Bottom) // If POSITION is in a button's focus limit
				{
					for (SHORT j = 0; j < Y_length[i]; ++j)
					{
						FillConsoleOutputAttribute(V.OUT_HANDLE, V.EVENT_OUT_BUFFER.wAttributes, X_length[i], {BUTTON[ACTIVE_BUTTONS[i]].Left, BUTTON[ACTIVE_BUTTONS[i]].Top + j}, V.FOOBAR); // Set output attributes inside the button's focus limit to focused
					}
					SetConsoleTextAttribute(V.OUT_HANDLE, V.EVENT_OUT_BUFFER.wAttributes); // Set text attributes to focused

					for (unsigned j = 0; j < BUTTON[ACTIVE_BUTTONS[i]].TextLines; ++j)
					{
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', BUTTON[ACTIVE_BUTTONS[i]].Text[j].length(), BUTTON[ACTIVE_BUTTONS[i]].TextPos[j], V.FOOBAR); // Changes button from default to focused
						SetConsoleCursorPosition(V.OUT_HANDLE, BUTTON[ACTIVE_BUTTONS[i]].TextPos[j]);
						std::cout << BUTTON[ACTIVE_BUTTONS[i]].Text[j]; // Changes button text from default to focused
					}

					POS = i; // Changes POS to the position in ACTIVE_BUTTON of the focused button
					break;
				}
			}
		}
		else if (V.IN_BUFFER[0].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) // If event was a mouse click (left button)
		{
			if (POS != -1) // If there is a currently focused button
			{
				FillConsoleOutputAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes, V.OUT_BUFFER_SIZE, {0, 0}, V.FOOBAR); // Sets output attributes to default
				SetConsoleTextAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes); // Sets text attributes to default

				delete[] X_length;
				delete[] Y_length;

				return ACTIVE_BUTTONS[POS];
			}
		}
		else if (V.IN_BUFFER[0].Event.KeyEvent.bKeyDown == TRUE) // If event was a key press
		{
			if (POS != -1) // If there is a currently focused button
			{
				switch (V.IN_BUFFER[0].Event.KeyEvent.wVirtualKeyCode)
				{
					case (VK_RETURN): // If the key was the return key (enter)
						FillConsoleOutputAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes, V.OUT_BUFFER_SIZE, {0, 0}, V.FOOBAR); // Sets output attributes to default
						SetConsoleTextAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes); // Sets text attributes to default

						delete[] X_length;
						delete[] Y_length;

						return ACTIVE_BUTTONS[POS];
					case (VK_LEFT):
					case (VK_RIGHT): // If the key was the left arrow key or the right arrow key
						FillConsoleOutputAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes, V.OUT_BUFFER_SIZE, {0, 0}, V.FOOBAR); // Sets output attributes to default
						SetConsoleTextAttribute(V.OUT_HANDLE, V.OUT_BUFFER.wAttributes); // Sets text attributes to default

						for (unsigned i = 0; i < BUTTON[ACTIVE_BUTTONS[POS]].TextLines; ++i)
						{
							FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', BUTTON[ACTIVE_BUTTONS[POS]].Text[i].length(), BUTTON[ACTIVE_BUTTONS[POS]].TextPos[i], V.FOOBAR);  // Changes button from focused to default
							SetConsoleCursorPosition(V.OUT_HANDLE, BUTTON[ACTIVE_BUTTONS[POS]].TextPos[i]);
							std::cout << BUTTON[ACTIVE_BUTTONS[POS]].Text[i]; // Changes button text from focused to default
						}
				}
			}
			switch (V.IN_BUFFER[0].Event.KeyEvent.wVirtualKeyCode)
			{
				case (VK_LEFT): // If the key was the left arrow key
					POS == 0 || POS == -1 ? POS = ACT_BUT_NUM - 1 : --POS;
					break;
				case (VK_RIGHT): // If the key was the right arrow key
					POS == ACT_BUT_NUM - 1 || POS == -1 ? POS = 0 : ++POS;
					break;
			}
			switch (V.IN_BUFFER[0].Event.KeyEvent.wVirtualKeyCode)
			{
				case (VK_LEFT):
				case (VK_RIGHT): // If the key was the left arrow key or the right arrow key
					for (SHORT i = 0; i < Y_length[POS]; ++i)
					{
						FillConsoleOutputAttribute(V.OUT_HANDLE, V.EVENT_OUT_BUFFER.wAttributes, X_length[POS], {BUTTON[ACTIVE_BUTTONS[POS]].Left, BUTTON[ACTIVE_BUTTONS[POS]].Top + i}, V.FOOBAR); // Set output attributes inside the button's focus limit to focused
					}
					SetConsoleTextAttribute(V.OUT_HANDLE, V.EVENT_OUT_BUFFER.wAttributes); // Set text attributes to focused

					for (unsigned i = 0; i < BUTTON[ACTIVE_BUTTONS[POS]].TextLines; ++i)
					{
						FillConsoleOutputCharacter(V.OUT_HANDLE, (TCHAR) ' ', BUTTON[ACTIVE_BUTTONS[POS]].Text[i].length(), BUTTON[ACTIVE_BUTTONS[POS]].TextPos[i], V.FOOBAR); // Changes button from default to focused
						SetConsoleCursorPosition(V.OUT_HANDLE, BUTTON[ACTIVE_BUTTONS[POS]].TextPos[i]);
						std::cout << BUTTON[ACTIVE_BUTTONS[POS]].Text[i]; // Changes button text from default to focused
					}
			}
		}
	}
}

//====================================================================================================
// ========== End of File ==========
//====================================================================================================