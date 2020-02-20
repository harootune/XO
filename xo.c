#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void draw_board(char game_grid[][3])
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




int main()
{
	bool game_over;
	bool game_win;
	bool space_ok;

	char game_grid[3][3];
	char player_1;
	char player_2;
	char current_player;
	char buffer_clear;

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

	game_over = false;
	turn_count = 0;
	res_row = 0;
	res_row = 0;
	
	printf("%s", "Player 1, please input your symbol: ");
	player_1 = getchar();
	getchar();
	printf("%s", "Player 2, please input your symbol: ");
	player_2 = getchar();
	getchar();
	
	current_player = player_1;

	while (!(game_over))
	{
		draw_board(game_grid);
		
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
			game_win = check_win(game_grid, res_row, res_column, current_player);

			if (game_win)
			{
				printf("\n%c %s\n", current_player, "wins!");
				game_over = true;

			}	
			else if (turn_count == 9)
			{
				printf("\n%s\n", "It's a draw!");
				game_over = true;
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

	draw_board(game_grid);

	printf("\n%s\n", "Game Over!");
	
	return 0;
};



