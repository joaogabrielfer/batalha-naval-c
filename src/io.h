#ifndef IO_H
#define IO_H

#include <stdbool.h>

typedef enum {
    NEW_GAME,
    CONFIG,
    QUIT,
    UNDEFINED
} Home_opt;

Home_opt print_home();
void get_nickname(char* nickname, int nickname_num);
int get_table_size();
bool is_automatic_position();
void get_shot_coords(char* buffer, int buffer_size); 
void get_shot_coords(char* buffer, int size);
void get_manual_placement_input(char* buffer, int size, const char* ship_name, int ship_len);

#endif 
