#ifndef TREE_INCLUDED
#define TREE_INCLUDED

//estrutura de arvore que recebera os dados;
typedef struct ArvNo{
	DataNode *dados;
	struct ArvNo *esqPtr; //ponteioro para o filho a esquerda (menor) da raiz
	struct ArvNo *dirPtr; //ponteiro para o filho a direita (maior) da raiz
	int altura; //inteiro para informar a altura do no
}*ArvNoPtr; //definindo o tipo como um ponteiro, assim, posso inicia-lo sem precisar do '*'

#include "Data.h"
#include <string.h>
#include <strings.h>

void inicializarTreeNO(ArvNoPtr *atual);
int maximo(int i, int j);
int pegarAltura(ArvNoPtr atual);
int fatorBalanceamento(ArvNoPtr raiz);
ArvNoPtr rotacaoDir(ArvNoPtr raiz);
ArvNoPtr rotacaoEsq(ArvNoPtr raiz);
ArvNoPtr BuscaArvoreMatricula(ArvNoPtr treePtr, int matricula);
void ImpressaoArvoreOrdem(ArvNoPtr treePtr);
void showAllTree(ArvNoPtr treePtr);
ArvNoPtr BuscaArvoreNome(ArvNoPtr treePtr, char *n, char *sn);
ArvNoPtr BalancearArvore(ArvNoPtr treePtr);
ArvNoPtr InserirNaArvore(ArvNoPtr treePtr, DataNode *data);

//funcao para alocar espaco numa estrutura de no
void inicializarTreeNO(ArvNoPtr *atual){
	(*atual)=(struct ArvNo *)malloc(sizeof(struct ArvNo));
}

//funcao para criar um novo NO de Arvore (geralmente raiz)
ArvNoPtr criarArvoreNo(){
	ArvNoPtr criado;		//cria e aloca espaco numa estrutura ArvNoPtr
	inicializarTreeNO(&criado);

	criado->altura=1;
	criado->esqPtr=NULL;
	criado->dirPtr=NULL;
	return (criado);		//retorna o NO criado
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
    if(treePtr != NULL){ //se a arvore nao estiver vazia, entï¿½o percorra
        ImpressaoArvoreOrdem(treePtr->esqPtr);

		showData(treePtr->dados);

		ImpressaoArvoreOrdem(treePtr->dirPtr);
    } // fim do if
}

//funcao de imprimir toda a arvore e avisar se estiver vazia
void showAllTree(ArvNoPtr treePtr) {
    if ( treePtr == NULL ) {
        printf("Arvore Vazia!\n");
    } else {
        ImpressaoArvoreOrdem(treePtr);
    }
}

//funcao para buscar elemento na arvore a partir do nome
//segue a ideia da impressao em ordem (esquerda, raiz, direita)
ArvNoPtr BuscaArvoreNome(ArvNoPtr treePtr, char *n, char *sn){
	//se estiver vazia, retorna o null
	if(treePtr==NULL){
		return NULL;
	}
	
	ArvNoPtr aux;
	aux=BuscaArvoreNome(treePtr->esqPtr, n, sn); //testa toda a esquerda 
	
	if(aux!=NULL){ //se nao retornou NULL, é porque é o elemento desejado
		return aux;
	}
	
	//testa se a raiz é o elemento desejado, se sim, retorna a raiz
	if((strcasecmp(n, (treePtr->dados)->nome) == 0) && (strcasecmp(sn, (treePtr->dados)->sobrenome) == 0)){
		return treePtr;
	}
	
	aux=BuscaArvoreNome(treePtr->dirPtr, n, sn);//testa agora a direita
	if(aux!=NULL){ //se nao retornou NULL, é porque é o elemento desejado
		return aux;
	}
	
	// se no final só encontrou NULL, então não encontrou o elemento, retorna NULL
	return NULL;
}

ArvNoPtr BalancearArvore(ArvNoPtr treePtr){
	
	int balanco=fatorBalanceamento(treePtr);
	
	if((balanco > 1) && (fatorBalanceamento(treePtr->esqPtr) >= 0)){//se esta desbalanceado para esq e seu filho esquerdo tambem
		return rotacaoDir(treePtr);		//rotaciona para a direita
	}
	
	if((balanco < -1) && (fatorBalanceamento(treePtr->dirPtr) <= 0)){//se esta desbalanceado para dir e seu filho direito tambem
		return rotacaoEsq(treePtr);		//rotaciona para a esquerda
	}
	
	if((balanco > 1) && (fatorBalanceamento(treePtr->esqPtr) < 0)){//se esta desbalanceado para esq e seu filho esquerdo pela dir
		treePtr->esqPtr=rotacaoEsq(treePtr->esqPtr);		//rotaciona a esquerda para arrumar o NO
		return rotacaoDir(treePtr);		//rotaciona a direita para enfim balancear
	}
	
	if((balanco < -1) && (fatorBalanceamento(treePtr->dirPtr) > 0)){//se esta desbalanceado para dir e seu filho direito pela esq
		treePtr->dirPtr=rotacaoDir(treePtr->dirPtr);		//rotaciona a direita para attumar o NO
		return rotacaoEsq(treePtr);		//rotaciona a esquerda para enfim balancear
	}
	
	//se nao houver nenhum desbalanceamento:
	return treePtr;	
}

//funcao para inserir os elementos na arvore em ordem de matricula
ArvNoPtr InserirNaArvore(ArvNoPtr treePtr, DataNode *data){
	
	//se os dados foram NULL, nao ha o que ser inserido, retorna a raiz normalmente
	if(data==NULL){
		printf("\nNao ha dados para inserir\n");
		return treePtr;
	}
	
	//se a raiz for nula, ele recebera os dados
	if(treePtr==NULL){
		treePtr=criarArvoreNo();
		treePtr->dados=data;
		return treePtr;
	}
	
	//se a matricula ja existir, nao e inserido e retorna a raiz original
	if((treePtr->dados)->matricula == data->matricula){
		printf("\nMatricula repetida, cadastro nao inserido\n");	//se a matricula for repetida, nao e inserida
		return treePtr;
	}
	
	//se chegar aqui, a matricula deverá ir para a esquerda ou direita
	if(data->matricula > (treePtr->dados)->matricula){
		treePtr->dirPtr=InserirNaArvore(treePtr->dirPtr, data);	//dispara recursivamente para a direita
	}else{
		treePtr->esqPtr=InserirNaArvore(treePtr->esqPtr, data);	//dispara recursivamente para a esquerda
	}
	
	treePtr->altura=1+maximo(pegarAltura(treePtr->esqPtr), pegarAltura(treePtr->dirPtr));	//atualiza a altura de um no da arvore
	treePtr=BalancearArvore(treePtr);	//chama a funcao de balancear a arvore
	
	return treePtr;	//retorna a raiz
}

#endif
