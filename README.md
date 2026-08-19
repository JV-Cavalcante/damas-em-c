# Jogo de Damas em C

Um projeto em C desenvolvido para praticar conceitos de **Estrutura de Dados** e **Lógica de Programação**, implementando a mecânica básica do jogo de Damas no terminal.

---

## Sobre o Projeto

Este projeto consiste em uma implementação modular em C de um jogo de damas jogável via linha de comando. O código está organizado com separação entre a interface/loop principal e a lógica estrutural das regras.

> ⚠️ **Status do Projeto:** 🛠️ *Em fase inicial de desenvolvimento.*

---

## Funcionalidades Atuais

- [x] Inicialização do tabuleiro com as peças em suas posições iniciais.
- [x] Impressão organizada do tabuleiro no terminal.
- [x] Leitura das jogadas dos jogadores.
- [x] Alternância de turnos entre os jogadores.
- [x] Verificação simples de fim de jogo.

---

## Próximas Atualizações (Roadmap)

O projeto para ficar 100% precisa dos seguintes pontos:

- [ ] **Captura Múltipla:** Permitir a captura de mais de uma peça na mesma jogada (combo de capturas).
- [ ] **Captura para Trás:** Implementar a mecânica de captura na direção oposta ao avanço normal.
- [ ] **Movimentação da Dama:** Permitir que a peça promovida a Dama corra por todas as casas da diagonal.
- [ ] **Validação Estrita:** Impor a obrigatoriedade de captura quando houver peça do oponente na mira.

---

## 📂 Estrutura do Código

├── main.c           # Loop principal do jogo e chamadas das rotinas
├── estrutural.c     # Implementação da lógica do jogo e manipulação do tabuleiro
├── estrutural.h     # Declaração das structs, constantes e protótipos de funções