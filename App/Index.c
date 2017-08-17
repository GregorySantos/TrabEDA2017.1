#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000
#define PATH 128

//estrutura para os dados
typedef struct datanode{
	int matricula; //inteiro para a matricula
	char *nome; //ponteiro de char para o nome
	char *sobreNome; //ponteiro de char para o sobre nome
	char *email; //ponteiro de char para o email
	char *telefone; //ponteiro de char para o telefone(por causa do separador -)
	double salario; //double para receber o salario com centavos
}*DataNodePtr;

//estrutura de lista
typedef struct nodeList {
    struct nodeList *back; //Armazenar o Anterior
    struct nodeList *next; //Armazenar o Próxima
    struct datanode *data;
}NodeList; //Cada Node da Lista

//cabeça da lista
typedef struct headList {
    struct nodeList *next; //Armazenar o Próxima
    int size; //Aramazna o Tamanho da Lista
}List;//Uma Lista

//estrutura de arvore que recebera os dados;
typedef struct ArvNo{
	DataNodePtr dados;
	struct ArvNo *esqPtr; //ponteioro para o filho a esquerda (menor) da raiz
	struct ArvNo *dirPtr; //ponteiro para o filho a direita (maior) da raiz
	int altura; //inteiro para informar a altura do no
}*ArvNoPtr; //definindo o tipo como um ponteiro, assim, posso inicia-lo sem precisar do '*'

//bloco para os cabecalhos das funoes:
//genericas:
void debug();
void giveFile();
int readFile(char output[]);
void breakLine ( char lineInput[] );
//para lista:
List * createList();
NodeList * createNodeList(DataNode *d);
int Insert(List *L, NodeList *NewNode);
//para arvore:
void inicializarDados(DataNodePtr *dados);
void inicializarNO(ArvNoPtr *atual);
int maximo(int i, int j);
int pegarAltura(ArvNoPtr atual);
ArvNoPtr criarNo(DataNodePtr dados);
int fatorBalanceamento(ArvNoPtr raiz);
ArvNoPtr rotacaoDir(ArvNoPtr raiz);
ArvNoPtr rotacaoEsq(ArvNoPtr raiz);


int main() {

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
  	
  giveFile();

  debug();

  return 0;
}

//FUNCOES DE LISTA//////////////////////////////////////////////////////////////////////////////////////////////////////
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
NodeList * createNodeList(DataNode d){
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


//FUNCOES DE ARVORE//////////////////////////////////////////////////////////////////////////////////////////////////////

//funcao para alocar espaco numa estrutura dos dados
void inicializarDados(DataNodePtr *dados){
	(*dados)=(struct datanode *)malloc(sizeof(struct datanode));
}

//funcao para alocar espaco numa estrutura de no
void inicializarNO(ArvNoPtr *atual){
	(*atual)=(struct ArvNo *)malloc(sizeof(struct ArvNo));
	inicializarDados(&(*atual)->dados);
}

//funcao para pegar o maior valor entre dois inteiros
int maximo(int i, int j){
    return (i > j)? i : j;
}

//funcao que retorna a altura de um no
int pegarAltura(ArvNoPtr atual){
	if(atual==NULL){
		return 0;
	}else{
		return atual->altura;
	}
}

//funcao para criar um novo NO (geralmente raiz)
ArvNoPtr criarNo(DataNodePtr dados){
	ArvNoPtr criado;		//cria e aloca espaco numa estrutura ArvNoPtr
	inicializarNO(&criado);
	
	//copia todos os dados para o NO criado
	//funcao strcpy copia os dados de um vetor de char para outro, necessita biblioteca string.h
	(criado->dados)->matricula=dados->matricula;
	/*strcpy((criado->dados)->nome, dados->nome);
	strcpy((criado->dados)->sobreNome, dados->sobreNome);
	strcpy((criado->dados)->email, dados->email);
	strcpy((criado->dados)->telefone, dados->telefone);
	(criado->dados)->salario=dados->salario;*/
	criado->altura=1;
	criado->esqPtr=NULL;
	criado->dirPtr=NULL;
	return (criado);		//retorna o NO criado
}

//funcao para obter o fator de balanceamento do no
int fatorBalanceamento(ArvNoPtr raiz){
	if(raiz==NULL){
		return 0;
	}else{
		return (pegarAltura(raiz->esqPtr) - pegarAltura(raiz->dirPtr));		//ira retornar a altura da esquerda subtraindo a altura da direita
	}
}

//funcao para rotacionar arvore para a direita
ArvNoPtr rotacaoDir(ArvNoPtr raiz){
	ArvNoPtr auxEsq, auxDir;		//dois auxiliares
	auxEsq=raiz->esqPtr;		//este recebe a esquerda do NO raiz
	auxDir=auxEsq->dirPtr;		//este recebe a direita da esquerda do NO raiz (pode ser NULL ou nao)
	
	//faz a rotacao
	auxEsq->dirPtr=raiz;		//sobe a esquerda da raiz para ser a nova raiz, colocando a antiga raiz na direita
	raiz->esqPtr=auxDir;		//coloca o que estava a direita da nova raiz na esquerda da antiga raiz, para nao perder dados
	
	//atualizar a altura dos nos que tiveram modificoes nos filhos (nos que nao tiveram filhos alterador nao precisam atualizar)
	raiz->altura=1+maximo(pegarAltura(raiz->esqPtr), pegarAltura(raiz->dirPtr));
	auxEsq->altura=1+maximo(pegarAltura(auxEsq->esqPtr), pegarAltura(auxEsq->dirPtr));
	
	return auxEsq;		//retorna a nova raiz;
}

//funcao para rotacionar arvore para a esquerda
ArvNoPtr rotacaoEsq(ArvNoPtr raiz){
	ArvNoPtr auxDir, auxEsq;		//dois auxiliares
	auxDir=raiz->dirPtr;		//este recebe a direita do NO raiz
	auxEsq=auxDir->esqPtr;		//este recebe a esquerda da direita do NO raiz (pode ser NULL ou nao)

	//faz a rotacao
	auxDir->esqPtr=raiz;		//sobe a direita da raiz para ser a nova raiz, colocando a antiga raiz na esquerda
	raiz->dirPtr=auxEsq;		//coloca o que estava na esquerda da nova raiz na direita da antiga raiz, para nao perder dados

	//atualizar a altura dos nos que tiveram modificoes nos filhos (nos que nao tiveram filhos alterador nao precisam atualizar)
	raiz->altura=1+maximo(pegarAltura(raiz->esqPtr), pegarAltura(raiz->dirPtr));
	auxDir->altura=1+maximo(pegarAltura(auxDir->esqPtr), pegarAltura(auxDir->dirPtr));

	return auxDir;		//retorna a nova raiz;
}
