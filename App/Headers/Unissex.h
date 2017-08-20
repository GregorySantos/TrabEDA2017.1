#ifndef UNISSEX_INCLUDED
#define UNISSEX_INCLUDED

//Dependências
#include "Tree.h"
#include "List.h"

void * Create(int type, DataNode * startData); //Cria alguma estrutura de Dado e retorna o seu ponteiro
void Insert(void * Tads[], void * Data, int type ); //Insere em Lista se Type == 1, caso contrário, espera inserir em AVL

//Insere em Lista se Type == 1, caso contrário, espera inserir em AVL
void Insert(void * Tads[], void * Data, int type ) {
    switch (type) {
        case 1:
            InsertList( (List *) Tads[type], createNodeList((DataNode *) Data));
            break;
        //case 0:
            // Tads[0] = InsertTree( (RootTree *) Tads[type], Data) @Função para Inserir na Arvore
            // break;
    }
}

//Cria alguma estrutura de Dado e retorna o seu ponteiro
void * Create(int type, DataNode * startData ) {
    switch (type) {
        case 1:
            return createList();
        //case 2:
            //return InsertTree( NULL, Data) @Função para Inserir na Arvore
    }
}

#endif
