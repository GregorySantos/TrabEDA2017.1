#include <stdio.h>
#include <string.h>
#define SIZE 100000
#define PATH 128

int main() {

  //Funçaõ para Ler algum Arquivo.
  int readFile(char output[]);
  char FilePath[PATH];

  printf("Digite o nome do arquivo com o formato '.csv': ");
  scanf("%s", FilePath);

  readFile(FilePath);
  return 0;
}

//Lê o Arquivo para encaminhar as Linhas com os Dados para a Função de Criar Node
int readFile(char output[]) {

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
void breakLine ( char lineInput[] ) {

  char *ptrData;

  ptrData = strtok(lineInput, ",");
  while ( ptrData ) {
    //Implementar a Criação de Node
    printf("%s\n", ptrData);
    ptrData = strtok(NULL, ",");
  }
}
