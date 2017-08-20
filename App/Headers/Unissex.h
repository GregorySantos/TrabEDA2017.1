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
void Select(void *Tads[], int type, int quant );//Visualiza os dados das TADS

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
    return 0;
}

//Cria alguma estrutura de Dado e retorna o seu ponteiro
void * Create(int type, DataNode * startData ) {
    switch (type) {
        case 1:
            return createList();
        //case 2:
            //return InsertTree( NULL, Data) @Função para Inserir na Arvore
    }
    return NULL;
}

//Deleta algum nó pela Matricula
void Delete(void *Tads[], int matricula, int type ) {
    switch (type) {
        case 1:
            if ( !(removeNodeList( (List *) Tads[type], matricula)) )
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
                        printf("Registro não encontrado!\n\n");
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
                        printf("Registro não encontrado!\n\n");
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
                        printf("Registro não encontrado!\n\n");
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
                        printf("Registro não encontrado!\n\n");
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
