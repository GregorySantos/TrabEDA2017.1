#ifndef FILE_INCLUDED
#define FILE_INCLUDED
#define SIZE 100000
#define PATH 128

//Assinaturas das Função de Arquivos
int readFile(char output[], int choose, void * Tads[]); //Funçaõ para Ler algum Arquivo.
void giveFile(void * Tads[]); //Função que recebe do usuario o nome do Arquivo

//Dependências
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Data.h"
#include "Menu.h"
#include "Unissex.h"
#include "Time.h"

DataNode * breakLine ( char lineInput[] ); //Função que Trata cada Linha para Inserir em um Node


//Pede ao Usuario o Nome do Arquivo e Depois Lê
void giveFile(void * Tads[]) {

    char FilePath[PATH];

    printf("Digite o nome do arquivo com o formato '.csv': ");
    scanf("%s", FilePath);
    showMenu(1);//Pergunbta ao Usuario qual será a Estrutura a ser Afetada
    int choose = validadeCommand(1, 4);
    if ( choose != 4 )//Pula se o usuario cancelar
        readFile(FilePath, choose, Tads);
}

//Lê o Arquivo para encaminhar as Linhas com os Dados para a Função de Criar Node
int readFile(char output[], int choose, void * Tads[]) {

    FILE *ptrFile;
    char Data[SIZE];

    switch (choose) { //Somente a Lista deve ser Inicializada sem um NodeData
        case 3:
        case 1:
            if ( Tads[1] == NULL )
                Tads[1] = (void *) Create(1, (DataNode *) NULL);
            break;
    }

    if ( ( ptrFile = fopen(output, "r") ) == NULL ) {
        printf("Erro ao Ler o Arquivo!\n");
        return 0;
    } else {
        TimePass(0); //Começa a Cronometrar
        fgets(Data, SIZE, ptrFile);//Pula a primeira Linha
        fgets(Data, SIZE, ptrFile);//Pula a segunda Linha
        while ( !feof(ptrFile) ) {
            fgets(Data, SIZE, ptrFile);
            switch (choose) {
                case 1:
                    Insert(Tads, breakLine(Data), 1); //Insere na Lista
                    break;
                case 2:
                    //if ( Tads[0] == NULL ) //Se a arvore não existe cria uma Raiz e Insere os Dados
                        //Tads[0] = Create(0, breakLine(data));
                    //else
                        //Insert(Tads, breakLine(Data), 0); //Insere na Arvore
                    break;
                case 3:
                    Insert(Tads, breakLine(Data), 1); //Insere na Lista
                    //if ( Tads[0] == NULL ) //Se a arvore não existe cria uma Raiz e Insere os Dados
                        //Tads[0] = Create(0, breakLine(data));
                    //else
                        //Insert(Tads, breakLine(Data), 0); //Insere na Arvore
                    break;
            }
        }
        showTime(TimePass(1));
        fclose(ptrFile);

        return 1;
    }
}

//Recebe a Linha e trata para enviar para algum Node os Dados
DataNode * breakLine ( char lineInput[] ) {

    DataNode * container = createData();
    int data = 0;
    int Quantidade; //Armazena quantos dados serão inseridos

    char *ptrData;

    ptrData = strtok(lineInput, ",");

    while ( ptrData ) { //Cada palavra da Linha é um Loop
        setFileData(ptrData, container, data);//Vai setando as informações no DataNode
        data = (data + 1) % 6; //Atualiza o Data
        ptrData = strtok(NULL, ",");
    }

    return container;
}

#endif
