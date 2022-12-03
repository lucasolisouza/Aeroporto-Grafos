#ifndef FUNTIONSM_H
#define FUNTIONSM_H
#include <stdio.h>
#include "Structure.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/*  Função responsável por ler o arquivo com as informações dos
 *  Aeroportos e inseri-las no vetor de Aeroportos dinamicamente 
 *  alocado.
 *  @param: None
 *  @return: vetor alocado de aeroportos. 
 */
Airports *getAirports();

/*  Função responsável por devolver o índice de um determinado
 *  aeroporto dentro do vetor de aeroportos.
 *  @param: String com a abreviação do aeroporto e o vetor de
 *  aeroportos.
 *  @return: índice do aeroporto.
 */
int getIndexAirport(char abv[],Airports *A);

/*  Função responsável por ler o arquivo com as informações das
 *  rotas e inseri-las no grafo de rotas.
 *  @param: grafo de rotas.
 *  @return: grafo de rotas.
 */
Graph getRoutes(Graph G);

/*  Função responsável por ler o arquivo com as informações dos
 *  voos e inseri-las no grafo de voos.
 *  @param: None
 *  @return: grafo de voos.
 */
GraphV getFlight();

/*  Implementação do Algoritmo de Dijkstra em relação a 
 *  distância (peso da aresta). 
 *  @param: Grafo de Rotas, vértice de origem e de destino.
 *  @return: None.
 */
void Dijkstra(Graph G,vertex origem, vertex destino);

/*  Implementação do Algoritmo de Dijkstra em relação a 
 *  distância e o tempo de voo (peso da aresta). 
 *  @param: Grafo de Voos, vértice de origem e de destino.
 *  @return: None.
 */
void Dijkstra_2(GraphV G,vertex origem, vertex destino);

/*  Função responsável apresentar os voos de um determinado
 *  Aeroporto que não possuem nenhuma escala e/ou conexões.
 *  @param: grafo de Voos, vértice do aeroporto e o vetor
 *  de Aeroportos.
 *  @return: None.
 */
void showFlightNoStops(GraphV G,vertex v, Airports *A);

/*  Função responsável por calcular a distâcia entre os
 *  aeroportos.
 *  @param: vértice dos 2 aeroportos.
 *  @return: distância em dezenas de Km.
 */
double calcularDistancia(vertex v, vertex w);

/*  Função responsável por transformar a hora em minutos.
 *  @param: hora e minutos.
 *  @return: tempo em minutos.
 */
int muda_horario (int hour, int minutes);

/*  Função responsável por calcular a diferença entre a
 *  saída e a chegada.
 *  @param: hora e minutos da saída e da chegada.
 *  @return: difirença em minutos.
 */
int dif_hora (int hour1, int minute1, int hour2, int minute2);

/*  Função responsável por calcular o tempo do voo.
 *  @param: String da saída e String da chegada.
 *  @return: difirença em minutos.
 */
int calculaTempoDeVoo(char departure[], char arrival[]);

/*  Função recursiva responsável por auxiliar a 
 *  DepthFirstSearch(Graph G, vertex w).  
 *  @param: Grafo de Rotas, vértice de origem e um vetor
 *  de visitados.
 *  @return: None.
 */
void dfsR( Graph G, vertex v, int visited[]);

/*  Implementação do Algoritmo de Busca em Profundidade adaptada
 *  para a resolução da 5.4. 
 *  @param: Grafo de Rotas, vértice de origem.
 *  @return: None.
 */
void DepthFirstSearch( Graph G, vertex w);

/*  Implementação do Algoritmo de Busca em Profundidade adaptada
 *  para a resolução da 5.5. 
 *  @param: Grafo de Rotas, vértice de origem.
 *  @return: None.
 */
void DepthFirstSearch_2( Graph G, vertex w);

#ifdef __cplusplus
}
#endif

#endif /* FUNTIONSM_H */

