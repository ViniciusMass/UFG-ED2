/*
O código abaixo apresenta a implementação de uma lista linear.

Para esse exemplo, faça:
- Implemente funções adicionais como buscar(int elemento) para encontrar a posição de um elemento na lista.
ou 
- Adicione métodos para inverter a lista, encontrar o máximo/mínimo, ou ordenar a lista.
*/

#include <stdio.h>
#define MAX_SIZE 3

int lista[MAX_SIZE];
int tamanho = 0;

void inserir(int elemento) { // Insere um dado elemento na primeira posição disponível da lista
    if (tamanho < MAX_SIZE) {
        lista[tamanho++] = elemento;
    } else { // Caso 'tamanho' da lista seja maior que o MAX_SIZE definido acima (3), ela n insere o elemento.
        printf("Lista cheia!\n");
    }
}

void remover(int index) { // Remove um certo elemento localizado numa posição dada da lista
    if (index < 0 || index >= tamanho) {
        printf("Índice inválido!\n"); // Não aceita uma posição que não existe
    } else {
        for (int i = index; i < tamanho - 1; i++) {
            lista[i] = lista[i + 1]; // Passa todos os elementos à frente do índice removido uma posição para trás
        }
        tamanho--;
    }
}

void imprimir() { // Imprime todos os elementos da lista em ordem
    printf("Elementos da lista:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

void buscar(int elemento) { // Procura um dado elemento, imprimindo a posição que ele ocupa na lista
    int aux = 0;
    for (int i = 0; i < tamanho; i++) {
        if (elemento == lista[i]){
            printf("Posição %d.\n", i);
            aux++;
        }
    }
    if (aux == 0) {
        printf("Não existe esse elemento na lista.\n"); // Caso esse elemento não exista
    }
}

void inverter() { // Inverte a ordem da lista
    int i, temp;
    for (i = 0; i < tamanho/2; i++) { // Passa até a metade do vetor, invertindo sua ordem
        temp = lista[i]; // Guarda o valor na posição i na variável 'temp'
        lista[i] = lista[tamanho - 1 - i]; // Troca o valor na posição i com o valor na sua posição 'simétrica'
        lista[tamanho - 1 - i] = temp; // Troca o valor na posição 'simétrica' de i
    }
}

void encontrarMaximo() { // Encontra o maior valor entre todos os elementos e o imprime, junto à posição que ele ocupa na lista
    int temp = lista[0];
    for(int i = 1; i < tamanho; i++) {
        if(lista[i] >= temp) {
            temp = lista[i];
        }
    }
    printf("Valor máximo: %d na(s) posição(ões):\n", temp);
    buscar(temp);
}

void encontrarMinimo() { // Encontra o menor valor entre todos os elementos e o imprime, junto à posição que ele ocupa na lista
    int temp = lista[0];
    for(int i = 1; i < tamanho; i++) {
        if(lista[i] <= temp) {
            temp = lista[i];
        }
    }
    printf("Valor mínimo: %d na(s) posição(ões):\n", temp);
    buscar(temp);
}

void ordenar() { // Coloca a lista em ordem crescente de valores
    int i, j, temp;
    for (i = 0; i < tamanho-1; i++) {
        for (j = 0; j < tamanho-i-1; j++) {
            if (lista[j] > lista[j+1]) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

int main() {
    inserir(20);
    inserir(10);
    inserir(30);
    buscar(10);
    buscar(15);
    imprimir();
    encontrarMaximo();
    encontrarMinimo();
    inverter();
    imprimir();
    ordenar();
    imprimir();
    remover(1);
    imprimir();
    return 0;
}
