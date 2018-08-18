#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <stdexcept>
#include <queue>

struct Pair
{
	int x;
	int y;
};

class Minesweeper {
private:
	int const UNVISITED_EMPTY = -1;
	int const VISITED_EMPTY = 1;
	int const MINE = 0;
	char ** matrix;
	int numberOfMines;
	int dimension;
	bool gameOver = false;
	bool firstMove = true;
	int visitedCells;
private: 
	int numberUnvisitedCells();
	void placeMinesRandom();
	void placeMines(Pair * pairs);
	void calculateNumberMinesAround();
	bool isEmpty(int rowNumber, int columnNumber);
	void makeFirstMove(int rowNumber, int columnNumber);
	void initialize();
	void initialize(Pair * pairs);
	bool isValidPosition(int rowNumber, int columnNumber);
	bool isValidUnvisitedPosition(int rowNumber, int columnNumber);
	bool isMineAt(int rowNumber, int columnNumber);
	char formatCell(char c);
public:
	Minesweeper(int dimension, int numberOfMines);
	Minesweeper(int dimension, int numberOfMines, Pair * pairs);
	void recursiveFlood(int rowNumber, int columnNumber);
	void iterativeFlood(int rowNumber, int columnNumber);
	bool isGameOver();
	void makeMove(int, int);
	void print(std::ostream& stream);
};