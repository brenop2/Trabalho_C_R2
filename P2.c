#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carros.h"

void exibir_todos(Carro* carros, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %s %d %d %.2f\n",
               carros[i].marca, carros[i].modelo,
               carros[i].ano, carros[i].km, carros[i].preco);
    }
}

void busca_substring(Carro* carros, int n, char* substr) {
    for (int i = 0; i < n; i++) {
        if (strstr(carros[i].modelo, substr)) {
            printf("%s %s %d %d %.2f\n",
                   carros[i].marca, carros[i].modelo,
                   carros[i].ano, carros[i].km, carros[i].preco);
        }
    }
}

void busca_km(NoArvore* arv, int min, int max) {
    if (!arv) return;
    if (arv->chave >= min) busca_km(arv->esq, min, max);
    if (arv->chave >= min && arv->chave <= max)
        printf("%s %s %d %d %.2f\n",
               arv->carro->marca, arv->carro->modelo,
               arv->carro->ano, arv->carro->km, arv->carro->preco);
    if (arv->chave <= max) busca_km(arv->dir, min, max);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <entrada.bin>\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "rb");
    if (!f) {
        printf("Erro ao abrir %s\n", argv[1]);
        return 1;
    }

    int n;
    fread(&n, sizeof(int), 1, f);
    Carro* carros = malloc(n * sizeof(Carro));
    fread(carros, sizeof(Carro), n, f);
    fclose(f);

    NoArvore* arv_km = NULL;
    NoArvore* arv_preco = NULL;

    for (int i = 0; i < n; i++) {
        inserir_arvore(&arv_km, carros[i].km, &carros[i]);
        inserir_arvore(&arv_preco, carros[i].preco, &carros[i]);
    }

    int op;
    do {
        printf("\n1 - Exibir todos\n2 - Buscar por substring\n3 - Buscar por kilometragem\n4 - Sair\n");
        scanf("%d", &op);
        if (op == 1) {
            exibir_todos(carros, n);
        } else if (op == 2) {
            char substr[31];
            printf("Substring: ");
            scanf("%s", substr);
            busca_substring(carros, n, substr);
        } else if (op == 3) {
            int min, max;
            printf("Min: ");
            scanf("%d", &min);
            printf("Max: ");
            scanf("%d", &max);
            busca_km(arv_km, min, max);
        }
    } while (op != 4);

    free(carros);
    liberar_arvore(arv_km);
    liberar_arvore(arv_preco);

    return 0;
}
