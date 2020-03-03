#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "xo_backend.h"

void draw_board(char game_grid[][3])
/*Prints the current game state to stdout*/
{
	printf("\n%s\n", "Game state:");
	printf(" %d %d %d\n", 1, 2, 3);
	for (int i=0; i<3; i++)
	{
		printf("%d", i+1);

		for (int j=0; j<3; j++)
		{
			printf(" %c", game_grid[i][j]);
		};

		printf("%c", '\n');
	};
};


char game_loop(char player_1, char player_2, char current_player)
/*Executes a complete 2-player game*/
{
	bool game_over;
	bool space_ok;

	char game_grid[3][3];
	char buffer_clear;
	char game_win;

	int res_row;
	int res_column;
	int turn_count;

	struct move best_move;
	
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			game_grid[i][j] = '-';
		};
	};

	turn_count = 0;
	res_row = 0;
	res_row = 0;
	
	while (1)
	{
		draw_board(game_grid);

		best_move = find_best_move(game_grid, current_player, player_1, player_2);
		printf("\n%s %d, %d", "The best possible move is:", best_move.row+1, best_move.column+1);
		
		printf("\n%c, %s\n", current_player, "Please input the coordinates of the space you'd like to fill (Format - row, column):");

		if (scanf("%d, %d", &res_row, &res_column) == 0)
		{	
			printf("\n%s\n", "Invalid input, try again");

			do
			{
				buffer_clear = getchar();
			}
			while (!isdigit(buffer_clear));
			ungetc(buffer_clear, stdin);	
		};

		if (res_row < 1 ||
		    res_row > 3 ||
		    res_column < 1 ||
		    res_column > 3)
		{
			printf("\n%s\n", "Invalid input, please check coordinates.");
			continue;
		};
		
		res_row -= 1;
		res_column -= 1;
		
		space_ok = check_space(game_grid, res_row, res_column);	

		if (space_ok)
		{
			turn_count += 1;
			game_grid[res_row][res_column] = current_player;
			game_win = check_win(game_grid);

			if (game_win == current_player)
			{
				return current_player;
			}	
			else if (turn_count == 9)
			{
				return 0;
			}
			else if (current_player == player_1)
			{
				current_player = player_2;
			}
			else if (current_player == player_2)
			{
				current_player = player_1;
			}
			else
			{
				printf("\n%s\n", "LINE 110 FUCKED");
			};	
		}
		else
		{
			printf("\n%s\n", "Space filled, please try again.");
		};
	};
};


int main()
{
	bool game_end;

	char player_1;
	char player_2;
	char buffer_clear;
	char current_player;
	char game_result;
	char res_continue;
	
	int player_1_wins;
	int player_2_wins;

	game_end = false;
	player_1_wins = 0;
	player_2_wins = 0;

	
	printf("%s", "Player 1, please input your symbol: ");
	if (scanf("%c%c", &player_1, &buffer_clear) == 0)
	{	
		printf("\n%s\n", "Invalid input, try again. Must be alphanumeric.");

		do
		{
			buffer_clear = getchar();
		}
		while (!isalnum(buffer_clear));
		ungetc(buffer_clear, stdin);	
	};
	printf("%s", "Player 2, please input your symbol: ");
	if (scanf("%c%c", &player_2, &buffer_clear) == 0)
	{	
		printf("\n%s\n", "Invalid input, try again. Must be alphanumeric.");

		do
		{
			buffer_clear = getchar();
		}
		while (!isalnum(buffer_clear));
		ungetc(buffer_clear, stdin);	
	};

	current_player = player_1;

	while (!game_end)
	{
		game_result = game_loop(player_1, player_2, current_player);
		getchar(); /*don't question it*/

		if (game_result == player_1)
		{
			printf("\n%c wins!\n", player_1); 
			player_1_wins += 1;	
		}
		else if (game_result == player_2)
		{
			printf("\n%c wins!\n", player_2); 
			player_2_wins += 1;	
		}
		else
		{
			printf("\n%s\n", "It's a draw.");
		};
		
		printf("%c: %d, %c: %d\n", player_1,
					   player_1_wins,
					   player_2,
					   player_2_wins);

		while (1)
		{
			printf("\n%s ", "Play again? (Y/N):");
			if (scanf("%c", &res_continue) == 0)
			{	
				printf("\n%s", "Invalid input, try again");

				do
				{
					buffer_clear = getchar();
				}
				while (!isalpha(buffer_clear));
				ungetc(buffer_clear, stdin);	
			};

			if (res_continue == 'y' || res_continue == 'Y')
			{
				if (game_result == player_1)
				{
					current_player = player_2;
				}
				else if (game_result == player_2)
				{
					current_player = player_1;
				}
				else
				{
					if (current_player == player_1)
					{
						current_player = player_2;
					}
					else
					{
						current_player = player_1;
					};
				};

				printf("\n%s\n", "Starting new game...");
				break;
			}
			else if (res_continue == 'n' || res_continue =='N')
			{
				game_end = true;
				break;
			}
			else
			{
				printf("\n%s", "Invalid input, must be Y, y, N, or n.");
			};
		};
	};
	
	printf("\n%s\n", "Thanks for Playing!");
	
	return 0;
};



