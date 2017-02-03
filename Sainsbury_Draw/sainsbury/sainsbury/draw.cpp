#include <random>
#include <iostream>
#include <cmath>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <iomanip> 
#include <cctype>


using namespace std;

int main()

{

	int max, n; // maximum of contestants, number of prizes to give,

	cout << "Let's Start the Sainsbury Draw!\n\nHow many contestants are entering: ";
	cin >> max;

	if (cin.fail()) // verify if input number is integer
	{
		cin.clear();
		cin.ignore(1000, '\n');

		cout << "\nThat number is not valid!\n\nPlease insert correct number of contestans: ";
		cin >> max;
	}

	cout << "\nHow many prizes are we giving out today?: ";
	cin >> n;

	if (cin.fail()) // verify if input number is integer
	{
		cin.clear();
		cin.ignore(1000, '\n');

		cout << "\nThat number is not valid!\n\nPlease insert correct number of prizes to give: ";
		cin >> n;
	}


	random_device rd; // obtain a random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr(1, max); // define the range

	for (int i = 1; i <= n; ++i)
	{ 

		cout << "\nAnd Winner Number " << i << " is: " << distr(eng) << ' ' << endl; // generate numbers
	}
	
	system("pause");
	return 0;

}
