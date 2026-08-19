#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "estrutural.h"

/// --- Lógica do jogo ----

void iniciar_jogo(struct Tabuleiro *novo){
    novo->pecas_jogador1 = 12;
    novo->pecas_jogador2 = 12;
    novo->turno = 1;

    for(int linha = 0; linha < 8; linha++){
        for(int coluna = 0; coluna < 8; coluna++){
            if((linha + coluna) % 2 != 0){
                if(linha < 3){
                    novo->campo[linha][coluna].cor = 2;
                    novo->campo[linha][coluna].e_dama = false;
                }
                else if(linha > 4){
                    novo->campo[linha][coluna].cor = 1;
                    novo->campo[linha][coluna].e_dama = false;
                }
                else{
                    novo->campo[linha][coluna].cor = 0;
                    novo->campo[linha][coluna].e_dama = false;
                }
            }
            else{
                novo->campo[linha][coluna].cor = 0;
                novo->campo[linha][coluna].e_dama = false;
            }
        }
    }
}

bool validar_movimento(struct Tabuleiro *juiz, int lin_origem, int col_origem, int lin_destino, int col_destino){

    // Checa se o destino está vazio.
    if(juiz->campo[lin_destino][col_destino].cor != 0){
        return false;
    }
    // Peças devem se mover apenas 1 casa na diagonal.
    if(abs(col_destino - col_origem) != 1 || abs(lin_destino - lin_origem) != 1){
        return false;
    }

    // Regra de direção para peças normais.
    if(!juiz->campo[lin_origem][col_origem].e_dama){
        // Jogador 1 sobe o tabuleiro (linha diminui)
        if(juiz->campo[lin_origem][col_origem].cor == 1 && lin_destino != lin_origem - 1){
            return false;
        }
        // Jogador 2 desce o tabuleiro (linha aumenta)
        if(juiz->campo[lin_origem][col_origem].cor == 2 && lin_destino != lin_origem + 1){
            return false;
        }
    }

    return true; // Movimento válido (para peças normais e damas)
}

void mover_pecas(struct Tabuleiro *mover, int lin_origem, int col_origem, int lin_destino, int col_destino){

    //usa col_origem na leitura da peça
    mover->campo[lin_destino][col_destino] = mover->campo[lin_origem][col_origem];

    //Esvazia a posição de origem
    mover->campo[lin_origem][col_origem].cor = 0;
    mover->campo[lin_origem][col_origem].e_dama = false;
    
    // Promove a Dama quando chegar ao fim do tabuleiro
    if(mover->campo[lin_destino][col_destino].cor == 1 && lin_destino == 0){
        mover->campo[lin_destino][col_destino].e_dama = true;
    }
    else if(mover->campo[lin_destino][col_destino].cor == 2 && lin_destino == 7){
        mover->campo[lin_destino][col_destino].e_dama = true;
    }
}

bool validar_captura(struct Tabuleiro *tab, int lin_origem, int col_origem, int lin_destino, int col_destino){

    // Destino precisa estar vazio
    if(tab->campo[lin_destino][col_destino].cor != 0){
        return false;
    }

    // A distância precisa ser exatamente de duas casas
    if(abs(lin_destino - lin_origem) != 2 || abs(col_destino - col_origem) != 2){
        return false;
    }

    // Calcula onde está a peça do meio
    int lin_meio = (lin_origem + lin_destino) / 2;
    int col_meio = (col_origem + col_destino) / 2;

    int cor_adversario = (tab->turno == 1) ? 2 : 1;

    // A casa do meio precisa ter uma peça adversária
    if(tab->campo[lin_meio][col_meio].cor != cor_adversario){
        return false;
    }

    // Direcionamento para peças normais
    if(!tab->campo[lin_origem][col_origem].e_dama){
        if(tab->turno == 1 && lin_destino >= lin_origem){
            return false;
        }
        if (tab->turno == 2 && lin_destino <= lin_origem){
            return false;
        }
    }

    return true; // Captura válida
}

void executar_captura(struct Tabuleiro *tab, int lin_origem, int col_origem, int lin_destino, int col_destino){

    tab->campo[lin_destino][col_destino] = tab->campo[lin_origem][col_origem];

    //limpa [lin_origem][col_origem]
    tab->campo[lin_origem][col_origem].cor = 0;
    tab->campo[lin_origem][col_origem].e_dama = false;

    // Remove a peça adversária (ponto médio)
    int lin_meio = (lin_origem + lin_destino) / 2;
    int col_meio = (col_origem + col_destino) / 2;

    tab->campo[lin_meio][col_meio].cor = 0;
    tab->campo[lin_meio][col_meio].e_dama = false;

    // Atualizando o placar
    if(tab->turno == 1){
        tab->pecas_jogador2--;
    }
    else{
        tab->pecas_jogador1--;
    }

    // Checando a promoção da dama
    if(tab->turno == 1 && lin_destino == 0){
        tab->campo[lin_destino][col_destino].e_dama = true;
    }
    else if(tab->turno == 2 && lin_destino == 7){
        tab->campo[lin_destino][col_destino].e_dama = true;
    }
}

void input(struct Tabuleiro *player){

    int lin_origem, col_origem;
    int lin_destino, col_destino;
    bool jogada_valida = false;

    while(!jogada_valida){
        printf("\n=======================================\n");
        printf("TURNO DO JOGADOR %d (P1: %d pecas | P2: %d pecas)\n", 
               player->turno, player->pecas_jogador1, player->pecas_jogador2);
        printf("=======================================\n");

        printf("Digite a linha e coluna da peça a ser movida (ex: 5 2): ");
        if(scanf("%d %d", &lin_origem, &col_origem) != 2){
            printf("Entrada inválida! Use números de 0 a 7.\n");
            while(getchar() != '\n');
            continue;
        }

        printf("Digite a linha e coluna de destino (ex: 4 3): ");
        if(scanf("%d %d", &lin_destino, &col_destino) != 2){
            printf("Entrada inválida! Use números de 0 a 7.\n");
            while(getchar() != '\n');
            continue;
        }

        // Validação de limites (0 a 7)
        if(lin_origem < 0 || lin_origem > 7 || col_origem < 0 || col_origem > 7 || 
           lin_destino < 0 || lin_destino > 7 || col_destino < 0 || col_destino > 7){
            printf("\n[ERRO] Coordenadas fora do tabuleiro (0 a 7)! Tente novamente.\n");
            continue;
        }

        if(player->campo[lin_origem][col_origem].cor != player->turno){
            printf("\n[ERRO] Escolha uma peça que pertence ao jogador %d!\n", player->turno);
            continue;
        }
        
        int dist = abs(lin_destino - lin_origem);

        //Decide se é movimento simples ou captura
        if(dist == 1){
            if(validar_movimento(player, lin_origem, col_origem, lin_destino, col_destino)){
                mover_pecas(player, lin_origem, col_origem, lin_destino, col_destino);
                jogada_valida = true;
                printf("\nMovimento realizado!\n");
            } else {
                printf("\n[ERRO] Movimento inválido para esta peça!\n");
            }
        }
        else if(dist == 2){
            if(validar_captura(player, lin_origem, col_origem, lin_destino, col_destino)){
                executar_captura(player, lin_origem, col_origem, lin_destino, col_destino);
                jogada_valida = true;
                printf("\nCaptura realizada com sucesso!\n");
            } else {
                printf("\n[ERRO] Captura inválida!\n");
            }
        }
        else {
            printf("\n[ERRO] Distância de movimento inválida! (Mova 1 casa ou pule 2 para comer).\n");
        }
    }

    // Alterna o turno do jogador ao concluir uma jogada válida
    player->turno = (player->turno == 1) ? 2 : 1;
}

//imprimi o tabuleiro perfeitamente durante a execução
void imprimir_tabuleiro(struct Tabuleiro *tab) {
    // Limpa a tela a cada turno (no Linux/Mint usa "clear")
    system("clear");

    printf("\n      === JOGO DE DAMAS ===\n\n");
    printf("    0   1   2   3   4   5   6   7   (Colunas)\n");
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int l = 0; l < 8; l++) {
        printf("%d |", l); // Número da linha no lado esquerdo
        
        for (int c = 0; c < 8; c++) {
            if (tab->campo[l][c].cor == 0) {
                if ((l + c) % 2 != 0) {
                    printf(" . |"); // Casa jogável vazia
                } else {
                    printf("   |"); // Casa inativa
                }
            } 
            else if (tab->campo[l][c].cor == 1) {
                if (tab->campo[l][c].e_dama) {
                    printf(" O |"); // Dama Jogador 1
                } else {
                    printf(" o |"); // Peça Jogador 1
                }
            } 
            else if (tab->campo[l][c].cor == 2) {
                if (tab->campo[l][c].e_dama) {
                    printf(" X |"); // Dama Jogador 2
                } else {
                    printf(" x |"); // Peça Jogador 2
                }
            }
        }
        //quebra de linha OBRIGATÓRIA ao terminar cada linha da matriz
        printf("\n  +---+---+---+---+---+---+---+---+\n");
    }
    printf("\n");
}

//checa a quantidade peças dos jogadores e define o vencedor
int checar_vencedor(struct Tabuleiro *tab){

    if(tab->pecas_jogador1 == 0) return 2;
    if(tab->pecas_jogador2 == 0) return 1;
    return 0; // Jogo continua
}