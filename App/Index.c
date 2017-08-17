#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000
#define PATH 128

//Estruturas Definidas

typedef struct datanode{
    int matricula;  //Armazenar a Matricula
    char *nome; //Armazenar o Nome
    char *sobrenome; //Armazenar o Sobrenome
    char *email; //Armazenar o Email
    char *telefone; //Armazena o Telefone
    double salario; //Armazena o Salario
}DataNode;
typedef struct nodeList {
    struct nodeList *back; //Armazenar o Anterior
    struct nodeList *next; //Armazenar o Próxima
    struct datanode *data;
}NodeList; //Cada Node da Lista
typedef struct headList {
    struct nodeList *next; //Armazenar o Próxima
    int size; //Aramazna o Tamanho da Lista
}List;//Uma Lista

//Assinaturas de Funções
void debug(); //Função para Debug
void showMenu(int level); //Função para mostrar o Menu
int readFile(char output[], int choose); //Funçaõ para Ler algum Arquivo.
void giveFile(); //Função que recebe do usuario o nome do Arquivo
void breakLine ( char lineInput[] ); //Função que Trata cada Linha para Inserir em um Node
void mainExecute(int command); //Execução dos Principais Comandos
int validadeCommand(int start, int end); //Valida os Comandos Recebidos da Faixa [start, end]

int main() {

    debug();
    return 0;
}

//Funções Complementares

void debug() {

    showMenu(0);
    mainExecute(validadeCommand(1, 4));
}

//Execução dos Comandos Principais
void mainExecute(int command) {
    switch (command) {
        case 1:
            giveFile();
            break;
    }
}
//Fim das Funções Complementares
//Funções de Menu

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

//Fim das Funções de Menu

//Funções Para Leitura de Arquivo

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

  FILE *ptrFile;
  char Data[SIZE];
  if ( ( ptrFile = fopen(output, "r") ) == NULL ) {
    printf("Erro ao Ler o Arquivo!\n");
    return 0;
  } else {
    while ( !feof(ptrFile) ) {
      fgets(Data, SIZE, ptrFile);
      breakLine(Data);
      //Implementar a Passada dos Nodes Datas Criado para Nodes Especificos para cada Estrutura
      //Bug: Na última Interação o BreakLine imprime o número 1000, não sei se ficará assim quando os dados forem inseridos diretamente no TAD.
    }
    fclose(ptrFile);
    return 1;
  }
}

//Recebe a Linha e trata para enviar para algum Node os Dados ( Implementar a Criação da Data )
void breakLine ( char lineInput[] )
{

    char *ptrData;

    ptrData = strtok(lineInput, ",");
    while ( ptrData ) {
        //Implementar a Criação de Data
        printf("%s\n", ptrData);
        ptrData = strtok(NULL, ",");
    }
}
//Fim das Funções de Leitura de Arquivo

//Funções de Lista

//Função que Aloca um Espaço para criar a Lista e Retorna o Ponteiro da Lista
List * createList()
{
    List * temp = malloc(sizeof(List));

    if ( temp != NULL) {
      (*temp).size = 0;
      (*temp).next = NULL;
    }

    return temp;

}
NodeList * createNodeList(DataNode *d){
    NodeList *node = (NodeList*) malloc(sizeof(NodeList));
    if(node != NULL){
        node->data = d;
        node->next = NULL;
        node->back = NULL;
    }
    return node;
}

//Função para inserir um nó na lista, ordenado pela matrícula
int Insert(List *L, NodeList *NewNode){
    if(L == NULL)
        return 0;

    L->size++;
    if(L->next == NULL){ //lista vazia: insere início
        L->next = NewNode;
        return 1;
    }
    else{
        NodeList *previous, *current = L->next;
        while(current != NULL && current->data->matricula < NewNode->data->matricula){ //busca onde inserir
            previous = current;
            current = current->next;
        }
        if(current == L->next){ //o elemento é o menor da lista, insere no início
            NewNode->back = NULL;
            L->next->back = NewNode;
            NewNode->next = L->next;
            L->next = NewNode;
        }else{ // insere no meio ou final
            NewNode->next = previous->next;
            NewNode->back = previous;
            previous->next = NewNode;
            if(current != NULL)
                current->back = NewNode;
        }
        return 1;
    }
}

//Fim das Funções de Lista
