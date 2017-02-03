#include<iostream>
#include<conio.h>
#include<ctime>
#include <windows.h>

using namespace std;

bool gameover;
const int widht = 40;
const int height = 40;
int x, y, fruitX, fruitY, score;
int tailx[100], taily[100];
int ntail; // specifies the lenght of the tail

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir; //it will hold the direction of the snake



void Setup() {

	gameover = false;
	dir = STOP;
	x = widht / 2;    //position of the skane head
	y = height / 2;   // it will be centered on the map
	fruitX = rand() % widht;
	fruitY = rand() % height;
	score = 0;

}

void Draw() {
	
	system("cls"); // it clear the console window

	for (int i = 0; i < widht+2; ++i)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; ++i) {

		for (int j = 0; j < widht; ++j) {

			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "<";
			else if (i == fruitY && j == fruitX)
				cout << "*";
			
			else {

				bool print = false;

				for (int k = 0; k < ntail; ++k) {
					if (tailx[k] == j && taily[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
				
			}
				

			if (j == widht - 1)
				cout << "#";

		}
		cout << endl;
	}

	for (int i = 0; i < widht+2 ; ++i)
		cout << "#";
	cout << endl;

	cout << "Score: " << score << endl;

}

void Input() {

	if (_kbhit()) {

		switch (_getch()) {
		
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'l':
			gameover = true;
			break;

		}
	}

}

void Logic() {

	// lets record the previous segment of the tail
	int prevx = tailx[0];
	int prevy = taily[0];

	int prev2x, prev2y;

	//setting the first segment of the tai to follow the head
	tailx[0] = x;
	taily[0] = y;

	for (int i = 1; i < ntail; ++i) {

		prev2x = tailx[i];
		prev2y = taily[i];

		tailx[i] = prevx;
		taily[i] = prevy;

		prevx = prev2x;
		prevy = prev2y;

	}

	switch (dir)
	{
	case LEFT:
		--x;
		break;
	case RIGHT:
		++x;
		break;
	case UP:
		--y;
		break;
	case DOWN:
		++y;
		break;
	default:
		break;
	}

	if (x > widht || x < 0 || y > height || y < 0) {
		//gameover = true; // terminates if it hits the wall (uncomment to turn it on)

		// to make the snake teleport if it hits the wall 
		if (x >= widht) {
			x = 0;
		}
		else if (x < 0)	{
			x = widht - 1;
		}

		if (y >= height) {
			y = 0;
		}
		else if (y < 0) {
			y = height - 1;
		}
	}

	for (int i = 0; i < ntail; ++i) {
		if (tailx[i] == x && taily[i] == y)
			gameover = true;
	}

	if (x == fruitX && y == fruitY) {

		score += 10;
		++ntail;

		// put the fruit in some other place in the map
		fruitX = rand() % widht;
		fruitY = rand() % height;

	}

}


int main() {

	Setup();

	while (!gameover) {

		Draw();
		Input();
		Logic();
		Sleep(25);
		
	}

	return 0;
}