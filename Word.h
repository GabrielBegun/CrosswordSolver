#ifndef _WORD
#define _WORD

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "CharacterSpace.h"

/* This class Word represents a word space in the dictionary

It has 5 variables:
myword - holds a string with the word's content
content_w - holds a vector of pointer to CharSpace. Used to verify if a letter has changed
possibleWords - holds a pointer to the words in the dictionary that have the correct size
iterator - points to the last word used. This is useful because it prevents us from trying the same words and falling in an infinite loop
done - used to know when a word is completed

The most important function is called complete()
It tries to find a possible solution. For example b__a_a -> banana

This class is intended to be used as a vector<Word> in Grid
*/

class Word{
private:
	std::string myword;
	std::vector<CharSpace*> content_w;
	std::vector<std::string> * possibleWords;
	std::vector<std::string>::iterator iterator;
	bool done; // true when the word is completed
	
	// Updates the content of the word
	void update();

public:
	// Constructor takes a vector of CharSpace * and a pointer to the possibleWords (part of the dictionary)
	Word(std::vector<CharSpace*> content_w, std::vector<std::string> *pw);

	// returns true if the current words is complete and fits in the dictionary.
	bool isComplete(); 	

	// if no match is found, those characterSpaces are set to "-_" 
	// the word found cannot be a word previousley used.
	void complete();

	// Reset the word to its default, empty state. Remember to setPossibleWords
	void reset();

	//  Store pointer to the possible words that can fit
	void setPossibleWords(std::vector<std::string> *pw);

	// Calls update and prints the word
	void print();

	// Returns a pointer to the CharSpaces that make up this word
	std::vector<CharSpace*> *getContent(){ return &content_w; }

};
#endif