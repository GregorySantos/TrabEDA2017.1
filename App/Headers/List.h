#ifndef LIST_INCLUDED
#define LIST_INCLUDED

//Estruturas Definidas

typedef struct nodeList {
    struct nodeList *back; //Armazenar o Anterior
    struct nodeList *next; //Armazenar o Próxima
    struct datanode *data;
}NodeList; //Cada Node da Lista

typedef struct headList {
    struct nodeList *next; //Armazenar o Próxima
    int size; //Aramazna o Tamanho da Lista
}List;//Uma Lista


List * createList(); //Cria, Inicializa e Retorna um Ponteiro para uma Lista
NodeList * createNodeList(DataNode *d);//cria um novo nó
int removeNode(List* L, int mat);//remove um nó pela matrícula
NodeList * buscaMatricula ( int inputMatricula, List * root );//Função para Busca por Matricula em Lista
int InsertList(List *L, NodeList *NewNode); //Função para inserir um nó na lista, ordenado pela matrícula
NodeList * buscaNome(List *L, char *n, char *sn); //função busca um nó na lista pelo nome e sobrenome, e retorna um ponteiro pro nó

//dependências
#include "Data.h"
#include <strings.h>


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

//Função para inserir um nó na lista, ordenado pela matrícula ( Retona 0 se Matricula já existe, ou Lista Não inicializada ou Espaço não Alocado )
int InsertList(List *L, NodeList *NewNode){

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

//função que remove um nó da lista, dada a matricula ( Retorna 0 caso lista não existe ou matrícula não existe )
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
    FreeDataNode(node->data);
    free(node);
    return 1;
}

//função busca um nó na lista pelo nome e sobrenome, e retorna um ponteiro pro nó
NodeList * buscaNome(List *L, char *n, char *sn){
    if( L == NULL || L->next == NULL)
        return NULL;

    NodeList *aux = L->next;

    while((strcasecmp(n, aux->data->nome) != 0) || (strcasecmp(sn, aux->data->sobrenome) != 0)  && aux->next != NULL){
        aux = aux->next;
    }

    if(aux->next == NULL && (strcasecmp(n, aux->data->nome) != 0) || (strcasecmp(sn, aux->data->sobrenome) != 0))
        return NULL;
    else
        return aux;
}

//Fim das Funções de Lista

#endif
