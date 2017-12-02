//John F Williams 
// 105201054
// CSCI 2312 -->PA2


#include"GameOfLife2_csci2312.h"
#include<new>
#include <ctime>
#include<random>
#include <iostream>



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//the following line is necessary for the
//  GetConsoleWindow() function to work!
//it basically says that you are running this
//  program on Windows 2000 or higher
#define _WIN32_WINNT 0x0500

//it is important that the above line be typed
//  BEFORE <windows.h> is included
#include "windows.h"
#include <string>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace csci2312;
using namespace std; 
//int** seedBoard(int**ptr, int size);    remove evenetually
int main()
{

	string size;
	string iterations;
	int numberOfIterations; 
	int sizeOfBoard = 0;
	char option = 'z';
	HWND console = GetConsoleWindow();


	cout << "Welcome to the game of life" << endl;

	while(true)
	{ 


	cout << "\t\tPlease select an option:" << endl<<endl<<endl;
	cout << "\t\tA: Load a standard board of size 30X30" << endl;
	cout << "\t\tB: Select a specific size for the board" << endl;
	cout << "\t\tC: EXIT" << endl;
	
	cout << endl<<endl<<"***NOTE*** a size of 30 or 40 will allow the user to upload a specific file" << endl;

		
	
	cin >> option;
	switch (toupper(option))
	{
		case 'A':
		{
			csci2312::GameOfLife game;

			RECT r;
			GetWindowRect(console, &r); //stores the console's current dimensions
			MoveWindow(console, -8, 0, 600, 575, TRUE);
			game.run();
			break;
		}
		case 'B':
		{
			cout << "How large should the board be??" << endl;

			cin.ignore();
			getline(cin, size);

			sizeOfBoard = atoi(size.c_str());

			while (sizeOfBoard == 0)
			{
				cout << "Please enter a valid board size" << endl;
				getline(cin, size);
				sizeOfBoard = atoi(size.c_str());

			}


			try
			{

				csci2312::GameOfLife game1(sizeOfBoard);
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//HWND console = GetConsoleWindow();
				RECT r;
				GetWindowRect(console, &r); //stores the console's current dimensions

											//MoveWindow(window_handle, x, y, width, height, redraw_window);
											//		MoveWindow(console, r.left, r.top, 800, 600, TRUE);



				MoveWindow(console, -8, 0, 10000, 10000, TRUE);
				//MoveWindow(console, r.top, r.bottom, -8, 768, TRUE);

				//MoveWindow(console, r.right, r.top,1000, 1000, TRUE);
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				game1.run();

			}
			catch (bad_alloc m)
			{
				cout << "The current memory available cannot sustain the size you selected";
				cout << "Please try another size" << endl;
				continue;
			}
			

			break;
		}
		case 'C':
		{
			cout << endl << endl << "\t\tGOODBYE" << endl;
			return 0;
		}
	default:
		{
			cout << endl<<"\tPlease enter a VALID selection\a" << endl << endl << endl;	
			break;
		}
	}


	
	}

	
}

