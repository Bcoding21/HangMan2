#include "AI.h"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <regex>


AI::AI(int wordSize, std::string filePath)
{
	std::ifstream file(filePath);

	if (file) {
		std::istream_iterator<std::string> start(file), end;
		std::copy_if(start, end,
			std::back_inserter(wordBank),
			[wordSize](const auto& word) {
			return word.size() == wordSize; }
		);
	}

	auto freq = getCharFreqency();

	std::sort(freq.begin(), freq.end(),
		[](const auto& l, const auto& r) {
		return l.second > r.second;
	});

	for (const auto& pair : freq) {
		guessQueue.push(pair.first);
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

void AI::setMatches(const std::string& guessWord) {

	std::string pattern;
	std::transform(guessWord.begin(), guessWord.end(),
		std::back_inserter(pattern),
		[guessWord](const auto& letter) {
		return (letter == '_') ? '.' : letter;
	});

	std::regex regexp(pattern);
	std::vector<std::string> updatedList;
	std::copy_if(wordBank.begin(), wordBank.end(), 
		std::back_inserter(updatedList),
		[regexp](const auto& word) {
		return std::regex_match(word, regexp);});

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

std::vector<std::pair<char, int>> AI::getCharFreqency() {

	std::vector<std::pair<char, int>> f;

	for (const auto& word : wordBank) {
		for (const auto& letter : word) {

			auto found = std::find_if(
				f.begin(), f.end(),
				[letter](const auto& pair) {
				return pair.first == letter; });

			if (found == f.end()) {
				f.push_back(std::make_pair(letter, 1));
			}
			else {
				++found->second;
			}
		}
	}

	return f;
}

void AI::updateGuessOrder() {

	auto temp = getCharFreqency();

	std::vector<std::pair<char, int>> freq;

	for (const auto& pair : temp) {

		auto found = std::find_if(used.begin(), used.end(),
			[pair](char letter) {
			return pair.first == letter;
		});

		if (found == used.end()) {
			freq.push_back(pair);

		}
	}

	auto allEqualOne = std::all_of(freq.begin(), freq.end(),
		[](const auto& pair) {
		return pair.second == 1;
	});

	if (!allEqualOne) {

		std::sort(freq.begin(), freq.end(),
			[](const auto& l, const auto& r) {
			return l.second > r.second;
		});


		std::queue<char> updatedOrder;

		for (const auto& pair : freq) {
			updatedOrder.push(pair.first);
		}

		guessQueue.swap(updatedOrder);
	}
}

bool AI::hasGuessedWord() {

	

	return false;
}

void AI::truncateList() {

char badGuess = used.back();

	std::vector<std::string> updatedList;

	std::copy_if(wordBank.begin(), wordBank.end(),
		std::back_inserter(updatedList),
		[badGuess](const auto& word) {
		return word.find(badGuess) == std::string::npos;
	});

	wordBank.swap(updatedList);
}