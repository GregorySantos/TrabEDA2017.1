#ifndef TREE_INCLUDED
#define TREE_INCLUDED
#include "Data.h"
#include <string.h>
#include <strings.h>

//estrutura de arvore que recebera os dados;
typedef struct ArvNo{
	DataNode *dados;
	struct ArvNo *esqPtr; //ponteioro para o filho a esquerda (menor) da raiz
	struct ArvNo *dirPtr; //ponteiro para o filho a direita (maior) da raiz
	int altura; //inteiro para informar a altura do no
}*ArvNoPtr; //definindo o tipo como um ponteiro, assim, posso inicia-lo sem precisar do '*'

void inicializarTreeNO(ArvNoPtr *atual);
int maximo(int i, int j);
int pegarAltura(ArvNoPtr atual);
int fatorBalanceamento(ArvNoPtr raiz);
ArvNoPtr rotacaoDir(ArvNoPtr raiz);
ArvNoPtr rotacaoEsq(ArvNoPtr raiz);
ArvNoPtr BuscaArvoreMatricula(ArvNoPtr treePtr, int matricula);
void ImpressaoArvoreOrdem(ArvNoPtr treePtr);

//funcao para alocar espaco numa estrutura de no
void inicializarTreeNO(ArvNoPtr *atual){
	(*atual)=(struct ArvNo *)malloc(sizeof(struct ArvNo));
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

//funcao para retornar um no a partir da matricula
ArvNoPtr BuscaArvoreMatricula(ArvNoPtr treePtr, int matricula){
    if(treePtr!=NULL){
        if(matricula==(treePtr->dados)->matricula){
            return treePtr;
        }else if(matricula<(treePtr->dados)->matricula){
            return BuscaArvoreMatricula(treePtr->esqPtr, matricula);
        }else{
            return BuscaArvoreMatricula(treePtr->dirPtr, matricula);
        }
    }else{
        return NULL;
    }
}

//funcao para imprimir toda a arvore por ordem da matricula
void ImpressaoArvoreOrdem(ArvNoPtr treePtr){
    if(treePtr != NULL){ //se a arvore nao estiver vazia, então percorra
        ImpressaoArvoreOrdem(treePtr->esqPtr);
        
		showData(treePtr->dados);
        
		ImpressaoArvoreOrdem(treePtr->dirPtr);
    } // fim do if
}

#endif
