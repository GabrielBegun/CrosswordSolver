#include "Grid.h"

void Grid::readDictionary(char * filename){
	// reads the file and stores it in vector of vectors (dictionary)
	std::cout << "Reading dictionary file. May take some time (~20s) " << std::endl;
	std::ifstream	 myfile;
	myfile.open(filename);
	std::string temp;
	myDics.resize(25); // MAX length size in the dictionary. Obtained empirically
	clock_t startTime = clock();
	while (!myfile.eof()){
		getline(myfile, temp);
		myDics[temp.size()].push_back(temp);
	}
	myfile.close();
	std::cout << "dictionary read and stored in vecs" << std::endl;
	std::cout << "It took "<< double(clock() - startTime) / (double)CLOCKS_PER_SEC << " seconds." << std::endl;

	#ifdef _MYDEBUG
	// Print how many words were found of each word size
	cout<< "Words found of each size" << endl;
	for (int ii = 0; ii<myDics.size(); ii++)
		cout << ii << " " << myDics[ii].size() << endl;
	#endif
	return;
}

void Grid::store(char * filename){
	std::ofstream file;
	file.open(filename);
	//for(int ii = 0; ii<sizex; ii++) file<<ii;
	for (int jj = 0; jj < sizey; jj++){
		//file<<endl<<jj<<"\t";
		for (int ii = 0; ii < sizex; ii++){
			file << mychars[jj*sizex + ii].getChar();
		}
		file << std::endl;
	}
	file << std::endl;
	file.close();
}

void Grid::formGrid(char * filename) {
	// reads the grid into words and chars
	std::ifstream myfile;
	myfile.open(filename);
	std::cout << "Loading Grid from " << filename << std::endl;
	std::string temp;
	std::stringstream temp_ss;
	char temp_c;

	// read size
	getline(myfile, temp);
	temp_ss.str(temp.substr(14, temp.size() - 14));
	temp_ss >> sizex >> temp_c>> sizey;
	std::cout << "size: " << sizex << "x" << sizey << std::endl;

	// read the grid and store it in the CharSpace vector
	// this is slow when the files are large..... it might be worth reading one line at a time.
	while (myfile.good()){
		myfile >> temp_c;
		CharSpace temp_CharSpace(temp_c);
		mychars.push_back(temp_CharSpace);
	}
	myfile.close();
	std::cout << "Grid read into memory" << std::endl;
	
	// Search the array to create new word objects.
	char current, last;
	std::vector<CharSpace*> temp_content; // use typedef
	last = '#';
	std::cout << "finding horizontal words " << std::endl;
	for (int ii = 0; ii < sizey; ii++){
		for (int jj = 0; jj < sizex; jj++){
			current = mychars[ii*sizex + jj].getChar();
			if (current == '_'){
				if (last == '#'){
					// new word starts here
					temp_content.clear();
				}
				temp_content.push_back(&mychars[ii*sizex + jj]);
				mychars[ii*sizex + jj].getWordVector()->push_back(mywords.size() - 1);
			} else { // current == '#'
				if (last == '_' && temp_content.size() > 1){ // word ends here. Store only words of zise > 1 
					Word temporary(temp_content, &myDics[temp_content.size()]);
					mywords.push_back(temporary);		
				} // else found two # in a row. Continue
			}
			last = current;
		}
		// line ends, hence the word ends as well
		if (last == '_' && temp_content.size() > 1){ // word ends here. Store only words of zise > 1 
			Word temporary(temp_content, &myDics[temp_content.size()]);
			mywords.push_back(temporary);
		}
		temp_content.clear();
		last = '#'; // pretend we start the row from a #
	}

	std::cout << "finding vertical words" << std::endl;
	for (int jj = 0; jj < sizex; jj++){
		for (int ii = 0; ii < sizey; ii++){
			current = mychars[ii*sizex + jj].getChar();
			if (current == '_'){
				if (last == '#'){
					// word starts here
					temp_content.clear();
				}
				temp_content.push_back(&mychars[ii*sizex + jj]);
				mychars[ii*sizex + jj].getWordVector()->push_back(mywords.size() - 1);
			}
			else { // current == '#'
				if (last == '_' && temp_content.size() > 1){ // word ends here. Store only words of zise > 1 
					Word temporary(temp_content, &myDics[temp_content.size()]);
					mywords.push_back(temporary);
				} // else found two # in a row. Continue
			}
			last = current;
		}
		// column ends
		if (last == '_' && temp_content.size() > 1){ // word ends here. Store only words of zise > 1 
			Word temporary(temp_content, &myDics[temp_content.size()]);
			mywords.push_back(temporary);
		}
		temp_content.clear();
		last = '#'; // pretend we start the row from a #
	}

	std::cout << "total words found " << mywords.size() << std::endl;
}

void Grid::print(){
	std::cout << "the Gird right now:" << std::endl;
	std::cout << "\t";
	for (int ii = 0; ii<sizex; ii++) std::cout << ii;
	for (int jj = 0; jj < sizey; jj++){
		std::cout << std::endl << jj << "\t";
		for (int ii = 0; ii < sizex; ii++){
			std::cout << mychars[jj*sizex + ii].getChar();
		}

	}
	std::cout << std::endl;
}

bool Grid::isDone(){
#ifdef _MYDEBUG
	std::cout << "isDONE" << std::endl;
#endif
	// returns true if all words done value is equal to one
	for (int ii = 0; ii<mywords.size(); ii++){
		//mywords[ii].update(&myDics[mywords[ii].getContent()->size()]);
		if (!mywords[ii].isComplete()){
			return 0;
		}
	}
	return 1;
}

void Grid::clear(){
	sizex = 0;
	sizey = 0;
	mychars.clear();
	mywords.clear();
	std::cout << "Grid cleared" << std::endl;
}

int Grid::solveSmallWords(){
	int wordsDone = 0;
	for (int ii = 0; ii<mywords.size(); ii++){
		if (!mywords[ii].isComplete()) {
			if (mywords[ii].getContent()->size() < 4) mywords[ii].complete();
		}
		else wordsDone++;
	}
	return wordsDone;
}

int Grid::solveBigWords(){
	int wordsDone = 0;
	for (int ii = 0; ii<mywords.size(); ii++){
		if (!mywords[ii].isComplete()) {
			if (mywords[ii].getContent()->size() >= 5) mywords[ii].complete();
		} else wordsDone++;
	}
	return wordsDone;
}

int Grid::solveForward(){
	int wordsDone = 0;
	for (int ii = 0; ii<mywords.size(); ii++){
		if (!mywords[ii].isComplete()) {
			 mywords[ii].complete();
		}
		else wordsDone++;
	}
	return wordsDone;
}

int Grid::solveBackward() {
	int wordsDone = 0;
	for (int ii = mywords.size() - 1; ii >= 0; ii--){
		if (!mywords[ii].isComplete()) {
			mywords[ii].complete();
		}
		else wordsDone++;
	}
	return wordsDone;
}

void Grid::clearAroundBlank(){
	for (int ii = 1; ii<mychars.size() - 1; ii++){
		if (mychars[ii].getChar() == '_'){
			if (!(mychars[ii - 1].getChar() == '#')) mychars[ii - 1].setChar('_');
			if (!(mychars[ii + 1].getChar() == '#')) mychars[ii + 1].setChar('_');
			if (ii>sizex && mychars[ii - sizex].getChar() != '#') mychars[ii - sizex].setChar('_');
			if (ii < (sizex*sizey - sizex) && mychars[ii + sizex].getChar() != '#') mychars[ii + sizex].setChar('_');;
		}
	}
}

void Grid::clearAroundBlankLarge(){
	for (int ii = 0; ii < 10; ii++) clearAroundBlank();
}


void Grid::solveRand(){
	std::cout << std::endl << "solving" << std::endl;
	int wordsDone = 0;
	std::vector<int> wordsDone_v;
	int solveCount = 0;
	int rand_int = 0;
	this->print();

	while (!this->isDone()){
		//std::cout << "Solving " <<	solveCount << std::endl;
		rand_int = rand() % 100; // 0 - 99
		if (rand_int < PERCENTFWD) wordsDone = solveForward();
		else if (rand_int < PERCENTBWD) wordsDone = solveBackward(); 
		else if (rand_int < PERCENTBIG) wordsDone = solveBigWords();
		else if (rand_int < PERCENTSMALL) wordsDone = solveSmallWords();
		else if (rand_int < PERCENTCLEAR) {	clearAroundBlank(); wordsDone = 0; }
		else if (rand_int < PERCENTCLEARL) { clearAroundBlankLarge(); wordsDone = 0; }
		else throw  1; // Should never happen
		wordsDone_v.push_back(wordsDone);
		std::cout << solveCount << " " << wordsDone << " " << rand_int << std::endl;
		if (solveCount % 10 == 0){
			this->print();
		}
		if (solveCount == 10000) {
			std::cout << "After 10000 attempts no solution was found. Sorry!" << std::endl;
			throw (-1);
		}
		solveCount++;
	} // END OF WHILE LOOP

	// if there are any empty cells - fill them with a word from the dictionary. This cells are not counted as words because they are an '_' surrounded by # or edges. In other words, they are single character long
	for (int ii = 0; ii<mychars.size(); ii++){
		if (mychars[ii].getChar() == '_') mychars[ii].setChar('a'); // a is a word in the dictionary
	}
}

void Grid::solve(){
	std::cout << std::endl << "solving" << std::endl;
	int wordsDone = 0;
	std::vector<int> wordsDone_v;
	int solveCount = 0;
	int patternSetting = 16;
	this->print();
	while (!this->isDone()){
		//std::cout << "Solving " <<	solveCount << std::endl;
		switch (solveCount % patternSetting) {
		case 0:
		case 6:
			wordsDone = solveBigWords();
			break;
		case 11:
			wordsDone = solveSmallWords();
			break;
		case 3:
		case 8:
		case 13:
			wordsDone = solveBackward();
			break;
		case 5:
		case 10:
			//clearAroundBlank();
			wordsDone = 0;
			break;
		case 15:
			//this->print();
			clearAroundBlankLarge();
			patternSetting+=7;
			wordsDone = 0;
			for (int ii = 0; ii < wordsDone_v.size(); ii++)
				//std::wcout << " " << wordsDone_v[ii];
			//std::wcout << std::endl;
			wordsDone_v.clear();
			break;
		default:
			wordsDone = solveForward();
			break;
		}
		wordsDone_v.push_back(wordsDone);
		std::cout << solveCount << " " << wordsDone << std::endl;
     	this->print();  //}
		//std::cout << "\tWords done " << wordsDone << std::endl;
		if (solveCount == 10000) {
			std::cout << "After 10000 attempts no solution was found. Sorry!" << std::endl;
			throw (-1);
		}
		solveCount++;
	} // END OF WHILE LOOP

	// if there are any empty cells - fill them with a word from the dictionary. This cells are not counted as words because they are an '_' surrounded by # or edges. In other words, they are single character long
	for (int ii = 0; ii<mychars.size(); ii++){
		if (mychars[ii].getChar() == '_') mychars[ii].setChar('a'); // a is a word in the dictionary
	}
}