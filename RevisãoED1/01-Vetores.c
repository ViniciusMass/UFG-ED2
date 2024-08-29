/*
O código abaixo realiza a impressão do vetor na ordem inversa.
1 - comente o código
2 - faça uma modificação para que seja possível inserir um vetor de n elementos.
*/

#include <stdio.h>

int main() {
    int n, i, temp; // Definição das variáveis
    
    printf("Tamanho do vetor: "); 
    scanf("%d", &n); // Recebe o tamanho 'n' do vetor
    printf("\n");
    int vetor[n];
    
    for (i = 0; i < n; i++) { // Declara os valores do vetor, onde: vetor[n] = {0, 1, 2, 3 ... n}
        vetor[i] = i; 
    }
    
    for (i = 0; i < n/2; i++) { // Passa até a metade do vetor, invertindo sua ordem
        temp = vetor[i]; // Guarda o valor na posição i na variável 'temp'
        vetor[i] = vetor[n - 1 - i]; // Troca o valor na posição i com o valor na sua posição 'simétrica'
        vetor[n - 1 - i] = temp; // Troca o valor na posição 'simétrica' de i
    }

    printf("Vetor invertido:\n"); 
    for (i = 0; i < n; i++) { // Imprime o vetor novo, invertido, posição por posição
        printf("%d ", vetor[i]);
    }

    return 0;
}
