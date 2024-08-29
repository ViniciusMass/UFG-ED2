/*
O código abaixo recebe do usuário elementos que são inseridos em uma matriz 3x3, em seguida, imprime a soma de sua diagonal principal.
- faça uma modificação para que seja possível dinamizar o tamanho da matriz (utilizar alocação dinâmica de memória usando malloc)
*/

#include <stdio.h>

int main() {
    int **matriz;
    int i, j, n, soma = 0;
    
    printf("Tamanho da matriz: "); 
    scanf("%d", &n); // Recebe o tamanho 'n' da matriz
    
    matriz = malloc (n * sizeof (int *)); // Faz a alocação dinamica da matriz, com tamanho 'n'
    for (int i = 0; i < n; ++i) {
        matriz[i] = malloc (n * sizeof (int)); // Seria possível definir a matriz com um número de colunas diferentes do numero de linhas, colocando 'm' nessa linha no lugar de 'n'
    }
        
    printf("Insira os elementos da matriz %dx%d:\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &matriz[i][j]); // Recebe cada elemento da matriz, passando linha por linha, da esquerda para a direita
            if (i == j) {
                soma += matriz[i][j]; // Quando o numero de linha é igual à coluna, ou seja, esta na diagonal principal, soma esse valor à variável 'soma'
            }
        }
    }

    printf("Soma dos elementos da diagonal principal: %d\n", soma); // Imprime a soma da diagonal principal
    return 0;
}
