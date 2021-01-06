#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct no{
    struct no *esq;
    struct no *dir;
    int valor;
    int altura;
}arvore;

int maior(int a, int b){
    if(a>b)return a; return b;
}
int altura(arvore *a){
    if(a==NULL)return -1;
    return(a->altura);
}
void balanceia(arvore **a){
    if((altura((*a)->esq))- altura((*a)->dir)==2){
        if((altura((*a)->esq->esq) - altura((*a)->esq->dir)) > 0){
             rotdireita(&*a);
        }
        else{
           rotduplaesquerda(&*a);
        }
    }else
        if((altura((*a)->esq))- altura((*a)->dir)==-2){
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
    inserir(&a,16);
    inserir(&a,15);
    inserir(&a,14);
    imprima(a);
    return 0;
}