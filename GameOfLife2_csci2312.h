//John F Williams 
// 105201054
// CSCI 2312 -->PA2


#pragma once
#include <iostream>  // Provides ostream
#include <string>    // String operations
#include <cstdlib>   // Randomizer


namespace csci2312
{
	using std::string;
	using std::ostream;
	using std::istream;
	
	// PA2: standard exception if memory allcation failed
	using std::bad_alloc;

	// Class Cell stays the same for PA1 and PA2	
	class Cell
	{
		
	public:
		static const char alive ='o';  // alive image
		static const char dead = '-';  // dead image
		
        
		Cell();
		Cell(bool cellState);  
		~Cell();

		// Accessors have no intention to modify the object, so it is a good practice to make them 'const' functions
		bool getState() const;		
		char getFace() const;

		// Mutators
		void setState(bool newState);
			
	private:
		bool state=false;
		char face;		
        	
	};

	// PA2: File IO Error custom exception  class
	class FileIOException
	{
		//  Nothing inside, just a class type to handle exception
	};

	// PA2: Class GameOfLife will have some new and some changed features
    class GameOfLife
    {
		
    public:
		// PA1: maximum display board size
		// PA2: default display board size
		static const unsigned int MAX_BOARD = 30;

		// PA2: New type (pointer to Cell type) handy with dynamic arrays
		typedef Cell* CellPtr;

		// PA1: Default constructor construct a board with all dark cells of MAX_BOARD size
		// GameOfLife();
		
		// PA1: Constructs the board of the requested size
		// GameOfLife(size_t boardSize);
		 
		// PA2: Constructs the board of the requested size, can throw exception.
		// If parameter is omitted, it becomes the default constructor, and the board will have MAX_BOARD size
		GameOfLife(size_t boardSize = MAX_BOARD) throw (bad_alloc);

		// PA2:  Copy-constructor creates a new instance as a deep copy of the referenced object
		GameOfLife(const GameOfLife& game);

		// PA2:  destructor must release memory taken by dynamic arrays
		~GameOfLife();
	 
		// PA1: seeds the board from a file
		// int seedBoard(string fileName);

		// PA2: seeds the board from a file and throws an exception if there was trouble with file
		void seedBoard(string fileName) throw (FileIOException);

		// PA1 and PA2: seeds the  board with a given number of seeds at randomized locations
		void seedBoard(size_t seeds);
		
		// PA1 and PA2: 
		void run();
		void run(unsigned int numberOfIterations);

		// Just an example of an possible accessor which reaches to a private array.  Not needed to satisfy PAs
		// A const(!) accessor method that returns a handle to the private currentLife array. 
		// The return type must also be 'const' because we return a pointer to a static array, and these are fixed
		// It is just an example.  It is not needed if we have a friend operator.		
		// PA1: const Cell(*getCurrentLife() const )[MAX_BOARD+2]  { return currentLife; };
		// PA2: const CellPtr* getCurrentLIfe() const { return currentLife; };

		// PA1 and PA2:  overloaded output operator to displsy the board 
		// friend operator can access private members of GameOfLife
		friend ostream& operator << (ostream& out, const GameOfLife& board);

		// PA2:  overloaded input operator to input the board (from file of keyboard)
		friend istream& operator >> (istream& in, const GameOfLife& board);
		
    private:		
		// PA2:  Executes Conway set of rules (same rules as PA1). Returns next state
		// Needed for TASK #5 to develop a test harness (the files test harness will be provided separately)
		bool executeRule110(unsigned int countAlive, bool currentState);

		// PA2:  Executes additional set of rules. Returns next state
		bool executeRuleXXX(unsigned int countAlive, bool currentState);


		// PA2:  Encapsulate next generation calculation in a methos.  Needed only for OPTIONAL Task #6
		void calculateNextGen(CellPtr *current, CellPtr *next);
		
		void calculateNextGen(CellPtr *current, CellPtr *next, int rule);



		// PA1:  static arrays of Cells.  With "Halo" approach we need a bigger board
		// Cell currentLife[MAX_BOARD + 2][MAX_BOARD + 2];
		// Cell nextLife[MAX_BOARD + 2][MAX_BOARD + 2];

		// PA2:  dynamic arrays of Cells. New type CellPtr defined (typedef Cell* CellPtr)
		// currentLife and and nextLife are handles to the dynamic arrays
		CellPtr *currentLife ;  
		CellPtr *nextLife ;
			



		// Just an example how to declare variable cl as a handle to our array of Cells.  Not needed to satisfy PAs
		// The accessor method getCurrentLife() above uses the same syntax for the return type
		// PA1 with static arrays:  const Cell(*cl)[MAX_BOARD + 2] = currentLife; 
		// PA2 with dynamic arrays: const CellPtr* cl = currentLife; 
	
	    // PA1 and PA2, keeps track of the actual board size, set in the constructor
	    size_t boardSize;           

		// PA2: A handle to the array that needs to be displyed next.  Only needed for OPTIONAL TASK #6 
		CellPtr *displayBoard;

    };
          
   
        
}
