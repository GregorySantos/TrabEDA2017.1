#ifndef TREE_INCLUDED
#define TREE_INCLUDED

//estrutura de arvore que recebera os dados;
typedef struct ArvNo{
	DataNodePtr dados;
	struct ArvNo *esqPtr; //ponteioro para o filho a esquerda (menor) da raiz
	struct ArvNo *dirPtr; //ponteiro para o filho a direita (maior) da raiz
	int altura; //inteiro para informar a altura do no
}*ArvNoPtr; //definindo o tipo como um ponteiro, assim, posso inicia-lo sem precisar do '*'

//funcao para alocar espaco numa estrutura dos dados
void inicializarDados(DataNodePtr *dados){
	(*dados)=(struct datanode *)malloc(sizeof(struct datanode));
}

//funcao para alocar espaco numa estrutura de no
void inicializarNO(ArvNoPtr *atual){
	(*atual)=(struct ArvNo *)malloc(sizeof(struct ArvNo));
	inicializarDados(&(*atual)->dados);
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

//funcao para criar um novo NO (geralmente raiz)
ArvNoPtr criarNo(DataNodePtr dados){
	ArvNoPtr criado;		//cria e aloca espaco numa estrutura ArvNoPtr
	inicializarNO(&criado);
	
	criado->dados=dados;
	criado->altura=1;
	criado->esqPtr=NULL;
	criado->dirPtr=NULL;
	
	return (criado);		//retorna o NO criado
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

//funcao para inserir um novo no na arvore, feita com base em retorno
ArvNoPtr inserirNo(ArvNoPtr atual, DataNodePtr dadosPtr){
	
	if(dadosPtr!=NULL){		//se dadosPtr nao for nulo, ira realizar as operacoes
		if(atual==NULL){		//se a raiz estiver nula, o novo no sera inserido no lugar dela
			return (criarNo(dadosPtr));		//chama a funcao de criar novo NO
		}else if((atual->dados)->matricula==dadosPtr->matricula){
			printf("Matricula repetida, cadastro nao inserido\n");		//se a matricula for repetida, nao e inserida
			return atual;
		}else if(dadosPtr->matricula > (atual->dados)->matricula){
			atual->dirPtr=inserirNo(atual->dirPtr, dadosPtr);		//dispara recursivamente para a direita
		}else{
			atual->esqPtr=inserirNo(atual->esqPtr, dadosPtr);		//dispara recursivamente para a esquerda
		}
		atual->altura=1+maximo(pegarAltura(atual->esqPtr), pegarAltura(atual->dirPtr));		//atualiza a altura de um no

		//aqui o bloco para balancear a arvore
		int balanco;
		balanco=fatorBalanceamento(atual);		//descobre o fator de balanceamento deste no da arvore
		
		if((balanco > 1 )&&(dadosPtr->matricula < ((atual->esqPtr)->dados)->matricula)){//se esta desbalanceado para esq e seu filho esquerdo tambem
			return rotacaoDir(atual);		//rotaciona para a direita
		}else if((balanco < -1 )&&(dadosPtr->matricula > ((atual->dirPtr)->dados)->matricula)){//se esta desbalanceado para dir e seu filho direito tambem
			return rotacaoEsq(atual);		//rotaciona para a esquerda
		}else if((balanco > 1 )&&(dadosPtr->matricula > ((atual->esqPtr)->dados)->matricula)){//se esta desbalanceado para esq e seu filho esquerdo pela dir
			atual->esqPtr=rotacaoEsq(atual->esqPtr);		//rotaciona a esquerda para arrumar o NO
			return rotacaoDir(atual);		//rotaciona a direita para enfim balancear
		}else if((balanco < -1 )&&(dadosPtr->matricula < ((atual->dirPtr)->dados)->matricula)){//se esta desbalanceado para dir e seu filho direito pela esq
			atual->dirPtr=rotacaoDir(atual->dirPtr);		//rotaciona a direita para attumar o NO
			return rotacaoEsq(atual);		//rotaciona a esquerda para enfim balancear
		}
		//se nao houver nenhum desbalanceamento:
		return atual;
	}else{
		printf("Conteudo nao inserido pois a memoria esta cheia!\n");//caso nao consiga espaco na memoria, imprime a mensagem de erro
	}
}

#endif
