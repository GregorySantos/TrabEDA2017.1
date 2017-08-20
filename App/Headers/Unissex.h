#ifndef UNISSEX_INCLUDED
#define UNISSEX_INCLUDED

//Dependências
#include "Time.h"
#include "Data.h"
#include "Tree.h"
#include "List.h"

void Delete(void *Tads[], int matricula, int type ); //Delta algum nó pela matricula
void * Create(int type, DataNode * startData); //Cria alguma estrutura de Dado e retorna o seu ponteiro
int Insert(void * Tads[], DataNode * Data, int type ); //Insere em Lista se Type == 1, caso contrário, espera inserir em AVL
int Update(void *Tads[], int matricula, int type ); //Retorna 0 caso não tenha algum erro de atualização

//Insere em Lista se Type == 1, caso contrário, espera inserir em AVL
int Insert(void * Tads[], DataNode * Data, int type ) {
    void * novo;
    switch (type) {
        case 1:
            novo = createNodeList(Data);
            if ( !(InsertList( (List *) Tads[type], (NodeList *) novo) ) )       { //Comunica Erro
                printf("\n=====Erro ao Inserir na Lista! Espaço Insuficiente ou Matrícula %d já Existente!=====\n", ((*(DataNode *) Data).matricula));
                deleteNodeList((NodeList *) novo);
                return 0;
            }
            return 1;
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

//Atualiza o nó fazendo uma busca interna, retorna 0 se a matrícula passada não existe
int Update(void *Tads[], int matricula, int type ) {

    void * find;
    showMenu(3);
    int choose = validadeCommand(1, 5);

    if (Tads[type] == NULL )//Se o Tad que será utilizado não existir, já retorna Erro
        return 0;

    while ( choose != 5 ) {
        TimePass(0);
        switch (type) {
            case 1:
                find = buscaEqualsList(matricula, Tads[type]); //Verifica se realmente a matricula existe na Lista
                if ( find == NULL ) {
                    showTime(TimePass(1));
                    return 0;
                } else
                    editDataNode(choose, ((NodeList *) find)->data); //Função para Editar o DataNode
                break;
            case 2: //Edita da Arvore
                find =  BuscaArvoreMatricula(Tads[type], matricula); //Verifica se realmente a matricula existe na Lista
                if ( find == NULL ) {
                    showTime(TimePass(1));
                    return 0;
                } else
                    editDataNode(choose, ((ArvNoPtr) find)->dados); //Função para Editar o DataNode
        }
        showTime(TimePass(1));
        showMenu(3);
        choose = validadeCommand(1, 5);
    }
    return 1;
}
#endif
