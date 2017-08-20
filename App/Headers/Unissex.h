#ifndef UNISSEX_INCLUDED
#define UNISSEX_INCLUDED

//Dependências
#include "Data.h"
#include "Tree.h"
#include "List.h"

void Delete(void *Tads[], int matricula, int type ); //Delta algum nó pela matricula
void * Create(int type, DataNode * startData); //Cria alguma estrutura de Dado e retorna o seu ponteiro
void Insert(void * Tads[], void * Data, int type ); //Insere em Lista se Type == 1, caso contrário, espera inserir em AVL

//Insere em Lista se Type == 1, caso contrário, espera inserir em AVL
void Insert(void * Tads[], void * Data, int type ) {
    switch (type) {
        case 1:
            if ( !(InsertList( (List *) Tads[type], createNodeList((DataNode *) Data))) ) { //Comunica Erro
                printf("\n=====Erro ao Inserir na Lista! Espaço Insuficiente ou Matrícula %d já Existente!=====\n", ((*(DataNode *) Data).matricula) );
            }
            break;
        //case 0:
            // Tads[0] = InsertTree( (RootTree *) Tads[type], Data) @Função para Inserir na Arvore | Tratamento de Erro Interno
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

//Deleta algum nó pela Matricula
void Delete(void *Tads[], int matricula, int type ) {
    switch (type) {
        case 1:
            if ( !(removeNode( (List *) Tads[type], matricula)) )
                printf("\n=====Erro ao Remover da Lista! Lista ou Matrícula %d não Existe!", matricula);
            break;
        //case 0:
            // Tads[0] = RemoveNodeTree( (RootTree *) Tads[type], Data) @Função para Remover da Arvore | Tratamento de Erro Interno
            // break;
    }
}


#endif
