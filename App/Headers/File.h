#ifndef FILE_INCLUDED
#define FILE_INCLUDED
#define SIZE 100000
#define PATH 128

//Dependências
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Data.h"
#include "Menu.h"
#include "Unissex.h"


//Assinaturas das Função de Arquivos

DataNode * breakLine ( char lineInput[] ); //Função que Trata cada Linha para Inserir em um Node
void giveFile(); //Função que recebe do usuario o nome do Arquivo
int readFile(char output[], int choose); //Funçaõ para Ler algum Arquivo.

//Pede ao Usuario o Nome do Arquivo e Depois Lê
void giveFile()
{

    char FilePath[PATH];

    printf("Digite o nome do arquivo com o formato '.csv': ");
    scanf("%s", FilePath);
    showMenu(1);//Pergunbta ao Usuario qual será a Estrutura a ser Afetada
    int choose = validadeCommand(1, 4);
    if ( choose != 4 )//Pula se o usuario cancelar
        readFile(FilePath, choose);
}

//Lê o Arquivo para encaminhar as Linhas com os Dados para a Função de Criar Node
int readFile(char output[], int choose)
{
	DataNode *d;
    FILE *ptrFile;
    char Data[SIZE];
    List *rootList;
    //ponteiro para árvore aqui

    switch (choose) {
        case 1:
            rootList = (List *) Create(1);
            break;
        case 2:
            // aqui vem a opção de criar árvore
            break;
        case 3:
            rootList = (List *) Create(1);
            // aqui vem a opção de criar árvore
            break;
    }

    if ( ( ptrFile = fopen(output, "r") ) == NULL ) {
        printf("Erro ao Ler o Arquivo!\n");
        return 0;
    } else {
        fgets(Data, SIZE, ptrFile);//Pula a primeira Linha
        fgets(Data, SIZE, ptrFile);//Pula a segunda Linha
        while ( !feof(ptrFile) ) {
            fgets(Data, SIZE, ptrFile);
            d = breakLine(Data);
            switch (choose) {
                case 1:
                    Insert(rootList, d, 1);
                    break;
                case 2:
                    //Insert(rootAvl, d, 0);
                    break;
                case 3:
                    Insert(rootList, d, 1);
                    //Insert(rootAvl, d, 0);
                    break;
            }
        }

        fclose(ptrFile);
        return 1;
    }
}

//Recebe a Linha e trata para enviar para algum Node os Dados
DataNode * breakLine ( char lineInput[] )
{

    DataNode * container = malloc(sizeof(DataNode));
    int data = 0;
    int Quantidade; //Armazena quantos dados serão inseridos

    char *ptrData;

    ptrData = strtok(lineInput, ",");

    while ( ptrData ) { //Cada palavra da Linha é um Loop
        setFileData(ptrData, container, data);//Vai setando as informações no DataNode
        data = (data + 1) % 6; //Atualiza o Data
        printf("%s\n", ptrData);
        ptrData = strtok(NULL, ",");
    }

    return container;
}

#endif
