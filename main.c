#include <stdio.h>
#include <stdlib.h>
#include "estrutural.h"

int main(){
    
    struct Tabuleiro jogo;

    //Prepara o tabuleiro e define as 12 peças de cada jogador
    iniciar_jogo(&jogo);

    int vencedor = 0;

    while(vencedor == 0){
        //exibe o estado atual do tabuleiro no terminal
        imprimir_tabuleiro(&jogo);

        input(&jogo); //pede a jogada do jogador da vez

        vencedor = checar_vencedor(&jogo); // checa se o jogo acabou
    }

    //exibe o tabuleiro final e o ganhador do jogo
    imprimir_tabuleiro(&jogo);
    printf("\n=======================================\n");
    printf("   FIM DE JOGO! JOGADOR %d VENCEU   \n", vencedor);
    printf("\n=======================================\n");
    
    return 0;
}