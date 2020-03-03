#include <stdbool.h>


struct move
{
	int row;
	int column;
};

bool check_space(char game_grid[][3], int res_row, int res_column);

bool is_moves_left(char game_grid[][3]);

char check_win(char game_grid[][3]);

int evaluate_board(char game_grid[][3], char maxplayer, char minplayer);

int minimax(char game_grid[][3], int depth, bool max, char maxplayer, char minplayer);

struct move find_best_move(char game_grid[][3], char current_player, char maxplayer, char minplayer);

