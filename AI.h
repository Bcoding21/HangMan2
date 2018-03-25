#pragma once

#include <vector>
#include <string>
#include <queue>
#include <set>

class AI
{
	std::vector<std::string> wordBank;
	std::queue<char> guessQueue;

	void updateWordBank(const std::string& word);
	bool isMatch(const std::string&, const std::string&);
	


public:

	AI(int, std::string = "etaoinsrhdlucmfywgpbvkxqjz", std::string = "words_alpha.txt");
	std::vector<std::pair<char, int>> getCharFreqency(const std::vector<std::string>&);
	char makeGuess();

};

