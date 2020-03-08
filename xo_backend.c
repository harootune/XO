#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "xo_backend.h"

bool check_space(char game_grid[][3], int res_row, int res_column)
{
	/*Check if space is available - return false if not*/

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
	/*Check board state - if board is locked, return false*/

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


char check_win(char game_grid[][3])
{
	/*Check for a win and return a character representing the result*/

	/*Check rows*/
	for (int i=0; i<3; i++)
	{
		if (game_grid[i][0]==game_grid[i][1] &&
		    game_grid[i][1]==game_grid[i][2])
		{
			return game_grid[i][0];
		};
	};
	/*Check columns*/
	for (int i=0; i<3; i++)
	{
		if (game_grid[0][i]==game_grid[1][i] &&
		    game_grid[1][i]==game_grid[2][i])
		{
			return game_grid[0][i];
		};
	};
	/*Check diagonals*/
	if ((game_grid[0][0]==game_grid[1][1] &&
	     game_grid[1][1]==game_grid[2][2]) ||
	    (game_grid[0][2]==game_grid[1][1] &&
	     game_grid[1][1]==game_grid[2][0]))
	{
		return game_grid[1][1];
	};

	return '-';
};


int minimax(char game_grid[][3], int depth, bool max, char maxplayer, char minplayer)
{
	/*Check for a terminal state*/

	char result = check_win(game_grid);

	if (result == maxplayer) 
	{
		return 10;
	}
	else if (result == minplayer)
	{
		return -10;
	}	
	else if (!(is_moves_left(game_grid)))
	{
		return 0;
	};


	/*Check next moves*/
	if (max)
	{
		int move_val;
		int best_val = -1000;

		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
			{
				if (check_space(game_grid, i, j))
				{
					game_grid[i][j] = maxplayer;

					move_val = minimax(game_grid, depth+1, !max, maxplayer, minplayer);
					if (move_val > best_val)
					{
						best_val = move_val;
					};
					
					game_grid[i][j] = '-';
				};	
			};
		};
		
		return best_val;
	}
	else	
	{
		int move_val;
		int best_val = 1000;

		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
			{
				if (check_space(game_grid, i, j))
				{
					game_grid[i][j] = minplayer;

					move_val = minimax(game_grid, depth+1, !max, maxplayer, minplayer);
					if (move_val < best_val)
					{
						best_val = move_val;
					};
					
					game_grid[i][j] = '-';
				};	
			};
		};
		
		return best_val;
	};
};


struct move* find_best_move(char game_grid[][3], char current_player, char maxplayer, char minplayer)
{
	/*Return the best move for a player in a given situation*/
	
	struct move* move_arr;

	struct move best_move;
	struct move second_move;
	struct move third_move;

	int move_val;
	int best_val;
	int second_val;
	int third_val;

	if (current_player == maxplayer)
	{
		best_val = -1000;
		second_val = -1000;
		third_val = -1000;
	
		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
			{
				if (check_space(game_grid, i, j))
				{
					game_grid[i][j] = current_player;

					move_val = minimax(game_grid, 0, false, maxplayer, minplayer);
					if (move_val > best_val)
					{
						best_move.row = i;
						best_move.column = j;
						best_val = move_val;
					}
					else if (move_val > second_val)
					{
						second_move.row = i;
						second_move.column = j;
						second_val = move_val;
					}
					else if (move_val > third_val)
					{
						third_move.row = i;
						third_move.column = j;
						third_val = move_val;
					};
						
					game_grid[i][j] = '-';
				};	
			};
		};

		if (second_val == -1000)
		{
			second_move.row = best_move.row;
			second_move.column = best_move.column;
			third_move.row = best_move.row;
			third_move.column = best_move.column;
		}
		else if (third_val == -1000)
		{
			third_move.row = second_move.row;
			third_move.column = second_move.column;
		};
	}
	else	
	{
		best_val = 1000;
		second_val = 1000;
		third_val = 1000;

		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
			{
				if (check_space(game_grid, i, j))
				{
					game_grid[i][j] = current_player;

					move_val = minimax(game_grid, 0, true, maxplayer, minplayer);
					if (move_val < best_val)
					{
						best_move.row = i;
						best_move.column = j;
						best_val = move_val;
					}
					else if (move_val < second_val)
					{
						second_move.row = i;
						second_move.column = j;
						second_val = move_val;
					}
					else if (move_val < third_val)
					{
						third_move.row = i;
						third_move.column = j;
						third_val = move_val;
					};

					game_grid[i][j] = '-';
				};	
			};
		};

		if (second_val == 1000)
		{
			second_move.row = best_move.row;
			second_move.column = best_move.column;
			third_move.row = best_move.row;
			third_move.column = best_move.column;
		}
		else if (third_val == 1000)
		{
			third_move.row = second_move.row;
			third_move.column = second_move.column;
		};

	};
	
	move_arr = malloc(sizeof(struct move) * 3);

	move_arr[0] = best_move;
	move_arr[1] = second_move;
	move_arr[2] = third_move;

	return move_arr;
};

