#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef enum {
    CELL_WATER, 
    CELL_SHIP,  
    CELL_HIT,   
    CELL_MISS   
} CellState;

typedef struct {
    CellState state;
    int ship_id; 
} Cell;

typedef struct {
    int rows, cols;
    Cell *cells; 
} Board;

Board* create_board(int rows, int cols);
void destroy_board(Board* board);
void print_board(const Board* board, bool show_ships);
Cell* get_cell(Board* board, int row, int col);
bool is_valid_placement(const Board* board, int ship_length, int start_row, int start_col, char orientation);

#endif // BOARD_H
