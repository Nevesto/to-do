#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int id;
    char desc[100];
    int priority;
    char date[11];
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

int insert(ListaCDE *l, int id) {
    Node *aux = (Node *) malloc(sizeof(Node));
    if(aux == NULL) return 0;

    aux->id = id;
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

int removal(ListaCDE *l, int id) {
    Node *aux;

    if(l->inicio == NULL) {
        printf("Lista vazia\n");
        return 0;
    }

    if((id == l->inicio->id) && (l->inicio == l->fim)) {
        aux = l->inicio;
        l->inicio = NULL;
        l->fim = NULL;
        free(aux);
        l->tam--;

        return 1;
    }

    if(id == l->inicio->id) {
        aux = l->inicio;
        l->inicio = aux->prox;
        l->inicio->ant = l->fim;
        l->fim->prox = l->inicio;
        free(aux);
        l->tam--;

        return 1;
    }

    if(id == l->fim->id) {
        aux = l->fim;
        l->fim = aux->ant;
        l->fim->prox = l->inicio;
        l->inicio->ant = l->fim;
        free(aux);
        l->tam--;

        return 1;
    }

    aux = l->inicio->prox;

    while((id != aux->id) && (aux != l->fim)) {
        aux = aux->prox;
    }

    if(aux == l->fim) {
        printf("Elemento %d nao encontrado\n", id);
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
    return l.inicio->id;
}

int getLast(ListaCDE l) {
    return l.fim->id;
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
                printf("Dado: %d\n", aux->id);
                aux = aux->prox;
            } while(aux != l.inicio);
        } else {
            aux = l.fim;
            do {
                printf("Data: %d\n", aux->id);
                aux = aux->ant;
            } while(aux != l.fim);
        }
    }
}

int main() {
    ListaCDE l;
    int data, sucess, option;

    create(&l);

    sucess = insert(&l, 1);
    sucess = insert(&l, 2);
    sucess = insert(&l, 3);
    sucess = insert(&l, 4);
    sucess = insert(&l, 5);

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