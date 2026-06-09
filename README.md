# Sistema de Manutenção de Contas em C

## Descrição

Este projeto implementa um sistema de manutenção de contas bancárias utilizando a linguagem C e arquivos binários.

O objetivo é demonstrar o uso das funções de manipulação de arquivos exigidas pelo enunciado:

* `fseek()`
* `fread()`
* `fwrite()`
* `rewind()`

Além disso, os registros são armazenados em um arquivo binário com tamanho fixo, permitindo acesso direto a posições específicas do arquivo.

---

## Estrutura do Registro

Cada cliente é armazenado através da estrutura:

```c
typedef struct {
    int numeroConta;
    char nome[50];
    float saldo;
    int ativo;
} Cliente;
```

### Campos

| Campo       | Descrição                                         |
| ----------- | ------------------------------------------------- |
| numeroConta | Número identificador da conta                     |
| nome        | Nome do cliente                                   |
| saldo       | Saldo atual da conta                              |
| ativo       | Indica se a conta está ativa (1) ou encerrada (0) |

O campo `ativo` foi utilizado para implementar a remoção lógica dos registros.

---

## Arquivo Binário

Os dados são armazenados no arquivo:

```text
contas.dat
```

O arquivo é aberto utilizando:

```c
fopen("contas.dat", "r+b");
```

Caso não exista, ele é criado com:

```c
fopen("contas.dat", "w+b");
```

---

## Funcionalidades Implementadas

### 1. Cadastrar Cliente

Permite inserir um cliente em uma posição específica do arquivo.

Exemplo:

```text
Posição: 3
Conta: 1001
Nome: João Silva
Saldo: 1500.00
```

Para acessar a posição desejada foi utilizado:

```c
fseek(arquivo, posicao * sizeof(Cliente), SEEK_SET);
```

Após posicionar o cursor, o registro é gravado com:

```c
fwrite(&cliente, sizeof(Cliente), 1, arquivo);
```

---

### 2. Consultar Cliente

Permite localizar um cliente através do número da conta.

O sistema percorre o arquivo utilizando:

```c
fread(&cliente, sizeof(Cliente), 1, arquivo);
```

Quando encontra o número informado, exibe seus dados.

---

### 3. Atualizar Saldo

Localiza a conta desejada e atualiza seu saldo.

Após localizar o registro:

```c
fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
```

O cursor retorna ao início do registro atual e os novos dados são gravados utilizando:

```c
fwrite(&cliente, sizeof(Cliente), 1, arquivo);
```

---

### 4. Encerrar Conta

A exclusão foi implementada através de remoção lógica.

Em vez de apagar fisicamente o registro, o campo:

```c
ativo = 0;
```

é atualizado.

Dessa forma o registro permanece no arquivo, mas deixa de aparecer nas consultas e listagens.

---

### 5. Listar Clientes

Exibe todos os clientes ativos cadastrados no arquivo.

A leitura é feita sequencialmente através de:

```c
fread()
```

Contas encerradas são ignoradas.

---

### 6. Restaurar Leitura com rewind()

Esta opção reposiciona o cursor do arquivo para o início.

```c
rewind(arquivo);
```

Isso permite repetir leituras e listagens sem fechar ou reabrir o arquivo.

---

### 7. Encerrar Sistema

Fecha o arquivo e finaliza a execução.

```c
fclose(arquivo);
```

---

## Funções de Manipulação de Arquivos Utilizadas

### fseek()

Permite mover o cursor para uma posição específica do arquivo.

Exemplo:

```c
fseek(arquivo, posicao * sizeof(Cliente), SEEK_SET);
```

Utilizada para acessar diretamente um registro.

---

### fread()

Lê registros do arquivo binário.

Exemplo:

```c
fread(&cliente, sizeof(Cliente), 1, arquivo);
```

---

### fwrite()

Grava registros no arquivo binário.

Exemplo:

```c
fwrite(&cliente, sizeof(Cliente), 1, arquivo);
```

---

### rewind()

Reposiciona o cursor no início do arquivo.

Exemplo:

```c
rewind(arquivo);
```

---

## Compilação

### Linux / MacOS

```bash
gcc contas.c -o contas
./contas
```

### Windows (MinGW)

```bash
gcc contas.c -o contas.exe
contas.exe
```

---

## Exemplo de Uso

```text
===== SISTEMA BANCARIO =====

1. Cadastrar novo cliente
2. Consultar cliente
3. Atualizar saldo
4. Encerrar conta
5. Listar clientes
6. Restaurar leitura (rewind)
7. Encerrar

Opcao: 1

Posicao para gravar: 0
Numero da conta: 1001
Nome: Maria Silva
Saldo: 2500
```

Posteriormente o cliente pode ser consultado, atualizado ou removido.


* Escrita com `fwrite()`;
* Reinicialização da leitura com `rewind()`.

O projeto demonstra conceitos fundamentais de persistência de dados em C e manipulação de arquivos binários.
