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
    int salario; //Armazena o Salario
}DataNode;

typedef struct nodeList {
    struct nodeList *back; //Armazenar o Anterior
    struct nodeList *next; //Armazenar o Próxima
    struct datanode data;
}NodeList; //Cada Node da Lista

typedef struct headList {
    struct nodeList *next; //Armazenar o Próxima
    int size; //Aramazna o Tamanho da Lista
}List;//Uma Lista

int main() {

  //Função que Pede ao Usuario o Nome do Arquivo e Depois o Lê
  void giveFile();
  //Cria, Inicializa e Retorna um Ponteiro para uma Lista
  List * createList();
  //FUNÇÃO PARA DEBUG
  void debug();
  //Insere um nó de dados na lista
  int Insert(List * L, DataNode d);
  

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
//Função para inserir um nó na lista, ordenado pela matrícula
int Insert(List * L, DataNode d){
    if(L == NULL) 
        return 0;

    NodeList *NewNode = (NodeList*) malloc(sizeof(NodeList));
    if(NewNode == NULL){
        printf("Memoria indisponivel. Nao eh possivel inserir.\n");
        return 0;
    }

    NewNode->data = d;
    L->size++;
    if(L->next == NULL){ //lista vazia: insere início
        NewNode->next = NULL;
        NewNode->back = NULL;
        L->next = NewNode;
        return 1;
    }
    else{
        NodeList *previous, *current = L->next;
        while(current != NULL && current->data.matricula < d.matricula){ //busca onde inserir
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
