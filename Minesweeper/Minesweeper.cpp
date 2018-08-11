#include "Minesweeper.h"

void initialboard(char board[][], char vizboard[][])
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			board[i][j] = '-';
			vizboard[i][j] = '-';
		}
}
void mineadd(char vizboard[][], int mines)
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