#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void draw_board(char game_grid[][3])
{
	printf("%s\n", "Game state:");
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


int check_space(char game_grid[][3], int res_row, int res_column)
{
	char space;
	
	space = game_grid[res_row-1][res_column-1];

	if (space == '-')
	{
		return 0;
	}
	else
	{
		printf("%s\n", "Space filled, please try again.");
		return 1;
	};

	return 1;
};


int main()
{
	bool game_over;
	char game_grid[3][3];
	char player_1;
	char player_2;
	char current_player;
	int res_row;
	int res_column;
	int space_status;
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
		
		printf("%c, %s\n", current_player, "Please input the coordinates of the space you'd like to fill (Format - row, column):");
		scanf("%d, %d", &res_row, &res_column);
		if (res_row < 1 ||
		    res_row > 3 ||
		    res_column < 1 ||
		    res_column > 3)
		{
			printf("%s\n", "Invalid input, try again");
			continue;
		};


		space_status = check_space(game_grid, res_row, res_column);	

		if (!(space_status))
		{
			turn_count += 1;
			game_grid[res_row-1][res_column-1] = current_player;
			
			if (current_player == player_1)
			{
				current_player = player_2;
			}
			else if (current_player == player_2)
			{
				current_player = player_1;
			}
			else
			{
				printf("%s", "LINE 110 FUCKED");
			};	

			if (turn_count == 9)
			{
				game_over = true;
			};
		};
	};

	draw_board(game_grid);

	printf("\n%s\n", "Game Over!");
	
	return 0;
};



