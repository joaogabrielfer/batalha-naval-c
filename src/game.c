#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "game.h"
#include "board.h"
#include "rnd.h"

void init_game(Game* game, const char* p1_name, const char* p2_name, int board_size) {
    strcpy(game->p1.nickname, p1_name);
    game->p1.player_board = create_board(board_size, board_size);
    game->p1.shots_board = create_board(board_size, board_size);
    initialize_fleet(&game->p1.fleet);
    game->p1.total_shots = 0; 
    game->p1.total_hits = 0;  

    strcpy(game->p2.nickname, p2_name);
    game->p2.player_board = create_board(board_size, board_size);
    game->p2.shots_board = create_board(board_size, board_size);
    initialize_fleet(&game->p2.fleet);
    game->p2.total_shots = 0;
    game->p2.total_hits = 0; 

    game->current_player = 0;
    game->game_over = false;
}

void destroy_game(Game* game) {
    destroy_board(game->p1.player_board);
    destroy_board(game->p1.shots_board);
    destroy_board(game->p2.player_board);
    destroy_board(game->p2.shots_board);
}

bool is_valid_placement(const Board* board, int ship_length, int start_row, int start_col, char orientation) {
    if (orientation == 'H') {
        if (start_col + ship_length > board->cols) return false;
    } else { // Vertical
        if (start_row + ship_length > board->rows) return false;
    }

    for (int i = 0; i < ship_length; i++) {
        int current_row = start_row;
        int current_col = start_col;

        if (orientation == 'H') {
            current_col += i;
        } else {
            current_row += i;
        }

        Cell* cell = get_cell((Board*)board, current_row, current_col);
        if (cell->state == CELL_SHIP) {
            return false; 
        }
    }

    return true; 
}

void place_ship_on_board(Board* board, int ship_id, int ship_length, int start_row, int start_col, char orientation) {
    for (int i = 0; i < ship_length; i++) {
        int current_row = start_row;
        int current_col = start_col;

        if (orientation == 'H') {
            current_col += i;
        } else {
            current_row += i;
        }

        Cell* cell = get_cell(board, current_row, current_col);
        cell->state = CELL_SHIP;
        cell->ship_id = ship_id;
    }
}

void place_ships_randomly(Player* player) {
    printf("Posicionando a frota de %s automaticamente...\n", player->nickname);

    for (int i = 0; i < player->fleet.count; i++) {
        Ship* current_ship = &player->fleet.ships[i];
        
        bool placed = false;
        while (!placed) {
            int start_row = random_int(0, player->player_board->rows - 1);
            int start_col = random_int(0, player->player_board->cols - 1);
            char orientation = (random_int(0, 1) == 0) ? 'H' : 'V';

            if (is_valid_placement(player->player_board, current_ship->length, start_row, start_col, orientation)) {
                place_ship_on_board(player->player_board, i, current_ship->length, start_row, start_col, orientation);
                current_ship->placed = true;
                placed = true;
            }
        }
    }
    printf("Frota de %s posicionada!\n", player->nickname);
}

void switch_player(Game* game) {
    game->current_player = 1 - game->current_player; 
}

bool handle_shot(Game* game, const char* coords) {
    if (strlen(coords) < 2 || strlen(coords) > 3) {
        printf("Formato de coordenada invalido. Use A1, B10, etc.\n");
        return false;
    }

    char col_char = toupper(coords[0]);
    if (col_char < 'A' || col_char >= 'A' + game->p1.player_board->cols) {
        printf("Coluna invalida.\n");
        return false;
    }
    int col = col_char - 'A';

    int row = atoi(&coords[1]) - 1;
    if (row < 0 || row >= game->p1.player_board->rows) {
        printf("Linha invalida.\n");
        return false;
    }

    Player* attacker = (game->current_player == 0) ? &game->p1 : &game->p2;
    Player* defender = (game->current_player == 0) ? &game->p2 : &game->p1;

    Cell* target_cell = get_cell(defender->player_board, row, col);

    if (target_cell->state == CELL_HIT || target_cell->state == CELL_MISS) {
        printf("Coordenada ja atingida. Tente novamente.\n");
        return false;
    }
	attacker->total_shots++;

    if (target_cell->state == CELL_WATER) {
        target_cell->state = CELL_MISS;
        get_cell(attacker->shots_board, row, col)->state = CELL_MISS;
        printf("Resultado: AGUA.\n");
    } else if (target_cell->state == CELL_SHIP) {
        target_cell->state = CELL_HIT;
        get_cell(attacker->shots_board, row, col)->state = CELL_HIT;
        attacker->total_hits++; // Incrementa acertos

        Ship* hit_ship = get_ship_by_id(&defender->fleet, target_cell->ship_id);
        hit_ship->hits++;

        if (hit_ship->hits == hit_ship->length) {
            hit_ship->sunk = true;
            printf("Resultado: AFUNDOU %s!\n", hit_ship->name);
            if (is_fleet_sunk(&defender->fleet)) {
                game->game_over = true;
            }
        } else {
            printf("Resultado: ACERTOU no %s!\n", hit_ship->name);
        }
    }
    return true;
}

void place_ships_manually(Player* player) {
    printf("\n--- Posicionamento Manual para %s ---\n", player->nickname);

    for (int i = 0; i < player->fleet.count; i++) {
        Ship* current_ship = &player->fleet.ships[i];
        bool placed = false;

        while (!placed) {
            printf("\n");
            print_board(player->player_board, true);
            
            printf("Posicione seu %s (%d celulas). Ex: B5 H\n> ", current_ship->name, current_ship->length);
            char coords[4];
            char orientation_char;
            scanf("%s %c", coords, &orientation_char);

            int row = atoi(&coords[1]) - 1;
            int col = toupper(coords[0]) - 'A';
            orientation_char = toupper(orientation_char);

            if (orientation_char != 'H' && orientation_char != 'V') {
                printf("Orientacao invalida. Use 'H' para horizontal ou 'V' para vertical.\n");
                continue;
            }

            if (is_valid_placement(player->player_board, current_ship->length, row, col, orientation_char)) {
                place_ship_on_board(player->player_board, i, current_ship->length, row, col, orientation_char);
                current_ship->placed = true;
                placed = true;
            } else {
                printf("Posicao invalida! O navio sai do tabuleiro ou sobrepoe outro.\n");
            }
        }
    }
    printf("\nFrota de %s posicionada com sucesso!\n", player->nickname);
}
