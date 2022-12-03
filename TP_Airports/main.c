#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"
#include "FuntionsM.h"


/*  Função responsável controlar o menu de interface e realizar
 *  as chamadas das funções.
 *  @param: None
 *  @return: None. 
 */
int main() {
    Graph grafoRotas = Init(N);
    grafoRotas = getRoutes(grafoRotas);
    GraphV grafoVoos = InitV(N);
    grafoVoos = getFlight();
    int op = 0;  
    Airports *airports = getAirports();
    vertex *pa = NULL;
    vertex pe[1000] = {};
    char source[6], destiny[6];
    do{
        printf("\n---------------CONTROLE DE AEROPORTOS---------------");
        printf("\n1 - PESQUISAR A ROTA ENTRE 2 AEROPORTOS.");
        printf("\n2 - PESQUISAR VOOS SEM CONEXÕES A PARTIR DE UM AEROPORTO.");
        printf("\n3 - PESQUISAR A VIAGEM COM O MENOR CUSTO.");
        printf("\n4 - PESQUISAR AEROPORTO - 1ºCaso Especial.");
        printf("\n5 - PESQUISAR AEROPORTO - 2ºCaso Especial.");
        printf("\n>>> ");
        scanf("%d",&op);
        switch (op){
            case 0:
                printf("\nSaindo...");
                break;
            case 1:
                printf("\nInsira a abreviação de origem (XXX): ");
                setbuf(stdin,NULL);
                fgets(source,6,stdin);
                source[strcspn(source, "\n")] = 0;
                printf("\nInsira a abreviação de destino (XXX): ");
                fgets(destiny,6,stdin);
                setbuf(stdin,NULL);
                destiny[strcspn(destiny, "\n")] = 0;
                int v = getIndexAirport(source,airports);
                int w = getIndexAirport(destiny,airports);
                if(v != -1 && w != -1){
                    printf("\n");
                    Dijkstra(grafoRotas,v,w);
                }
                break;
            case 2:
                printf("\nInsira a abreviação do Aeroporto (XXX): ");
                setbuf(stdin,NULL);
                fgets(source,6,stdin);
                source[strcspn(source, "\n")] = 0;
                int h = getIndexAirport(source,airports);
                if(h != -1)
                    showFlightNoStops(grafoVoos,h,airports);
                break;
            case 3:
                printf("\nInsira a abreviação de origem (XXX): ");
                setbuf(stdin,NULL);
                fgets(source,6,stdin);
                source[strcspn(source, "\n")] = 0;
                printf("\nInsira a abreviação de destino (XXX): ");
                fgets(destiny,6,stdin);
                setbuf(stdin,NULL);
                destiny[strcspn(destiny, "\n")] = 0;
                v = getIndexAirport(source,airports);
                w = getIndexAirport(destiny,airports);
                if(v != -1 && w != -1){
                    printf("\n");
                    Dijkstra_2(grafoVoos,v,w);
                }
                break;
            case 4:
                printf("\nInsira a abreviação de origem (XXX): ");
                setbuf(stdin,NULL);
                fgets(source,6,stdin);
                source[strcspn(source, "\n")] = 0;
                v = getIndexAirport(source,airports);
                DepthFirstSearch(grafoRotas,v);
                break;
            case 5:
                printf("\nInsira a abreviação de origem (XXX): ");
                setbuf(stdin,NULL);
                fgets(source,6,stdin);
                source[strcspn(source, "\n")] = 0;
                v = getIndexAirport(source,airports);
                DepthFirstSearch_2(grafoRotas,v);
                break;
            default:
                printf("\nOpção Inválida.");
        }
    }while(op!=0);
    return (EXIT_SUCCESS);
}

