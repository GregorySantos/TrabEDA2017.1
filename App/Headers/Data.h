#ifndef DATA_INCLUDED
#define DATA_INCLUDED

//Dependências
#include <stdio.h>
#include <string.h>

typedef struct datanode{
    int matricula;  //Armazenar a Matricula
    char *nome; //Armazenar o Nome
    char *sobrenome; //Armazenar o Sobrenome
    char *email; //Armazenar o Email
    char *telefone; //Armazena o Telefone
    double salario; //Armazena o Salario
}DataNode;

void setFileData( char * input, DataNode * new, int data );//Vai setando o DataNode

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

//Cria uma Estrutura Data
DataNode * createData() {
    return malloc(sizeof(DataNode));
}

//Libera todos os ponteiros de um datanode
FreeDataNode(Datanode *D){
    free(nome);
    free(sobrenome);
    free(email);
    free(telefone);
    free(D);
}

//Cria um DataNode Individual
DataNode * setDataNode() {
    DataNode * new = createData();
    printf("Digite a Matricula: ");
    scanf("%d", &((*new).matricula));
    printf("Digite o Nome ( Max: 128 Caracters ): ");
    (*new).nome = createString(128);
    printf("Digite o Sobrenome ( Max: 512 Caracters ): ");
    (*new).sobrenome = createString(512);
    printf("Digite o Email ( Max: 128 Caracters ): ");
    (*new).email = createString(128);
    printf("Digite o telefone: ( Max: 16 Caracters ): ");
    (*new).telefone = createString(16);
    printf("Digite o salario: ");
    scanf("%f", &((*new).salario));

    return new;
}

//Cria uma String no Tamanho máximo de sizeMax.
char * createString(int sizeMax) {
    char *string = malloc(sizeof(char) * (sizeMax + 1));
    fgets(string, 60, stdin);
    strtok(string, "\n");
    string = (char *) realloc(string, strlen(string) * sizeof(char) + 1);
    return string;
}
#endif
