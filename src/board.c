#include <stdio.h>
#include <stdlib.h>
#include "board.h"

Board* create_board(int rows, int cols) {
    Board* board = (Board*) malloc(sizeof(Board));
    if (!board) return NULL;

    board->rows = rows;
    board->cols = cols;
    board->cells = (Cell*) malloc(rows * cols * sizeof(Cell));
    if (!board->cells) {
        free(board);
        return NULL;
    }

    for (int i = 0; i < rows * cols; i++) {
        board->cells[i].state = CELL_WATER;
        board->cells[i].ship_id = -1;
    }
    return board;
}

void destroy_board(Board* board) {
    if (board) {
        free(board->cells);
        free(board);
    }
}

void print_board(const Board* board, bool show_ships) {
    printf("  ");
    for (int i = 0; i < board->cols; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < board->rows; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < board->cols; j++) {
            Cell cell = board->cells[i * board->cols + j];
            char c = '~'; 
            switch (cell.state) {
                case CELL_SHIP:
                    c = show_ships ? 'S' : '~';
                    break;
                case CELL_HIT:
                    c = 'X'; 
                    break;
                case CELL_MISS:
                    c = '.';
                    break;
                case CELL_WATER:
                default:
                    c = '~';
                    break;
            }
            printf("%c ", c);
        }
        printf("\n");
    }
}

Cell* get_cell(Board* board, int row, int col) {
    if (row >= 0 && row < board->rows && col >= 0 && col < board->cols) {
        return &board->cells[row * board->cols + col];
    }
    return NULL;
}
