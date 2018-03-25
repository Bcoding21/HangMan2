#include "Game.h"
#include <iostream>
#include <sstream>


Game::Game(int size, int trys) :numTrys(trys) {
	for (int i = 0; i < size; i++) {
		mysteryWord += '_';
	}
}

void Game::displayProgres() {

	for (char slot : mysteryWord) {
		std::cout << slot << ' ';
	}

}

std::string Game::getUpdatedWord(char letter, std::string indexes) {

	auto indexList = parseIndexes(indexes);

	for (auto index : indexList) {
		mysteryWord[index - 1] = letter;
	}

	return mysteryWord;
}

std::vector<int> Game::parseIndexes(std::string indexes) {

	std::istringstream ss(indexes);
	std::vector<int> indexList;
	std::string stringIndex;
	while (std::getline(ss, stringIndex, ',')) {
		int index = std::stoi(stringIndex);
		indexList.push_back(index);
	}
	return indexList;
}

bool Game::hasTries() { return numTrys; }

bool Game::hasGuessedWord() {
	for (char letter : mysteryWord) {
		if (letter == '_') {
			return false;
		}
	}
	return true;
}
