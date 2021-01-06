#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct no{
    struct no *esq;
    struct no *dir;
    int valor;
    int altura;
}arvore;
//Fun��o que calcula qual e maior
int maior(int a, int b){
    if(a>b)return a; return b;
}
//Fun��o que devine qual o tamanho da altura de uma folha
int altura(arvore *a){
    if(a==NULL)return -1;
    return(a->altura);
}
//Fun��o que balanceia
void balanceia(arvore **a){
    //Se altura esquera menos a altura a direia for igual a dois ela esta ou desbalanceada a direita ou dupla para a esquerda.
    if((altura((*a)->esq))- altura((*a)->dir)==2){
            //Apos entrar ele testa se o resultado for maior que  e rota��o para direita se for menor ou igual rotdupla esquerda
        if((altura((*a)->esq->esq) - altura((*a)->esq->dir)) > 0){
             rotdireita(&*a);
        }
        else{
           rotduplaesquerda(&*a);
        }
    //se a altura esquerda menos a altura direita for igual a -2  ela esta ou desbalanceada para esquerda ou dupla direita
    }else
        if((altura((*a)->esq))- altura((*a)->dir)==-2){
                //Apos entrar ela testa se o resultado for menor que 1 e rota��o para a esquerda e se for maior ou igual rotdupladireita
                if((altura((*a)->dir->esq) - altura((*a)->dir->dir)) < 0){
                rotesquerda(&*a);
            }else{
            rotdupladireita(&*a);
            }
        }
    (*a)->altura = maior( altura( (*a)->esq), altura( (*a)->dir ) ) + 1;
}
void inserir(arvore **a, int b){
    if((*a) == NULL){
        *a= (arvore*)malloc(sizeof(arvore));
        (*a)->valor = b;
        (*a)->esq = NULL;
        (*a)->dir = NULL;
        (*a)->altura=0;
        printf("adicionando - %d\n",b);
    }else
        if(b < (*a)->valor)
            inserir( &(*a)->esq, b);
        else
            if(b > (*a)->valor)
                inserir(&(*a)->dir, b);

    balanceia(&*a);
}

void rotdireita (arvore **a){
    arvore *aux =(*a)->esq;
    (*a)->esq=aux->dir;
    aux->dir=(*a);

    (*a)->altura = maior( altura( (*a)->dir), altura( (*a )->esq ) ) + 1;
    aux->altura = maior( altura( aux->esq), (*a)->altura ) + 1;
    (*a)=aux;
}
void rotesquerda(arvore **a){
    arvore *aux=(*a)->dir;
    (*a)->dir=aux->esq;
    aux->esq=(*a);

    (*a)->altura = maior( altura( (*a)->esq), altura( (*a)->dir ) ) + 1;
    aux->altura = maior( (*a)->altura,altura( aux->dir) ) + 1;
    (*a)=aux;
}
void rotduplaesquerda(arvore **a){
    rotesquerda(&(*a)->esq);
    rotdireita(&*a);
}
void rotdupladireita(arvore **a){
    rotdireita(&(*a)->dir);
    rotesquerda(&*a);
}
void imprima(arvore *a){
    if(a!=NULL){
        imprima(a->esq);
        printf("Valor = %d, Altura %d\n", a->valor, a->altura);
        imprima(a->dir);
    }
}
int main()
{   arvore *a = NULL;
    inserir(&a,3);
    inserir(&a,2);
    inserir(&a,1);
    inserir(&a,4);
    inserir(&a,5);
    inserir(&a,6);
    inserir(&a,7);
    imprima(a);
    /*
    char valor[10];


    printf("-----------------------------VAMOS INSERIR NUMA ARVORE AVL-------------------------------------\t\t");
    do{
    printf("\n______________________Insira um numero para ser inserido na arvore AVL_____________________________\n");
    printf("Ou digite sair par Sair               Ou i para imprimir a arvore\n");
    scanf("%s",valor);

    if(strcasecmp(valor,"i")==0)imprimea(a);
    else if(!strcasecmp(valor,"sair")==0)inserir(&a, atoi(valor));
    else printf("Saindo\n");
    }while(!strcasecmp(valor,"sair")==0);
    */
    return 0;
}
