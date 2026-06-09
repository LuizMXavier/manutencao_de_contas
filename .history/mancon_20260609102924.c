#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numeroConta;
    char nome[50];
    float saldo;
    int ativo; // 1 = ativo, 0 = removido
} Cliente;

void cadastrarCliente(FILE *arquivo);
void consultarCliente(FILE *arquivo);
void atualizarSaldo(FILE *arquivo);
void encerrarConta(FILE *arquivo);
void listarClientes(FILE *arquivo);

int main() {
    FILE *arquivo;
    int opcao;

    arquivo = fopen("contas.dat", "r+b");

    if (arquivo == NULL) {
        arquivo = fopen("contas.dat", "w+b");

        if (arquivo == NULL) {
            printf("Erro ao criar arquivo.\n");
            return 1;
        }
    }

    do {
        printf("\n===== SISTEMA BANCARIO =====\n");
        printf("1. Cadastrar novo cliente\n");
        printf("2. Consultar cliente\n");
        printf("3. Atualizar saldo\n");
        printf("4. Encerrar conta\n");
        printf("5. Listar clientes\n");
        printf("6. Restaurar leitura (rewind)\n");
        printf("7. Encerrar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarCliente(arquivo);
                break;

            case 2:
                consultarCliente(arquivo);
                break;

            case 3:
                atualizarSaldo(arquivo);
                break;

            case 4:
                encerrarConta(arquivo);
                break;

            case 5:
                listarClientes(arquivo);
                break;

            case 6:
                rewind(arquivo);
                printf("\nLeitura reposicionada para o inicio do arquivo.\n");
                break;

            case 7:
                printf("\nSistema encerrado.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 7);

    fclose(arquivo);

    return 0;
}

void cadastrarCliente(FILE *arquivo) {
    Cliente cliente;
    int posicao;

    printf("\nPosicao para gravar: ");
    scanf("%d", &posicao);

    printf("Numero da conta: ");
    scanf("%d", &cliente.numeroConta);

    getchar();

    printf("Nome: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

    printf("Saldo: ");
    scanf("%f", &cliente.saldo);

    cliente.ativo = 1;

    fseek(arquivo, posicao * sizeof(Cliente), SEEK_SET);

    fwrite(&cliente, sizeof(Cliente), 1, arquivo);

    fflush(arquivo);

    printf("\nCliente cadastrado com sucesso!\n");
}
void consultarCliente(FILE *arquivo) {
    Cliente cliente;
    int conta;
    int encontrou = 0;

    printf("\nNumero da conta: ");
    scanf("%d", &conta);

    rewind(arquivo);

    while(fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {

        if(cliente.ativo && cliente.numeroConta == conta) {
            printf("\nCliente encontrado:\n");
            printf("Conta: %d\n", cliente.numeroConta);
            printf("Nome : %s\n", cliente.nome);
            printf("Saldo: %.2f\n", cliente.saldo);

            encontrou = 1;
            break;
        }
    }

    if(!encontrou) {
        printf("\nConta nao encontrada.\n");
    }
}