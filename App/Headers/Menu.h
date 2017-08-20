#ifndef MENU_INCLUDED
#define MENU_INCLUDED

//Assinaturas de Funções do Menu

int mainExecute(int command, void * Tads[]); //Execução dos Principais Comandos
int validadeCommand(int start, int end); //Valida os Comandos Recebidos da Faixa [start, end]
void showMenu(int level); //Função para mostrar o Menu

//Dependências
#include "File.h"
#include "Data.h"
#include <stdio.h>


//Execução dos Comandos Principais
int mainExecute(int command, void * Tads[]) {
    switch (command) {
        case 1:
            giveFile(Tads);
            return 1;
        case 2:
            giveData(Tads);
            //Função para Criar NodeData
            //FunçãO para Ligar o NodeData a algum Nó de alguma Tad que o Usuario escolher
            return 1;
        case 3:
            showMenu(1);
            validadeCommand(1, 4);//Escolhe qual Estrutura irá editar
            //Função que Recebe qual estrutura irá editar como parâmetro, e pergunta se deseja Editar ou Excluir os Dados
            return 1;
        case 4:
            showMenu(1);
            validadeCommand(1, 4);//Função que recebe qual a Estrutura irá ser visualizada
            //Função que Recebe qual Tad será visualizado, quantos serão visualizados e exibe na tela
            return 1;
        case 5:
            return 0;
    }
}

//Função que Valida os Dados que Recebe do Menu
int validadeCommand(int start, int end) {

    int res;

    printf("Digite o comando: ");
    scanf("%d", &res);

    while ( res < start || res > end ) {
        printf("Comando não identificado! Por favor, digite novamente: ");
        scanf("%d", &res);
    }

    return res;
}

//Função que Apresenta o Menu
void showMenu(int level) {

    switch ( level ) {
        case 0:
            printf("Lista de Opções: \n\n1 - Importar Arquivo CSV\n2 - Importar Dados\n3 - Editar Dados\n4 - Visualizar Dados\n5 - Sair\n\n");
            break;
        case 1:
            printf("Qual Estrutura deseja utilizar? \n\n1 - Lista Duplamente Encadeada\n2 - Árvore AVL\n3 - Ambas\n4 - Voltar\n\n");
            break;
        case 2:
            printf("Como deseja Editar?1 - Excluir\n2 - Atualizar\n3 - Voltar\n\n");
            break;
    }
}

#endif
