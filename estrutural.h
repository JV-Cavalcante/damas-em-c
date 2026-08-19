#ifndef ESTRUTUTRAL_H
#define ESTRUTURAL_H
#include <stdbool.h>

struct Pecas{
    int cor; // 0 -> vazio, 1 -> preto, 2 -> branco
    bool e_dama; // inicia com False, se torna True quando virar dama.
};

struct Tabuleiro{
    struct Pecas campo[8][8];
    int turno; // 1 ou 2
    int pecas_jogador1; // começa com 12
    int pecas_jogador2; //começa com 12
};

//Protótipos das funções
void iniciar_jogo(struct Tabuleiro *novo);
bool validar_movimento(struct Tabuleiro *juiz, int lin_origem, int col_origem, int lin_destino, int col_destino);
void mover_pecas(struct Tabuleiro *mover, int lin_origem, int col_origem, int lin_destino, int col_destino);
void input(struct Tabuleiro *player);
bool validar_captura(struct Tabuleiro *tab, int lin_origem, int col_origem, int lin_destino, int col_destino);
void executar_captura(struct Tabuleiro *tab, int lin_origem, int col_origem, int lin_destino, int col_destino);
int checar_vencedor(struct Tabuleiro *tab);
void imprimir_tabuleiro(struct Tabuleiro *tab);

#endif //ESTRUTURAL_H