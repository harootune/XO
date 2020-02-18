#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main()
{
	bool game_over;
	char response;
	
	game_over = false;

	while (!(game_over))
	{
		printf("%s\n", "Would you like to end the game? (y/n):");
		response = getchar();

		if (response == 'y' || response == 'Y')
		{
			game_over = true;
		};
	};

	return 0;
};
