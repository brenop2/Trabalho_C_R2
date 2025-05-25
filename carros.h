#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carros.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <entrada.csv> <saida.bin>\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        printf("Erro ao abrir %s\n", argv[1]);
        return 1;
    }

    NoCarro* lista = NULL;
    Carro carro;
    while (fscanf(f, "%20[^,],%30[^,],%d,%d,%f\n",
                  carro.marca, carro.modelo, &carro.ano, &carro.km, &carro.preco) == 5) {
        inserir_lista(&lista, carro);
                  }
    fclose(f);

    salvar_binario(argv[2], lista);
    liberar_lista(lista);

    printf("Arquivo binário salvo com sucesso.\n");

    return 0;
}
