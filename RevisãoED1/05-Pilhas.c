/*
O código abaixo apresenta a implementação de uma pilha e suas operações básicas.

1 - comente o código
2 - implemente uma função para verificar se a pilha está vazia.
3 - proponha uma função que possa fazer expansão dinâmica quando a capacidade máxima é atingida, em vez de simplesmente negar novas inserções na pilha.
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

int *pilha;
int topo = -1;
int tamanho = SIZE;

void aumentar(){ // Aumenta o tamanho da pilha
    tamanho++; 
    pilha = (int*)realloc(pilha, tamanho * sizeof(int)); // Realoca o novo tamanho
    if (pilha == NULL) { // Se falhar, encerra o programa
        printf("Erro ao expandir a pilha.\n");
        exit(1);
    }
}

void push(int elemento) { // Adiciona um elemento ao topo da pilha
    if (topo >= SIZE - 1) {
        aumentar();
    }
    pilha[++topo] = elemento;
}

int pop() { // Retira o elemento do topo ta pilha
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } else {
        return pilha[topo--];
    }
}

int top() { // Indica qual o elemento localizado no topo da pilha.
    if (topo == -1) {
        printf("Pilha vazia!\n");
        return -1;
    } else {
        return pilha[topo];
    }
}

void imprimir() { // Imprime todos os valores da pilha, de cima pra baixo
    printf("Conteúdo da pilha:\n");
    for (int i = topo; i >= 0; i--) {
        printf("%d ", pilha[i]);
    }
    printf("\n");
}

void verificarVazia() { // Verifica se a pilha está ou não vazia
    if (topo == -1) {
        printf("Pilha vazia!\n");
    }
    else {
        printf("A pilha não está vazia!\n");
    }
}

int main() {
    pilha = (int*)malloc(SIZE * sizeof(int)); // Inicialização da pilha
    if (pilha == NULL) { // Encerra o programa se a alocação falhar
        printf("Erro ao inicializar pilha\n");
        return 1;
    }
    
    verificarVazia();
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    verificarVazia();
    imprimir();
    printf("Elemento no topo: %d\n", top());
    printf("Elemento removido: %d\n", pop());
    imprimir();
    return 0;
}
