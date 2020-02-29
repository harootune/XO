#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "xo_backend.h"


struct move
{
	int row;
	int column;
	int value;
};


bool check_space(char game_grid[][3], int res_row, int res_column)
{
	char space;
	
	space = game_grid[res_row][res_column];

	if (space == '-')
	{
		return true;
	}
	else
	{
		return false;
	};

	return false;
};


bool is_moves_left(char game_grid[][3])
{
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			if (game_grid[i][j] == '-')
			{
				return true;
			};
		};
	};

	return false;
};


bool check_win(char game_grid[][3], int res_row, int res_column, char current_player)
{
	if (game_grid[res_row][0] == current_player &&
	    game_grid[res_row][1] == current_player &&
	    game_grid[res_row][2] == current_player)
	{
		return true;
	}
	else if (game_grid[0][res_column] == current_player &&
		 game_grid[1][res_column] == current_player &&
		 game_grid[2][res_column] == current_player)
	{
		return true;
	}
	else if ((game_grid[0][0] == current_player &&
		  game_grid[1][1] == current_player &&
		  game_grid[2][2] == current_player) ||
		 (game_grid[0][2] == current_player &&
		  game_grid[1][1] == current_player &&
		  game_grid[2][0] == current_player))
	{
		return true;
	};
	
	return false;
};


int evaluate_board(char game_grid[][3], char maxplayer, char minplayer)
{
	/*Return a value for the game board*/
	return 0;
};


int minimax(char game_grid[][3], int depth, bool max)
{
	/*Return the value of a move*/
};


struct move find_best_move(char game_grid[][3])
{
	/*Return the best move for a player in a given situation*/
};

