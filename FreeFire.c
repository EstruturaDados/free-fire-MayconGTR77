#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

/*
 * Estrutura Item
 * Armazena os dados essenciais de cada item da mochila:
 * - nome: nome do item coletado
 * - tipo: categoria do item (arma, munição, cura, etc.)
 * - quantidade: quantidade do item disponível
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/*
 * Função: listarItens
 * Exibe todos os itens atualmente armazenados na mochila.
 */
void listarItens(Item mochila[], int qtd) {
    printf("\n=== Itens na Mochila ===\n");

    if (qtd == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

/*
 * Função: buscarItem
 * Realiza uma busca sequencial pelo nome de um item na mochila.
 * Se encontrar, mostra seus dados; se não, informa que não achou.
 */
int buscarItem(Item mochila[], int qtd, char nomeBuscado[]) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBuscado) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return i; // Retorna o índice do item encontrado
        }
    }

    printf("\nItem '%s' não encontrado na mochila.\n", nomeBuscado);
    return -1;
}

/*
 * Função: inserirItem
 * Adiciona um novo item à mochila (se houver espaço).
 */
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n=== Inserir Novo Item ===\n");

    printf("Nome do item: ");
    scanf("%s", mochila[*qtd].nome);

    printf("Tipo do item (arma, municao, cura, etc): ");
    scanf("%s", mochila[*qtd].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);

    (*qtd)++; // Aumenta a quantidade de itens na mochila

    printf("\nItem adicionado com sucesso!\n");
}

/*
 * Função: removerItem
 * Remove um item da mochila com base no nome informado.
 */
void removerItem(Item mochila[], int *qtd) {
    char nomeRemover[30];

    if (*qtd == 0) {
        printf("\nA mochila está vazia. Nada para remover.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja remover: ");
    scanf("%s", nomeRemover);

    int indice = buscarItem(mochila, *qtd, nomeRemover);

    if (indice != -1) {
        // Desloca os itens para a esquerda para preencher o espaço
        for (int i = indice; i < (*qtd) - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        (*qtd)--; // diminui a quantidade de itens
        printf("Item removido com sucesso!\n");
    }
}

/*
 * Função principal
 * Controla o menu e o fluxo da aplicação.
 */
int main() {
    Item mochila[MAX_ITENS];
    int qtdItens = 0;
    int opcao;

    do {
        printf("\n\n=== Sistema de Inventário – Mochila do Jogador ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item pelo nome\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtdItens);
                listarItens(mochila, qtdItens);
                break;

            case 2:
                removerItem(mochila, &qtdItens);
                listarItens(mochila, qtdItens);
                break;

            case 3:
                listarItens(mochila, qtdItens);
                break;

            case 4: {
                char busca[30];
                printf("Nome do item para buscar: ");
                scanf("%s", busca);
                buscarItem(mochila, qtdItens, busca);
                break;
            }

            case 5:
                printf("\nEncerrando sistema... Até a próxima!\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}