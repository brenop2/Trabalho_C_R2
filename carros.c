#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carros.h"

void inserir_lista(NoCarro** head, Carro carro) {
    NoCarro* novo = malloc(sizeof(NoCarro));
    novo->carro = carro;
    novo->prox = NULL;

    if (!*head) {
        *head = novo;
    } else {
        NoCarro* temp = *head;
        while (temp->prox) temp = temp->prox;
        temp->prox = novo;
    }
}

void salvar_binario(const char* nome, NoCarro* head) {
    FILE* f = fopen(nome, "wb");
    if (!f) return;

    int count = 0;
    NoCarro* temp = head;
    while (temp) {
        count++;
        temp = temp->prox;
    }

    fwrite(&count, sizeof(int), 1, f);
    temp = head;
    while (temp) {
        fwrite(&(temp->carro), sizeof(Carro), 1, f);
        temp = temp->prox;
    }
    fclose(f);
}

void liberar_lista(NoCarro* head) {
    NoCarro* temp;
    while (head) {
        temp = head;
        head = head->prox;
        free(temp);
    }
}

void inserir_arvore(NoArvore** raiz, float chave, Carro* carro) {
    if (!*raiz) {
        *raiz = malloc(sizeof(NoArvore));
        (*raiz)->chave = chave;
        (*raiz)->carro = carro;
        (*raiz)->esq = (*raiz)->dir = NULL;
    } else if (chave < (*raiz)->chave) {
        inserir_arvore(&((*raiz)->esq), chave, carro);
    } else {
        inserir_arvore(&((*raiz)->dir), chave, carro);
    }
}

void em_ordem_arvore(NoArvore* raiz) {
    if (raiz) {
        em_ordem_arvore(raiz->esq);
        printf("%s %s %d %d %.2f\n", raiz->carro->marca, raiz->carro->modelo,
               raiz->carro->ano, raiz->carro->km, raiz->carro->preco);
        em_ordem_arvore(raiz->dir);
    }
}

void liberar_arvore(NoArvore* raiz) {
    if (raiz) {
        liberar_arvore(raiz->esq);
        liberar_arvore(raiz->dir);
        free(raiz);
    }
}
