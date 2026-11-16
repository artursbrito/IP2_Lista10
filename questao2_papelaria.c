/*
 * Lista 10 - Structs - Questao 2
 * Cadastro de produtos da Papelaria Escolar
 * Vetor de 40 registros (structs)
 */
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 40
#define TAM_DESC 50

/* ---------- Estruturas ---------- */
typedef struct {
    int codigo;
    char descricao[TAM_DESC];
    float valor;
    int estoque;
} Produto;

/* ---------- Funcoes auxiliares ---------- */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerTexto(char *destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}

/* Retorna a posicao do produto no vetor ou -1 se nao existir */
int buscarProduto(Produto cadastro[], int qtd, int codigo) {
    int i;
    for (i = 0; i < qtd; i++) {
        if (cadastro[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* ---------- (a) Cadastrar novo produto ---------- */
void cadastrarProduto(Produto cadastro[], int *qtd) {
    Produto novo;

    if (*qtd >= MAX_PRODUTOS) {
        printf("Cadastro cheio! (maximo de %d produtos)\n", MAX_PRODUTOS);
        return;
    }

    printf("Codigo: ");
    scanf("%d", &novo.codigo);
    limparBuffer();

    if (buscarProduto(cadastro, *qtd, novo.codigo) != -1) {
        printf("Ja existe um produto com esse codigo!\n");
        return;
    }

    printf("Descricao: ");
    lerTexto(novo.descricao, TAM_DESC);
    printf("Valor unitario: ");
    scanf("%f", &novo.valor);
    printf("Quantidade em estoque: ");
    scanf("%d", &novo.estoque);
    limparBuffer();

    cadastro[*qtd] = novo;
    (*qtd)++;
    printf("Produto cadastrado com sucesso!\n");
}

/* ---------- (b) Alterar valor unitario ---------- */
void alterarValor(Produto cadastro[], int qtd, int codigo) {
    int pos = buscarProduto(cadastro, qtd, codigo);

    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    printf("Valor atual: R$ %.2f\n", cadastro[pos].valor);
    printf("Novo valor: ");
    scanf("%f", &cadastro[pos].valor);
    limparBuffer();
    printf("Valor alterado com sucesso!\n");
}

/* ---------- (c) Informar valor unitario ---------- */
/* Retorna o valor ou -1 se o produto nao existir */
float consultarValor(Produto cadastro[], int qtd, int codigo) {
    int pos = buscarProduto(cadastro, qtd, codigo);

    if (pos == -1) {
        return -1;
    }
    return cadastro[pos].valor;
}

/* ---------- (d) Informar quantidade em estoque ---------- */
/* Retorna a quantidade ou -1 se o produto nao existir */
int consultarEstoque(Produto cadastro[], int qtd, int codigo) {
    int pos = buscarProduto(cadastro, qtd, codigo);

    if (pos == -1) {
        return -1;
    }
    return cadastro[pos].estoque;
}

/* ---------- (e) Venda ---------- */
void venderProduto(Produto cadastro[], int qtd, int codigo, int quantidade) {
    int pos = buscarProduto(cadastro, qtd, codigo);
    char resp;

    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    if (cadastro[pos].estoque == 0) {
        printf("Produto sem estoque!\n");
        return;
    }

    if (quantidade <= cadastro[pos].estoque) {
        /* Tem estoque suficiente: venda normal */
        cadastro[pos].estoque -= quantidade;
        printf("Venda realizada! Valor a pagar: R$ %.2f\n",
               quantidade * cadastro[pos].valor);
    } else {
        /* Quantidade desejada maior que o estoque */
        printf("Estoque insuficiente! Existem apenas %d unidade(s).\n",
               cadastro[pos].estoque);
        printf("Deseja comprar todas as unidades disponiveis? (s/n): ");
        scanf(" %c", &resp);
        limparBuffer();

        if (resp == 's' || resp == 'S') {
            printf("Compra efetivada! Valor a pagar: R$ %.2f\n",
                   cadastro[pos].estoque * cadastro[pos].valor);
            cadastro[pos].estoque = 0;
        } else {
            printf("Compra cancelada.\n");
        }
    }
}

/* ---------- (f) Atualizar quantidade em estoque ---------- */
void atualizarEstoque(Produto cadastro[], int qtd, int codigo) {
    int pos = buscarProduto(cadastro, qtd, codigo);

    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    printf("Estoque atual: %d\n", cadastro[pos].estoque);
    printf("Novo estoque: ");
    scanf("%d", &cadastro[pos].estoque);
    limparBuffer();
    printf("Estoque atualizado com sucesso!\n");
}

/* ---------- (g) Exibir todos os produtos ---------- */
void exibirProdutos(Produto cadastro[], int qtd) {
    int i;

    if (qtd == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("\n--- PRODUTOS CADASTRADOS ---\n");
    for (i = 0; i < qtd; i++) {
        printf("Codigo: %d | Descricao: %s\n",
               cadastro[i].codigo, cadastro[i].descricao);
    }
}

/* ---------- (h) Exibir produtos com estoque zero ---------- */
void exibirSemEstoque(Produto cadastro[], int qtd) {
    int i, achou = 0;

    printf("\n--- PRODUTOS SEM ESTOQUE ---\n");
    for (i = 0; i < qtd; i++) {
        if (cadastro[i].estoque == 0) {
            printf("Codigo: %d | Descricao: %s\n",
                   cadastro[i].codigo, cadastro[i].descricao);
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhum produto com estoque zero.\n");
    }
}

/* ---------- Menu ---------- */
void exibirMenu(void) {
    printf("\n===== PAPELARIA ESCOLAR =====\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Alterar valor unitario\n");
    printf("3 - Consultar valor unitario\n");
    printf("4 - Consultar estoque\n");
    printf("5 - Vender produto\n");
    printf("6 - Atualizar estoque\n");
    printf("7 - Listar todos os produtos\n");
    printf("8 - Listar produtos sem estoque\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

int lerCodigo(void) {
    int codigo;
    printf("Codigo do produto: ");
    scanf("%d", &codigo);
    limparBuffer();
    return codigo;
}

/* ---------- Programa principal ---------- */
int main(void) {
    Produto cadastro[MAX_PRODUTOS];
    int qtd = 0;
    int opcao, codigo, quantidade;
    float valor;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarProduto(cadastro, &qtd);
                break;
            case 2:
                codigo = lerCodigo();
                alterarValor(cadastro, qtd, codigo);
                break;
            case 3:
                codigo = lerCodigo();
                valor = consultarValor(cadastro, qtd, codigo);
                if (valor < 0) printf("Produto nao encontrado!\n");
                else printf("Valor unitario: R$ %.2f\n", valor);
                break;
            case 4:
                codigo = lerCodigo();
                quantidade = consultarEstoque(cadastro, qtd, codigo);
                if (quantidade < 0) printf("Produto nao encontrado!\n");
                else printf("Quantidade em estoque: %d\n", quantidade);
                break;
            case 5:
                codigo = lerCodigo();
                printf("Quantidade desejada: ");
                scanf("%d", &quantidade);
                limparBuffer();
                venderProduto(cadastro, qtd, codigo, quantidade);
                break;
            case 6:
                codigo = lerCodigo();
                atualizarEstoque(cadastro, qtd, codigo);
                break;
            case 7:
                exibirProdutos(cadastro, qtd);
                break;
            case 8:
                exibirSemEstoque(cadastro, qtd);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
