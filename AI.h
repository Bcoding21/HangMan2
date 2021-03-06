#pragma once

#include <vector>
#include <string>
#include <queue>
#include <set>

class AI
{
	std::vector<std::string> wordBank;
	std::queue<char> guessQueue;
	std::vector<char> used;
	std::string mysteryWord;

	bool isMatch(const std::string&, const std::string&);
	std::vector<std::pair<char, int>> getCharFreqency();
	

public:

	AI(int, std::string = "words_alpha.txt");
	char makeGuess();
	void setMatches(const std::string& word);
	void updateGuessOrder();
	bool hasGuessedWord();
	void truncateList();

};

