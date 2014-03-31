#include <iostream>
#include <fstream>
#include <string>
#include "Grid.h"
//#include "Util.cpp"
using namespace std;

/* TODO
Handle file io errors
Make a private constructor for Grid and use a factory to obtain it
fix Word::isComplete() so that it runs in consant time (because of done). The function update() may not be needed
improve exit strategy for solve();
*/

int main(int argc, char* argv){
	cout << "Crossword Solver!" << endl;
//	createPuzzles(5, 20);
//	tolowcaps("dicctionary.txt");
//	tolowcaps("smallDic.txt");
//	return 1;

	try {
		Grid grid;
		char gridfile[] = "Grids/grid0.txt";
		char storefile[] = "Solutions/sol0.txt";
		//grid.readDictionary("lowersmallDic.txt");
		grid.readDictionary("lowerdicctionary.txt"); // Do something in case this fails

		for (int ii = 0; ii < 10; ii++){
			gridfile[10] = (char)(ii + 48);
			storefile[9] = (char)(ii + 48);
			grid.formGrid(gridfile);
			//grid.solve(); // Slow and less efficent. Does not always work
			grid.solveRand(); // Better solving algorithm
			grid.print(); // Print solution
			grid.store(storefile);
			grid.clear();
		}
		cout << "All grids solved!" << endl;
	}
	catch (int e) {
		cout << "Exception Thrown by my code" << endl;
	}
	catch (exception e){
		cout << "Exception thrown by system" << endl;
	}

	while (1){}
	return 1;
}

