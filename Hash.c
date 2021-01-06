
//Tabela Hash com divisao e controle de colisoes e Tres primeiras letras
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Cad{
    char nome[100];
    char curso[10];
    int numero[15];
    char matricula[12];
}Cad;
typedef struct Hash{
    int max,somar,base;
    struct Cad **alunos;
}Hash;
void inicializarhash(Hash **h,int max,Cad **d,int base){
    (*h) = (Hash*)malloc(sizeof(Hash));
    (*h)->max=0;
    (*h)->somar=max;
    (*h)->base=base;
    (*h)->alunos=(Cad**)malloc(max * sizeof(Cad*));
      for(int i=0;i<max;i++){
        (*h)->alunos[i] = NULL;
      }
}
int divisao3(char *a,int max,int base){
    int valor=0;
    valor = ((int) a[0] * 1)+((int) a[1] * base)+((int) a[2] * base*base);
    return valor;
}

int adicionar(Cad **d, Hash **h){
    (*d) = (Cad*)malloc(sizeof(Cad));
    if(d!=NULL || (*h)->max <= 31){
   /* printf("Curso\n");
    scanf(" %[^\n]",(*d)->curso);
    printf("Numero\n");
    scanf(" %[^\n]",(*d)->numero);*/
    printf("Nome\n");
    scanf(" %[^\n]",(*d)->nome);
   /* printf("Nº matricula\n");
    scanf(" %[^\n]",(*d)->matricula); */
    (*h)->max++;
    }
   return divisao3((*d)->nome,(*h)->somar,(*h)->base);
}
void imprimirhash(Hash *h){
    for(int i=0;i<h->somar;i++){
            if(h->alunos[i]!=NULL){
             printf("Na [%d] nome = %s\n", i, h->alunos[i]->nome);
             printf("Curso %s\n Numero %s \n Matricula %s\n", h->alunos[i]->curso,h->alunos[i]->numero,h->alunos[i]->matricula);
           }
    }
}
void tratamentocoli(Hash **h,int valor,Cad **d){
    printf("Valor %d\n", valor);
    int valor2;
    if((*h)->alunos[(valor%(*h)->somar)]==NULL){
        printf("Adicionando no null \n ");
        (*h)->alunos[(valor%(*h)->somar)]=*d;
    }else{
         valor2 = 2 +(valor%((*h)->somar - 2));
         valor = valor%(*h)->somar;
        printf("Adicionando no else %d %d \n", valor, valor2);
        (*h)->alunos[valor + valor2]=*d;
    }
}
int main(){
    Hash *h;
    Cad *d;
    int valor;
    inicializarhash(&h,5,&d,53);
    char opcoe[10];

   valor = adicionar(&d, &h);
    tratamentocoli(&h,24,&d);
    imprimirhash(h);
    valor = adicionar(&d, &h);
    tratamentocoli(&h,24,&d);
    imprimirhash(h);
}


//Tabela Hash com divisao e Sem controle de colisoes e Adiçao

/*
typedef struct Cad{
    char nome[100];
    char curso[10];
    int numero[15];
    char matricula[12];
}Cad;
typedef struct Hash{
    int max,somar;
    struct Cad **alunos;
}Hash;
void inicializarhash(Hash **h,int max,Cad **d){
    (*h) = (Hash*)malloc(sizeof(Hash));
    (*h)->max=0;
    (*h)->somar=max;
    (*h)->alunos=(Cad**)malloc(max * sizeof(Cad*));
      for(int i=0;i<max;i++){
        (*h)->alunos[i] = NULL;
      }
}
int divisao(char *a, int max){
    int valor=0;
    for(int i=0;i<strlen(a);i++){
       valor = valor + (int)a[i];
    }
    valor = (valor%max);
    return valor;
}
adicionar(Cad **d, Hash **h){
    (*d) = (Cad*)malloc(sizeof(Cad));
    if(d!=NULL || (*h)->max <= 31){
    printf("Curso\n");
    scanf(" %[^\n]",(*d)->curso);
    printf("Numero\n");
    scanf(" %[^\n]",(*d)->numero);
    printf("Nome\n");
    scanf(" %[^\n]",(*d)->nome);
    printf("Nº matricula\n");
    scanf(" %[^\n]",(*d)->matricula);
    (*h)->max++;
    }
}
void imprimirhash(Hash *h,int max){
    for(int i=0;i<max;i++){
            if(h->alunos[i]!=NULL){
             printf("Na [%d] nome = %s\n", i, h->alunos[i]->nome);
             printf("Curso %s\n Numero %s \n Matricula %s\n", h->alunos[i]->curso,h->alunos[i]->numero,h->alunos[i]->matricula);
           }
    }
}
/*
void receba(){
    FILE *arq;
    char ch1[100],ch2[1000],ch3[1000];
    int b;
    arq = fopen("Test.txt", "r");
    while (!feof(arq))
  {
      fscanf(arq,"%s %s %s\n", &ch1, &ch2, &ch3);
      printf("%s %s %s\n", ch1, ch2, ch3);
  }
  fclose(arq);
}

int main(){
    Hash *h;
    Cad *d;
    int valor;
    inicializarhash(&h,31,&d);
    char opcoe[10];
    printf("Vamos adicionar\n");

    adicionar(&d, &h);
    valor = divisao(d->nome,h->somar);
    h->alunos[valor]=d;
    imprimirhash(h,h->somar);

    adicionar(&d, &h);
    valor = divisao(d->nome,h->somar);
    h->alunos[valor]=d;
    imprimirhash(h,h->somar);

    adicionar(&d, &h);
    valor = divisao(d->nome,h->somar);
    h->alunos[valor]=d;
    imprimirhash(h,h->somar);

}
*/
//Tabela Hash Test
/*
typedef struct Hash{
    char nome[100];
    int idade;
}Hash;

struct Hash tabela[31];
int main()
{
    char x[100]="marcos";
    int valor = 3, div;
    Hash tabela[31];
    for(int i=0;i<31;i++){
     tabela[i].idade=0;
     strcpy(tabela[i].nome,"0");
    }
    div = (valor % 31);
    strcpy(tabela[div].nome,x);
    tabela[div].idade = 10;

    strcpy(x,"loko");
    valor = 50;
    div = (valor % 31);
    strcpy(tabela[div].nome,x);
    tabela[div].idade = 60;

    for(int i=0;i<31;i++){
    if(tabela[i].idade!=0){
       printf("Tabela = %s ,%d result = %d\n",tabela[i].nome,tabela[i].idade,i);
    }

    }

    return 0;
}
*/
