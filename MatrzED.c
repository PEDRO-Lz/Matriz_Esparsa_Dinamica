#include <stdio.h>
#include <stdlib.h>

struct elemento{
    struct elemento *direita, *abaixo;
    int linha, coluna;
    int valor;
};
struct elemento *base=NULL;
int maiorc=-1, maiorl=-1;

void gerabase(){
    base = (struct elemento *) malloc (sizeof(struct elemento));
    base->linha = -1;
    base->coluna = -1;
    base->valor = 0;
    base->direita = base;
    base->abaixo = base;
}
void geramat();

void alteravalor(int l, int c, int n) {
    struct elemento *aux, *p1, *p2;

    p1=base;
    while(p1->direita->coluna < c && p1->direita->coluna != -1) p1=p1->direita;
    if(p1->direita->coluna == c){
        p1=p1->direita;
        while(p1->abaixo->linha < l && p1->abaixo->linha != -1) p1=p1->abaixo;
    }
    else {
        aux = (struct elemento *) malloc(sizeof(struct elemento));
        aux->direita = p1->direita;
        p1->direita = aux;
        aux->abaixo = aux;
        aux->coluna = c;
        aux->linha = -1;
        p1=aux;
    }

    p2=base;
    while(p2->abaixo->linha < l && p2->abaixo->linha != -1) p2=p2->abaixo;
    if(p2->abaixo->linha == l){
        p2=p2->abaixo;
        while(p2->direita->coluna < c && p2->direita->coluna != -1) p2=p2->direita;
    }
    else{
        aux = (struct elemento *) malloc (sizeof(struct elemento));
        aux->abaixo = p2->abaixo;
        p2->abaixo = aux;
        aux->direita = aux;
        aux->coluna = -1;
        aux->linha = l;
        p2=aux;
    }

    if(p1->abaixo->coluna == c && p1->abaixo->linha == l)
        p1->abaixo->valor = n;
    else {
        aux = (struct elemento *) malloc(sizeof(struct elemento));
        aux->abaixo = p1->abaixo;
        p1->abaixo = aux;
        aux->direita = p2->direita;
        p2->direita = aux;
        aux->linha = l;
        aux->coluna = c;
        aux->valor = n;
    }
}

void remover(int l, int c){
    struct elemento *p1, *p2, *aux, *auxc, *auxl;

    p1=base;
    while(p1->direita->coluna < c && p1->direita->coluna != -1) p1=p1->direita;
    auxc = p1;
    p1 = p1->direita;
    if(p1->coluna == c)
        while(p1->abaixo->linha < l && p1->abaixo->linha != -1) p1=p1->abaixo;
    else{printf("\nElemento nao existe\n"); return;}
    aux = p1->abaixo;
    p1->abaixo = p1->abaixo->abaixo;

    p2=base;
    while(p2->abaixo->linha < l && p2->abaixo->linha != -1) p2=p2->abaixo;
    auxl = p2;
    p2 = p2->abaixo;
    if(p2->linha == l)
        while(p2->direita->coluna < c && p2->direita->coluna != -1) p2=p2->direita;
    else{printf("Elemento nao existe"); return;}
    p2->direita = p2->direita->direita;

    free(aux);

    if(p1->abaixo == p1){
        auxc->direita = p1->direita;
        free(p1);
    }
    if(p2->direita == p2){
        auxl->abaixo = p2->abaixo;
        free(p2);
    }
}

int consulta(int l, int c){
    struct elemento *p1;

    for(p1=base; p1->coluna < c && p1->direita->coluna != -1; p1=p1->direita);
    if(p1->coluna == c){
        for(; p1->linha < l && p1->abaixo->linha != -1; p1=p1->abaixo);
        if(p1->linha == l) return p1->valor;
    }
    return 0;
}

void exibelinha(int l){
    struct elemento *p1;
    int coluna=0;

    for(p1=base; p1->linha != l && p1->abaixo->linha != -1; p1=p1->abaixo);
    if(p1->linha != l){printf("\nLinha nao existe"); return; }

    for(; coluna <= maiorc; p1=p1->direita, coluna++){
        if(p1->direita->coluna == coluna)
            printf("%d ", p1->direita->valor);
        else
            printf("0 ");
    }
}

void exibecoluna(int c){
    struct elemento *p1;
    int linha=0;

    for(p1=base; p1->coluna != c && p1->direita->coluna != -1; p1=p1->direita);
    if(p1->coluna != c){printf("\nColuna nao existe"); return; }

    for(; linha <= maiorl; p1=p1->abaixo, linha++){
        if(p1->abaixo->linha == linha)
            printf("%d ", p1->abaixo->valor);
        else
            printf("0 ");
    }
}

int somaTrianguloSuperior(){
    int soma = 0;
    struct elemento *p1, *p2;
    printf("Valores: ");
    for(p1=base->abaixo->direita; p1->linha != -1; p1=p1->abaixo){
        for(p2=p1; p2->coluna != -1; p2=p2->direita){
            if(p2->coluna >= p2->linha){
                printf("%d ", p2->valor);
                soma += p2->valor;
            }
        }
    }
    return soma;
}

void limpabase() {
    struct elemento *linhaAtual = base->abaixo;
    struct elemento *colunaAtual = base->direita;

    while (linhaAtual != base) {
        struct elemento *proximaLinha = linhaAtual->abaixo;
        free(linhaAtual);
        linhaAtual = proximaLinha;
    }

    while (colunaAtual != base) {
        struct elemento *proximaColuna = colunaAtual->direita;
        free(colunaAtual);
        colunaAtual = proximaColuna;
    }
    base = NULL;
}

void limpa() {
    struct elemento *p1, *p2, *temp;

    for (p1 = base->abaixo; p1->linha != -1; p1 = p1->abaixo) {
        for (p2 = p1->direita; p2->coluna != -1; p2 = temp) {
            temp = p2->direita;
            free(p2);
        }
    }
    limpabase();
}

int main(){
    int x=-1, l, c, v, consu;

    gerabase();

    while(x!=0){
        printf("\n1 - Alterar um Valor  ||  2 - Consultar um Valor");
        printf("\n3 - Exibir Linha      ||  4 - Exibir Coluna");
        printf("\n5 - Soma do Triangulo Superior");
        printf("\n6 - Gera uma Matriz para teste");
        printf("\n0 - SAIR\n");
        scanf("%d", &x);

        if(x==1){
            printf("Digite a linha: ");
            scanf("%d", &l);
            printf("\nDigite a coluna: ");
            scanf("%d", &c);
            printf("\nDigite a valor: ");
            scanf("%d", &v);
            if(v){
                if(l>maiorl) maiorl=l;
                if(c>maiorc) maiorc=c;
                alteravalor(l,c,v);
            }
            else remover(l,c);
        }
        else if(x==2){
            printf("Digite a linha: ");
            scanf("%d", &l);
            printf("\nDigite a coluna: ");
            scanf("%d", &c);
            consu = consulta(l,c);
            if(consu) printf("Valor: %d ", consu);
            else printf("Valor inválido");
        }
        else if(x==3){
            printf("Digite a linha: ");
            scanf("%d", &l);
            exibelinha(l);
        }
        else if(x==4){
            printf("Digite a coluna: ");
            scanf("%d", &c);
            exibecoluna(c);
        }
        else if(x==5) printf("\nSoma Triangulo Sup = %d", somaTrianguloSuperior());
        else if(x==6){ limpa(); geramat();}
    }

    limpa();

    return 0;
}
/* Esta funcao gera uma matriz para testes */
void geramat(){
    gerabase();
    alteravalor(2,2,100);
    alteravalor(2,3,5);
    alteravalor(0,0,100);
    alteravalor(0,1,0);
    alteravalor(0,2,0);
    alteravalor(1,0,10);
    alteravalor(1,2,20);
    alteravalor(1,3,0);
    alteravalor(2,0,0);
    alteravalor(1,1,0);
    alteravalor(0,0,50);
    alteravalor(3,0,-3);
    alteravalor(0,3,0);
    alteravalor(2,1,0);
    alteravalor(2,2,0);
    alteravalor(3,3,5);
    alteravalor(2,3,0);
    alteravalor(3,1,0);
    alteravalor(3,2,-60);
    maiorc=3;
    maiorl=3;
}