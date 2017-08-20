#ifndef UNISSEX_INCLUDED
#define UNISSEX_INCLUDED

//Dependências
#include "Tree.h"
#include "List.h"

void * Create(int type); //Cria alguma estrutura de Dado e retorna o seu ponteiro
void Insert(void * Head, void * Node, int type ); //Insere em Lista se Type == 1, caso contrário, espera inserir em AVL
void Delete(void *Tads[], int matricula, int type ); //Delta algum nó pela matricula

//Insere em Lista se Type == 1, caso contrário, espera inserir em AVL
void Insert(void * Head, void * Data, int type ) {
    if (type)
        InsertList( (List *) Head, createNodeList((DataNode *) Data));
    // else
        //Insert AVL
}

//Cria alguma estrutura de Dado e retorna o seu ponteiro
void * Create(int type) {
    if (type)
        return createList();
    //else
        //Return Função criar AVL
}

//Deleta algum nó pela Matricula
void Delete(void *Tads[], int matricula, int type ) {
    switch (type) {
        case 1:
            removeNode(Tads[1], int mat);
            break;
    }
}
#endif
