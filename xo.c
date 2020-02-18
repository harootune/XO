#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main()
{
	bool game_over;
	char game_grid[3];
	char response;
	
	game_grid[0] = '-';
	game_grid[1] = '-';
	game_grid[2] = '-';

	game_over = false;

	while (!(game_over))
	{
		printf("%s\n", "Game state:");
		printf("%d %d %d\n", 1, 2, 3);
		printf("%c %c %c\n", game_grid[0], game_grid[1], game_grid[2]);

		printf("%s\n", "Please select a space to fill (1-3):");
		response = getchar();
		getchar();
		
		switch(response)
		{
			case '1':
				if (game_grid[0] == '-')
				{
					game_grid[0] = 'X';
				}
				else
				{
					printf("\n%s\n", "Space already filled, try again");
				};
				break;
			case '2':
				if (game_grid[1] == '-')
				{
					game_grid[1] = 'X';
				}
				else
				{
					printf("\n%s\n", "Space already filled, try again");
				};
				break;
			case '3':
				if (game_grid[2] == '-')
				{
					game_grid[2] = 'X';
				}
				else
				{
					printf("\n%s\n", "Space already filled, try again");
				};
				break;
			default:
				printf("%s\n", "Not a valid input, try again.");		
		};

		if (game_grid[0] == 'X' && game_grid[1] == 'X' && game_grid[2] == 'X')
		{
			game_over = true;
		};
	};

	printf("%s\n", "Game state:");
	printf("%d %d %d\n", 1, 2, 3);
	printf("%c %c %c\n", game_grid[0], game_grid[1], game_grid[2]);
	printf("%s\n", "Game Over!");
	
	return 0;
};


