#ifndef _CHARSPACE
#define _CHARSPACE

#include <vector>

/**class CharSpace
 * holds a character an a vector of the words it is part of 
 */

class CharSpace{
private:
	char content_c;
	std::vector<int> inWords;

public:	
	CharSpace(char c){ content_c = c;}

	void setChar(char c){ content_c = c; }
	char getChar() { return content_c; }

	void addWord(int word, int place) { inWords.push_back(word); }
	std::vector<int> * getWordVector(){ return &inWords; }
};

#endif