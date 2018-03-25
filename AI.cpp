#include "AI.h"
#include <fstream>
#include <algorithm>
#include <iterator>


AI::AI(int wordSize, std::string guessOrder, std::string filePath)
{

	std::ifstream file(filePath);

	if (file) {
		std::istream_iterator<std::string> start(file), end;
		std::copy_if( start, end,
			std::back_inserter(wordBank), 
			[wordSize](const auto& word) {
			return word.size() == wordSize; }
		);
	}

	for (const auto& letter : guessOrder) {
		guessQueue.push(letter);
	}

	
}

bool AI::isMatch(const std::string& wordWithBlanks, const std::string& wordInList) {

	if (wordWithBlanks.size() != wordInList.size()) {
		return false;
	}

	for (int i = 0; i < wordInList.size(); i++) {
		char char1 = wordInList[i];
		char char2 = wordWithBlanks[i];

		if (char1 != '_' && char2 != '_') {
			if (char1 != char2) {
				return false;
			}
		}

	}

	return true;
}

void AI::updateWordBank(const std::string& guessWord) {

	std::vector<std::string> updatedList;

	std::copy_if(wordBank.begin(), wordBank.end(), 
		std::back_inserter(updatedList),
		[guessWord, this](const auto& potentialWord) {
		return isMatch(guessWord, potentialWord);});

	std::swap(wordBank, updatedList);
}

char AI::makeGuess() {

	if (guessQueue.empty()) {
		return '?';
	}

	auto freq = getCharFreqency(wordBank);

	char guess = guessQueue.front();
	guessQueue.pop();
	return guess;
}

std::vector<std::pair<char, int>> AI::getCharFreqency(const std::vector<std::string>& wordBank) {

	std::vector<std::pair<char, int>> frequencies;
	for (char alpha = 'a'; alpha <= 'z'; alpha++) {
		frequencies.push_back(std::make_pair(alpha, 0));
	}

	for (const auto& word : wordBank) {
		for (const auto& letter : word) {
			auto pair = std::find_if(
				frequencies.begin(),
				frequencies.end(),
				[letter](const auto& pair) {
				return pair.first == letter;
			});
			++pair->second;
		}
	}

	return frequencies;
}