#include "Word.h"

Word::Word(std::vector<CharSpace*> cw, std::vector<std::string> *pw){
	if ((*pw).empty()) {
		throw - 1;
	}
	this->possibleWords = pw;
	this->content_w = cw;
	iterator = (*possibleWords).begin();
	for (int ii = 0; ii < content_w.size(); ii++) myword.append("_");
	done = false;
}

void Word::complete(){
	#ifdef _MYDEBUG
	cout << "completing " << myword << " with ";
	#endif
	bool found;
	int wordSize = myword.size();
	std::vector<std::string>::iterator lastIterator = iterator; // Used to know when we have checked all possible words	
	iterator++;
	if (iterator == (*possibleWords).end()) 
		iterator = (*possibleWords).begin();
	do{
		found = true;
		for (int jj = 0; jj <wordSize; jj++){
			if (!(myword[jj] == iterator->at(jj) || myword[jj] == '_')){
				jj = wordSize; // virtually break;
				found = false;
			}
		}
		if (found){
			// The word found works. Update all the appropiate fields
			myword.assign(iterator->c_str());
			for (int ii	= 0; ii<wordSize; ii++) {
				content_w[ii]->setChar(myword[ii]);
			}
			done = true;
			return;
		} 

		iterator++;
		if (iterator == (*possibleWords).end()) 
			iterator = (*possibleWords).begin();
	} while (lastIterator != iterator);

	// no word was found. clear the entire string
	#ifdef _MYDEBUG
	cout << " NO MATCH." << endl;
	#endif

	for (int ii = 0; ii<content_w.size(); ii++) {
		myword[ii] = '_';
		content_w[ii]->setChar('_');
	}
	done = false;
	//iterator = (*possibleWords).begin();
	return;
}

bool Word::isComplete(){// or Trie * trie
#ifdef _MYDEBUG
	cout << "ISCOMPLETE ";
#endif
	this->update();
	if (done) return 1;
	else return 0;
}

void Word::update(){
	std::string temp;
	// See if the entire word has a character
	for (int ii = 0; ii < content_w.size(); ii++) {
		if (content_w[ii]->getChar() == '_'){
			done = false;
		}
		temp += content_w[ii]->getChar();
	}
	myword = temp;
	if (done = false) return;
	// See if the word is in our dictionary. This could be improved. I know the words are sorted
	std::vector<std::string>::iterator startIT = (*possibleWords).begin();
	std::vector<std::string>::iterator endIT = (*possibleWords).end();
	for (; startIT != endIT; startIT++){
		if (myword.compare(startIT->c_str()) == 0){ // compare returns 0 if they are equal
			done = true;
			return;
		}
	}
	done = false;
	return;
}

void Word::reset(){
	content_w.clear();
	done = false;
}

void Word::print(){
	this->update();
	std::cout << myword << std::endl;;
}

void Word::setPossibleWords(std::vector<std::string> *pw) { 
	this->possibleWords = pw; 
	iterator = (*possibleWords).begin();
	myword.resize(content_w.size());
	for (int ii = 0; ii < content_w.size(); ii++) 
		myword[ii] = '_';
}