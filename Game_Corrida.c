#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define NUM_CAVALOS 5
#define TAM_PISTA 50

char nomes[NUM_CAVALOS][20] = {"Relampago", "Trovão", "Vento", "Tempestade", "Fumaça"};
int tempos[NUM_CAVALOS];
int posicoes[NUM_CAVALOS];

void limpar_tela() {
    printf("\033[H\033[J");
}

void preparar_corrida() {
    srand(time(NULL));
    for (int i = 0; i < NUM_CAVALOS; i++) {
        tempos[i] = 5 + rand() % 10;
        posicoes[i] = 0;
    }
}

void mostrar_pista() {
    for (int i = 0; i < NUM_CAVALOS; i++) {
        printf("%-12s |", nomes[i]);
        for (int j = 0; j < TAM_PISTA; j++) {
            if (j == posicoes[i]) printf(">");
            else printf("-");
        }
        printf("| Tempo total: %d\n", tempos[i]);
    }
}

void corrida_fifo() {
    printf("\nModo FIFO - Um por vez na pista\n");
    for (int i = 0; i < NUM_CAVALOS; i++) {
        while (posicoes[i] < TAM_PISTA - 1) {
            posicoes[i]++;
            limpar_tela();
            mostrar_pista();
            usleep(100000);
        }
        printf("\n%s cruzou a linha de chegada!\n", nomes[i]);
        sleep(1);
    }
}

void corrida_sjf() {
    printf("\nModo SJF - Começam os mais rápidos\n");

    for (int i = 0; i < NUM_CAVALOS - 1; i++) {
        for (int j = i + 1; j < NUM_CAVALOS; j++) {
            if (tempos[j] < tempos[i]) {
                int temp = tempos[i];
                tempos[i] = tempos[j];
                tempos[j] = temp;

                char nomeTemp[20];
                strcpy(nomeTemp, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], nomeTemp);
            }
        }
    }

    for (int i = 0; i < NUM_CAVALOS; i++) {
        while (posicoes[i] < TAM_PISTA - 1) {
            posicoes[i]++;
            limpar_tela();
            mostrar_pista();
            usleep(100000);
        }
        printf("\n%s chegou ao final!\n", nomes[i]);
        sleep(1);
    }
}

void mostrar_vencedor() {
    int menor = tempos[0];
    int vencedor = 0;
    for (int i = 1; i < NUM_CAVALOS; i++) {
        if (tempos[i] < menor) {
            menor = tempos[i];
            vencedor = i;
        }
    }
    printf("\nO vencedor é: %s com tempo total %d!\n", nomes[vencedor], tempos[vencedor]);
}

int main() {
    int escolha;

    printf("Corrida de Cavalos\n");
    printf("Escolha o modo da corrida:\n");
    printf("1 - FIFO (Um por um)\n");
    printf("2 - SJF (Mais rápidos vão primeiro)\n");
    printf("Opção: ");
    scanf("%d", &escolha);

    preparar_corrida();

    if (escolha == 1) corrida_fifo();
    else if (escolha == 2) corrida_sjf();
    else {
        printf("Escolha inválida.\n");
        return 1;
    }

    mostrar_vencedor();
    return 0;
}
