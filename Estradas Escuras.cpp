// Daniel Figueiredo Macedo - 14A - 201820276
// Pedro Carvalho Pereira - 14A - 201820265
// A ser corrigido no perfil Daniel Macedo

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
#define TAM 200000

typedef struct //estrutura que armazena a estrada bidirecional que liga 2 junções e o seu custo
{
    int v1, v2, c;
} parVertice;

void ligar(int x, int y, int conjuntoVertices[][1])
{
    //se a subárvore x é maior que a subárvore y, x passa a ser pai de y
    if (conjuntoVertices[x][1] > conjuntoVertices[y][1])
        conjuntoVertices[y][0] = x;

    //caso contrário, y passa a ser o pai de x
    else
    {
        conjuntoVertices[x][0] = y;
        if (conjuntoVertices[x][1] == conjuntoVertices[y][1])
            conjuntoVertices[y][1] = conjuntoVertices[y][1] + 1;
    }
}

int encontraConjunto(int conjuntoVertices[][1], int x)
{

    int noh = x;
    int pai = conjuntoVertices[noh][0];

    //iterativamente, busca a raiz da subárvore (quando o id e o pai são iguais)
    while (noh != pai)
    {
        noh = pai;
        pai = conjuntoVertices[noh][0];
    }

    conjuntoVertices[x][0] = pai;
    return pai;
}

void swap(parVertice *a, parVertice *b) //quicksort
{
    parVertice t = *a;
    *a = *b;
    *b = t;
}

int partition(parVertice arr[], int low, int high) //quicksort
{
    int pivot = arr[high].c;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j].c < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(parVertice arr[], int low, int high) //quicksort
{
    if (low < high)
    {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    parVertice arvMin[TAM];
    parVertice xy[TAM];
    int conjuntoVertices[TAM][1];
    int auxv1, auxv2, auxcusto, conju, conjv, resposta1, x, y, m, n;
    int somaCusto = 0;
    int n_arestas = 0;
    int custo = 0;

    do
    {
        cin >> x >> y; //entrada de vértices e arestas

        if (x >= 1 and y >= x - 1)
        {
            for (int i = 0; i < y; i++)
            {
                cin >> m >> n >> custo; //entrada de dois vértices que serão ligados por uma estrada bidirecional e o seu respectivo custo
                somaCusto += custo;
                xy[i].v1 = m;
                xy[i].v2 = n;
                xy[i].c = custo;
            }

            quickSort(xy, 0, y - 1); //ordenação com base no custo

            for (int i = 0; i < y; i++) //"seta" o pai e o rank dos vértices
            {
                conjuntoVertices[i][0] = i;
                conjuntoVertices[i][1] = 0;
            }

            int contador = 0;

            for (int i = 0; i < y; i++) //pra cada par de vértices ele checa se o conjunto de um vértice é diferente do conjunto do outro, se for, ele adiciona o par de vértices na AGM e liga os dois conjuntos
            {
                conju = encontraConjunto(conjuntoVertices, xy[i].v1);
                conjv = encontraConjunto(conjuntoVertices, xy[i].v2);

                if (conju != conjv)
                {
                    arvMin[contador].v1 = xy[i].v1;
                    arvMin[contador].v2 = xy[i].v2;
                    arvMin[contador].c = xy[i].c;
                    contador++;
                    n_arestas++;
                    if (n_arestas == x - 1) //checa se o grafo tem o mínimo de arestas para ser conexo
                    {
                        i = y; //break
                    }
                    ligar(conju, conjv, conjuntoVertices);
                }
            }

            for (int i = 0; i < n_arestas; i++) //armazenando o custo da AGM
            {

                resposta1 += arvMin[i].c;
            }

            int resultado;

            resultado = somaCusto - resposta1;

            cout << resultado << endl;

            contador = 0;
            n_arestas = 0;
            resposta1 = 0;
            somaCusto = 0;
            conju = 0;
            conjv = 0;
        }

    } while (x > 0 and y > 0);

    return 0;
}