#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "xo_backend.h"

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


char check_win(char game_grid[][3])
{
	for (int i=0; i<3; i++)
	{
		if (game_grid[i][0]==game_grid[i][1] &&
		    game_grid[i][1]==game_grid[i][2])
		{
			return game_grid[i][0];
		};
	};

	for (int i=0; i<3; i++)
	{
		if (game_grid[0][i]==game_grid[1][i] &&
		    game_grid[1][i]==game_grid[2][i])
		{
			return game_grid[0][i];
		};
	};

	if ((game_grid[0][0]==game_grid[1][1] &&
	     game_grid[1][1]==game_grid[2][2]) ||
	    (game_grid[0][2]==game_grid[1][1] &&
	     game_grid[1][1]==game_grid[2][0]))
	{
		return game_grid[1][1];
	};

	return '-';
};


/*
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
*/

int evaluate_board(char game_grid[][3], char maxplayer, char minplayer)
{
	char result = check_win(game_grid);

	if (result == maxplayer)
	{
		return 10;
	}
	else if (result == minplayer)
	{
		return -10;
	}
	else
	{
		return 0;
	};
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


struct move find_best_move(char game_grid[][3], char current_player, char maxplayer, char minplayer)
{
	/*Return the best move for a player in a given situation*/
	
	struct move best_move;
	int move_val;
	int best_val;

	if (current_player == maxplayer)
	{
		best_val = -1000;
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
					};
						
					game_grid[i][j] = '-';
				};	
			};
		};
	}
	else	
	{
		best_val = 1000;
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
					};
						
					game_grid[i][j] = '-';
				};	
			};
		};
	};

	return best_move;
};

