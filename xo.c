#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "xo_backend.h"

void draw_board(char game_grid[][3])
{
	/*Prints the current game state to stdout*/
	
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


char game_loop(char player_1, char player_2, char current_player, bool ai, int difficulty)
{
	/*Executes a complete 2-player game*/

	bool game_over;
	bool space_ok;

	char game_grid[3][3];
	char buffer_clear;
	char game_win;

	int res_row;
	int res_column;
	int turn_count;

	
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

		if (ai)
		{
			if (current_player == player_1)
			{
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
			}
			else
			{

				struct move* best_moves;

				best_moves = find_best_move(game_grid, current_player, player_1, player_2);
			
				if (difficulty == 0)
				{
					res_row = best_moves[0].row+1;
					res_column = best_moves[0].column+1;
				}
				else
				{		
					srand(time(0));
					int chance = rand() % 4;

					if (difficulty == 1)
					{
						if (chance == 0 || chance == 1)
						{
							res_row = best_moves[1].row+1;
							res_column = best_moves[1].column+1;
						}
						else
						{
							res_row = best_moves[2].row+1;
							res_column = best_moves[2].column+1;
						};
					}
					else if (difficulty == 2)
					{
						if (chance == 0)
						{
							res_row = best_moves[0].row+1;
							res_column = best_moves[0].column+1;
						}
						else if (chance == 1 || chance == 2)
						{
							res_row = best_moves[1].row+1;
							res_column = best_moves[1].column+1;
						}
						else
						{
							res_row = best_moves[2].row+1;
							res_column = best_moves[2].column+1;
						};
					}
					else if (difficulty == 3)
					{
						if (chance == 0 || chance == 1)
						{
							res_row = best_moves[0].row+1;
							res_column = best_moves[0].column+1;
						}	
						else if (chance == 2)
						{
							res_row = best_moves[1].row+1;
							res_column = best_moves[1].column+1;
						}
						else
						{
							res_row = best_moves[2].row+1;
							res_column = best_moves[2].column+1;
						};
					}
					else
					{
						printf("%s", "Difficulty not assigned properly");
					};

				};
				sleep(2);

				free(best_moves);

				printf("\nThe AI has chosen: %d, %d\n", res_row, res_column);
			};

		}
		else
		{
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
	/*Main tic-tac-toe functionality*/

	bool game_end;
	bool ai;

	char player_1;
	char player_2;
	char buffer_clear;
	char current_player;
	char game_result;
	char res_ai;
	char res_continue;
	
	int difficulty;
	int player_1_wins;
	int player_2_wins;

	game_end = false;
	player_1_wins = 0;
	player_2_wins = 0;

	while (1)
	{
		printf("%s\n", "Would you like to play against an AI opponent? (y - yes, n - no, two player local multiplayer):");
		if (scanf("%c%c", &res_ai, &buffer_clear ) == 0)
		{	
			printf("\n%s\n", "Invalid input, please try again.");

			do
			{
				buffer_clear = getchar();
			}
			while (!isalpha(buffer_clear));
			ungetc(buffer_clear, stdin);	
		};


		if (res_ai == 'y' || res_ai == 'Y')
		{
			printf("\n%s\n", "Single-player mode selected.");
			ai = true;
			break;
		}
		else if (res_ai == 'n' || res_ai == 'N')
		{
			printf("\n%s\n", "Two-player mode selected.");
			ai = false;
			break;
		}
		else
		{
			printf("\n%s\n", "Invalid input, please try again.");
		};
	};
	
	if (ai)
	{
		while (1)
		{
			printf("%s\n", "Please select difficulty (0 - Perfect AI, 1 - Easy, 2 - Medium, 3 - Hard)");
			if (scanf("%d%c", &difficulty, &buffer_clear ) == 0)
			{	
				printf("\n%s\n", "Invalid input, please try again.");

				do
				{
					buffer_clear = getchar();
				}
				while (!isdigit(buffer_clear));
				ungetc(buffer_clear, stdin);	
			};

			if (difficulty == 0 ||
				difficulty == 1 ||
				difficulty == 2 ||
				difficulty ==3)
			{
				printf("\n%s: %d\n", "Difficulty selected",  difficulty);
				break;
			}
			else
			{
				printf("\n%s\n", "Invalid input, must be 0, 1, 2, or 3.");
			};
		};
	};

	/*Get player inputs symbols*/	
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

	if (ai)
	{
		printf("%s", "Please select your opponent's symbol: ");
	}
	else
	{
		printf("%s", "Player 2, please input your symbol: ");
	};
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

	/*Session loop*/
	while (!game_end)
	{
		game_result = game_loop(player_1, player_2, current_player, ai, difficulty);
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



