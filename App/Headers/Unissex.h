#ifndef UNISSEX_INCLUDED
#define UNISSEX_INCLUDED

//Dependencias
#include "Time.h"
#include "Data.h"
#include "Tree.h"
#include "List.h"

void Delete(void *Tads[], int matricula, int type ); //Delta algum no pela matricula
void * Create(int type, DataNode * startData); //Cria alguma estrutura de Dado e retorna o seu ponteiro
int Insert(void * Tads[], DataNode * Data, int type ); //Insere em Lista se Type == 1, caso contrario, espera inserir em AVL
int Update(void *Tads[], int matricula, int type ); //Retorna 0 caso nao tenha algum erro de atualizacao
void Select(void *Tads[], int type, int quant );//Visualiza os dados das TADS

//Insere em Lista se Type == 1, caso contrario, espera inserir em AVL
int Insert(void * Tads[], DataNode * Data, int type ) {
    void * novo;
    switch (type) {
        case 1:
            novo = createNodeList(Data);
            if ( !(InsertList( (List *) Tads[type], (NodeList *) novo) ) )       { //Comunica Erro
                printf("\n=====Erro ao Inserir na Lista! Espaco Insuficiente ou Matricula %d ja Existente!=====\n", ((*(DataNode *) Data).matricula));
                deleteNodeList((NodeList *) novo);
                return 0;
            }
            return 1;
        case 0:
            if ( BuscaArvoreMatricula(Tads[type], Data->matricula) == NULL ){
                Tads[type] = InserirNaArvore((ArvNoPtr) Tads[type], Data);
                if ( Tads[type] == NULL ) {
                    printf("\n=====Erro ao Inserir na Arvore! Espaco Insuficiente!=====\n");
                }
                return 1;
            } else {
                printf("\n=====Erro ao Inserir na Arvore! Espaco Insuficiente ou Matricula %d ja Existente!=====\n", ((*(DataNode *) Data).matricula));
                FreeDataNode(Data);
                return 0;
            }
            break;
    }
    return 0;
}

//Cria alguma estrutura de Dado e retorna o seu ponteiro
void * Create(int type, DataNode * startData ) {
    switch (type) {
        case 1:
            return createList();
        case 0:
            return InserirNaArvore(NULL, startData);
    }
    return NULL;
}

//Deleta algum no pela Matricula
void Delete(void *Tads[], int matricula, int type ) {
    switch (type) {
        case 1:
            if ( !(removeNodeList( (List *) Tads[type], matricula)) )
                printf("\n=====Erro ao Remover da Lista! Lista ou Matricula %d nao Existe!", matricula);
            break;
        case 0:
            if ( BuscaArvoreMatricula(Tads[type], matricula) != NULL ) {
                Tads[type] = DelecaoArvore( (ArvNoPtr) Tads[type], matricula);
            } else {
                printf("Registro nao encontrado!\n");
            }
            break;
    }
}

//Atualiza o no fazendo uma busca interna, retorna 0 se a matricula passada nao existe
int Update(void *Tads[], int matricula, int type ) {

    void * find;
    showMenu(3);
    int choose = validadeCommand(1, 5);

    if (Tads[type] == NULL )//Se o Tad que sera utilizado nao existir, ja retorna Erro
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
                    editDataNode(choose, ((NodeList *) find)->data); //Funcao para Editar o DataNode
                break;
            case 2: //Edita da Arvore
                find =  BuscaArvoreMatricula(Tads[type], matricula); //Verifica se realmente a matricula existe na Lista
                if ( find == NULL ) {
                    showTime(TimePass(1));
                    return 0;
                } else
                    editDataNode(choose, ((ArvNoPtr) find)->dados); //Funcao para Editar o DataNode
        }
        showTime(TimePass(1));
        showMenu(3);
        choose = validadeCommand(1, 5);
    }
    return 1;
}

//Visualiza os dados das TADS
void Select(void *Tads[], int type, int quant ) {

    static int matricula;
    char *nome, *sobrenome;
    void * res;

    switch (type) {
        case 1://Escolheu a Lista
            switch (quant) {
                case 1://Matricula
                    printf("Digite a matricula: ");
                    scanf("%d", &matricula);
                    getchar();
                    TimePass(0);
                    res = buscaEqualsList(matricula, Tads[type]);
                    if ( res != NULL ) {
                        showData(((NodeList *) res)->data);
                    } else {
                        printf("Registro nao encontrado!\n\n");
                    }
                    showTime(TimePass(1));
                    break;
                case 2://Nome
                    printf("Digite o Nome ( Max: 128 Caracters ): ");
                    nome = createString(128);
                    printf("Digite o Sobrenome ( Max: 512 Caracters ): ");
                    sobrenome = createString(512);
                    TimePass(0);
                    res = buscaNomeList(Tads[type], nome, sobrenome);
                    free(nome);
                    free(sobrenome);
                    if ( res != NULL ) {
                        showData(((NodeList *) res)->data);
                    } else {
                        printf("Registro nao encontrado!\n\n");
                    }
                    showTime(TimePass(1));
                    break;
                case 3://Todos
                    TimePass(0);
                    showAllList((List *) Tads[type]);
                    showTime(TimePass(1));
                    break;
            }
            break;
        case 0://Escolheu a Arvore
            switch (quant) {
                case 1://Matricula
                    printf("Digite a matricula: ");
                    scanf("%d", &matricula);
                    getchar();
                    TimePass(0);
                    res = BuscaArvoreMatricula(Tads[type], matricula);
                    if ( res != NULL ) {
                        showData(((ArvNoPtr) res)->dados);
                    } else {
                        printf("Registro nao encontrado!\n\n");
                    }
                    showTime(TimePass(1));
                    break;
                case 2://Nome
                    printf("Digite o Nome ( Max: 128 Caracters ): ");
                    nome = createString(128);
                    printf("Digite o Sobrenome ( Max: 512 Caracters ): ");
                    sobrenome = createString(512);
                    TimePass(0);
                    res = BuscaArvoreNome((ArvNoPtr) Tads[type], nome, sobrenome);
                    free(nome);
                    free(sobrenome);
                    if ( res != NULL ) {
                        showData(((ArvNoPtr) res)->dados);
                    } else {
                        printf("Registro nao encontrado!\n\n");
                    }
                    showTime(TimePass(1));
                    break;
                case 3://Todos
                    TimePass(0);
                    showAllTree((ArvNoPtr) Tads[type]);
                    showTime(TimePass(1));
                    break;
            }
            break;
    }
}

#endif
