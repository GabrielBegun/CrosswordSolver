#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "Grid.h"
using namespace std;

/* TODO
Handle file io errors
Make a private constructor for Grid and use a factory to obtain it
fix Word::isComplete() so that it runs in consant time (because of done). The function update() may not be needed
improve exit strategy for solve();
*/

void tolowcaps(char * filename); // 
void createPuzzles(int n, int length); // Creates n new puzzles of length x length size 

int main(int argc, char* argv){
	cout << "Crossword Solver!" << endl;
//	createPuzzles(5, 20);
//	tolowcaps("dicctionary.txt");
//	tolowcaps("smallDic.txt");
//	return 1;

	try {
		Grid grid;
		char gridfile[] = "grid0.txt";
		char storefile[] = "sol0.txt";
		//grid.readDictionary("lowersmallDic.txt");
		grid.readDictionary("lowerdicctionary.txt"); // Do something in case this fails

		for (int ii = 0; ii < 10; ii++){
			gridfile[4] = (char)(ii + 48);
			storefile[3] = (char)(ii + 48);
			grid.formGrid(gridfile);
			//grid.solve();
			grid.solveRand();
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

void tolowcaps(char * filename){
	ifstream inFile;
	inFile.open(filename);
	ofstream newFile;
	string newfilename = "lower";
	newfilename.append(filename);
	newFile.open(newfilename.c_str());
	string temp_s;
	while (!inFile.eof()){
		getline(inFile, temp_s);
		for (int ii = 0; ii<temp_s.size(); ii++)
			temp_s[ii] = tolower(temp_s[ii]);
		newFile << temp_s.c_str() << endl;
		cout << temp_s.c_str() << endl;
	}
	inFile.close();
	newFile.close();
	cout << "New lower case version of " << filename << " called " << newfilename << endl;
}

void createPuzzles(int nn, int length = 400){
	if (nn >= 10 || nn < 0){
		cout << "Please create less grids. Double digits or negatives not yet supported" << endl;
		return;
	}
	cout << "Creating " << nn << " grids of size " << length << "x" << length << endl;
	srand(time(NULL));
	char  filename[] = "mgrid0.txt";
	ofstream myfile;
	for (int ii = 0; ii<nn; ii++){
		filename[5] = (char)(ii + 48);
		myfile.open(filename);
		myfile << "Board size is " << length << " x " << length << endl;
		for (int jj = 0; jj<length; jj++){
			for (int kk = 0; kk<length; kk++){
				// should be 1/2
				if (rand()<(RAND_MAX / 2)) myfile << '_'; // find correct param
				else myfile << '#';
			}
			myfile << endl;
		}
		myfile.close();
	}
	cout << nn << " puzzles created" << endl;
}