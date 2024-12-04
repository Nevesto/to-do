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

    if(l->start == NULL) {
        aux->prox = aux;
        aux->ant = aux;
        l->start = aux;
        l->end = aux;
        l->tam++;
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

            l->tam++;
            return 1;
        }

        current = current->prox;
    } while(current != l->start);

    aux->prox = l->start;
    aux->ant = l->end;
    l->end->prox = aux;
    l->start->ant = aux;
    l->end = aux;

    l->tam++;
    return 1;
}

int removal(ListaCDE *l, int id) {
    Node *aux;

    if(l->start == NULL) {
        printf("Lista vazia\n");
        return 0;
    }

    aux = l->start;
    do {
        if(aux->id == id) {
            if(aux == l->start && aux == l->end) {
                l->start = NULL;
                l->end = NULL;
            } else {
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
                if(aux == l->start) l->start = aux->prox;
                if(aux == l->end) l->end = aux->ant;
            }
            free(aux);
            l->tam--;
            return 1;
        }
        aux = aux->prox;
    } while(aux != l->start);

    printf("Elemento %d nao encontrado\n", id);
    return 0;
}

int isEmpty(ListaCDE l) {
    return l.start == NULL;
}

void show(ListaCDE l) {
    Node *aux;

    if(l.start == NULL) {
        printf("Lista vazia\n");
        return;
    } else {
        aux = l.start;
        do{
            printf("ID: %d\n", aux->id);
            printf("Prioridade: %d\n", aux->priority);
            printf("Descricao: %s\n", aux->desc);
            printf("Data de entrega: %s\n\n", aux->date);
            aux = aux->prox;
        } while(aux != l.start);
    }
}

void saveToFile(ListaCDE l) {
    FILE *file = fopen("todo.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo todo.txt para escrita.\n");
        return;
    }

    if (l.start == NULL) {
        fprintf(file, "");
    } else {
        Node *aux = l.start;
        do {
            fprintf(file, "%d;%d;%s;%s\n", aux->id, aux->priority, aux->desc, aux->date);
            aux = aux->prox;
        } while (aux != l.start);
    }
    fclose(file);
}

void loadFromFile(ListaCDE *l) {
    FILE *file = fopen("todo.txt", "r");
    if (file == NULL) {
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int id, priority;
        char desc[100], date[11];

        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ";");
        if (token != NULL) id = atoi(token);

        token = strtok(NULL, ";");
        if (token != NULL) priority = atoi(token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(desc, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(date, token);

        insert(l, id, desc, priority, date);
    }
    fclose(file);
}

int main() {
    ListaCDE l;
    int id, priority, success, option;
    char desc[100], date[11];

    create(&l);

    loadFromFile(&l);

    if(!isEmpty(l)) {
        printf("Tarefas existentes:\n");
        show(l);
    } else {
        printf("Nenhuma tarefa existente.\n");
    }

    do {
        printf("\nSelecione uma opcao:\n");
        printf("1 - Adicionar tarefa\n");
        printf("2 - Remover tarefa\n");
        printf("3 - Mostrar tarefas\n");
        printf("0 - Sair\n");
        printf("-> ");
        scanf("%d", &option);
        getchar();

        switch(option) {
            case 1:
                printf("Digite o ID da tarefa: ");
                scanf("%d", &id);
                getchar();

                printf("Digite a prioridade da tarefa (1: Alta, 2: Media, 3: Baixa): ");
                scanf("%d", &priority);
                getchar();

                printf("Digite a descricao da tarefa: ");
                fgets(desc, sizeof(desc), stdin);
                desc[strcspn(desc, "\n")] = '\0';

                printf("Digite a data de entrega da tarefa (dd/mm/aaaa): ");
                fgets(date, sizeof(date), stdin);
                date[strcspn(date, "\n")] = '\0';

                success = insert(&l, id, desc, priority, date);

                if(!success) {
                    printf("Erro ao adicionar a tarefa: %d\n", id);
                } else {
                    saveToFile(l);
                    printf("Tarefa adicionada com sucesso.\n");
                }
                break;

            case 2:
                if(isEmpty(l)) {
                    printf("Nenhuma tarefa para remover.\n");
                    break;
                }
                printf("Digite o ID da tarefa que deseja remover: ");
                scanf("%d", &id);

                success = removal(&l, id);
                if(!success) {
                    printf("Erro ao remover a tarefa: %d\n", id);
                } else {
                    saveToFile(l);
                    printf("Tarefa removida com sucesso.\n");
                }
                break;

            case 3:
                if(isEmpty(l)) {
                    printf("Nenhuma tarefa para mostrar.\n");
                } else {
                    show(l);
                }
                break;

            case 0:
                saveToFile(l);
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while(option != 0);

    while(!isEmpty(l)) {
        removal(&l, l.start->id);
    }

    return 0;
}