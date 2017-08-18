#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000
#define PATH 128

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

<<<<<<< HEAD
  //Função que Pede ao Usuario o Nome do Arquivo e Depois o Lê
  void giveFile();
  //Cria, Inicializa e Retorna um Ponteiro para uma Lista
  List * createList();
  //FUNÇÃO PARA DEBUG
  void debug();
  //Insere um nó de dados na lista
  int Insert(List * L, DataNode *d);
  //cria um novo nó
  NodeList * createNodeList(DataNode *d);
  //remove um nó pela matrícula
  int removeNode(List* L, int mat)
  
=======
NodeList * buscaMatricula ( int inputMatricula, List * root );//Função para Busca por Matricula em Lista
void giveFile(); //Função que Pede ao Usuario o Nome do Arquivo e Depois o Lê
List * createList();//Cria, Inicializa e Retorna um Ponteiro para uma Lista
void debug();//FUNÇÃO PARA DEBUG
int Insert(List *L, NodeList *NewNode); //Insere um nó de dados na lista
NodeList * createNodeList(DataNode *d);//cria um novo nó

int main() {
>>>>>>> master

  giveFile();

  debug();

  return 0;
}

void debug() {

  int readFile(char output[]);
  void giveFile();
  List * createList();

  List * d = createList();
  printf("O Tamanho é %d --DEBUG\n\n", (*d).size);

}

//Pede ao Usuario o Nome do Arquivo e Depois Lê
void giveFile()
{

  //Funçaõ para Ler algum Arquivo.
  int readFile(char output[]);

  char FilePath[PATH];

  printf("Digite o nome do arquivo com o formato '.csv': ");
  scanf("%s", FilePath);

  readFile(FilePath);
}

//Lê o Arquivo para encaminhar as Linhas com os Dados para a Função de Criar Node
int readFile(char output[])
{

  FILE *ptrFile;
  char Data[SIZE];

  //Função que Trata cada Linha para Inserir em um Node
  void breakLine ( char lineInput[] );

  if ( ( ptrFile = fopen(output, "r") ) == NULL ) {
    printf("Erro ao Ler o Arquivo!\n");
    return 0;
  } else {
    while ( !feof(ptrFile) ) {
      fgets(Data, SIZE, ptrFile);
      breakLine(Data);
      //Bug: Na última Interação o BreakLine imprime o número 1000, não sei se ficará assim quando os dados forem inseridos diretamente no TAD.
    }
    fclose(ptrFile);
    return 1;
  }
}

//Recebe a Linha e trata para enviar para algum Node os Dados
void breakLine ( char lineInput[] )
{

  char *ptrData;

  ptrData = strtok(lineInput, ",");
  while ( ptrData ) {
    //Implementar a Criação de Node
    printf("%s\n", ptrData);
    ptrData = strtok(NULL, ",");
  }
}

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

    NodeList *atual = buscaMatricula(NewNode->data->matricula, L);

    if ( atual == NULL ) {
        if ( L == NULL )
            return 0;
        L->next = NewNode;
    } else {
        if(atual->data->matricula == NewNode->data->matricula) // se a matricula já existir não insere
            return 0;
        if ( atual == L->next && atual->data->matricula > NewNode->data->matricula) { //o elemento é o menor da lista, insere no início
            NewNode->back = NULL;
            L->next->back = NewNode;
            NewNode->next = L->next;
            L->next = NewNode;
        } else { // insere no meio ou final
            NewNode->next = atual->next;
            NewNode->back = atual;
            atual->next = NewNode;
            if( NewNode->next != NULL)
                NewNode->next->back = NewNode;
        }
    }
    L->size++;
    return 1;
}

//Função que Busca o Registro pela Matricula, e retorna o POnteiro desse Registro... Caso não encontre, ele retorna o Ponteiro Anterior
NodeList * buscaMatricula( int inputMatricula, List * root ) {

    if ( root == NULL || (*root).next == NULL )
        return NULL;

    NodeList * res = (*root).next;

    while ( res->data->matricula != inputMatricula && res->data->matricula < inputMatricula && (*res).next != NULL ) {
        res = (*res).next;
    }

    if ( res->data->matricula == inputMatricula || (*res).next == NULL )
        if(res->data->matricula > inputMatricula)
            return res->back;
        else
            return res;
    else if ((*res).back != NULL)
        return (*res).back;
    else
        return res;
}

//função que remove um nó da lista, dada a matricula
int removeNode(List* L, int mat){
    NodeList *node = buscaMatricula(mat, L);

    if(node == NULL) // lista nao existe ou está vazia
        return 0;
    if(node->data->matricula != mat) //valor nao encontrado
        return 0;
    else
        if(node->back == NULL) // valor encontrado no primeiro nó
            L->next = node->next;
        else
            node->back->next = node->next; // valor encontrado no meio ou final

    if(node->next != NULL) // se o valor não é o último
        node->next->back = node->back;

    L->size--; //decrementa o tamanho da lista
    free(node);
    return 1;
}
