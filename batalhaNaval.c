#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5

// ---------------------------------------------------
// Inicializa todo o tabuleiro com água (🌊 = 0)
// ---------------------------------------------------
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// ---------------------------------------------------
// Mostra o tabuleiro de forma amigável
// ~ = água, # = navio, * = habilidade
// (aqui troquei pra emojis pra ficar ainda mais visual)
// ---------------------------------------------------
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== BATALHA NAVAL ===\n\n");

    // Cabeçalho das colunas (1 a 10)
    printf("    ");
    for (int j = 1; j <= TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    // Cada linha com letra A–J
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c | ", 'A' + i); // letra da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf("🌊 ");
            else if (tabuleiro[i][j] == 3) printf("🚢 ");
            else if (tabuleiro[i][j] == 5) printf("🔥 ");
        }
        printf("\n");
    }
    printf("\n");
}

// ---------------------------------------------------
// Criação da área em formato de CONE
// ---------------------------------------------------
void criarCone(int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= TAMANHO_HABILIDADE/2 - i && j <= TAMANHO_HABILIDADE/2 + i) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// ---------------------------------------------------
// Criação da área em formato de CRUZ
// ---------------------------------------------------
void criarCruz(int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE/2 || j == TAMANHO_HABILIDADE/2) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// ---------------------------------------------------
// Criação da área em formato de OCTAEDRO (losango)
// ---------------------------------------------------
void criarOctaedro(int octa[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - TAMANHO_HABILIDADE/2) + abs(j - TAMANHO_HABILIDADE/2) <= TAMANHO_HABILIDADE/2) {
                octa[i][j] = 1;
            } else {
                octa[i][j] = 0;
            }
        }
    }
}

// ---------------------------------------------------
// Aplica uma habilidade no tabuleiro a partir de uma
// origem (linha, coluna)
// ---------------------------------------------------
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                       int linhaOrigem, int colunaOrigem) {
    int deslocamento = TAMANHO_HABILIDADE/2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linha = linhaOrigem + (i - deslocamento);
                int coluna = colunaOrigem + (j - deslocamento);

                // Só aplica se estiver dentro dos limites
                if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha][coluna] == 0) {
                        tabuleiro[linha][coluna] = 5; // marca como área afetada
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Colocando dois navios só de exemplo
    for (int k = 0; k < 3; k++) {
        tabuleiro[2][4 + k] = 3; // navio horizontal em C5–C7
        tabuleiro[6 + k][1] = 3; // navio vertical em G2–I2
    }

    // Criar as habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Jogar as habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 1, 5);     // cone centrado em B6
    aplicarHabilidade(tabuleiro, cruz, 5, 5);     // cruz centrada em F6
    aplicarHabilidade(tabuleiro, octaedro, 8, 8); // octaedro centrado em I9

    // Mostrar tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
