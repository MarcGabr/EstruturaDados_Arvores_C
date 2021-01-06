#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//ESTRUTURA PARA CRIAR ARVORE
typedef struct no
{
    int  valor;
    struct no *esq;
    struct no *dir;
} arvore;
// FUNÇÃO PARA INSERIR ELEMENTO DE FORMA ORDENADA NA ARVORE
void inserir(arvore**a, int b)
{
    if(*a==NULL)
    {
        *a= (arvore*)malloc(sizeof(arvore));
        (*a)->esq = NULL;
        (*a)->dir = NULL;
        (*a)->valor = b;
        printf("adicionando - %d\n",b);
    }
    else
    {

        if(b <= (*a)->valor){
          printf("Entrei na esquerda\n");inserir(&((*a)->esq), b);
        }
        else if(b > (*a)->valor){
        printf("Entrei na direita\n");inserir(&((*a)->dir), b);

        }
    }
    }
//LER ARVORE EM ORDEM
void Iemordem(arvore *a){
    if(a!=NULL){
        Iemordem((a)->esq);
        printf("%d\n", a->valor);
        Iemordem((a)->dir);
    }
}
//LER ARVORE EM POS ORDEM
void Iposordem(arvore *a){
    if(a!=NULL){
        Iposordem((a)->esq);
        Iposordem((a)->dir);
        printf("%d\n", a->valor);
    }
}
//LER ARVORE EM PRE ORDEM
void Ipreordem(arvore *a){
    if(a!=NULL){
        printf("%d\n", a->valor);
        Ipreordem((a)->esq);
        Ipreordem((a)->dir);
    }
}
//CRIAR UMA ARVORE COM VALORES ALEATORIOS
void criar(arvore **a){
    int b;
    for(int i =0; i<15;i++){
      b = rand() % 99;
      inserir(&*a,b);
    }
}
//RECEBA UMA ARVORE DE UM DOCUMENTO DE TEXTO
void receba(arvore **a){
    FILE *arq;
    char Linha[10];
    int b;
    arq = fopen("AED2.txt", "rt");
    while (!feof(arq))
  {
      fgets(Linha, 100, arq);
        b = atoi(Linha);
        inserir(&*a,b);
  }
  fclose(arq);
}
//DEFINE A PROFUNDIDADE MAXIMA
    int profundidade(arvore *a){
       if(a==NULL || (a->esq==NULL && a->dir==NULL)){
            return 0;
       }else{
          return 1 + maior(profundidade((a)->esq), profundidade((a)->dir));
       }
    }
    //SE FOR MAIOR COMPARAR PARA RETORNAR O TAMANHO
    int maior(int a, int b){
        if(a>b){
            return a;
        }else{
            return b;
        }
    }
//PILHA
    typedef struct dos{
        int valor;
        struct dos *prox
    }Pilha;

//Testa se a arvore e ordenada ou nao. Se for retorna 1 se nao menos 1
int ordenado(arvore *a, Pilha **p){
    int d,b,c;
    if(a!=NULL){
        d = ordenado((a)->esq, &*p);
        if(d<0){
            return -1;
        }
        b = push(&*p, a->valor);
        if(b<0){
            return -1;
        }
        d  = ordenado((a)->dir, &*p);
        if(d<0){
            return -1;
        }
    }
    return 1;
}
int push(Pilha **p, int a){
        if(*p!=NULL && (*p)->valor > a){
                return -1;
        }
    Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
    novo->prox = *p;
    novo->valor = a;
    *p = novo;
    printf("Adicione %d\n", a);
    return 1;
    }

 void push2(Pilha **p, int a){
    Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
    novo->prox = *p;
    novo->valor = a;
    *p = novo;
    }
    void pop(Pilha **p){
   Pilha *aux;
   aux = *p;
   *p = (*p)->prox;
   free(aux);
   }
   void imprimircaminho(Pilha **p){
    Pilha *auxi;
    auxi = *p;
    printf("Caminho\n");
        while(auxi !=NULL){
            printf("%d\n", auxi->valor);
            auxi = auxi->prox;
        }
   }
  void caminho(arvore *a, Pilha **p){
      if(a!=NULL){
      push2(&*p, a->valor);
      caminho((a)->esq, &*p);
     // if(a->esq==NULL && a->dir==NULL){
        imprimircaminho(&*p);
      //}
      //printf("\n");
      caminho((a)->dir, &*p);
      pop(&*p);
      }
  }

int main()
{
    arvore *a = NULL;
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p = NULL;
    inserir(&a,77);
    inserir(&a,65);
    inserir(&a,82);
    inserir(&a,67);
    inserir(&a,79);
    inserir(&a,83);
    inserir(&a,85);
    inserir(&a,70);
    inserir(&a,84);
    inserir(&a,117);

     Iemordem(a);

    //receba(&a);
    //Ipreordem(a);
    //caminho(a,&p);

    //int c = ordenado(a, &p);
    //printf("%d", c);
    //Ipreordem(a);
    //Iposordem(a);

    //criar(&a);
    //int b = profundidade(a);
    //printf("Profundidade - %d", b);
    return 0;
}
