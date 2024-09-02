/*
O código abaixo apresenta a implementação de uma fila e suas operações básicas.

1 - comente o código
2 - implemente uma função para contar o número de elementos na fila.
3 - implemente uma função para limpar todos os elementos da fila, liberando memória apropriadamente.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node { // Declaração dos nós
    int data;
    struct Node* next;
} Node;

typedef struct Queue { // Declaração da fila
    Node* front;
    Node* rear;
    int tamanho;
} Queue;

Queue* createQueue() { // Cria a fila (inicializa)
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Falha na alocação de memória para a fila.\n");
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, int value) { // Enfileira um novo valor na fila
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Falha na alocação de memória para o novo nó.\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear == NULL) { 
        q->front = q->rear = newNode;
    } else { 
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->tamanho++;
}

int dequeue(Queue* q) { // Desenfileira um valor da fila
    if (q->front == NULL) { 
        printf("Fila está vazia.\n");
        return -1;
    }
    Node* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->tamanho--;
    return data;
}

int isEmpty(Queue* q) { // Confere se a fila está vazia
    return q->front == NULL;
}

void printQueue(Queue* q) { // Imprime todos os valores da fila
    if (isEmpty(q)) {
        printf("A fila está vazia.\n");
        return;
    }
    Node* temp = q->front;
    printf("Elementos da fila: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void numElementos(Queue* q) { // Imprime a quantidade de elementos da fila
    printf("A fila tem %d elementos.\n", q->tamanho);
}

void limparFila(Queue* q) { // Remove e libera a memória dos nós
    while (!isEmpty(q)) {
        dequeue(q); 
    }
    printf("Memória liberada com sucesso.\n");
}

int main() {
    Queue* q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    numElementos(q);
    printQueue(q);

    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    limparFila(q);

    return 0;
}
