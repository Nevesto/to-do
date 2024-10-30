#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *ant;
    struct node *prox;
} Node;

typedef struct list {
    Node *inicio;
    Node *fim;
    int tam;
} ListaCDE;

void create(ListaCDE *l) {
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
}

int insert(ListaCDE *l, int data) {
    Node *aux = (Node *) malloc(sizeof(Node));
    if(aux == NULL) return 0;

    aux->data = data;
    l->tam++;

    if(l->inicio == NULL) {
        l->inicio = aux;
        l->fim = aux;
        aux->prox = l->inicio;
        aux->ant = l->fim;

        return 1;
    }

    aux->prox = l->inicio;
    aux->ant = l->fim;
    l->fim->prox = aux;
    l->fim = aux;
    l->inicio->ant = l->fim;

    return 1;
}

int removal(ListaCDE *l, int data) {
    Node *aux;

    if(l->inicio == NULL) {
        printf("Lista vazia\n");
        return 0;
    }

    if((data == l->inicio->data) && (l->inicio == l->fim)) {
        aux = l->inicio;
        l->inicio = NULL;
        l->fim = NULL;
        free(aux);
        l->tam--;

        return 1;
    }

    if(data == l->inicio->data) {
        aux = l->inicio;
        l->inicio = aux->prox;
        l->inicio->ant = l->fim;
        l->fim->prox = l->inicio;
        free(aux);
        l->tam--;

        return 1;
    }

    if(data == l->fim->data) {
        aux = l->fim;
        l->fim = aux->ant;
        l->fim->prox = l->inicio;
        l->inicio->ant = l->fim;
        free(aux);
        l->tam--;

        return 1;
    }

    aux = l->inicio->prox;

    while((data != aux->data) && (aux != l->fim)) {
        aux = aux->prox;
    }

    if(aux == l->fim) {
        printf("Elemento %d nao encontrado\n", data);
        return 0;
    }

    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
    free(aux);
    l->tam--;

    return 1;
}

int isEmpty(ListaCDE l) {
    if(l.inicio == NULL) return 1;
    return 0;
}

int getFirst(ListaCDE l) {
    return l.inicio->data;
}

int getLast(ListaCDE l) {
    return l.fim->data;
}

int getSize(ListaCDE l) {
    return l.tam;
}

void show(ListaCDE l, int sense) {
    Node *aux;

    if(l.inicio == NULL) {
        printf("Lista vazia\n");
        return;
    } else {
        if(sense == 1) {
            aux = l.inicio;
            do{
                printf("Dado: %d\n", aux->data);
                aux = aux->prox;
            } while(aux != l.inicio);
        } else {
            aux = l.fim;
            do {
                printf("Data: %d\n", aux->data);
                aux = aux->ant;
            } while(aux != l.fim);
        }
    }
}

int main() {
    ListaCDE l;
    int data, sucess, option;

    create(&l);

    sucess = insert(&l, 400);
    sucess = insert(&l, 240);
    sucess = insert(&l, 320);
    sucess = insert(&l, 500);
    sucess = insert(&l, 600);

    if(!isEmpty(l)) {
        printf("Deseja ver os dados a partir de onde?\n");
        printf("1 - Inicio\n");
        printf("2 - Fim\n");
        printf("-> ");
        scanf("%d", &option);

        show(l, option);
    }

    option = 1;
    while(option == 1) {
        printf("Selecione o dado que deseja remover: ");
        scanf("%d", &data);

        sucess = removal(&l, data);
        if(!sucess) {
            printf("Erro ao remover o dado: %d\n", data);
        }
        
        show(l, 1);

        printf("Deseja remover outro dado?\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n");
        printf("-> ");
        scanf("%d", &option);
    }

    while(!isEmpty(l)) {
        sucess = removal(&l, getFirst(l));
    }
}