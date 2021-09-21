#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct AVL{
    int info;
    char let;
    int FB;
    struct AVL *esq;
    struct AVL *dir;
}AVL;


AVL *lerArvore(FILE *arq){
    char c;
    int num;
    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);
    if(num == -1){
        fscanf(arq, "%c", &c);
        return NULL;
    }
    else{
        AVL *a = (AVL*) malloc(sizeof(AVL));
        a->info = num;
        fscanf(arq, "%c", &a->let);
        a->esq = lerArvore(arq);
        a->dir = lerArvore(arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}


AVL *destroiArvore(AVL *a){
    if(a != NULL){
        a->esq = destroiArvore(a->esq);
        a->dir = destroiArvore(a->dir);
        free(a);
        return a;
    }
    return NULL;
}


char *decifraMorse(char *pal, AVL *m){
    int i;
    AVL *aux = m;
    pal[strlen(pal)] = ' ';
    for(i = 0; i < strlen(pal) + 1; i++){
        if(aux == NULL)
            return "\nCaractere nao encontrado.\n";
        switch(pal[i]){
            case '-':
                aux = aux->dir;
            break;
            case '.':
                aux = aux->esq;
            break;
            case ' ':
                printf("%c", aux->let);
                aux = m;
            break;
        }
    }
    return "\nProcesso Concluido.\n";
}


char *decifraMorseArq(FILE *arq, AVL *a){
    int tam, i = 0;
    char c, *word;
    fseek(arq, 0, SEEK_END);
    tam = ftell(arq);
    rewind(arq);
    word = (char *) malloc(sizeof(char)*tam+1);
    while(i != tam){
        fscanf(arq, "%c", &c);
        if(c == '\n' || c == '\t')
            word[i] = 32;
        else
            word[i] = c;
        i++;
    }
    printf("%s", decifraMorse(word, a));
    return "Arquivo lido com sucesso.\n";
}


int main(){
    FILE *arq;
    AVL *a;
    int resp = 1;
    char mensagem[200], arquivo[20];
    arq = fopen("ARVO.txt", "r");
    if(arq == NULL){
        printf("O arquivo nao existe");
        printf("\n");
        system("pause");
    }
    else{
        a = lerArvore(arq);
        fclose(arq);
    }
    while(resp != 0){
        printf("(1)Escrever uma mensagem.\n");
        printf("(2)Ler um arquivo.\n");
        printf("(0)Sair\n");
        scanf("%d", &resp);
        switch(resp){
            case 1:
                printf("Escreva o codigo morse em pontos(.) e tracos(-):");
                fflush(stdin);
                gets(mensagem);
                printf("%s", decifraMorse(mensagem, a));
            break;
            case 2:
                printf("Digite o nome do arquivo:");
                fflush(stdin);
                gets(arquivo);
                arq = fopen(arquivo, "r");
                printf("%s", decifraMorseArq(arq, a));
                fclose(arq);
            break;
        }
    }
    a = destroiArvore(a);
    return 0;
}
