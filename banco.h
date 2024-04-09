typedef struct{
    char logradouro[250];
    char bairro[120];
    char cidade[120];
    char uf[3];
    char cep[9];
}Endereco;

typedef struct{
    char nome[120];
    int idade;
    float renda;
    char cpf[12];
    Endereco endereco;
}Titular;

typedef struct{
    char operacao[9];
    char descricao[250];
    float valor;
}Transacao;

typedef struct{
    int numero;
    float saldo;
    Titular titular;
    Transacao extratos[100];
    int operacoesRealizadas;
}Conta;

typedef struct{
    Conta contas[100];
    char nome[120];
    Endereco endereco;
}Banco;
