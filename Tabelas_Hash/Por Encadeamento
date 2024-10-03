#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar uma paciente financeira
typedef struct Paciente {
    char nome[100];               // nome único da paciente
    int gravidade;          // gravidade da paciente
    float horaChegada;       // horaChegada da paciente
    int historico;      // historico: "normal" ou "suspeita"
    struct Paciente *proximo; // Ponteiro para a próxima paciente (lista ligada)
} Paciente;

// Estrutura da Tabela Hash
typedef struct {
    Paciente *tabela[TAMANHO_HASH];  // Array de ponteiros para o início da lista ligada
} TabelaHash;

// Função Hash: Retorna o índice baseado no nome do paciente
int funcao_hash (char *str) {
    int soma =0;
    for (int i=0; str[i] != '\0'; i++){
        soma += str[i];
    }
    
    return soma % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função para criar uma nova paciente
Paciente *criar_paciente(const char *nome, int gravidade, float horaChegada, int historico) {
    Paciente *novo_paciente = (Paciente *)malloc(sizeof(Paciente));
    if (novo_paciente == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novo_paciente->nome, nome);
    novo_paciente->gravidade = gravidade;
    novo_paciente->horaChegada = horaChegada;
    novo_paciente->historico = historico;
    novo_paciente->proximo = NULL;
    return novo_paciente;
}

// Função para inserir uma paciente na tabela hash (usando listas ligadas para colisões)
void inserir(TabelaHash *tabela, Paciente *paciente) {
    int indice = funcao_hash(paciente->nome);  // Calcula o índice baseado no ID
    paciente->proximo = tabela->tabela[indice];  // Insere no início da lista ligada
    tabela->tabela[indice] = paciente;
}

// Função para exibir todas as transações
void exibir_todas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Paciente *atual = tabela->tabela[i];
        while (atual != NULL) {
            printf("paciente nome: %s, gravidade: %d, horaChegada: %.2f, historico: %d (Índice: %d)\n",
                   atual->nome, atual->gravidade, atual->horaChegada, atual->historico, i);
            atual = atual->proximo;  // Avança para a próxima paciente
        }
    }
}

// Função para buscar uma paciente na tabela hash pelo nome
Paciente *buscar(TabelaHash *tabela, char *nome) {
    int indice = funcao_hash(nome);  // Calcula o índice para busca
    Paciente *atual = tabela->tabela[indice];
    while (atual != NULL) {
        if (strcpy(atual->nome, nome)) {
            return atual;  // Retorna a paciente se encontrada
        }
        atual = atual->proximo;  // Vai para a próxima paciente na lista ligada
    }
    return NULL;  // Retorna NULL se não for encontrada
}

// Função para excluir uma paciente na tabela hash pelo nome
void excluir(TabelaHash *tabela, char *nome) {
    int indice = funcao_hash(nome);  // Calcula o índice para exclusão
    Paciente *atual = tabela->tabela[indice];
    Paciente *anterior = NULL;

    while (atual != NULL) {
        if (strcpy(atual->nome, nome)) {
            printf("---\n");
            // Se o elemento a ser removido for o primeiro da lista
            if (anterior == NULL) {
                printf("--\n");
                tabela->tabela[indice] = atual->proximo;  // Remove o primeiro elemento
            } else {
                printf("-\n");
                anterior->proximo = atual->proximo;  // Remove o elemento no meio ou fim
            }
            free(atual);  // Libera a memória da paciente
            printf("paciente com nome %s foi excluída.\n", nome);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("paciente com nome %s não encontrada para exclusão.\n", nome);
}

// Função para contar o número total de elementos (transações) na tabela hash
int contar_elementos(TabelaHash *tabela) {
    int total = 0;

    // Percorre todas as posições da tabela hash
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Paciente *atual = tabela->tabela[i];

        // Percorre a lista ligada em cada posição
        while (atual != NULL) {
            total++;  // Incrementa o contador para cada paciente encontrada
            atual = atual->proximo;  // Vai para o próximo elemento na lista
        }
    }

    return total;
}


// Função para inserir 20 transações predefinidas na tabela hash
void inserir_dados_predefinidos(TabelaHash *tabela) {
    // Inserindo transações diretamente
    
    inserir(tabela, criar_paciente("Bruno", 3, 14.25, 2));
    inserir(tabela, criar_paciente("Carla", 1, 9.50, 4));
    inserir(tabela, criar_paciente("Diego", 5, 17.15, 1));
    inserir(tabela, criar_paciente("Amanda", 5, 21.10, 3));
    inserir(tabela, criar_paciente("Fernanda", 2, 12.40, 3));
    inserir(tabela, criar_paciente("Gabriel", 4, 19.35, 5));
    inserir(tabela, criar_paciente("Helena", 3, 8.10, 2));
    inserir(tabela, criar_paciente("Igor", 1, 16.55, 4));
    inserir(tabela, criar_paciente("Julia", 2, 13.20, 1));
    inserir(tabela, criar_paciente("Lucas", 5, 18.45, 3));
    inserir(tabela, criar_paciente("Mariana", 4, 10.30, 5));
    inserir(tabela, criar_paciente("Natália", 1, 7.05, 2));
    inserir(tabela, criar_paciente("Otávio", 3, 15.50, 4));
    inserir(tabela, criar_paciente("Paula", 2, 11.15, 1));
    inserir(tabela, criar_paciente("Rafael", 5, 20.25, 3));
    inserir(tabela, criar_paciente("Sabrina", 4, 6.40, 5));
    inserir(tabela, criar_paciente("Thiago", 2, 17.35, 2));
    inserir(tabela, criar_paciente("Vanessa", 1, 12.50, 4));
    inserir(tabela, criar_paciente("Wagner", 3, 9.20, 1));
    inserir(tabela, criar_paciente("Yasmin", 5, 19.10, 3));

    printf("Transações foram inseridas com sucesso.\n");
}


// Função principal para demonstrar o uso da tabela hash com transações financeiras
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Inserir os dados predefinidos na tabela hash
    inserir_dados_predefinidos(&tabela);
    
    // Exibir todas as transações inseridas
    printf("\nTodas as transações inseridas: %d\n", contar_elementos(&tabela));
    exibir_todas(&tabela);

    
    // Busca por uma paciente específica
    printf("\nBuscar uma paciente:\n");
    Paciente *t = buscar(&tabela, "Amanda");
    if (t != NULL) {
        printf("paciente encontrada: nome: %s, gravidade: %d, horaChegada: %.2f, historico: %d\n",
               t->nome, t->gravidade, t->horaChegada, t->historico);
    } else {
        printf("paciente não encontrada.\n");
    }
    
    
    // Excluir as transações selecionadas
    printf("\nTransações excluidas:\n");
    excluir(&tabela, "Amanda");
    
    
    // Exibir todas as transações inseridas
    printf("\nTransações Atualizadas: %d\n", contar_elementos(&tabela));
    exibir_todas(&tabela);
    

    return 0;
}
