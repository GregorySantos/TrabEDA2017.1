#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100000
#define PATH 128

//Estruturas Definidas

typedef struct datanode{
    int matricula; //inteiro para a matricula
	char *nome; //ponteiro de char para o nome
	char *sobrenome; //ponteiro de char para o sobre nome
	char *email; //ponteiro de char para o email
	char *telefone; //ponteiro de char para o telefone(por causa do separador -)
	double salario; //double para receber o salario com centavos
}DataNode;

typedef DataNode *DataNodePtr; //declarando a estrutura de dados como ponteiro

//estrutura de lista
typedef struct nodeList {
    struct nodeList *back; //Armazenar o Anterior
    struct nodeList *next; //Armazenar o Pr�xima
    struct datanode *data;
}NodeList; //Cada Node da Lista

//cabe�a da lista
typedef struct headList {
    struct nodeList *next; //Armazenar o Pr�xima
    int size; //Aramazna o Tamanho da Lista
}List;//Uma Lista

//estrutura de arvore que recebera os dados;
typedef struct ArvNo{
	DataNodePtr dados;
	struct ArvNo *esqPtr; //ponteioro para o filho a esquerda (menor) da raiz
	struct ArvNo *dirPtr; //ponteiro para o filho a direita (maior) da raiz
	int altura; //inteiro para informar a altura do no
}*ArvNoPtr; //definindo o tipo como um ponteiro, assim, posso inicia-lo sem precisar do '*'

//Assinaturas de Fun��es

//Genericas:
int mainExecute(int command); //Execu��o dos Principais Comandos
int validadeCommand(int start, int end); //Valida os Comandos Recebidos da Faixa [start, end]
void debug(); //FUNÇÃO PARA DEBUG
void giveFile(); //Função que recebe do usuario o nome do Arquivo
int readFile(char output[], int choose); //Funçaõ para Ler algum Arquivo.
void showMenu(int level); //Função para mostrar o Menu
//lista:
DataNode * breakLine ( char lineInput[] ); //Função que Trata cada Linha para Inserir em um Node
List * createList(); //Cria, Inicializa e Retorna um Ponteiro para uma Lista
NodeList * createNodeList(DataNode *d);//cria um novo nó
int removeNode(List* L, int mat);//remove um nó pela matrícula
NodeList * buscaMatricula ( int inputMatricula, List * root );//Função para Busca por Matricula em Lista
int Insert(List *L, NodeList *NewNode); //Insere um nó de dados na lista
void setFileData( char * input, DataNode * new, int data );//Vai setando o DataNode
//Arvore:
void inicializarDados(DataNodePtr *dados);
void inicializarNO(ArvNoPtr *atual);
int maximo(int i, int j);
int pegarAltura(ArvNoPtr atual);
ArvNoPtr criarNo(DataNodePtr dados);
int fatorBalanceamento(ArvNoPtr raiz);
ArvNoPtr rotacaoDir(ArvNoPtr raiz);
ArvNoPtr rotacaoEsq(ArvNoPtr raiz);

int main(){

	debug();
	return 0;
}

//Fun��es Complementares

void debug() {

    do {
        showMenu(0);
    }while ( mainExecute(validadeCommand(1, 5)) );
}

//Execução dos Comandos Principais
int mainExecute(int command) {
    switch (command) {
        case 1:
            giveFile();
            return 1;
        case 2:
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
        fgets(Data, SIZE, ptrFile);//Pula a primeira Linha
        fgets(Data, SIZE, ptrFile);//Pula a segunda Linha
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
//Fim das Funções de Leitura de Arquivo

//Funções de Lista

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
            text = (char*) malloc(sizeof(char) * strlen(input));
            strncpy(text, input, strlen(input));
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

//Fim das Funções de Lista

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

	(criado->dados)->nome=malloc(sizeof(dados->nome));
	strcpy((criado->dados)->nome, dados->nome);

	(criado->dados)->sobrenome=malloc(sizeof(dados->sobrenome));
	strcpy((criado->dados)->sobrenome, dados->sobrenome);

	(criado->dados)->email=malloc(sizeof(dados->email));
	strcpy((criado->dados)->email, dados->email);

	(criado->dados)->telefone=malloc(sizeof(dados->telefone));
	strcpy((criado->dados)->telefone, dados->telefone);

	(criado->dados)->salario=dados->salario;

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
