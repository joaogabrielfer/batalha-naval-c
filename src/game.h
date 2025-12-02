#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    Board* player_board; 
    Board* shots_board;  
    Fleet fleet;
    char nickname[32];
	int total_shots; 
    int total_hits;
} Player;

typedef struct {
    Player p1;
    Player p2;
    int current_player; 
    bool game_over;
} Game;

void init_game(Game* game, const char* p1_name, const char* p2_name, int board_size);
void destroy_game(Game* game);
void place_ships_randomly(Player* player);
void place_ships_manually(Player* player);
void switch_player(Game* game);
bool handle_shot(Game* game, const char* coords); 
bool is_valid_placement(const Board* board, int ship_length, int start_row, int start_col, char orientation);
void place_ship_on_board(Board* board, int ship_id, int ship_length, int start_row, int start_col, char orientation);

#endif // GAME_H
