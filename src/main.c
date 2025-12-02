#include <stdio.h>
#include <stdlib.h> 
#include "io.h"
#include "game.h"
#include "rnd.h"

void clear_screen() {
#ifdef _WIN32
    system("cls")
#else
    system("clear");
#endif
}

int main() {
    init_random();

    Home_opt option;
    do {
        option = print_home();
        if (option == QUIT) {
            printf("Obrigado por jogar!\n");
            return 0;
        }
        if (option != NEW_GAME) {
            printf("Opcao invalida ou nao implementada.\n");
        }
    } while (option != NEW_GAME);

    char nickname1[32];
    char nickname2[32];
    get_nickname(nickname1, 1);
    get_nickname(nickname2, 2);
    int size = get_table_size();
    bool auto_pos = is_automatic_position();

    Game game;
    init_game(&game, nickname1, nickname2, size);

    if (auto_pos) {
        place_ships_randomly(&game.p1);
        place_ships_randomly(&game.p2);
    } else {
        clear_screen();
        place_ships_manually(&game.p1);
        clear_screen();
        place_ships_manually(&game.p2);
    }

    printf("\nTodos os navios posicionados! O jogo vai comecar.\n");
    printf("Pressione Enter para continuar...");
    getchar(); 
    getchar(); 

    while (!game.game_over) {
        clear_screen();
        Player* current_p = (game.current_player == 0) ? &game.p1 : &game.p2;
        
        printf("==============================\n");
        printf("      TURNO DE: %s\n", current_p->nickname);
        printf("==============================\n\n");

        printf("SEU MAPA DE TIROS (em %s):\n", (game.current_player == 0) ? game.p2.nickname : game.p1.nickname);
        print_board(current_p->shots_board, false);
        printf("\nSEU TABULEIRO (seus navios):\n");
        print_board(current_p->player_board, true);
        printf("\n");

        char coords_input[10];
        bool shot_ok = false;
        do {
            get_shot_coords(coords_input, sizeof(coords_input));
            shot_ok = handle_shot(&game, coords_input);
        } while (!shot_ok);
        
        if (!game.game_over) {
            printf("\nPressione Enter para passar o turno...");
            getchar(); 
            getchar(); 
            switch_player(&game);
        }
    }

    clear_screen();
    Player* winner = (game.current_player == 0) ? &game.p1 : &game.p2;
    Player* loser = (game.current_player == 0) ? &game.p2 : &game.p1;

    printf("\n*************************\n");
    printf("***   FIM DE JOGO   ***\n");
    printf("*************************\n\n");
    printf("VENCEDOR: %s\n\n", winner->nickname);

    float accuracy = 0.0f;
    if (winner->total_shots > 0) {
        accuracy = ((float)winner->total_hits / winner->total_shots) * 100.0f;
    }
    printf("--- Estatisticas de %s ---\n", winner->nickname);
    printf("Tiros Totais: %d\n", winner->total_shots);
    printf("Total de Acertos: %d\n", winner->total_hits);
    printf("Precisao: %.1f%%\n\n", accuracy);

    printf("--- Estado final do tabuleiro de %s (Vencedor) ---\n", winner->nickname);
    print_board(winner->player_board, true);
    printf("\n--- Estado final do tabuleiro de %s ---\n", loser->nickname);
    print_board(loser->player_board, true);

    destroy_game(&game); 

    return 0;
}
