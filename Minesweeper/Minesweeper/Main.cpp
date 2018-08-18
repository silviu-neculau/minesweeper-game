#include <iostream>
#include "Minesweeper.h"
using namespace std;
int main() {
	Minesweeper*  m = new Minesweeper(9, 10);
	while (!m->isGameOver()) {
		try {
			int rownumber, columnnumber;
			std::cout << "Choose two coordinates" << endl;
			std::cin >> rownumber >> columnnumber;
			m->makeMove(rownumber, columnnumber);
			m->print(cout);
			//m->print(cout);
		}
		catch (const std::invalid_argument& e) {
				cout << "Invalid coordinates! Please choose positive coordinates within the range of the game."<<endl;
		}
	}
	 
	cout << "END";
	return 0;
}