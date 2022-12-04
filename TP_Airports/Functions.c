#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Structure.h"
#include "FuntionsM.h"
 
int ult;
int cnt;
int pre[100];


/*  Função responsável por ler o arquivo com as informações dos
 *  Aeroportos e inseri-las no vetor de Aeroportos dinamicamente 
 *  alocado.
 *  @param: None
 *  @return: vetor alocado de aeroportos. 
 */
Airports *getAirports(){
  FILE *file;
  Airports tempAirport;
  char text[500];
  int index = 0;
  Airports *airports = (Airports *)malloc(N*sizeof(Airports));
  file = fopen("Airports.txt", "r");
  if (file == NULL) printf("ERRO! O arquivo não foi aberto!\n");
  while(fgets(text, 500, file) != NULL){
        char *token = strtok(text, ";");
        for(int i=0;token!=NULL;i++){
            switch (i){
                case 0:
                    strcpy(tempAirport.abbreviation, token);
                    break;
                case 1:
                    tempAirport.timeZone = atoi(token);
                    break;
                case 2:
                    tempAirport.coord_x = atoi(token);
                    break;
                case 3:
                    tempAirport.coord_y = atoi(token);
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ";");
        }
        airports[index++] = tempAirport;
  }
  fclose(file);
  return airports;
}

/*  Função responsável por devolver o índice de um determinado
 *  aeroporto dentro do vetor de aeroportos.
 *  @param: String com a abreviação do aeroporto e o vetor de
 *  aeroportos.
 *  @return: índice do aeroporto.
 */
int getIndexAirport(char abv[],Airports *A){
    for(int i=0;i<N;i++){
        if(strcmp(A[i].abbreviation,abv) == 0) return i;
    }
    printf("\nNot found.");return -1;
}

/*  Função responsável por ler o arquivo com as informações das
 *  rotas e inseri-las no grafo de rotas.
 *  @param: grafo de rotas.
 *  @return: grafo de rotas.
 */
Graph getRoutes(Graph G){
  FILE *file;
  vertex v,w;
  char source[6] = {}, destiny[6] = {};
  char text[100];
  int index = 0;
  Airports *A = getAirports();
  file = fopen("Connections.txt", "r");
  if (file == NULL) printf("ERRO! O arquivo não foi aberto!\n");
  while(fgets(text, 100, file) != NULL){
        char *token = strtok(text, ";");
        for(int i=0;token!=NULL;i++){
            switch (i){
                case 0:
                    strcpy(source, token);
                    source[strcspn(source, "\n")] = 0;
                    setbuf(stdin,NULL);
                    v = getIndexAirport(source,A);
                    break;
                case 1:
                    strcpy(destiny, token);
                    destiny[strcspn(destiny, "\n")] = 0;
                    setbuf(stdin,NULL);
                    w = getIndexAirport(destiny,A);
                    break;
                default:
                    break;
            }
            token = strtok(NULL, ";");
        }
        double d = calcularDistancia(v,w);
        InsertArc_c(G,v,w,(int) d,0);
        InsertArc_c(G,w,v,(int) d,0);
  }
  fclose(file);free(A);
  return G;
}


/*  Função responsável por ler o arquivo com as informações dos
 *  voos e inseri-las no grafo de voos.
 *  @param: None
 *  @return: grafo de voos.
 */
GraphV getFlight(){
    FILE *file;
    GraphV G = InitV(N);
    vertex v,w;
    int n, s, duracao=0;
    char text[100];
    char source[6] = {}, destiny[6] = {};
    char departure[10] = {}, arrival[10] = {};
    int index = 0;
    Airports *A = getAirports();
    file = fopen("Flight_Schedule.txt", "r");
    if (file == NULL) printf("ERRO! O arquivo não foi aberto!\n");
    while(fgets(text, 100, file) != NULL){
          char *token = strtok(text, ",");
          for(int i=0;token!=NULL;i++){
              switch (i){
                  case 0:
                      n = atoi(token);
                      break;
                  case 1:
                      strcpy(source, token);
                      source[strcspn(source, "\n")] = 0;
                      setbuf(stdin,NULL);
                      v = getIndexAirport(source,A);                   
                      break;
                  case 2:
                      strcpy(departure, token);
                      break;
                  case 3:
                      strcpy(destiny, token);
                      destiny[strcspn(destiny, "\n")] = 0;
                      setbuf(stdin,NULL);
                      w = getIndexAirport(destiny,A);                      
                      break;
                  case 4:
                      strcpy(arrival, token);
                      break;
                  case 5:
                      s = atoi(token);
                      break;
                  default:
                      break;
              }
              token = strtok(NULL, ",");
          }
          double d = calcularDistancia(v,w);
          duracao = calculaTempoDeVoo(departure,arrival);
          InsertArcV_c(G,v,w,n,(int) d,s,duracao,departure,arrival);
    }
    fclose(file);
    return G;   
}


/*  Implementação do Algoritmo de Dijkstra em relação a 
 *  distância (peso da aresta). 
 *  @param: Grafo de Rotas, vértice de origem e de destino.
 *  @return: None.
 */
void Dijkstra(Graph G,vertex origem, vertex destino){
    Airports *A = getAirports();
    int i, v, anterior[N], visited[N];     
    int min = 0, dist[N];
    int way[N], last = 0;
    TipoFila fila;
    TipoItem Item;
    FFVazia(&fila);
    
    
    for (i = 0; i < N; i++) {
        dist[i] = INF;
        anterior[i] = -1;
        visited[i] = 0;
    }
    visited[origem] = 1;
    dist[origem] = 0;
    Item.Chave = origem;
    Enfileira(Item,&fila);
    
    
    do{
      int atual;
      
      atual = fila.Item[fila.Frente-1].Chave;
      
      for (link prox = G->adj[atual]; prox != NULL; prox = prox->next) {
        int distancia = prox->distancia;
        int w = prox->w;
        if(distancia + dist[atual] < dist[w]){
            dist[w] = distancia + dist[atual];
            anterior[w] = atual;
        }
        if(visited[w] != 1) {
            visited[w] = 1;
            Item.Chave = w;
            Enfileira(Item,&fila);
        }
           
      }
      Desenfileira(&fila,&Item);
    }while(!Vazia(fila));
    
    way[last++] = destino;
    while(way[last-1]!=origem){
        int ant = way[last-1];
        way[last++] = anterior[ant];
    }
    
    
    printf("\n");
    for (i = last -1; i >= 0; i--) {
        if(i == 0) printf(GREEN "%s" NONE, A[way[i]].abbreviation);
        else printf(GREEN "%s --> " NONE, A[way[i]].abbreviation);
    }
}

/*  Função responsável apresentar os voos de um determinado
 *  Aeroporto que não possuem nenhuma escala e/ou conexões.
 *  @param: grafo de Voos, vértice do aeroporto e o vetor
 *  de Aeroportos.
 *  @return: None.
 */
void showFlightNoStops(GraphV G,vertex v,Airports *A){
    for (linkV prox = G->adj[v]; prox != NULL; prox = prox->next) {
        int w = prox->n_paradas;
        int p = prox->w;
        if(w == 0){
           printf(GREEN "\n%s --> %s" NONE,A[v].abbreviation,
                   A[p].abbreviation);
        }
    }  
}

/*  Função responsável por calcular a distâcia entre os
 *  aeroportos.
 *  @param: vértice dos 2 aeroportos.
 *  @return: distância em dezenas de Km.
 */
double calcularDistancia(vertex v, vertex w){
    Airports *A = getAirports();
    double dist = pow((A[v].coord_x - A[w].coord_x),2) + 
                + pow((A[v].coord_y - A[w].coord_y),2);
    dist = sqrt(dist);
    return dist*10;
}

/*  Função responsável por transformar a hora em minutos.
 *  @param: hora e minutos.
 *  @return: tempo em minutos.
 */
int muda_horario (int hour, int minutes){
	int minutesnew;
	minutesnew= (hour * 60) + minutes;
}

/*  Função responsável por calcular a diferença entre a
 *  saída e a chegada.
 *  @param: hora e minutos da saída e da chegada.
 *  @return: difirença em minutos.
 */
int dif_hora (int hour1, int minute1, int hour2, int minute2){
    int dif = muda_horario (hour1, minute1) - muda_horario (hour2, minute2);
    return dif;
}

/*  Função responsável por calcular o tempo do voo.
 *  @param: String da saída e String da chegada.
 *  @return: difirença em minutos.
 */
int calculaTempoDeVoo(char departure[], char arrival[]){
    Horario saida;
    Horario chegada;
    sscanf(departure, "%d:%d/%c",&saida.hora,
            &saida.min,&saida.meridiem);
    sscanf(arrival, "%d:%d/%c",&chegada.hora,
            &chegada.min,&chegada.meridiem);
    if(saida.meridiem == 'P' && saida.hora != 12){
        saida.hora += 12;
        if(saida.hora >= 24) {
            saida.hora = 0;
            saida.meridiem = 'A';
        }
    }
    if(chegada.meridiem == 'P' && chegada.hora != 12){
        chegada.hora += 12;
        if(chegada.hora  >= 24) {
            chegada.hora = 0;
            chegada.meridiem = 'A';
        }
    }
    int diferenca = dif_hora(chegada.hora,chegada.min,saida.hora,saida.min);
    return diferenca;
}

/*  Implementação do Algoritmo de Dijkstra em relação a 
 *  distância e o tempo de voo (peso da aresta). 
 *  @param: Grafo de Voos, vértice de origem e de destino.
 *  @return: None.
 */
void Dijkstra_2(GraphV G,vertex origem, vertex destino){
    Airports *A = getAirports();
    int i, v, anterior[N], visited[N];     
    int min = 0, dist[N], temp[N];
    int way[N], last = 0;
    TipoFila fila;
    TipoItem Item;
    FFVazia(&fila);
    for (i = 0; i < N; i++) {
        dist[i] = INF;
        temp[i] = INF;
        anterior[i] = -1;
        visited[i] = 0;
    }
    visited[origem] = 1;
    dist[origem] = 0;
    temp[origem] = 0;
    Item.Chave = origem;
    Enfileira(Item,&fila);  
    do{
      int atual;
      
      atual = fila.Item[fila.Frente-1].Chave;
      
      for (linkV prox = G->adj[atual]; prox != NULL; prox = prox->next) {
        int distancia = prox->distancia;
        int duracao = prox->duracao;
        int w = prox->w;
        if((distancia + dist[atual] < dist[w]) && 
                (duracao + temp[atual] < temp[w])){
            dist[w] = distancia + dist[atual];
            temp[w] = duracao + temp[atual];
            anterior[w] = atual;
        }
        if(visited[w] != 1) {
            visited[w] = 1;
            Item.Chave = w;
            Enfileira(Item,&fila);
        }        
      }
      Desenfileira(&fila,&Item);
    }while(!Vazia(fila));
    
    way[last++] = destino;
    while(way[last-1]!=origem){
        int ant = way[last-1];
        way[last++] = anterior[ant];
    }  
    for (i = last -1; i >= 0; i--) {
        if(i == 0) printf(GREEN "%s" NONE, A[way[i]].abbreviation);
        else printf(GREEN "%s --> " NONE, A[way[i]].abbreviation);
    }
}


/*  Implementação do Algoritmo de Busca em Profundidade adaptada
 *  para a resolução da 5.4. 
 *  @param: Grafo de Rotas, vértice de origem.
 *  @return: None.
 */
void DepthFirstSearch( Graph G, vertex w) { 
    Airports *A = getAirports();
    int visited[N] = {};
    visited[w] = 1;
    //primiera parte.
    dfsR(G, w, visited);   
    //verifica se é conexo,
    for(vertex v = 0; v < N; v++) {
        if(visited[v] == 0){
            printf("\nO grafo é desconexo."); return;
        }
    }  
    //segunda parte.
    int i;
    for(vertex v = 0; v < N; v++){
        i = N;
        while(i!=-1) visited[i--] = 0;
        visited[w] = 1;
        visited[v] = 1;
        dfsR(G, w, visited);
        for(vertex s = 0; s < N; s++) {
            if(visited[s] == 0)
                printf(RED "\n%s --X--> %s" NONE,A[v].abbreviation,
                        A[s].abbreviation);
        }
    } 
}

/*  Função recursiva responsável por auxiliar a 
 *  DepthFirstSearch(Graph G, vertex w).  
 *  @param: Grafo de Rotas, vértice de origem e um vetor
 *  de visitados.
 *  @return: None.
 */
void dfsR( Graph G, vertex v, int visited[]) { 
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if(visited[w] == 0){
            visited[w] = 1;     
            ult = w;
            pre[cnt++] = w;
            dfsR(G, w, visited);
        }
    }
}

/*  Implementação do Algoritmo de Busca em Profundidade adaptada
 *  para a resolução da 5.5. 
 *  @param: Grafo de Rotas, vértice de origem.
 *  @return: None.
 */
void DepthFirstSearch_2( Graph G, vertex w) { 
    Airports *A = getAirports();
    cnt = 0;
    //primeira parte.
    int k = 100;
    while(k<100) pre[k++] = 0;
    
    int visited[N] = {};
    visited[w] = 1;
    dfsR(G, w, visited);
    
    for(vertex s = 0; s < cnt-1; s++) 
        printf(GREEN "%s --> " NONE, A[pre[s]].abbreviation);
    Dijkstra(G, ult, w);
    
    //segunda parte
    for (int i = 0; i < cnt; i++) {
        for (int j = i + 1; j < cnt; j++) {
            if (pre[i] == pre[j]) {
                printf("\nNão é um circuito Hamiltoniano.");
            }
        }
    }
    printf("\nÉ um circuito Hamiltoniano.");
}
