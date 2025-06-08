#ifndef CARROS_H
#define CARROS_H

typedef struct {
    char marca[21];
    char modelo[31];
    int ano;
    int km;
    float preco;
} Carro;

typedef struct noCarro {
    Carro carro;
    struct noCarro* prox;
} NoCarro;

typedef struct noArvore {
    float chave;
    Carro* carro;
    struct noArvore* esq;
    struct noArvore* dir;
} NoArvore;

// Funções de lista
void inserir_lista(NoCarro** head, Carro carro);
void salvar_binario(const char* nome, NoCarro* head);
void liberar_lista(NoCarro* head);

// Funções de árvore
void inserir_arvore(NoArvore** raiz, float chave, Carro* carro);
void em_ordem_arvore(NoArvore* raiz);
void liberar_arvore(NoArvore* raiz);

#endif
