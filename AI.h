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

	bool isMatch(const std::string&, const std::string&);
	std::vector<std::pair<char, int>> getCharFreqency(const std::vector<std::string>&);
	void updateWordBank(const std::string& word);
	void updateGuessOrder(const std::vector<std::string>&, const std::vector<char>&);

public:

	AI(int, std::string = "etaoinsrhdlucmfywgpbvkxqjz", std::string = "words_alpha.txt");
	char makeGuess();
	void calculateNextMove(std::string);

};

