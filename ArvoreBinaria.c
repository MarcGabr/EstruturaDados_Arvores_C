
//TRABALHO DE ARVORE BINARIA
//UFT - UNIVERSIDADE FERDERAL DO TOCANTINS
//ALUNO: MARCOS GABRIEL PEREIRA ARAUJO

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
typedef struct no
{
    int  valor;
    struct no *esq;
    struct no *dir;
} arvore;
typedef struct dos{
    int valor;
    struct dos *prox
}Pilha;
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
        if(b < (*a)->valor)
        {inserir(&((*a)->esq), b);}
        else
        {inserir(&((*a)->dir), b);}
    }
}
void criar(arvore **a, int b){
    for(int i =0; i<b;i++){
      inserir(&*a,rand() % 100);
    }
}
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
 int profundidade(arvore *a){
       if(a==NULL || (a->esq==NULL && a->dir==NULL)){
            return 0;
       }else{
          return 1 + maior(profundidade((a)->esq), profundidade((a)->dir));
       }
    }
    int maior(int a, int b){
        if(a>b){
            return a;
        }else{
            return b;
        }
    }
void Iemordem(arvore *a){
    if(a!=NULL){
        Iemordem((a)->esq);
        printf("%d\n", a->valor);
        Iemordem((a)->dir);
    }
}
void Iposordem(arvore *a){
    if(a!=NULL){
        Iposordem((a)->esq);
        Iposordem((a)->dir);
        printf("%d\n", a->valor);
    }
}
void Ipreordem(arvore *a){
    if(a!=NULL){
        printf("%d\n", a->valor);
        Ipreordem((a)->esq);
        Ipreordem((a)->dir);
    }
}
 void caminho(arvore *a, Pilha **p){
      if(a!=NULL){
      push2(&*p, a->valor);
      caminho((a)->esq, &*p);
      if(a->esq==NULL && a->dir==NULL){
        imprimircaminho(&*p);
      }
      caminho((a)->dir, &*p);
      pop(&*p);
      }
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
   //FUNÇÃO PARA TESTAR testar se uma dada árvore binária é uma "árvore binária de procura"
   //NAO FOI IMPLEMENTADO POIS O PROGRAMA NAO CRIA ARVORES DESORDENADAS
   //ELE RETORNA -1 CASO NAO ESTEJA ORDENADA OU 1 CASO ESTEJA.
int ordenado(arvore *a, Pilha **p){
    int d,b,c;
    if(a!=NULL){
        d = ordenado((a)->esq, &*p);
        if(d<0){return -1;}
        b = push(&*p, a->valor);
        if(b<0){return -1;}
        d  = ordenado((a)->dir, &*p);
        if(d<0){return -1;}
    }
    return 1;
}
int push(Pilha **p, int a){
        if(*p!=NULL && (*p)->valor > a){return -1;}
    Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
    novo->prox = *p;
    novo->valor = a;
    *p = novo;
    return 1;
    }

int main()
{
    arvore *a = NULL;
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p = NULL;
    int opcao, prof;char opcao2[20];
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("**************Deseja criar uma arvore ordenada**************\n");
    printf("*************Digite 1 para inserir uma arvore***************\n");
    printf("**********Digite 2 para que o sistema crie um arvore*********\n");
    printf("***Digite 3 para a arvore ordenada de 1 ate 7 seja inserida***\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    scanf("%d", &opcao);
    if(opcao==1){
            printf("Digite letra 'sair' para que seja parada a insercao\n");
            char numeros[10];
        do{
            scanf("%s", numeros);
            if(strcasecmp(numeros , "sair")!=0){
              inserir(&a,atoi(numeros));
            }
        }while(strcasecmp(numeros , "sair")!=0);
    }else if(opcao == 2){
        int aleatorio;
        printf("Deseja adicionar quantos numeros aleatorios?\n");
        scanf("%d", &aleatorio);
        criar(&a, aleatorio);
    }else(receba(&a));

    do{
        printf("O que faremos agora?\n");
        printf(" Digite 1 para analisarmos a profundidade da arvore criada\n" ) ;
        printf("Digite 2 para funcoes de percurso\n");
        printf("Digite 3 para impressao dos percursos\n");
         printf("Digite 4 para verificar se e ordenada ou nao\n");
        printf("'sair' para sair\n");
        scanf("%s",opcao2);
        if(strcasecmp(opcao2 , "1")==0){
            prof = profundidade(a);
            printf("Valor da profundidade %d\n", prof+1);
        }else if(strcasecmp(opcao2 , "2")==0){
            int c;
            printf("1 para preordem, 2 para posordem ou 3 para em ordem\n");
            scanf("%d",&c);
            if(c==1){
                printf("\n\n");
                Ipreordem(a);
            }else if(c==2){
                 printf("\n\n");
                Iposordem(a);
            }else{
                 printf("\n\n");
                Iemordem(a);
            }
        }else if(strcasecmp(opcao2, "3")==0){
            caminho(a,&p);
        }else{
            int k = ordenado(a,&p);
            if(k>0)printf("A arvore esta ordenada\n");
            else printf("ERRO\n");
        }
    }while(strcasecmp(opcao2 , "sair")!=0);
    return 0;
}
