#pragma once
#include "Minesweeper.h"
#include <cstdlib>
#include <time.h> 



Minesweeper::Minesweeper(int dimension, int numberOfMines) {
	this->dimension = dimension;
	this->numberOfMines = numberOfMines;
	this->gameOver = false;
	// allocate memory for the matrix
	matrix = new char*[dimension];
	for (int i = 0; i < dimension; i++)
	{
		matrix[i] = new char[dimension];
	}
	this->initialize();
}

Minesweeper::Minesweeper(int dimension, int numberOfMines, Pair * pairOfMines) {
	this->dimension = dimension;
	this->numberOfMines = numberOfMines;// verifica ca nu e NULL si ca are macar 1 element !!!;
	this->gameOver = false;
	// allocate memory for the matrix
	matrix = new char*[dimension];
	for (int i = 0; i < dimension; i++)
	{
		matrix[i] = new char[dimension];
	}
	this->initialize(pairOfMines);
}

void Minesweeper::initialize(Pair * pairOfMines) {
	// Clear the matrix and make everything unvisited.
	for (int i = 0; i< this->dimension; i++)
		for (int j = 0; j < this->dimension; j++)
		{
			matrix[i][j] = -1;
		}
	placeMines(pairOfMines);
	calculateNumberMinesAround();
}

void Minesweeper::initialize() {
	// Clear the matrix and make everything unvisited.
	for(int i = 0; i< this->dimension; i++)
		for (int j = 0; j < this->dimension; j++)
		{
			matrix[i][j] = -1;
		}
	placeMinesRandom();
	calculateNumberMinesAround();
}

void Minesweeper::placeMines(Pair * pairOfMines) {
	for (int i = 0; i < numberOfMines; i++) {
		matrix[pairOfMines[i].x][pairOfMines[i].y] = MINE;
	}
}

void Minesweeper::placeMinesRandom() {
	srand(time(NULL));
	// Populate mines.
	int randomRowNumber = 0;
	int randomColumnNumber = 0;
	int minesContor = 0;
	while (minesContor < numberOfMines)
	{
		randomRowNumber = rand() % dimension;
		randomColumnNumber = rand() % dimension;
		// isMineAt
		if (!isMineAt(randomRowNumber, randomColumnNumber))
		{
			matrix[randomRowNumber][randomColumnNumber] = 0;
			minesContor++;
		}
	}
}
void Minesweeper::calculateNumberMinesAround() {
	// Compute numbers near the mines.
	for (int i = 0; i < this->dimension; i++)
	{
		for (int j = 0; j < this->dimension; j++)
		{
			if (isMineAt(i, j))
			{
				if (isValidPosition(i - 1, j - 1) && !isMineAt(i - 1, j - 1))
					matrix[i - 1][j - 1]--;
				if (isValidPosition(i - 1, j) && !isMineAt(i - 1, j))
					matrix[i - 1][j]--;
				if (isValidPosition(i - 1, j + 1) && !isMineAt(i - 1, j + 1))
					matrix[i - 1][j + 1]--;
				if (isValidPosition(i, j - 1) && !isMineAt(i, j - 1))
					matrix[i][j - 1]--;
				if (isValidPosition(i, j + 1) && !isMineAt(i, j + 1))
					matrix[i][j + 1]--;
				if (isValidPosition(i + 1, j - 1) && !isMineAt(i + 1, j - 1))
					matrix[i + 1][j - 1]--;
				if (isValidPosition(i + 1, j) && !isMineAt(i + 1, j))
					matrix[i + 1][j]--;
				if (isValidPosition(i + 1, j + 1) && !isMineAt(i + 1, j + 1))
					matrix[i + 1][j + 1]--;
			}
		}
	}
}
/**
 * 
 * 	
 * 
 */
bool Minesweeper::isValidPosition(int rowNumber, int columnNumber) {
	if (   rowNumber >= 0 &&    rowNumber < dimension && 
		columnNumber >= 0 && columnNumber < dimension )
		return true;
	return false;
}

/**
 *	This function checks if the current cell 
 * has a bomb
 *
 */
bool Minesweeper::isMineAt(int rowNumber, int columnNumber) {
	if(!isValidPosition(rowNumber, columnNumber))
		throw std::invalid_argument("Invalid coordinates!"); //  + rowNumber + " " + columnNumber
	if (matrix[rowNumber][columnNumber] == MINE)
		return true;
	return false;
}

void Minesweeper::print(std::ostream & stream) {
	stream << "  ";
	for (int i = 0; i < this->dimension; i++)
		stream << i;
	stream << std::endl;
	// -------------------------------------
	stream << " " << "+";
	for (int i = 0; i < this->dimension; i++)
		stream << "-";
	stream << "+" << std::endl;
	// -------------------------------------
	for (int i = 0; i < this->dimension; i++) {
		stream << i << "|";
		for (int j = 0; j < this->dimension; j++)
		{
			stream << this->formatCell(matrix[i][j]);
		}
		stream << "|" << std::endl;
	}
	// -------------------------------------
	stream << " " << "+";
	for (int i = 0; i < this->dimension; i++)
		stream << "-";
	stream << "+" << std::endl;
}

/*
*	The function below checks every cell
* returning the state of it
*
*
*/
char Minesweeper::formatCell(char c) {
	// 1|000 0001 = 1 * 2^7 + 1 * 2^0 = ..
	if (c == MINE)
		return '*'; // Not visible bomb
	if (c == VISITED_EMPTY)
		return 'x'; // Visible empty space
	if (c == UNVISITED_EMPTY)
		return ' '; // Empty space (Not visible)
	if (c > 1)
		return c + 47; // Visible bomb-number
	// c < -1 // Not visible bomb-number
	return ' ';// c * (-1) + 47;// 'x';
}

void Minesweeper::makeMove(int rowNumber, int columnNumber) {
	if (gameOver)
		return;
	if (!isValidPosition(rowNumber, columnNumber))
		throw std::invalid_argument("Invalid coordinates! Please choose positive coordinates within the range of the game.");
	if (firstMove)
	{
		makeFirstMove(rowNumber, columnNumber);
		firstMove = false;
		return;
	}

	if (matrix[rowNumber][columnNumber] == MINE)
	{
		gameOver = true;
		return;
	}
	if (matrix[rowNumber][columnNumber] == UNVISITED_EMPTY){
		iterativeFlood(rowNumber, columnNumber);
		
	}
	if(matrix[rowNumber][columnNumber]<=-2){
		matrix[rowNumber][columnNumber] = matrix[rowNumber][columnNumber] * -1;
		visitedCells++;
	}
}
void Minesweeper::makeFirstMove(int rowNumber, int columnNumber) 
{
	while (isMineAt(rowNumber,columnNumber) || !isEmpty(rowNumber, columnNumber) ) {
		initialize();
	}
	iterativeFlood(rowNumber, columnNumber);
}

void Minesweeper::iterativeFlood(int rowNumber, int columnNumber) {
	std::queue<Pair> q;
	if (matrix[rowNumber][columnNumber] == VISITED_EMPTY)
		return;
	q.push({ rowNumber, columnNumber });
	while (!q.empty()) {
		Pair currentPair = q.front();
		q.pop();
		if (matrix[currentPair.x][currentPair.y] == UNVISITED_EMPTY) {
			matrix[currentPair.x][currentPair.y] = VISITED_EMPTY;
			visitedCells++;
		}
		if (matrix[currentPair.x][currentPair.y] <= -2) {
			matrix[currentPair.x][currentPair.y] = matrix[currentPair.x][currentPair.y] * -1;
			visitedCells++;
			continue;
		}
		if (matrix[currentPair.x][currentPair.y] != VISITED_EMPTY) {
			continue;
		}
		if (isValidUnvisitedPosition(currentPair.x - 1, currentPair.y - 1)) {
			q.push({ currentPair.x - 1, currentPair.y - 1 });
		}
		if (isValidUnvisitedPosition(currentPair.x - 1, currentPair.y)) {
			q.push({ currentPair.x - 1, currentPair.y });
		}
		if (isValidUnvisitedPosition(currentPair.x - 1, currentPair.y + 1)) {
			q.push({ currentPair.x - 1, currentPair.y + 1 });
		}
		if (isValidUnvisitedPosition(currentPair.x, currentPair.y - 1)) {
			q.push({ currentPair.x, currentPair.y - 1 });
		}
		if (isValidUnvisitedPosition(currentPair.x, currentPair.y + 1)) {
			q.push({ currentPair.x, currentPair.y + 1 });
		}
		if (isValidUnvisitedPosition(currentPair.x + 1, currentPair.y - 1)) {
			q.push({ currentPair.x + 1, currentPair.y - 1 });
		}
		if (isValidUnvisitedPosition(currentPair.x + 1, currentPair.y)) {
			q.push({ currentPair.x + 1, currentPair.y });
		}
		if (isValidUnvisitedPosition(currentPair.x + 1, currentPair.y + 1)) {
			q.push({ currentPair.x + 1, currentPair.y + 1 });
		}
	
	}
}

bool Minesweeper::isValidUnvisitedPosition(int rowNumber, int columnNumber) {
	if (isValidPosition(rowNumber, columnNumber) && matrix[rowNumber][columnNumber] <= -1 )
		return true;
	return false;
}

void Minesweeper::recursiveFlood(int rowNumber, int columnNumber) {
	if (matrix[rowNumber][columnNumber] == VISITED_EMPTY) {
		return;
	}
	if (matrix[rowNumber][columnNumber] == UNVISITED_EMPTY) {
		matrix[rowNumber][columnNumber] = VISITED_EMPTY;
		if (isValidPosition(rowNumber - 1, columnNumber - 1)) {
			recursiveFlood(rowNumber - 1, columnNumber - 1);
		}
		if (isValidPosition(rowNumber - 1, columnNumber)) {
			recursiveFlood(rowNumber - 1, columnNumber);
		}
		if (isValidPosition(rowNumber - 1, columnNumber + 1)) {
			recursiveFlood(rowNumber - 1, columnNumber + 1);
		}
		if (isValidPosition(rowNumber, columnNumber - 1)) {
			recursiveFlood(rowNumber, columnNumber - 1);
		}
		if (isValidPosition(rowNumber, columnNumber + 1)) {
			recursiveFlood(rowNumber, columnNumber + 1);
		}
		if (isValidPosition(rowNumber + 1, columnNumber - 1)) {
			recursiveFlood(rowNumber + 1, columnNumber - 1);
		}
		if (isValidPosition(rowNumber + 1, columnNumber)) {
			recursiveFlood(rowNumber + 1, columnNumber);
		}
		if (isValidPosition(rowNumber + 1, columnNumber + 1)) {
			recursiveFlood(rowNumber + 1, columnNumber + 1);
		}
	}
}

bool Minesweeper::isGameOver() {
	int unvisitedCells = this->dimension*this->dimension;
	if (gameOver == true) {
		return true;
	}
	if (unvisitedCells - visitedCells == numberOfMines) {
		return true;
	}
	return false;
}

bool Minesweeper::isEmpty(int rowNumber, int columnNumber) {
	if (matrix[rowNumber][columnNumber] == UNVISITED_EMPTY)
		return true;
	return false;
}