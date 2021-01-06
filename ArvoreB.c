#include <stdio.h>
#include <stdlib.h>

typedef struct f_arvoreB arvoreB;

typedef struct f_arvoreB {
    int num_chaves;
    int chaves[4];
    struct f_arvoreB *filhos[5];
};

int pesquisa(int chave2, int *vetorchave, int n){
    int pos=0;
    while (pos < n && chave2 > vetorchave[pos]) pos++;
    return pos;
}
int dividido(arvoreB **b, int local, int *subida, arvoreB **No){
    arvoreB *ultimopont;
    int ultima;
    if (local == 4){
        ultima = (*subida);
        ultimopont = *No;
    }else{
        ultima = (*b)->chaves[3];
        ultimopont = (*b)->filhos[4];
        for (int i=3; i>local; i--){
            (*b)->chaves[i] = (*b)->chaves[i-1];
            (*b)->filhos[i+1] = (*b)->filhos[i];
        }
        (*b)->chaves[local] = (*subida);
        (*b)->filhos[local+1] = (*No);
    }
    (*subida) = (*b)->chaves[2];
    (*No)=(arvoreB*)malloc(sizeof(struct f_arvoreB));
    (*No)->num_chaves = 4-2;
    int i=0;
    for (i=0; i < (*No)->num_chaves-1; i++){
        (*No)->filhos[i] = (*b)->filhos[i + 2 + 1];
        (*No)->chaves[i] = (*b)->chaves[i + 2 + 1];
    }
    (*No)->filhos[i] = (*b)->filhos[i + 2 + 1];
    (*No)->chaves[i] = ultima;
    (*No)->filhos[(*No)->num_chaves] = ultimopont;
    (*b)->num_chaves = 2;
    return 3;
}

int insirasemsubir(arvoreB **b, int *subir, arvoreB **No){
        int local = pesquisa(*subir, (*b)->chaves, (*b)->num_chaves);
        for (int i=(*b)->num_chaves; i>local; i--){
            (*b)->chaves[i] = (*b)->chaves[i-1];
            (*b)->filhos[i+1] = (*b)->filhos[i];
        }
        (*b)->num_chaves++;
        (*b)->chaves[local] = (*subir);
        (*b)->filhos[local+1] = (*No);
        return 2;
}

int Insere(arvoreB **b, int chave, int *subir, arvoreB **No){
    if ((*b) == NULL){(*subir) = chave;return 3;}

    int local = pesquisa(chave, (*b)->chaves, (*b)->num_chaves);

    if (local < (*b)->num_chaves && chave == (*b)->chaves[local]){
              printf("Ja existe essa chave\n");
              return 1;
    }
    int status;
    if ((status=Insere(&(*b)->filhos[local], chave, subir, No)) != 3)
        return status;
    if ((*b)->num_chaves < 4)
        return insirasemsubir(b, subir, No);
    return dividido(b,local,subir,No);
}
void Inserir(arvoreB **b,int chave){
    arvoreB *novo=NULL;
    int subir;
    if ( Insere(b, chave, &subir, &novo) == 3){
        arvoreB *aux = (*b);
        (*b)=(arvoreB*)malloc(sizeof(struct f_arvoreB));
        (*b)->num_chaves = 1;
        (*b)->chaves[0] = subir;
        (*b)->filhos[0] = aux;
        (*b)->filhos[1] = novo;
    }
}

int Delete(arvoreB **b, int chave, arvoreB ** pai){
    if ((*b) == NULL)
        return 5;
    int local = pesquisa(chave, (*b)->chaves, (*b)->num_chaves);
    if ((*b)->filhos[0] == NULL){
        if (chave < (*b)->chaves[local] || local == (*b)->num_chaves)
            return 5;
        for (int i=local+1; i < (*b)->num_chaves; i++){
            (*b)->chaves[i-1] = (*b)->chaves[i];
            (*b)->filhos[i] = (*b)->filhos[i+1];
        }
        (*b)->num_chaves--;
        return (*b)->num_chaves < (*b==(*pai) ? 1 : 2) ? 4: 2;
    }
    if (chave == (*b)->chaves[local] && local < (*b)->num_chaves){
        arvoreB *aux = (*b)->filhos[local], *aux2;
        int chave_pos;
        while(1){
            if (aux->filhos[aux->num_chaves] == NULL){
                chave_pos = aux->num_chaves;
                break;
            }
            aux = aux->filhos[aux->num_chaves];
        }
        (*b)->chaves[local] = aux->chaves[chave_pos-1];
        aux->chaves[chave_pos - 1] = chave;
    }
    int status ;
    if (status= Delete(&(*b)->filhos[local], chave, pai) != 4)
        return status;
    arvoreB *esqueda,*direita;
    if ( (*b)->filhos[local-1]->num_chaves > 2 && local > 0 ){
        esqueda = (*b)->filhos[local - 1];
        direita = (*b)->filhos[local];
        direita->filhos[direita->num_chaves + 1] = direita->filhos[direita->num_chaves];
        for (int i=direita->num_chaves; i>0; i--){
            direita->chaves[i] = direita->chaves[i-1];
            direita->filhos[i] = direita->filhos[i-1];
        }
        direita->num_chaves++;
        direita->chaves[0] = (*b)->chaves[local - 1];
        direita->filhos[0] = esqueda->filhos[esqueda->num_chaves];
        (*b)->chaves[local - 1] = esqueda->chaves[--esqueda->num_chaves];
        return 2;
    }
    if ((*b)->filhos[local + 1]->num_chaves > 2 && local < (*b)->num_chaves){
        esqueda = (*b)->filhos[local];
        direita = (*b)->filhos[local+1];
        esqueda->chaves[esqueda->num_chaves] = (*b)->chaves[local];
        esqueda->filhos[esqueda->num_chaves + 1] = direita->filhos[0];
        (*b)->chaves[local] = direita->chaves[0];
        esqueda->num_chaves++;
        direita->num_chaves--;
        for (int i=0; i < direita->num_chaves; i++){
            direita->chaves[i] = direita->chaves[i+1];
            direita->filhos[i] = direita->filhos[i+1];
        }
        direita->filhos[direita->num_chaves] = direita->filhos[direita->num_chaves + 1];
        return 2;
    }
    int position =(local == (*b)->num_chaves?(local-1):local);
    esqueda = (*b)->filhos[position];
    direita = (*b)->filhos[position+1];
    esqueda->chaves[esqueda->num_chaves] = (*b)->chaves[position];
    esqueda->filhos[esqueda->num_chaves + 1] = direita->filhos[0];
    for (int i=0; i < direita->num_chaves; i++){
        esqueda->chaves[esqueda->num_chaves + 1 + i] = direita->chaves[i];
        esqueda->filhos[esqueda->num_chaves + 2 + i] = direita->filhos[i+1];
    }
    esqueda->num_chaves += direita->num_chaves +1;
    free(direita);
    for (int i=local+1; i < (*b)->num_chaves; i++){
        (*b)->chaves[i-1] = (*b)->chaves[i];
        (*b)->filhos[i] = (*b)->filhos[i+1];
    }
    (*b)->num_chaves--;
    return (*b)->num_chaves >= ((*b) == (*pai) ? 1 : 2) ?  4: 2;
}
void deleta(arvoreB **b,int chave){
    if (Delete(b,chave,b)==4){
        arvoreB *aux = (*b);
        (*b) = (*b)->filhos[0];
        free(aux);
    }
}
void imprimir(arvoreB *b, int posicao){
    if (b!=NULL){
        for (int i=0; i < b->num_chaves; i++)printf("CHAVE = %d ",b->chaves[i]);printf(" LOCALIZADA %d\n", posicao +1);
        for (int i=0; i <= b->num_chaves; i++)imprimir(b->filhos[i], posicao+1);
    }
}

int main(){
    arvoreB *arvore=NULL;
    Inserir(&arvore, 3);
    Inserir(&arvore, 14);
    Inserir(&arvore, 7);
    Inserir(&arvore, 1);
    Inserir(&arvore, 8);
    Inserir(&arvore, 5);
    Inserir(&arvore, 11);
    Inserir(&arvore, 17);
    Inserir(&arvore, 13);
    Inserir(&arvore, 6);
    Inserir(&arvore, 23);
    Inserir(&arvore, 12);
    Inserir(&arvore, 20);
    Inserir(&arvore, 26);
    Inserir(&arvore, 4);
    Inserir(&arvore, 16);
    Inserir(&arvore, 18);
    Inserir(&arvore, 24);
    Inserir(&arvore, 25);
    Inserir(&arvore, 19);
    deleta(&arvore, 8);
    deleta(&arvore, 20);
    deleta(&arvore, 18);
    deleta(&arvore, 5);
    deleta(&arvore, 7);
    imprimir(arvore,0);
    return 0;
}
