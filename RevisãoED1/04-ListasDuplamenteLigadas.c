/*
O código apresenta uma lista duplamente ligada com operações básicas para inserir, deletar e imprimir.

1 - comente o código.
2 - Modifique a operação de inserção de dados, para que o usuário seja capaz de inserir valores para a lista.
3 - Faça uma operação de buscar por um valor específico, informado pelo usuário, onde o programa deve apresentar se o valor foi encontrado e, em caso afirmativo, exibir detalhes(vizinhos) do nó correspondente.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node { // Definição da lista
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* head = NULL;

void insertFront(int value) { // Insere um dado valor á lista
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL)
        head->prev = newNode;
    head = newNode;
}

void deleteNode(Node* node) { // Deleta um dado nó da lista
    if (node == head)
        head = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    free(node);
}

void printList() { // Imprime a lista inteira
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void buscarValor(int valor) { // Busca um dado valor
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == valor) {
            printf("Valor %d encontrado!\n", valor);
            printf("Detalhes do nó:\n");
            printf("Valor: %d\n", temp->data);
            if (temp->prev != NULL) { // Imprime o valor anterior, caso esse exista (se o valor buscado não for o primeiro nó da lista)
                printf("Anterior: %d\n", temp->prev->data);
            } else {
                printf("Este é o primeiro nó da lista.\n");
            }
            if (temp->next != NULL) { // Imprime o próximo valor, caso esse exista (se o valor buscado não for o último nó da lista)
                printf("Próximo: %d\n", temp->next->data);
            } else {
                printf("Este é o último nó da lista.\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("Valor %d não encontrado na lista.\n", valor); // Caso o valor buscado não existir na lista.
}

int main() {
    int valor, operacao;
    
    while (1) {
        printf("O que deseja fazer?\n0-Sair\n1-Inserir valor\n2-Buscar Valor\n3-Remover nó\n"); // "Menu" de opções para permitir a busca, inserção e remoção de valores
        scanf("%d", &operacao);
        switch(operacao){
            case 0:
                break;
            case 1:
                printf("Digite o valor que deseja inserir: ");
                scanf("%d", &valor);
                insertFront(valor);
                printf("Valor inserido!\n");
                break;
            case 2:
                printf("Digite o valor que deseja buscar: ");
                scanf("%d", &valor);
                buscarValor(valor);
                break;
            case 3:
                printf("Digite o valor que deseja deletar: ");
                scanf("%d", &valor);
                Node* temp = head;
                while (temp != NULL && temp->data != valor) {
                    temp = temp->next;
                }
                if (temp != NULL) {
                    deleteNode(temp);
                    printf("Valor removido!\n");
                } else {
                    printf("Valor nao encontrado!\n");
                }
                break;
            default:
                printf("Operação não reconhecida.\n");
        }
        if(operacao==0){
            break;
        }
    }
    
    printList();
    return 0;
}
