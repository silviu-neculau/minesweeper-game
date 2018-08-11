#include <iostream>
#include "Minesweeper.h"

int main() {

	// Minesweeper(dimensiune, numarMine, randomNumberGenerator)
	// Minesweeper(dimensiune, numarMine)
	// Minesweeper(dimensiune)
	// constructor chaining 

	// documentatie pe metode (unde e cazul)..
	// comis pe git pe un repository -- minesweeper-game

	Minesweeper m = new Minesweeper(8, 10);

	while (m.isOver()) {
		m.print(cout);
		try {
			m.makeMove(int rowNumber, int columnNumber);
		}
		catch (Exception e) {
			//.. tratezi eroarea
			//.. iei decizii daca continui sau opresti jocul
		}
	}

	return 0;
}