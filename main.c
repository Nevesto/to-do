#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int id;
    char desc[100];
    int priority; // 1 for high, 2 for medium, 3 for low
    char date[11]; // dd/mm/yyyy
    struct node *ant;
    struct node *prox;
} Node;

typedef struct list {
    Node *start;
    Node *end;
    int tam;
} ListaCDE;

void create(ListaCDE *l) {
    l->start = NULL;
    l->end = NULL;
    l->tam = 0;
}

int insert(ListaCDE *l, int id, char *desc, int priority, char *date) {
    Node *aux = (Node *) malloc(sizeof(Node));
    if(aux == NULL) return 0;

    aux->id = id;
    aux->priority = priority;
    strcpy(aux->desc, desc);
    strcpy(aux->date, date);

    l->tam++;

    if(l->start == NULL) {
        l->start = aux;
        l->end = aux;
        aux->prox = l->start;
        aux->ant = l->end;

        return 1;
    }

    Node *current = l->start;
    do {
        if(current->priority > aux->priority) {
            aux->prox = current;
            aux->ant = current->ant;
            current->ant->prox = aux;
            current->ant = aux;

            if(current == l->start) l->start = aux;

            return 1;
        }

        current = current->prox;
    } while(current != l->start);

    aux->prox = l->start;
    aux->ant = l->end;
    l->end->prox = aux;
    l->end = aux;
    l->start->ant = l->end;

    return 1;
}

int removal(ListaCDE *l, int id) {
    Node *aux;

    if(l->start == NULL) {
        printf("Lista vazia\n");
        return 0;
    }

    if((id == l->start->id) && (l->start == l->end)) {
        aux = l->start;
        l->start = NULL;
        l->end = NULL;
        free(aux);
        l->tam--;

        return 1;
    }

    if(id == l->start->id) {
        aux = l->start;
        l->start = aux->prox;
        l->start->ant = l->end;
        l->end->prox = l->start;
        free(aux);
        l->tam--;

        return 1;
    }

    if(id == l->end->id) {
        aux = l->end;
        l->end = aux->ant;
        l->end->prox = l->start;
        l->start->ant = l->end;
        free(aux);
        l->tam--;

        return 1;
    }

    aux = l->start->prox;

    while((id != aux->id) && (aux != l->end)) {
        aux = aux->prox;
    }

    if(aux == l->end) {
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
    if(l.start == NULL) return 1;
    return 0;
}

int getFirst(ListaCDE l) {
    return l.start->id;
}

int getLast(ListaCDE l) {
    return l.end->id;
}

int getSize(ListaCDE l) {
    return l.tam;
}

void show(ListaCDE l, int sense) {
    Node *aux;

    if(l.start == NULL) {
        printf("Lista vazia\n");
        return;
    } else {
        if(sense == 1) {
            aux = l.start;
            do{
                printf("Mostrando a lista: \n");
                printf("ID: %d\n", aux->id);
                printf("Prioridade: %d\n", aux->priority);
                printf("Descricao: %s\n", aux->desc);
                printf("Data de entrega: %s\n", aux->date);
                aux = aux->prox;
            } while(aux != l.start);
        } else {
            aux = l.end;
            do {
                printf("Mostrando a lista: \n");
                printf("ID: %d\n", aux->id);
                printf("Prioridade: %d\n", aux->priority);
                printf("Descricao: %s\n", aux->desc);
                printf("Data de entrega: %s\n", aux->date);
                aux = aux->ant;
            } while(aux != l.end);
        }
    }
}

int main() {
    ListaCDE l;
    int data, sucess, option;

    create(&l);

    sucess = insert(&l, 1, "Teste 1", 1, "01/01/2021");
    sucess = insert(&l, 2, "Teste 2", 1, "01/01/2021");
    sucess = insert(&l, 3, "Teste 3", 1, "01/01/2021");
    sucess = insert(&l, 4, "Teste 4", 1, "01/01/2021");

    if(!isEmpty(l)) {
        printf("Deseja ver os dados a partir de onde?\n");
        printf("1 - start\n");
        printf("2 - end\n");
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