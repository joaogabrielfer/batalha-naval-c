#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io.h"

Home_opt print_home(){
	int scan_var;

	printf("=== BATALHA NAVAL ===\n");
	printf("1) Novo jogo\n");
	printf("2) Sair\n");

	scanf("%d", &scan_var);
	switch (scan_var){
		case 1:
			return NEW_GAME;
		case 2:
			return QUIT;
	}
	return UNDEFINED;
}

void get_nickname(char* nickname, int nickname_num) {
	printf("Insira o apelido do jogador %d:\n> ", nickname_num);
	scanf("%s", nickname);
}

int get_table_size(){
	int result;
	do{
		printf("Tamanho do tabuleiro (6-26):\n> ");
		scanf("%d", &result);
	} while(result < 6 || result > 26);

	return result;
}

bool is_automatic_position(){
	char posicionamento = 'e';
	do{
		printf("Posicionamento (M)anual ou (A)utomatico?\n> ");
		scanf(" %c", &posicionamento);
		switch(posicionamento){
			case 'm':
				return false;
			case 'M':
				return false;
			case 'a':
				return true;
			case 'A':
				return true;
		}
	}while (posicionamento == 'e');
	return true;
}

void get_shot_coords(char* buffer, int size) {
    printf("Digite a coordenada do tiro (ex: E5):\n> ");
    scanf("%s", buffer);
}

void get_manual_placement_input(char* buffer, int size, const char* ship_name, int ship_len) {
    printf("Posicione seu %s (%d celulas).\n", ship_name, ship_len);
    printf("Digite a coordenada inicial e a orientacao (ex: B5 H):\n> ");
    scanf("%s", buffer); 
    scanf(" %c", &buffer[strlen(buffer)]); 
}
