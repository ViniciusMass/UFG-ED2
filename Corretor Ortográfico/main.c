#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 3 // Ordem da árvore B (número máximo de chaves por nó)

typedef struct BTreeNode {
    char *keys[MAX_KEYS];        // Chaves armazenadas (palavras)
    struct BTreeNode *children[MAX_KEYS + 1]; // Filhos do nó
    int numKeys;                 // Número atual de chaves no nó
    int isLeaf;                  // Indica se o nó é folha
} BTreeNode;

// Função para criar um novo nó
BTreeNode* createBTreeNode(int isLeaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->numKeys = 0;
    node->isLeaf = isLeaf;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        node->children[i] = NULL;
    }
    return node;
}


// Função para dividir um nó cheio
void splitChild(BTreeNode *parent, int i) {
    BTreeNode *fullChild = parent->children[i];
    BTreeNode *newChild = createBTreeNode(fullChild->isLeaf);

    newChild->numKeys = MAX_KEYS / 2;

    // Copia as últimas chaves para o novo nó
    for (int j = 0; j < MAX_KEYS / 2; j++) {
        newChild->keys[j] = fullChild->keys[j + MAX_KEYS / 2 + 1];
    }

    if (!fullChild->isLeaf) {
        // Copia os filhos também
        for (int j = 0; j <= MAX_KEYS / 2; j++) {
            newChild->children[j] = fullChild->children[j + MAX_KEYS / 2 + 1];
        }
    }

    fullChild->numKeys = MAX_KEYS / 2;

    // Move os filhos do pai para dar espaço
    for (int j = parent->numKeys; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newChild;

    // Move as chaves do pai para dar espaço
    for (int j = parent->numKeys - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = fullChild->keys[MAX_KEYS / 2];
    parent->numKeys++;
}


// Função auxiliar para buscar uma palavra em um nó
int searchInNode(BTreeNode *node, const char *key) {
    for (int i = 0; i < node->numKeys; i++) {
        if (strcmp(node->keys[i], key) == 0) {
            return 1; // Palavra encontrada
        }
    }
    return 0; // Palavra não encontrada
}

// Função para buscar uma palavra na Árvore B
int searchBTree(BTreeNode *root, const char *key) {
    if (!root) {
        return 0; // Árvore vazia
    }

    int i = 0;
    while (i < root->numKeys && strcmp(key, root->keys[i]) > 0) {
        i++;
    }

    if (i < root->numKeys && strcmp(key, root->keys[i]) == 0) {
        return 1; // Palavra encontrada no nó atual
    }

    if (root->isLeaf) {
        return 0; // Palavra não encontrada
    }

    return searchBTree(root->children[i], key); // Busca no filho correspondente
}

// Função para inserir uma palavra em um nó não cheio
void insertNonFull(BTreeNode *node, const char *key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        // Insere a palavra no local correto
        while (i >= 0 && strcmp(key, node->keys[i]) < 0) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = strdup(key);
        node->numKeys++;
    } else {
        // Encontra o filho onde a palavra deve ser inserida
        while (i >= 0 && strcmp(key, node->keys[i]) < 0) {
            i--;
        }
        i++;

        if (node->children[i]->numKeys == MAX_KEYS) {
            // Divide o filho se estiver cheio
            splitChild(node, i);
            if (strcmp(key, node->keys[i]) > 0) {
                i++;
            }
        }

        insertNonFull(node->children[i], key);
    }
}

// Função principal para inserir uma palavra na Árvore B
void insertBTree(BTreeNode **root, const char *key) {
    if (*root == NULL) {
        *root = createBTreeNode(1); // Cria a raiz se não existir
    }

    if ((*root)->numKeys == MAX_KEYS) {
        // Divide a raiz se estiver cheia
        BTreeNode *newRoot = createBTreeNode(0);
        newRoot->children[0] = *root;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
        *root = newRoot;
    } else {
        insertNonFull(*root, key);
    }
}

// Função para imprimir as palavras em ordem lexicográfica
void printBTree(BTreeNode *root) {
    if (!root) {
        return;
    }

    for (int i = 0; i < root->numKeys; i++) {
        if (!root->isLeaf) {
            printBTree(root->children[i]);
        }
        printf("%s\n", root->keys[i]);
    }

    if (!root->isLeaf) {
        printBTree(root->children[root->numKeys]);
    }
}

void carregarPalavras(BTreeNode **root, const char *arquivo){
    FILE *dicionario = fopen(arquivo, "r");
    
    if(!arquivo){
        printf("Erro ao abrir o arquivo: %s\n", arquivo);
        return;
    }

    char word[100];
    while(fscanf(dicionario, "%99s", word) == 1){
        insertBTree(root, word);
    }

    fclose(dicionario);
}

// Função auxiliar para verificar se uma palavra começa com um prefixo
int startsWith(const char *word, const char *prefix){
    return strncmp(word, prefix, strlen(prefix)) == 0;
}

// Função para coletar palavras com um determinado prefixo
void collectAllSuggestions(BTreeNode *node, const char *prefix, char ***suggestions, int *count){
    if(!node){
        return;
    }

    for(int i = 0; i < (node -> numKeys); i++){
        if(startsWith(node -> keys[i], prefix)){
            *suggestions = realloc(*suggestions, (*count + 1) * sizeof(char *));
            (*suggestions)[*count] = strdup(node -> keys[i]);
            (*count)++;
        }
        if(!node -> isLeaf){
            collectAllSuggestions(node -> children[i], prefix, suggestions, count);
        }
    }

    if(!node -> isLeaf){
        collectAllSuggestions(node -> children[node -> numKeys], prefix, suggestions, count);
    }
}

void suggestWords(BTreeNode *root, const char *prefix){
    char **suggestions = NULL;
    int count = 0;

    collectAllSuggestions(root, prefix, &suggestions, &count);

    if(count == 0){
        printf("\nNenhuma sugestão encontrada para o prefixo '%s'.\n", prefix);
    } else {
        printf("\nSugestões para o prefixo '%s':\n", prefix);
        for(int i = 0; i < count; i++){
            printf("%s\n", suggestions[i]);
            free(suggestions[i]);
        }
    }
    free(suggestions);
}

// Função principal para testar a Árvore B
int main() {
    BTreeNode *root = NULL;

    // Inserção de palavras
    carregarPalavras(&root, "dicionario.txt");
    int op;
    
    while(1){
        printf("\nEscolha uma opção:\n");
        printf("1. Inserir palavra\n");
        printf("2. Buscar palavra\n");
        printf("3. Sugerir palavras (autocompletar)\n");
        printf("4. Printar todas as palavras\n");
        printf("5. Sair\n");
        scanf("%d", &op);
        
        switch (op) {
            case 1: {
                char palavra[100];
                printf("Digite a palavra que deseja inserir: ");
                scanf("%s", palavra);
                
                insertBTree(&root, palavra);
                
                printf("Palavra '%s' inserida.\n", palavra);
                break;
            }

            case 2: {
                char palavra[100];
                printf("Digite a palavra que deseja buscar: ");
                scanf("%s", palavra);
                
                if(searchBTree(root, palavra)) {
                    printf("Palavra '%s' encontrada\n", palavra);
                } else {
                    printf("Palavra '%s' não encontrada.\n", palavra);
                }
                break;
            }

            case 3: {
                char prefixo[100];
                printf("Digite o prefixo para buscar sugestões: ");
                scanf("%s", prefixo);
                
                suggestWords(root, prefixo);
                break;
            }

            case 4:
                printf("\nPalavras na árvore:\n");
                printBTree(root);
                printf("\n");
                break;
                
            case 5:
                printf("Saindo do programa...\n");
                return 0;

            default:
                printf("Opção inválida! Escolha novamente.\n");
                break;
        }
    }

    return 0;
}
