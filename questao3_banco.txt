/*
 * Lista 10 - Structs - Questao 3
 * Banco Dinheiro Certo - cadastros de conta corrente e poupanca
 * Cada cadastro e um vetor de structs (maximo de 100 contas)
 */
#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100
#define TAM_NOME 50
#define TAM_CPF 20
#define TAM_TEL 20

/* ---------- Estruturas ---------- */
typedef struct {
    int numero;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char telefone[TAM_TEL];
    float saldo;
} Conta;

typedef struct {
    Conta contas[MAX_CONTAS];
    int qtd;
} Cadastro;

/* ---------- Funcoes auxiliares ---------- */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerTexto(char *destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}

/* ---------- (a) Funcao de busca ---------- */
/* Retorna a posicao da conta, -1 se o cadastro estiver vazio
   e -2 se a conta nao for encontrada */
int buscarConta(Cadastro *cad, int numero) {
    int i;

    if (cad->qtd == 0) {
        return -1;
    }
    for (i = 0; i < cad->qtd; i++) {
        if (cad->contas[i].numero == numero) {
            return i;
        }
    }
    return -2;
}

/* ---------- (b) Cadastrar nova conta ---------- */
void cadastrarConta(Cadastro *cad, int numero) {
    Conta nova;

    if (cad->qtd >= MAX_CONTAS) {
        printf("Cadastro cheio! (maximo de %d contas)\n", MAX_CONTAS);
        return;
    }

    if (buscarConta(cad, numero) >= 0) {
        printf("Numero de conta repetido! Cadastro nao realizado.\n");
        return;
    }

    nova.numero = numero;
    printf("Nome do cliente: ");
    lerTexto(nova.nome, TAM_NOME);
    printf("CPF: ");
    lerTexto(nova.cpf, TAM_CPF);
    printf("Telefone: ");
    lerTexto(nova.telefone, TAM_TEL);
    printf("Saldo inicial: ");
    scanf("%f", &nova.saldo);
    limparBuffer();

    cad->contas[cad->qtd] = nova;
    cad->qtd++;
    printf("Conta cadastrada com sucesso!\n");
}

/* ---------- (c) Consultar saldo ---------- */
void consultarSaldo(Cadastro *cad, int numero) {
    int pos = buscarConta(cad, numero);

    if (pos < 0) {
        printf("Conta nao cadastrada!\n");
    } else {
        printf("Saldo da conta %d: R$ %.2f\n", numero, cad->contas[pos].saldo);
    }
}

/* ---------- (d) Depositar ---------- */
void depositar(Cadastro *cad, int numero) {
    int pos = buscarConta(cad, numero);
    float valor;

    if (pos < 0) {
        printf("Conta nao cadastrada!\n");
        return;
    }
    printf("Valor do deposito: ");
    scanf("%f", &valor);
    limparBuffer();

    if (valor <= 0) {
        printf("Valor invalido!\n");
        return;
    }
    cad->contas[pos].saldo += valor;
    printf("Deposito realizado! Novo saldo: R$ %.2f\n", cad->contas[pos].saldo);
}

/* ---------- (e) Sacar ---------- */
void sacar(Cadastro *cad, int numero) {
    int pos = buscarConta(cad, numero);
    float valor;

    if (pos < 0) {
        printf("Conta nao cadastrada!\n");
        return;
    }
    printf("Valor do saque: ");
    scanf("%f", &valor);
    limparBuffer();

    if (valor <= 0) {
        printf("Valor invalido!\n");
    } else if (valor > cad->contas[pos].saldo) {
        printf("Saldo insuficiente!\n");
    } else {
        cad->contas[pos].saldo -= valor;
        printf("Saque realizado! Novo saldo: R$ %.2f\n", cad->contas[pos].saldo);
    }
}

/* ---------- (f) Exibir contas ---------- */
void exibirContas(Cadastro *cad) {
    int i;

    if (cad->qtd == 0) {
        printf("Cadastro vazio.\n");
        return;
    }
    printf("\n--- CONTAS CADASTRADAS ---\n");
    for (i = 0; i < cad->qtd; i++) {
        printf("Conta: %d | Titular: %s | Telefone: %s\n",
               cad->contas[i].numero,
               cad->contas[i].nome,
               cad->contas[i].telefone);
    }
}

/* ---------- Menus ---------- */
int escolherTipoConta(void) {
    int tipo;
    printf("\nTipo de conta: 1 - Corrente | 2 - Poupanca: ");
    scanf("%d", &tipo);
    limparBuffer();
    return tipo;
}

void exibirMenu(void) {
    printf("\n===== BANCO DINHEIRO CERTO =====\n");
    printf("1 - Cadastrar conta\n");
    printf("2 - Consultar saldo\n");
    printf("3 - Depositar\n");
    printf("4 - Sacar\n");
    printf("5 - Listar contas\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

int lerNumeroConta(void) {
    int numero;
    printf("Numero da conta: ");
    scanf("%d", &numero);
    limparBuffer();
    return numero;
}

/* ---------- Programa principal ---------- */
int main(void) {
    Cadastro corrente = { .qtd = 0 };
    Cadastro poupanca = { .qtd = 0 };
    Cadastro *cad;
    int opcao, tipo, numero;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao >= 1 && opcao <= 5) {
            tipo = escolherTipoConta();
            if (tipo == 1) cad = &corrente;
            else if (tipo == 2) cad = &poupanca;
            else {
                printf("Tipo invalido!\n");
                continue;
            }

            switch (opcao) {
                case 1:
                    numero = lerNumeroConta();
                    cadastrarConta(cad, numero);
                    break;
                case 2:
                    numero = lerNumeroConta();
                    consultarSaldo(cad, numero);
                    break;
                case 3:
                    numero = lerNumeroConta();
                    depositar(cad, numero);
                    break;
                case 4:
                    numero = lerNumeroConta();
                    sacar(cad, numero);
                    break;
                case 5:
                    exibirContas(cad);
                    break;
            }
        } else if (opcao == 0) {
            printf("Encerrando o programa...\n");
        } else {
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
