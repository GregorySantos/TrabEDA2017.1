#ifndef DATA_INCLUDED
#define DATA_INCLUDED

typedef struct datanode{
    int matricula;  //Armazenar a Matricula
    char *nome; //Armazenar o Nome
    char *sobrenome; //Armazenar o Sobrenome
    char *email; //Armazenar o Email
    char *telefone; //Armazena o Telefone
    double salario; //Armazena o Salario
}DataNode;

//Assinaturas das Funções de Data
void setFileData( char * input, DataNode * new, int data );//Vai setando o DataNode
DataNode * createData(); //Cria uma Estrutura Data
void FreeDataNode(DataNode *D); //Exclui completamente a Estrutura DataNode
DataNode * setDataNode(); //Cria um DataNode individualmente
char * createString(int sizeMax); //Helper para Criação de Strings
void giveData(void * Tads[]); //Função que será chamada para colocar um novo Node em alguma Tad
void editDataNode(int choose, DataNode *D); //Função para Editar o DataNode
void showData(DataNode * data);//Exibe o DataNode

//Dependências
#include <stdio.h>
#include <string.h>
#include "Menu.h"
#include "Unissex.h"
#include "Time.h"

//Vai setando o DataNode
void setFileData( char * input, DataNode * new, int data ) {
    char * text;

    switch (data) {//Verifica qual o tipo de Dado que será lido
        case 0://Caso seja a Matricula
            (*new).matricula = atoi(input);
            break;
        case 1://Caso seja Uma String
        case 2://Caso seja Uma String
        case 3://Caso seja uma String
        case 4://Caso seja uma String
            text = (char*) malloc(sizeof(char) * strlen(input) + 1);
            strncpy(text, input, strlen(input) + 1);
            switch (data) {//Verfica que da do Tipo String será passado
                case 1://Caso seja o nome
                    (*new).nome = text;
                    break;
                case 2://Caso seja o Sobrenome
                    (*new).sobrenome = text;
                    break;
                case 3://Caso seja o Email
                    (*new).email = text;
                    break;
                case 4://Caso seja o Telefone
                    (*new).telefone = text;
                    break;
            }
            break;
        case 5://Caso seja o Salario
            (*new).salario = atof(input);
            break;
    }
}

//Cria uma Estrutura Data
DataNode * createData() {
    return malloc(sizeof(DataNode));
}

//Libera todos os ponteiros de um datanode
void FreeDataNode(DataNode *D){
    free((*D).nome);
    free((*D).sobrenome);
    free((*D).email);
    free((*D).telefone);
    free(D);
}

//Edita o DataNode Recebido
void editDataNode(int choose, DataNode *D) {
    switch (choose) {
        case 1:
        free((*D).nome);
            printf("Digite o Nome ( Max: 128 Caracters ): ");
            (*D).nome = createString(128);
            break;
        case 2:
            free((*D).sobrenome);
            printf("Digite o Sobrenome ( Max: 512 Caracters ): ");
            (*D).sobrenome = createString(512);
            break;
        case 3:
            free((*D).email);
            printf("Digite o Email ( Max: 128 Caracters ): ");
            (*D).email = createString(128);
            break;
        case 4:
            free((*D).telefone);
            printf("Digite o Telefone: ( Max: 16 Caracters ): ");
            (*D).telefone = createString(16);
            break;
        case 5:
            printf("Digite o Salario: ");
            scanf("%lf", &((*D).salario));
            getchar();
            break;
    }
}

//Cria um DataNode Individual
DataNode * setDataNode() {
    DataNode * new = createData();
    printf("Digite a Matricula: ");
    scanf("%d", &((*new).matricula));
    getchar();
    printf("Digite o Nome ( Max: 128 Caracters ): ");
    (*new).nome = createString(128);
    printf("Digite o Sobrenome ( Max: 512 Caracters ): ");
    (*new).sobrenome = createString(512);
    printf("Digite o Email ( Max: 128 Caracters ): ");
    (*new).email = createString(128);
    printf("Digite o Telefone: ( Max: 16 Caracters ): ");
    (*new).telefone = createString(16);
    printf("Digite o Salario: ");
    scanf("%lf", &((*new).salario));
    getchar();

    return new;
}

//Cria uma String no Tamanho máximo de sizeMax.
char * createString(int sizeMax) {
    char *string = malloc(sizeof(char) * (sizeMax + 1));
    fgets(string, 60, stdin);
    strtok(string, "\n");
    string = (char *) realloc(string, strlen(string) * sizeof(char) + 1);
    return string;
}

void giveData(void * Tads[]) {//Vai setar um Nó em alguma Estrutura Individualmente

    DataNode * Uno;

    showMenu(1);//Pergunbta ao Usuario qual será a Estrutura a ser Afetada
    int choose = validadeCommand(1, 3);

    switch (choose) {
        case 1:
            if ( Tads[1] == NULL )
                Tads[1] = Create(1, NULL);
            Uno = setDataNode();
            TimePass(0); //Começa a Cronometrar
            Insert(Tads, Uno, 1); //Insere na Lista
            showTime(TimePass(1));
            break;
        case 2:
            Uno = setDataNode();
            TimePass(0); //Começa a Cronometrar
            if ( Tads[0] == NULL ) { //Se a arvore não existe cria uma Raiz e Insere os Dados
                Tads[0] = Create(0, Uno);
                if ( Tads[0] == NULL ) {
                    printf("Espaço Insuficiente\n");
                }
            } else
                Insert(Tads, Uno, 0); //Insere na Arvore
            showTime(TimePass(1));
            break;
    }
}

void showData(DataNode * data) {//Exibe o DataNode
    printf("\n=====\nMatricula: %d\nNome: %s %s\nE-Mail: %s\nTelefone: %s\nSalario: %.2f\n=====\n", data->matricula, data->nome, data->sobrenome, data->email, data->telefone, data->salario);
}

#endif
