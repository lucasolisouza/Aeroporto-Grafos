#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <stdio.h>
#include <string.h>
#include <limits.h>


#ifdef __cplusplus
extern "C" {
#endif

    
//cores em ANSI.
#define NONE   "\033[0m"
#define RED    "\033[31m"    
#define GREEN  "\033[32m"    
    
#define vertex int    
#define N 23
#define INF INT_MAX

    
typedef struct Horario{
    int hora;
    int min;
    char meridiem;
}Horario;

typedef struct Airports{
    char abbreviation[6];
    int timeZone;
    int coord_x;
    int coord_y;
}Airports;



//lista de adjacência - Grafo dos Voos.
typedef struct nodeV *linkV;
struct nodeV {
    int n_voo;
    char departure[8];
    char arrival[8];
    int distancia;
    int n_paradas;
    int duracao;
    vertex w;
    linkV next;
};
struct graphV {
    int V;
    int A;
    linkV *adj;
};
typedef struct graphV *GraphV;

static linkV NEWnodeV_c(vertex w, linkV next, int n, int d, int s,
                        int duracao, char departure[], char arrival[]);
GraphV InitV(int V);
void InsertArcV_c(GraphV G, vertex v, vertex w, int n, int d, int s,
                        int duracao, char departure[], char arrival[]);
void GRAPHshowV(GraphV G);



//lista de adjacência - Grafo das Rotas.
typedef struct node *link;
struct node {
    int qtd_voos;
    int distancia;
    vertex w;
    link next;
};
struct graph {
    int V;
    int A;
    link *adj;
};
typedef struct graph *Graph;

static link NEWnode_c(vertex w, link next, int d,int qtd);
Graph Init(int V);
void InsertArc_c(Graph G, vertex v, vertex w, int d,int qtd);
void GRAPHshow(Graph G);

//========================================
#define MAXTAM N
typedef int TipoApontador;
typedef int TipoChave;
typedef struct {
    TipoChave Chave;
    /*----Outros Componentes----*/
}TipoItem;
typedef struct {
    TipoItem Item[MAXTAM];
    TipoApontador Frente, Tras;
}TipoFila;


void FFVazia(TipoFila *Fila);
void Imprimir(TipoFila Fila);
void Enfileira(TipoItem x, TipoFila *Fila);
void Desenfileira(TipoFila *Fila, TipoItem *Item);
int Vazia(TipoFila Fila);


#ifdef __cplusplus
}
#endif

#endif /* STRUCTURE_H */

