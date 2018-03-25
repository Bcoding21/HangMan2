#include <iostream>
#include "AI.h"
#include "Game.h"



int main() {

	int wordSize = 0;
	std::cout << "Enter length of word: ";
	std::cin >> wordSize;

	int numTires;
	std::cout << "Enter number of tries for AI: ";
	std::cin >> numTires;

	Game game(wordSize, numTires);
	AI computer(wordSize);

	while (true) {

		game.displayProgres();
		std::cout << '\n';

		char letter = computer.makeGuess();

		if (!isalpha(letter)) {
			std::cout << "Computer has given up. You win!";
			return 0;
		}

		std::cout << "\nThe comptuer has guessed: " << "\"" << letter << "\"\n";

		char input;

		do {
			std::cout << "Does this letter occur in your word? (Enter \"y\" or \"n\"): ";
			std::cin >> input;
			std::cin.ignore();
		} while (input != 'y' && input != 'n');

		if (input == 'y') {
			std::string positions;
			std::cout << "Enter the positions that the letters occur at separate by a comma. (1, 2, 3, 4): ";
			std::getline(std::cin, positions);

			std::string updatedWord = game.getUpdatedWord(letter, positions);
			computer.calculateNextMove(updatedWord);
		}

		if (!game.hasTries()) {

		}

		if (game.hasGuessedWord()) {

		}
	}

	

}