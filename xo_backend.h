#include <stdbool.h>


struct move;

bool check_space(char game_grid[][3], int res_row, int res_column);

bool is_moves_left(char game_grid[][3]);

bool check_win(char game_grid[][3], int res_row, int res_column, char current_player);

int evaluate_board(char game_grid[][3], char maxplayer, char minplayer);

int minimax(char game_grid[][3], int depth, bool max);

struct move find_best_move(char game_grid[][3]);

