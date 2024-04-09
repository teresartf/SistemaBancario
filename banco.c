#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "banco.h"
#include <math.h>


void abrirBanco(Banco *novoBanco);
void abrirConta(Conta *contas, int *qtdContas);
void limparTela();
int numeroDaConta();
bool validarCPF(char *cpf);
bool validarCEP(char *cep);
bool validarUF(char *uf);
void listarContas(Conta *contas, int *qtdContas);
void sacar(Conta *contas, float valor, char *cpf, int *qtdContas);
void depositar(Conta *contas, float valor, char *cpf, int *qtdContas);
void mostrarSaldo(Conta *contas, char *cpf, int *qtdContas);
void realizarPIX(Conta *contas, char *cpfOrigem, char *cpfDestino, int *qtdContas);
void mostrarExtrato(Conta *contas, char *cpf, int *qtdContas);
void adicionarTransacao(Conta *contas, int i, char *descricao, char *operacao, float valor);
void menu(){
    printf("\n- - - - - - - - - - BANCO R1 - - - - - - - - - -");
    printf("\n\n1-Abrir Conta");
    printf("\n2-Listar Contas");
    printf("\n3-Sacar");
    printf("\n4-Depositar");
    printf("\n5-Transferência(PIX)");
    printf("\n6-Consultar extrato");
    printf("\n7-Consultar saldo");
    // printf("\n8-Atualizar dados");
    printf("\n\n0-Sair");
    printf("\n\n>>>> ");
}

int main(){
    Banco novoBanco;

    int qtdContas = 0;

    Conta contas[100];

    abrirBanco(&novoBanco);
    limparTela();

    int opcao;
    menu();
    scanf("%d", &opcao);

    while(opcao != 0){
    if(opcao == 1){
        limparTela();
        abrirConta(contas, &qtdContas);
    }
    else if(opcao == 2){
        limparTela();
        listarContas(contas, &qtdContas);
        printf("\n");
    }
    else if(opcao == 3){
        char cpf[12];
        printf("\nCPF da conta que deseja sacar: ");
        scanf(" %12[^\n]", cpf);

        bool cpfValidado = validarCPF(cpf);
         while(!cpfValidado){
            printf("\nCPF é inválido, digite novamente: ");
            scanf(" %12[^\n]", cpf);
            cpfValidado = validarCPF(cpf);
            while(getchar() != '\n');
        }

        float valor;
        printf("Valor que deseja sacar: ");
        scanf("%f", &valor);
        sacar(contas, valor, cpf, &qtdContas);
        printf("\n");

    }
    else if(opcao == 4){
        char cpf[12];
        printf("\nCPF da conta que deseja realizar depósito: ");
        scanf(" %12[^\n]", cpf);

        bool cpfValidado = validarCPF(cpf);
         while(!cpfValidado){
            printf("\nCPF é inválido, digite novamente: ");
            scanf(" %12[^\n]", cpf);
            cpfValidado = validarCPF(cpf);
            while(getchar() != '\n');
        }

        float valor;
        printf("Valor que deseja depositar: ");
        scanf("%f", &valor);
        depositar(contas, valor, cpf, &qtdContas);
        printf("\n");
    }
    else if(opcao == 5){
        limparTela();
        char cpfOrigem[12];
        char cpfDestino[12];

        printf("\nCPF de Origem para PIX: ");
        scanf(" %12[^\n]", cpfOrigem);

        bool cpfOrigemValidado = validarCPF(cpfOrigem);
         while(!cpfOrigemValidado){
            printf("\nCPF é inválido, digite novamente: ");
            scanf(" %12[^\n]", cpfOrigem);
            cpfOrigemValidado = validarCPF(cpfOrigem);
            while(getchar() != '\n');
        }

        printf("\nCPF de Destino para PIX: ");
        scanf(" %12[^\n]", cpfDestino);

        bool cpfDestinoValidado = validarCPF(cpfDestino);
         while(!cpfDestinoValidado){
            printf("\nCPF é inválido, digite novamente: ");
            scanf(" %12[^\n]", cpfDestino);
            cpfDestinoValidado = validarCPF(cpfDestino);
            while(getchar() != '\n');
        }

        realizarPIX(contas, cpfOrigem, cpfDestino, &qtdContas);
        printf("\n");
    }
    else if(opcao == 6){
        char cpf[12];
        printf("\nCPF da conta que deseja acessar o extrato: ");
        scanf(" %12[^\n]", cpf);

        bool cpfValidado = validarCPF(cpf);
         while(!cpfValidado){
            printf("\nCPF é inválido, digite novamente: ");
            scanf(" %12[^\n]", cpf);
            cpfValidado = validarCPF(cpf);
            while(getchar() != '\n');
        }

        mostrarExtrato(contas, cpf, &qtdContas);

    }
    else if(opcao == 7){
        char cpf[12];
        printf("\nCPF da conta que deseja acessar o saldo: ");
        scanf(" %12[^\n]", cpf);

        bool cpfValidado = validarCPF(cpf);
         while(!cpfValidado){
            printf("\nCPF é inválido, digite novamente: ");
            scanf(" %12[^\n]", cpf);
            cpfValidado = validarCPF(cpf);
            while(getchar() != '\n');
        }
        
        mostrarSaldo(contas, cpf, &qtdContas);

    }
    // else if(opcao == 8){

    // }
    limparTela();
    menu();
    scanf("%d", &opcao);
    }

    return 0;
}

void abrirBanco(Banco *novoBanco){
    char nome[120];
    char logradouro[250];
    char bairro[120];
    char cidade[120];
    char uf[3];
    char cep[9];

    printf("- - - - - - - - - - - Banco - - - - - - - - - - - - -");
    //nome
    printf("\n\nNome do Banco: ");
    scanf(" %120[^\n]", nome);

    //endereço
    printf("\n\n- - - - - - - - - - ENDEREÇO - - - - - - - - - -");
    printf("\n\nLogradouro: ");
    scanf(" %250[^\n]", logradouro);
    printf("Bairro: ");
    scanf(" %120[^\n]", bairro);
    printf("Cidade: ");
    scanf(" %120[^\n]", cidade);

    printf("UF: ");
    scanf(" %3[^\n]", uf);
    bool ufValidado = validarUF(uf);

    while(!ufValidado){
        printf("\nUF é inválido, digite novamente: ");
        scanf(" %3[^\n]", uf);
        ufValidado = validarUF(uf);
        while(getchar() != '\n');
    }

    printf("CEP: ");
    scanf(" %9[^\n]", cep);
    bool cepValidado = validarCEP(cep);

    while(!cepValidado){
        printf("\nCEP é inválido, digite novamente: ");
        scanf(" %9[^\n]", cep);
        cepValidado = validarCEP(cep);
        while(getchar() != '\n');
    }
    while(!cepValidado){
        printf("\nCEP é inválido!");
        printf("\nDigite novamente: ");
        scanf(" %9[^\n]", cep);
        cepValidado = validarCEP(cep);
        while(getchar() != '\n');
    } 
    strcpy(novoBanco->nome, nome);
    strcpy(novoBanco->endereco.logradouro,logradouro);
    strcpy(novoBanco->endereco.bairro, bairro);
    strcpy(novoBanco->endereco.cidade, cidade);
    strcpy(novoBanco->endereco.uf, uf);
    strcpy(novoBanco->endereco.cep, cep);

    printf("\nBanco criado com sucesso!!!\n");

}

//gerando o número da conta aleatoriamente
int numeroDaConta(){
    srand(time(NULL));

    int numero = rand() % 100000000 + 10000000;
    return numero;
}

bool validarCPF(char *cpf) {
    if (strlen(cpf) != 11) {
        return false;
    }

    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return false;
        }
    }

    return true;
}

bool validarUF(char *uf){
    if(strlen(uf) != 2){
        return false;
    }

    for (int i = 0; i < 2; i++){
        if(!isalpha(uf[i])){
            return false;
        }
    }

    return true;
}

bool validarCEP(char *cep){
    if(strlen(cep) != 8){
        return false;
    }

    for (int i = 0; i < 8; i++){
        if(!isdigit(cep[i])){
            return false;
        }
    }

    return true;
}

bool validarValor(float valor){
    if(isnan(valor)){
        return false;
    }

    if(valor == 0.0 || valor < 0){
        return false;
    }

    return true;
}
//validar data
bool ehAnoBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

bool validarData(int dia, int mes, int ano, char *dataValida) {
    if (ano < 1 || ano > 2024) {
        return false; // Ano deve estar entre 1 e 2024
    }

    if (mes < 1 || mes > 12) {
        return false; // Mês deve estar entre 1 e 12
    }

    int diasNoMes;

    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasNoMes = 31;
            break;
        case 4: case 6: case 9: case 11:
            diasNoMes = 30;
            break;
        case 2:
            diasNoMes = ehAnoBissexto(ano) ? 29 : 28;
            break;
        default:
            return false;
    }

    if (dia < 1 || dia > diasNoMes) {
        return false; // Dia deve estar dentro do intervalo correto para o mês
    }

    // Se chegou aqui, a data é válida
    sprintf(dataValida, "%02d/%02d/%04d", dia, mes, ano); // Formata a data como string
    return true; // Data válida
}

void abrirConta(Conta *contas, int *qtdContas){
    int numero = numeroDaConta();
    float saldo = 0.00;
    int qtdOperacoes = 0;
    char nome[120];
    int idade;
    float renda;
    char cpf[12];
    char logradouro[250];
    char bairro[120];
    char cidade[120];
    char uf[3];
    char cep[9];

    printf("- - - - - - - - - - DADOS DO TITULAR - - - - - - - - - -");
    //nome
    printf("\n\nNome do titular: ");
    scanf(" %120[^\n]", nome);

    //idade
    bool entradaValida = false; 

    while (!entradaValida) {
        printf("Idade do titular: ");
        if(scanf("%d", &idade) == 1) {
            entradaValida = true;
        }else{
            printf("\nIdade inválida, digite novamente.\n");
            while (getchar() != '\n'); 
        }
    }

    if(idade < 18){
        printf("\nApenas maiores de 18 anos podem abrir uma conta bancária.\n");
    }
    else {
        printf("Renda: ");
        scanf("%f", &renda);

        printf("CPF do titular: ");
        scanf(" %12[^\n]", cpf);
        bool cpfValidado = validarCPF(cpf);

        while(!cpfValidado){
            printf("\nCPF é inválido, digite novamente: ");
            scanf(" %12[^\n]", cpf);
            cpfValidado = validarCPF(cpf);
            while(getchar() != '\n');
        }

        printf("\n\n- - - - - - - - - - ENDEREÇO - - - - - - - - - -");
        printf("\n\nLogradouro: ");
        scanf(" %250[^\n]", logradouro);
        printf("Bairro: ");
        scanf(" %120[^\n]", bairro);
        printf("Cidade: ");
        scanf(" %120[^\n]", cidade);

        printf("UF: ");
        scanf(" %3[^\n]", uf);
        bool ufValidado = validarUF(uf);

        while(!ufValidado){
           if(!validarUF(uf)){
           printf("\nUF é inválido, digite novamente: ");
           scanf(" %3[^\n]", uf);
           ufValidado = validarUF(uf);
           while(getchar() != '\n');
           } else{
            ufValidado = true;
           }
        }

        printf("CEP: ");
        scanf(" %9[^\n]", cep);
        bool cepValidado = validarCEP(cep);

        while(!cepValidado){
            printf("\nCEP é inválido, digite novamente: ");
            scanf(" %9[^\n]", cep);
            cepValidado = validarCEP(cep);
            while(getchar() != '\n');
        }
    
        Conta novaConta;
        contas[*qtdContas] = novaConta;

        contas[*qtdContas].numero = numero;
        contas[*qtdContas].saldo = saldo;
        strncpy(contas[*qtdContas].titular.nome, nome, sizeof(contas[*qtdContas].titular.nome));
        contas[*qtdContas].titular.idade = idade;
        contas[*qtdContas].titular.renda = renda;
        strncpy(contas[*qtdContas].titular.cpf, cpf, sizeof(contas[*qtdContas].titular.cpf));
        strncpy(contas[*qtdContas].titular.endereco.logradouro,logradouro, sizeof(contas[*qtdContas].titular.endereco.logradouro));
        strncpy(contas[*qtdContas].titular.endereco.bairro, bairro, sizeof(contas[*qtdContas].titular.endereco.bairro));
        strncpy(contas[*qtdContas].titular.endereco.cidade, cidade, sizeof(contas[*qtdContas].titular.endereco.cidade));
        strncpy(contas[*qtdContas].titular.endereco.uf, uf, sizeof(contas[*qtdContas].titular.endereco.uf));
        strncpy(contas[*qtdContas].titular.endereco.cep, cep, sizeof(contas[*qtdContas].titular.endereco.cep));
        contas[*qtdContas].operacoesRealizadas = qtdOperacoes;

        printf("\nConta criada com sucesso!!!\n");
        (*qtdContas)++;
    }
}

void limparTela(){
    printf("\n<enter> to continue...");
    getchar();
    while(getchar() != '\n');
    system("clear");
}

void listarContas(Conta *contas, int *qt_contas){
    printf("- - - - - - - - Contas Cadastradas - - - - - - - -\n");

    for(int i = 0; i < (*qt_contas); i++){
        printf("\n******Conta %d******", i+1);
        printf("\nNúmero da Conta- %d", contas[i].numero);
        printf("\nNome do Titular- %s", contas[i].titular.nome);
        printf("\nRenda do Titular- R$%.2f", contas[i].titular.renda);
        printf("\nCPF do titular- %s", contas[i].titular.cpf);
        printf("\n");
    }
}

void sacar(Conta *contas, float valor, char *cpf, int *qtdContas){
    bool cpfEncontrado = false;
    for (int i = 0; i < (*qtdContas); i++){
        if (strcmp(contas[i].titular.cpf, cpf) == 0){
            cpfEncontrado = true;
            if(!validarValor(valor)){
                printf("\nValor inválido!");
            }else if(contas[i].saldo < valor){
                printf("\nSaldo insuficiente! Saque não foi realizado.");
            }else{
                char operacao[9] = "Saque";

                int dia, mes, ano;
                char data[11];
                
                printf("Data da operação(DD/MM/AAAA): ");
                scanf("%d/%d/%d", &dia, &mes, &ano);

                bool dataValidada = validarData(dia, mes, ano, data);

                while(!dataValidada){
                    printf("\nData inválida!\n");
                    printf("Data(DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &dia, &mes, &ano);
                    dataValidada = validarData(dia, mes, ano, data);
                    while(getchar() != '\n');
                    
                }

                char descricao[250] = "Transação em: ";
                strcat(descricao, data);

                contas[i].saldo -= valor;

                adicionarTransacao(contas, i, descricao, operacao, valor);
                printf("\nSaque realizado com sucesso!");
            }
        }
    }
    if(!cpfEncontrado){
        printf("\nCPF não encontrado.");

    }

}

void depositar(Conta *contas, float valor, char *cpf, int *qtdContas){ 
    bool cpfEncontrado = false;
    for(int i = 0; i < (*qtdContas); i++){
        if (strcmp(contas[i].titular.cpf, cpf) == 0){
            cpfEncontrado = true;
            if(!validarValor(valor)){
                printf("\nValor inválido.");
                return;
            }else{
                char operacao[9] = "Depósito";
    
                int dia, mes, ano;
                char data[11];
                
                printf("Data (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &dia, &mes, &ano);

                bool dataValida = validarData(dia, mes, ano, data);
                
                while(!dataValida){
                    printf("Data inválida!\n");
                    printf("Data (DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &dia, &mes, &ano);
                    dataValida = validarData(dia, mes, ano, data);
                    while (getchar() != '\n'); // Limpa o buffer de entrada
                }

                char descricao[250] = "Transação em: ";
                strcat(descricao, data);

                //REALIZANDO DEPÓSITO
                contas[i].saldo += valor; 

                adicionarTransacao(contas, i, descricao, operacao, valor);
                printf("\nDepósito realizado com sucesso!");
                return;
            }
        }
    }

    if(!cpfEncontrado){
        printf("\nCPF não encontrado.");

    }
}

void mostrarSaldo(Conta *contas, char *cpf, int *qtdContas){
    int cpfEncontrado = 0;
    for (int i = 0; i < (*qtdContas); i++){
        if (strcmp(contas[i].titular.cpf, cpf) == 0){ 
            printf("\nSaldo atual: R$%.2f\n", contas[i].saldo);
            cpfEncontrado = 1;
        }
    }

    if(!cpfEncontrado){
        printf("\nCPF não foi encontrado. Impossível consultar saldo.\n");
    }
}

void realizarPIX(Conta *contas, char *cpf_origem, char *cpf_destino, int *qtdContas){
    int id_conta_origem;
    int id_conta_destino;
    int nao_encontrados_o = 0;
    int nao_encontrados_d = 0;

    for(int i = 0; i < (*qtdContas); i++){
        if (strcmp(contas[i].titular.cpf, cpf_origem) != 0){
           nao_encontrados_o++;
        }else{
            id_conta_origem = i;
        }
    } 

    for(int i = 0; i < (*qtdContas); i++){
        if (strcmp(contas[i].titular.cpf, cpf_destino) != 0){
            nao_encontrados_d++;
        }else{
            id_conta_destino = i;
        }
    }
    
    for(int i = 0; i < (*qtdContas); i++){
        if(nao_encontrados_o != (*qtdContas) && nao_encontrados_d != (*qtdContas)){
                float valor;
                printf("\nValor (R$) que deseja transferir via PIX: ");
                scanf("%f", &valor);
                if(!validarValor(valor)){
                    printf("\nValor inválido.");
                    break;
            }else{
                if(contas[id_conta_origem].saldo < valor){
                        printf("\nSaldo insuficiente.");
                break;
                }else{
                    char operacao[9] = "PIX";
                    char origem[120];
                    char destino[120];

                    strcpy(origem, contas[id_conta_origem].titular.nome);
                    strcpy(destino, contas[id_conta_destino].titular.nome);

                    int dia, mes, ano;
                    char data[11];
                    
                    printf("Data (DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &dia, &mes, &ano);

                    bool dataValida = validarData(dia, mes, ano, data);
                    
                    while(!dataValida){
                        printf("Data inválida!\n");
                        printf("Data (DD/MM/AAAA): ");
                        scanf("%d/%d/%d", &dia, &mes, &ano);
                        dataValida = validarData(dia, mes, ano, data);
                        while (getchar() != '\n'); // Limpa o buffer de entrada
                    }

                    char descricao[250] = "Transação em: ";
                    strcat(descricao, data);
                    strcat(descricao, "\nDe: ");
                    strcat(descricao, origem);
                    strcat(descricao, "\nPara: ");
                    strcat(descricao, destino);    

                    char descricao_origem[250] = "Transação em: ";
                    strcat(descricao_origem, data);
                    strcat(descricao_origem, "\nDe: ");
                    strcat(descricao_origem, origem);
                    strcat(descricao_origem, "\nPara: ");
                    strcat(descricao_origem, destino);                        

                    //REALIZANDO PIX
                    contas[id_conta_origem].saldo -= valor; 
                    contas[id_conta_destino].saldo += valor; 
                    printf("\nTransferência PIX realizada com sucesso!");

                    adicionarTransacao(contas, id_conta_destino, descricao, operacao, valor);
                    adicionarTransacao(contas, id_conta_origem, descricao, operacao, valor);

                    break;
                }
            }
        }else if((nao_encontrados_o == (*qtdContas) && nao_encontrados_d == (*qtdContas))){
            printf("\nCPF de origem e CPF de destino não foram encontrados.\n");
            break;
        }
        else if(nao_encontrados_o == (*qtdContas) && nao_encontrados_d != (*qtdContas)){
            printf("\nCPF de origem não encontrado.");
            break;
        }
        else if(nao_encontrados_o != (*qtdContas) && nao_encontrados_d == (*qtdContas)){
            printf("\nCPF de destino não encontrado.");
            break;
        }
    }
}

void mostrarExtrato(Conta *contas, char *cpf, int *qtdContas){
    int cpfEncontrado = 0; 
    for(int i = 0; i < (*qtdContas); i++){
        if (strcmp(contas[i].titular.cpf, cpf) == 0){
            printf("\n");
            limparTela();
            printf("- - - - - - - - - - - - Extrato da Conta - - - - - - - - - - - - -");
            printf("\n\nSaldo atual: R$ %.2f\n\n", contas[i].saldo);
            printf("- - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - -\n");
            for(int j = 0; j < contas[i].operacoesRealizadas; j++){
                printf("\nTipo de operação: %s", contas[i].extratos[j].operacao);
                printf("\n%s", contas[i].extratos[j].descricao);
                printf("\nValor: R$%.2f",contas[i].extratos[j].valor);
            printf("\n\n- - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - -\n");
            }
            cpfEncontrado = 1;
        }
    }
    if (!cpfEncontrado) { 
        printf("\nCPF não encontrado.\n");
    }
    
}    

void adicionarTransacao(Conta *contas, int i, char *descricao, char *operacao, float valor){
    if(contas[i].operacoesRealizadas < 100){
        Transacao novaTransacao;
        strcpy(novaTransacao.descricao, descricao);
        strcpy(novaTransacao.operacao, operacao);
        novaTransacao.valor = valor;
        contas[i].extratos[(contas[i].operacoesRealizadas)++] = novaTransacao;
    } else {
        printf("Número máximo de transações atingido.\n");
    }
}