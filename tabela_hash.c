//Christian Kennedy Daniel Martins GRR20221099

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABELA 100
#define NOME 50
#define TELEFONE 15

typedef struct {
    char nome[NOME];
    char telefone[TELEFONE];
    int ocupado; 
} Contato;

Contato tabelaHash[TABELA];

unsigned int funcaoHash(const char *key, int tentativa) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash += key[i];
    }
    return (hash + tentativa * tentativa) % TABELA;
}

void inicializaTabela() {
    for (int i = 0; i < TABELA; i++) {
        tabelaHash[i].ocupado = 0;
    }
}

int adicionarContato(const char *nome, const char *telefone) {
    for (int tentativa = 0; tentativa < TABELA; tentativa++) {
        int index = funcaoHash(nome, tentativa);
        if (tabelaHash[index].ocupado == 0 || tabelaHash[index].ocupado == -1) {
            strncpy(tabelaHash[index].nome, nome, NOME - 1);
            strncpy(tabelaHash[index].telefone, telefone, TELEFONE - 1);
            tabelaHash[index].ocupado = 1;
            return 1;
        }
    }
    return 0;
}

int buscaContato(const char *nome, char *telefone) {
    for (int tentativa = 0; tentativa < TABELA; tentativa++) {
        int index = funcaoHash(nome, tentativa);
        if (tabelaHash[index].ocupado == 1 && strcmp(tabelaHash[index].nome, nome) == 0) {
            strncpy(telefone, tabelaHash[index].telefone, TELEFONE);
            return 1;
        }
        if (tabelaHash[index].ocupado == 0) break;
    }
    return 0;
}

int removeContato(const char *nome) {
    for (int tentativa = 0; tentativa < TABELA; tentativa++) {
        int index = funcaoHash(nome, tentativa);
        if (tabelaHash[index].ocupado == 1 && strcmp(tabelaHash[index].nome, nome) == 0) {
            tabelaHash[index].ocupado = -1; 
            return 1;
        }
        if (tabelaHash[index].ocupado == 0) break; 
    }
    return 0; 
}

void mostraContatos() {
    printf("\nContatos:\n");
    for (int i = 0; i < TABELA; i++) {
        if (tabelaHash[i].ocupado == 1) {
            printf("Nome: %s, Telefone: %s\n", tabelaHash[i].nome, tabelaHash[i].telefone);
        }
    }
}

double tempo(void (*func)(void)) {
    clock_t start = clock();
    func();
    return (double)(clock() - start) / CLOCKS_PER_SEC * 1000.0;
}

int main() {
    inicializaTabela();
    char nome[NOME];
    char telefone[TELEFONE];
    int option;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Nome: ");
                scanf("%s", nome);
                printf("Telefone: ");
                scanf("%s", telefone);
                if (adicionarContato(nome, telefone)) {
                    printf("Contato adicionado com sucesso.\n");
                } else {
                    printf("Erro: A tabela esta cheia.\n");
                }
                break;

            case 2:
                printf("Nome: ");
                scanf("%s", nome);
                clock_t start = clock();
                if(buscaContato(nome, telefone)) {
                    double search_time = (double)(clock() - start) / CLOCKS_PER_SEC * 1000.0;
                    printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", nome, telefone, search_time);
                } else {
                    printf("Erro: Contato nao encontrado.\n");
                }
                break;

            case 3:
                printf("Nome: ");
                scanf("%s", nome);
                if (removeContato(nome)) {
                    printf("Contato removido com sucesso.\n");
                } else {
                    printf("Erro: Contato nao encontrado.\n");
                }
                break;

            case 4:
                mostraContatos();
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (option != 0);

    return 0;
}
