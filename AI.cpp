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

bool AI::updateWordBank(const std::string& guessWord) {

	std::vector<std::string> updatedList;

	std::copy_if(wordBank.begin(), wordBank.end(), 
		std::back_inserter(updatedList),
		[guessWord, this](const auto& potentialWord) {
		return isMatch(guessWord, potentialWord);});

	wordBank.swap(updatedList);
}

char AI::makeGuess() {

	if (guessQueue.empty() || wordBank.empty()) {
		return '?';
	}
	char guess = guessQueue.front();
	used.push_back(guess);
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

void AI::updateGuessOrder(const std::vector<std::string>& wordBank, const std::vector<char>& usedList) {

	auto freq = getCharFreqency(wordBank);

	std::sort(freq.begin(), freq.end(),
		[](const auto& l, const auto& r) {
		return l.second > r.second;
	});

	std::queue<char> updatedOrder;

	for (const auto& pair : freq) {

		auto found = std::find_if(usedList.begin(), usedList.end(),
			[pair](const auto& usedChar) {
			return usedChar == pair.first; });

		if (found == usedList.end()) {
			updatedOrder.push(pair.first);
		}
	}

	guessQueue.swap(updatedOrder);

}