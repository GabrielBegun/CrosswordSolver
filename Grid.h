#ifndef _GRID
#define _GRID

//#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>
#include "Word.h"
#include "CharacterSpace.h"

#define PERCENTFWD		40
#define PERCENTBWD		75
#define PERCENTBIG		85
#define PERCENTSMALL	92	
#define PERCENTCLEAR	97
#define PERCENTCLEARL	100


/* Class Grid

This class represents a crossword puzzle grid. The grid is held in a CharSpace vector. Each CharSpace is assigned to one or two words to which it belongs to.
There are currently two solve functions. SolveRand() is faster than solve() because the specific function called has a defined chance of executing. Boths functions act in a greedy way
The Grid also holds a dictionary that must be read using the readDictionary() function. It only needs to be read once.
The general use behind this class is load a grid, solve it and store it.
*/

class Grid{
private:
	int sizex, sizey;
	std::vector<CharSpace> mychars;
	std::vector<Word> mywords;
	std::vector<std::vector<std::string> > myDics;

	// These functions do one attempt at solving according to a specific criteria. They return the amount of words finished in the last iteration
	int solveBigWords();
	int solveSmallWords();
	int solveForward();
	int solveBackward();

	void clearAroundBlank(); // Clears the adjecent spaces of a blank
	void clearAroundBlankLarge();

public:
	// Reads and stores the dictionary into a vector of vector of strings. The dictionary is used to find words for the solution
	void readDictionary(char * filename);

	// Reads a grid file into memory
	void formGrid(char * filename);

	// Stores the current solution in a file
	void store(char * filename);

	// prints the current state of the grid
	void print();

	// returns true if all words are done
	bool isDone();
			
	// Clears the content of the object (except for the dictionary)
	void clear();

	// finds a solution to the grid
	// this is the really tricky one hahah
	// right now I go word by word, finding a match. if no match is found I clear the words next to it. If you get stuck with this i "try harder" by also clearing its sorrounding words.
	// a different approach would be to do larger words first and then do small words (because small words are easier to fit). Maybe I should loop through everything and if there are any words larger than 5 than complete it. If there are any words larger than 24 than the grid cannot be solved with the current dictionary.
	void solve();

	// Same as solve but each function has a percentage chance of happening
	void solveRand();
};

#endif