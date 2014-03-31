#ifndef _UTIL
#define _UTIL

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

// Converts file to lower case
// Should be used when loading a new dictionaty 
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
	char  filename[] = "grid0.txt";
	ofstream myfile;
	for (int ii = 0; ii<nn; ii++){
		filename[5] = (char)(ii + 48);
		myfile.open(filename);
		myfile << "Board size is " << length << " x " << length << endl;
		for (int jj = 0; jj<length; jj++){
			for (int kk = 0; kk<length; kk++){
				// should be 50 - 50. Change this to alter the '#' / '_' ratio
				if (rand()<(RAND_MAX / 2)) myfile << '_'; // find correct param
				else myfile << '#';
			}
			myfile << endl;
		}
		myfile.close();
	}
	cout << nn << " puzzles created" << endl;
}

#endif