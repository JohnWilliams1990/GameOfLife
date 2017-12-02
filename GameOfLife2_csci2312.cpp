//John F Williams 
// 105201054
// CSCI 2312 -->PA2

//	[~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~]1
//	[~][->][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]2
//  [~][][][][][][][][][][][][][][][][][1][2][3]|[][][][][][][][~]3
//	[~][][][][][][][][][][][][][][][][][8][X][4]|[][][][][][][][~]4
//	[~][][][][][][][][][][][][][][][][][7][6][5]|[][][][][][][][~]5
//  [~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]6
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]7
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]8
//  [~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]9
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]10
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]11
//  [~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]12
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]13
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]14
//  [~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]15
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]16
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]17
//  [~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]18
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]19
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]20
//  [~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]21
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]22
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]23
//  [~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]24
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]25
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]26
//  [~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]27
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]28
//	[~][][][][][][][][][][][][][][][][][][][][][][][][][][][][][~]29
//  [~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~][~]30

//the following line is necessary for the
//  GetConsoleWindow() function to work!
//it basically says that you are running this
//  program on Windows 2000 or higher
#define _WIN32_WINNT 0x0500

//it is important that the above line be typed
//  BEFORE <windows.h> is included
#define _CRT_SECURE_NO_WARNINGS // remove the secure warnings for the compiler
#include <cwchar> // size of font

#include <windows.h>
#include "GameOfLife2_csci2312.h"
#include<new>
#include<ctime>
#include <iostream>
#include<thread>
#include <string>
#include <fstream>

using namespace std;
using std::bad_alloc;
void swapLarge(int);


namespace csci2312
{
	HWND console = GetConsoleWindow();
	RECT r;
	
	
	// PA2: Constructs the board of the requested size, can throw exception.
	// If parameter is omitted, it becomes the default constructor, and the board will have MAX_BOARD size
	
	
	GameOfLife::GameOfLife(size_t boardSize ) throw (bad_alloc)//GameOfLife::GameOfLife(size_t boardSize = MAX_BOARD) throw (bad_alloc)
	{
	
		bad_alloc m;
		CellPtr* cellPtr = nullptr;
		/*cellPtr = currentLife;
		*/

		// dynamicly create a board for current life 
		currentLife = new CellPtr[boardSize+2];
		

		for (int i = 0; i < boardSize+2; i++)
		{
			currentLife[i] = new Cell[boardSize+2];
		}
		// // dynamicly create a board for nextlife;
		
		
		nextLife = new CellPtr[boardSize + 2];
		for (int i = 0; i < boardSize + 2; i++)
		{
			nextLife[i] = new Cell[boardSize + 2];
		}
		this->boardSize = boardSize;

		
	}

	// PA2:  Copy-constructor creates a new instance as a deep copy of the referenced object
	GameOfLife::GameOfLife(const GameOfLife& game) 
	{
		////////////////////////////////////////////////////////////////////////////////////////////
		**game.currentLife = new CellPtr[this->boardSize+2];

		for (int i = 0; i < this->boardSize + 2; i++)
		{
			game.currentLife[i] = new Cell[this->boardSize + 2];
		}


		for (int i = 0; i < this->boardSize + 2; i++)
		{

			for (int j = 0; j < this->boardSize + 2; j++)
			{
				game.currentLife[i][j].setState(true);
				game.currentLife[i][j] = this->currentLife[i][j];
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////


		////////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < this->boardSize + 2; i++)
		{
			delete[] this->currentLife[i];
			delete[] this->nextLife[i];

		}
		
		delete[] this->currentLife;
		delete[] this->nextLife;

		this->currentLife = nullptr;
		this->nextLife = nullptr;
		////////////////////////////////////////////////////////////////////////////////////////////

		//game.boardSize = boardSize;


	}

	// PA2:  destructor must release memory taken by dynamic arrays
	GameOfLife::~GameOfLife()
	{

		
		for (int i = 0; i < boardSize+2; i++)
		{
			delete[] this->currentLife[i];
			delete[] this->nextLife[i];
			currentLife[i] = nullptr;
			nextLife[i] = nullptr;
		}
		delete[] this->currentLife;
		delete[] this->nextLife;

		this->currentLife = nullptr;
		this->nextLife = nullptr;
	}

	
	// PA2: seeds the board from a file and throws an exception if there was trouble with file
	void GameOfLife::seedBoard(string fileName) throw (FileIOException) 
	{
	
		FileIOException e;
		fstream file;
		string temp;
		string line;
		int count = 0; 
		char ch;

		file.open(fileName);

		if (file.fail())//throw
		{
		
			throw e;
			
		}
		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < boardSize + 2; i++)// size			
		{
			for (int j = 0; j < boardSize + 2; j++)// size 
			{
				currentLife[i][j].setState(false);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		while (!file.eof())
		{
			file >> *this;
			count++;
		
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (count > boardSize  )
		{
			cout << "\t\t*NOTE* BOARDSIZE IS INCOMPATABLE" << endl;
			throw e;
		}

		if (boardSize > 70)
			swapLarge(5);
		cout << *this << endl;
		cout << endl << "Press any key to continue" << endl << endl;
		cin.ignore();
		cin.get(ch);

		system("CLS");
		swapLarge(18);

		
		//system("PAUSE");
	}

	// PA1 and PA2: seeds the  board with a given number of seeds at randomized locations
	void GameOfLife::seedBoard(size_t seeds)
	{


		unsigned long long int seed = time(0);// seed to seed the rand() function for actual randomization 

											  //srand(rand());


		srand(seed);// seed the rand()



		for (int i = 0; i < boardSize+2; i++)// size			
		{
			for (int j = 0; j < boardSize+2; j++)// size 
			{
				currentLife[i][j].setState(false);
			}
		}
		


		int col = 0;
		int row = 0;
		
			for (int i = 0; i < (boardSize + 2); i++)
			{
				for (int j = 0; j < (boardSize + 2); j++)
				{


					row = (rand()) % (boardSize + 2);
					col = (rand()) % (boardSize + 2);
					if(i*j%10 > 0)
					currentLife[col][row].setState(true);
				}
			}
		
		



			////////////////////////////////////////////////////////////////////////////////////////////


			
	}


	




	// PA1 and PA2: 
	void GameOfLife::run() 
	{
		char ch = ' ';
		char option; 
		bool menu = true;

		system("CLS");
		
		while (menu == true)
		{

			

		cout << "Please select an option" << endl;
		cout << "A: Load a random board" << endl;
		cout << "B: load from a file" << endl;
		cout << "C: Run the game with x number iterations" << endl;
		cout << "D: Run the game one step at a time" << endl;
		cout << "E: Edit board" << endl;
		cout << "F: Clear board" << endl;
		cout << "G: EXIT to main menu and save current board" << endl;
		

		cin >> option;



			switch (toupper(option))
			{

			
			case 'A':
			{


				seedBoard(this->boardSize);
				if (boardSize > 70)
					swapLarge(5);
				system("CLS");

				cout << *this << endl;
				system("Pause");
				system("CLS");
				swapLarge(18);
				cout << endl << "Press any key to continue" << endl << endl;
				cin.ignore();
				cin.get(ch);

				//system("PAUSE");

				break;
			}
			case 'B':
			{

				string filename;
				if (boardSize == 30)
				{
					

					cout << "Please select an file" << endl;				
					cout << "A: Load Flipper Army" << endl;
					cout << "B: Load Glider Army" << endl;
					cout << "C: Load Pentadecathlon (period 15)" << endl;
					cout << "D: Load Pulsar (period 3)" << endl;
					cout << "E: Load Queen Bee Shuttle, (period 30)" << endl;
					cout << "F: Load Last game saved" << endl;


					cout << endl << endl << endl;
					cout << "Files for Seeds (cellular automaton){b2/s}" << endl;
					cout << "G: Load flipper" << endl;
					cout << "H: simple starter" << endl;


					cin >> option;

					switch (toupper(option))
					{
					case 'A':
					{
						 filename = "run1.txt";
						break;
					}
					case 'B':
					{
						 filename = "run2.txt";
						break;
					}case 'C':
					{
						 filename = "run3.txt";
						break;
					}case 'D':
					{
						 filename = "run4.txt";
						break;
					}
					case 'E':
					{
						filename = "run5.txt";
						break;
					}

					case 'F':
					{
						filename = "Last iteration.txt";
						break;
					}
					case 'G':
					{
						filename = "run7.txt";
						break;
					}
					case 'H':
					{
						filename = "run8.txt";
						break;
					}
					default:
					{
						cout << endl << endl << "\t\tPlease Select A Valid Option" << endl;
					}

					}
					FileIOException e;

					try
					{
						
						seedBoard(filename);
					}
					catch (FileIOException)
					{
						cout << endl <<"\t\t\tThere was an error opening the file." << endl;
						cout << "\t\t\tPlease Check the file and try again" << endl << endl;
						

						cout << endl << "Press any key to continue" << endl << endl;
						cin.ignore();
						cin.get(ch);

						//system("pause");
					}
				}
				else if (boardSize == 100)
				{
					filename = "run10.txt";

					try
					{
						seedBoard(filename);

					}
					catch (FileIOException)
					{
						cout << endl << "\t\t\tThere was an error opening the file." << endl;
						cout << "\t\t\tPlease Check the file and try again" << endl << endl;

					}
				}

				else if (boardSize == 40)
				{

					cout << "A:Load Queen Bee Shuttle, (period 30)" << endl;
					cout << "B:Load Last game saved" << endl;

					cin >> option;
					if (toupper(option) == 'A')
					{

						filename = "run6.txt"; /// gossiper gun 
					}
					else if (toupper(option) == 'B')
					{
						filename = "Last iteration.txt";

					}

					else
					{
						cout << endl << endl << "\t\tPlease Select A Valid Option" << endl;

					}

				
					

						try
						{
							seedBoard(filename);

						}
						catch (FileIOException)
						{
							cout << endl << "\t\t\tThere was an error opening the file." << endl;
							cout << "\t\t\tPlease Check the file and try again" << endl << endl;

						}

					}

			


					

				break;
			}
			case 'C':
			{
				string iterations;
				int numberOfIterations = 0;
				cout << "How many iterations of the game?" << endl;
				getline(cin, iterations);
				numberOfIterations = atoi(iterations.c_str());


				while (numberOfIterations == 0)
				{
					cout << "Please enter a valid number of iterations" << endl;
					getline(cin, iterations);
					numberOfIterations = atoi(iterations.c_str());

				}
		
	




				
				
				run(numberOfIterations);
				system("CLS");
				swapLarge(18);



				break;
			}
			case 'D':
			{
				system("CLS");
				int rule = -9;
				cout << "What version of Conway's game would yo like to load??" << endl;

				cout << "A: Standard version" << endl;
				cout << "B: Highlife (cellular automaton)" << endl;

				cin >> option;

				while (toupper(option) != 'A'&&toupper(option) != 'B')
				{
					cout << "What version of Conway's game would yo like to load??" << endl;

					cout << "A: Standard version" << endl;
					cout << "B: Highlife (cellular automaton)" << endl;

					cin >> option;
				}
				if (toupper(option) == 'A')
				{
					rule = 0;
				}
				else if (toupper(option) == 'B')
				{
					rule = 1;
				}


				cout << endl << endl << endl << endl << "\t\tENTER X TO EXIT THIS PORTION OF THE PROGRAM" << endl;
				cout << "\t\tOTHERWISE PRESS ENTER TO MOVE TO THE NEXT ITERATION" << endl;

				
				cout << endl << "Press any key to continue" << endl << endl;
				cin.get(ch);
				while (true)
				{

					cin.get(ch);

					if (toupper(ch) == 'X')
					{
						break;
						{


						}
					}
					if (boardSize > 70)
					swapLarge(5);
					cout << *this << endl;

					
					//////////////////////////////////////////
					calculateNextGen(currentLife, nextLife, rule);
					////////////////////////////////////////////////////////
					
				}
				system("CLS");
				swapLarge(18);
				break;
			}

			case 'E':
			{
				int indexRow = 0;

				int indexCol = 0;
				cout << "Please enter the row of the cell you wish to edit within the boardsize" << endl;
				cin >> indexRow;

				cout << "Please enter the column of the cell you wish to edit within the boardsize" << endl;
				cin >> indexCol;

				while (indexRow > boardSize||indexCol > boardSize)
				{
					cout << "Please enter a valid cell number" << endl;
					cout << "Please enter the row of the cell you wish to edit within the boardsize" << endl;
					cin >> indexRow;

					cout << "Please enter the column of the cell you wish to edit within the boardsize" << endl;
					cin >> indexCol;

				}

				currentLife[indexRow][indexCol].setState(true);
				cout << *this;

				cout << endl << "Press any key to continue" << endl << endl;
				cin.ignore();
				cin.get(ch);


				break;

			}
			case 'F':
			{

				for (int i = 0; i < boardSize +2; i++)
				{
					for (int j = 0; j < boardSize + 2; j++)
					{
						currentLife[i][j].setState(false);

					}
				}

				cout << *this;


				cout << endl << "Press any key to continue" << endl << endl;
				cin.ignore();
				cin.get(ch);

				break;
			}
			case 'G':
			{
				fstream file;
				string filename;
				int name1;
				int name2; 
				int name3;
				//if (boardSize > 100)
				//{
				//	name1 = boardSize / 100;
				//	name2 = (boardSize % 100) / 10;
				//	name3 = (boardSize % 100) % 10;
				//}
				//cout << name1 << name2 << name3 << endl;
				//filename = (static_cast<char>(name1))+ (static_cast<char>(name1))+ (static_cast<char>(name1));
				///*filename = static_cast<char>(name2);
				//filename =  static_cast<char>(name3);*/
				//cout << "filename:"<<filename << endl;
				//filename = string::insert(static_cast<char>(name1))
			
					filename = "Last iteration.txt";
				if (this->boardSize == 40)
					filename = "Last iteration size40.txt";


				file.open(filename, ios::out);

				file << endl << endl;
				for (int i = 0; i < (boardSize + 2); i++)
				{
					file << "\t";
					for (int j = 0; j < (boardSize + 2); j++)
					{
						file << currentLife[i][j].getState() << " ";
					}
					file << endl;
				}

				//file << *this;
				file.close();
				system("cls");
				return;
				

			}
			}
		}
	
	}
	void GameOfLife::run(unsigned int numberOfIterations) 
	{
		int iteraton = 0;
		char option = ' ';
		int rule = -9;
		cout << "What version of Conway's game would yo like to load??" << endl;

		cout << "A: Standard version" << endl;
		cout << "B: Highlife (cellular automaton)" << endl;

		cin >> option;

		while (toupper(option) != 'A'&&toupper(option) != 'B')
		{
			cout << "What version of Conway's game would yo like to load??" << endl;

			cout << "A: Standard version" << endl;
			cout << "B: Highlife (cellular automaton)" << endl;

			cin >> option;
		}
		if (toupper(option) == 'A')
		{
			rule = 0;
		}
		else if (toupper(option) == 'B')
		{
			rule = 1;
		}
		if (boardSize > 70)
		swapLarge(5);
		while (iteraton < numberOfIterations)

		{

			
			cout << *this << endl;
			//////////////////////////////////////////
			calculateNextGen(currentLife, nextLife, rule);
			////////////////////////////////////////////////////////
			
			// sleep pauses the screen for the user to briefly study the screen and not notice my mistakes
			////////////////////////////////////////////////////////////////////////////////////
			
			std::this_thread::sleep_for(std::chrono::seconds(1));
			//system("CLS");

			/*http://stackoverflow.com/questions/26047412/cant-compile-c-code-with-sleep-on-linux-which-library-to-include*/
			//Sleep(1000);//Sleep(1000); // Sleep function used to delay the prompt to the screen 


			iteraton++;
		}


		//need to make a set up of the number of iterations either in main or in the run();
	
	
	}

	// Just an example of an possible accessor which reaches to a private array.  Not needed to satisfy PAs
	// A const(!) accessor method that returns a handle to the private currentLife array. 
	// The return type must also be 'const' because we return a pointer to a static array, and these are fixed
	// It is just an example.  It is not needed if we have a friend operator.		
	// PA1: const Cell(*getCurrentLife() const )[MAX_BOARD+2]  { return currentLife; };
	// PA2: const CellPtr* getCurrentLIfe() const { return currentLife; };

	// PA1 and PA2:  overloaded output operator to displsy the board 
	// friend operator can access private members of GameOfLife
	ostream& operator << (ostream& out, const GameOfLife& board) 
	{
		/*
		out << " ~";
		for (int i = 1; i < (board.boardSize + 1); i++)
		{
			out << " ~";
		}
		out << endl;*/

		for (int i = 1; i < (board.boardSize + 1) ; i++)/// (board.boardSize + 1)/ 2 - 10
		{
			out << "| ";
			for (int j = 1; j < (board.boardSize + 1) ; j++)
			{
				if (board.currentLife[i][j].getState() == true)
				out << board.currentLife[i][j].alive << " ";
				
				else if (board.currentLife[i][j].getState() == false)
					out << "  ";//out << board.currentLife[i][j].dead << " "; //out << "  ";
			}
			//if (i < board.boardSize)
				out << "|";
				out << endl;//out << board.currentLife[i][j].dead << " ";

		}
		//out << endl;

		for (int i = 1; i < (board.boardSize + 2); i++)
		{
			out << " ~";
		}

		return out;
	}

	// PA2:  overloaded input operator to input the board (from file of keyboard)
	istream& operator >> (istream& in, const GameOfLife& board)
	{
		char character;
		for (int i = 1; i < (board.boardSize + 1); i++)
		{
			for (int j = 1; j < (board.boardSize + 1); j++)
			{
				in >> character;
				if (static_cast<int>(character) == 48)
					
					board.currentLife[i][j].setState(false);

				else if(static_cast<int>(character) == 49)
					 board.currentLife[i][j].setState(true);
			}
		}
	
			
	
	
		return in;
	}



	bool GameOfLife::executeRule110(unsigned int countAlive, bool currentState)
	{
		
				if (countAlive <= 2 && currentState == false)//(m[i][j] <= 2 && currentLife[i][j].getState() == false)
				{
					return false;
				}
				if (countAlive < 2 && currentState == true)  // if
				{
					return false;
				}
				else if (countAlive == 3 && currentState == false)
				{
					return true;
				}
				else if (countAlive > 3 && currentState == true)
				{
					return false;
				}
				else if (countAlive > 3 && currentState == false)
				{
					return false;
				}
		
		
	}

	bool GameOfLife::executeRuleXXX(unsigned int countAlive, bool currentState)
	{
		/* In each time step, a cell turns on or is "born" if 
		it was off or "dead" but had exactly two neighbors that were on; all other cells turn off.*/
		
		if (countAlive == 2 && currentState == false)
		{
			return true;
		}

		else 		
		{
			return false;
		}
		
	}

	void GameOfLife::calculateNextGen(CellPtr *current, CellPtr *next, int rule)
	{
		

	



		typedef int* ptr;

		ptr * m = new ptr[boardSize + 2];

		for (int i = 0; i < boardSize + 2; i++)
		{
			m[i] = new int[boardSize + 2];
		}


		//initilaize to zero
		for (int i = 0; i < boardSize + 2; i++)
		{
			for (int j = 0; j < boardSize + 2; j++)
			{
				m[i][j] = 0;

			}
		}


		int number = 0;
		for (int i = 1; i < boardSize + 1; i++)
		{

			//[-1,-1][-1,0][-1,1]
			//[0,-1][0,0][0,1]
			//[1,-1][1,0][1,1]
			for (int j = 1; j < boardSize + 1; j++)
			{
				number = 0;
				if (currentLife[i - 1][j - 1].getState() == true)//[-1][-1]
				{
					number++;
				}
				if (currentLife[i][j - 1].getState() == true)
				{
					number++;
				}
				if (currentLife[i + 1][j - 1].getState() == true)
				{
					number++;
				}
				if (currentLife[i - 1][j].getState() == true)
				{
					number++;
				}
				if (currentLife[i + 1][j].getState() == true)
				{
					number++;
				}
				if (currentLife[i - 1][j + 1].getState() == true)
				{
					number++;
				}
				if (currentLife[i][j + 1].getState() == true)
				{
					number++;
				}
				if (currentLife[i + 1][j + 1].getState() == true)
				{
					number++;
				}

				m[i][j] = number;
				number = 0;
			}
		}

		for (int i = 1; i < boardSize + 1; i++)
		{
			for (int j = 1; j < boardSize + 1; j++)
			{
				nextLife[i][j].setState(true);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////remove

		for (int i = 1; i < boardSize + 1; i++)
		{
			for (int j = 1; j < boardSize + 1; j++)
			{
				//////////////////////////////////////////////////////////////////////////////////////////////////////

				if (rule == 0)
				{ 
					nextLife[i][j].setState(executeRule110(m[i][j], currentLife[i][j].getState()));
				}
				else if (rule == 1)
				{
					
					nextLife[i][j].setState(executeRuleXXX(m[i][j], currentLife[i][j].getState()));
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}



		for (int i = 1; i < boardSize + 1; i++)
		{
			for (int j = 1; j < boardSize + 1; j++)
			{
				currentLife[i][j] = nextLife[i][j];
			}

		}
	
		//**displayBoard = currentLife[0][0];


		////////////////////DECONSTRUCT THE ARRAY THAT WAS USED///////////////////////////////
		for (int i = 0; i < boardSize + 2; i++)
		{

			delete[] m[i];
		}


		delete[]m;
		//-----------------------------------------------------------------------------------------------------------

	
	}

	// PA2:  Encapsulate next generation calculation in a methos.  Needed only for OPTIONAL Task #6
	void GameOfLife::calculateNextGen(CellPtr* current, CellPtr* next)
	{
	

		typedef int* ptr;

		ptr * m = new ptr[boardSize + 2];

		for (int i = 0; i < boardSize + 2; i++)
		{
			m[i] = new int[boardSize + 2];
		}


		//initilaize to zero
		for (int i = 0; i < boardSize + 2; i++)
		{
			for (int j = 0; j < boardSize + 2; j++)
			{
				m[i][j] = 0;

			}
		}


		int number = 0;
		for (int i = 1; i < boardSize + 1; i++)
		{

			//[-1,-1][-1,0][-1,1]
			//[0,-1][0,0][0,1]
			//[1,-1][1,0][1,1]
			for (int j = 1; j < boardSize + 1; j++)
			{
				number = 0;
				if (currentLife[i - 1][j - 1].getState() == true)//[-1][-1]
				{
					number++;
				}
				if (currentLife[i][j - 1].getState() == true)
				{
					number++;
				}
				if (currentLife[i + 1][j - 1].getState() == true)
				{
					number++;
				}
				if (currentLife[i - 1][j].getState() == true)
				{
					number++;
				}
				if (currentLife[i + 1][j].getState() == true)
				{
					number++;
				}
				if (currentLife[i - 1][j + 1].getState() == true)
				{
					number++;
				}
				if (currentLife[i][j + 1].getState() == true)
				{
					number++;
				}
				if (currentLife[i + 1][j + 1].getState() == true)
				{
					number++;
				}

				m[i][j] = number;
				number = 0;
			}
		}

		for (int i = 1; i < boardSize + 1; i++)
		{
			for (int j = 1; j < boardSize + 1; j++)
			{
				nextLife[i][j].setState(true);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////remove

		for (int i = 1; i < boardSize + 1; i++)
		{
			for (int j = 1; j < boardSize + 1; j++)
			{
				
				if (m[i][j] <= 2 && currentLife[i][j].getState() == false)//(m[i][j] <= 2 && currentLife[i][j].getState() == false)
				{
					//currentLife[i][j].setState(false);
					nextLife[i][j].setState(false);

				}
				if (m[i][j] < 2 && currentLife[i][j].getState() == true)  // if
				{
					//currentLife[i][j].setState(false);
					nextLife[i][j].setState(false);
				}
				else if (m[i][j] == 3 && currentLife[i][j].getState() == false)
				{

					//currentLife[i][j].setState(true);
					nextLife[i][j].setState(true);
				}
				else if (m[i][j] > 3 && currentLife[i][j].getState() == true)
				{

					//currentLife[i][j].setState(false);
					nextLife[i][j].setState(false);
				}
				else if (m[i][j] > 3 && currentLife[i][j].getState() == false)
				{

					//currentLife[i][j].setState(false);
					nextLife[i][j].setState(false);
				}
			}
		}

		for (int i = 1; i < boardSize + 1; i++)
		{
			for (int j = 1; j < boardSize + 1; j++)
			{

				currentLife[i][j] = nextLife[i][j];
			}
			
		}

		////////////////////DECONSTRUCT THE ARRAY THAT WAS USED///////////////////////////////
		for (int i = 0; i < boardSize + 2; i++)
		{

			delete [] m[i];
		}


		delete[]m;
		//-----------------------------------------------------------------------------------------------------------

		
	}


	Cell::Cell()
	{
		state = false;
		face = dead;
	}
	Cell::Cell(bool cellState)
	{
		state = cellState;
		
		if (cellState == true)
		{
			face = alive;
		}
		else if (cellState == false)
		{
			face = '-';
		}
			



	}
	Cell::~Cell()
	{}
	// Accessors have no intention to modify the object, so it is a good practice to make them 'const' functions
	bool Cell::getState() const 
	{
		return state;
	}
	char Cell::getFace() const 
	{
		return face;
	}

	// Mutators
	void Cell::setState(bool newState) 
	{
		state = newState;
		if (newState == true)
		{
			face = alive;
		}
		else if (newState == false)
		{
			face = '-';
		}
	}
}

void swapLarge(int size)
{
	// font size 
	/////////////////////////////////////////////////////////////////////////////////////////////////

	//#define _CRT_SECURE_NO_WARNINGS -> at the top of the page
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;  //0                 // Width of each character in the font
	cfi.dwFontSize.Y = size;  //10                // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	//std::cout << "Font: Consolas, Size: 24\n";
	/////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, -8, 0, 10000, 10000, TRUE);


	/////////////////////////////////////////////////////////////////////////////////////////
}