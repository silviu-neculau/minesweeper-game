// Minesweeper.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <cstdlib>
#include "stdafx.h"
using namespace std;
char vizboard[16];
char board[16];
void initialboard(char board[][], char vizboard[][])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{			
			board[i][j] = '-';
			vizboard[i][j] = '-';
		}
}
void mineadd(char vizboard[][],int mines)
{
	int mines, nrmines = 0;
	while (nrmines < mines)
	{
		mines = rand() % (n * n);

		if (board[mines] != '*')
		{
			board[mines] = '*';
			nrmines++;
		}
	}
}

int main()
{
    return 0;
}

