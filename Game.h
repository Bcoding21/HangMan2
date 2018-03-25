#pragma once
#include <string>
#include <vector>


class Game
{
	int wordLength;
	std::string mysteryWord;
	int numTrys;
	

public:
	Game(int, int);

	void displayProgres();

	std::string getUpdatedWord(char letter, std::string indexes);

	std::vector<int> parseIndexes(std::string);

	bool hasTries();

	bool hasGuessedWord();
	
};

