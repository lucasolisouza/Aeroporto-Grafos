#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"


//lista de adjacência. 
static linkV NEWnodeV_c(vertex w, linkV next, int n, int d, int s,
                        int duracao, char departure[], char arrival[]) {
    linkV a = malloc(sizeof (struct nodeV));
    a->w = w;
    a->next = next;
    a->n_voo = n;
    a->distancia = d;
    a->n_paradas = s;
    a->duracao = duracao;
    strcpy(a->arrival,arrival);
    strcpy(a->departure,departure);
    return a;
}

GraphV InitV(int V) {
    GraphV G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof (linkV));
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

void InsertArcV_c(GraphV G, vertex v, vertex w, int n, int d, int s,
                        int duracao, char departure[], char arrival[]) {
    G->adj[v] = NEWnodeV_c(w, G->adj[v], n, d, s, duracao, departure, arrival);
    G->A++;
}

void GRAPHshowV(GraphV G) {
    for (vertex v = 0; v < G->V; ++v) {
        printf("%2d:", v);
        for (linkV a = G->adj[v]; a != NULL; a = a->next)
            printf(" %2d", a->w);
        printf("\n");
    }
}
//=======================================

//lista de adjacência - Rotas.
static link NEWnode_c(vertex w, link next, int d,int qtd) {
    link a = malloc(sizeof (struct node));
    a->w = w;
    a->next = next;
    a->distancia = d;
    a->qtd_voos = qtd;
    return a;
}

Graph Init(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof (link));
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

void InsertArc_c(Graph G, vertex v, vertex w, int d,int qtd) {
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        if (a->w == w) {
            a->distancia = d;
            a->qtd_voos = qtd;
            return;
        }
    }
    G->adj[v] = NEWnode_c(w, G->adj[v], d, qtd);
    G->A++;
}

void GRAPHshow(Graph G) {
    for (vertex v = 0; v < G->V; ++v) {
        printf("%2d:", v);
        for (link a = G->adj[v]; a != NULL; a = a->next)
            printf(" %2d", a->w);
        printf("\n");
    }
}

//===================================================

void FFVazia(TipoFila *Fila){
    Fila->Frente = 1;
    Fila->Tras = Fila->Frente;
}

void Enfileira(TipoItem x, TipoFila *Fila){
    if(Fila->Tras % MAXTAM + 1 == Fila->Frente)
        printf("\nErro: Fila está cheia!");
    else {
        Fila->Item[Fila->Tras - 1] = x;
        Fila->Tras = Fila->Tras % MAXTAM + 1;
    }
}

void Desenfileira(TipoFila *Fila, TipoItem *Item){
    if(Vazia(*Fila)) printf("\nErro: Fila está vazia");
    else {
        *Item = Fila->Item[Fila->Frente - 1];
        Fila->Frente = Fila->Frente % MAXTAM + 1;
    }
}

void Imprimir(TipoFila Fila){
    int i;
    for(i=Fila.Frente-1;i<Fila.Tras-1;i++){
        printf(" %d",Fila.Item[i]);
    }
}

int Vazia(TipoFila Fila) {
    return (Fila.Frente ==  Fila.Tras);
}