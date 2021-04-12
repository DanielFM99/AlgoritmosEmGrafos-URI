// Daniel Figueiredo Macedo - 14A - 201820276
// Pedro Carvalho Pereira - 14A - 201820265
// A ser corrigido no perfil Daniel Macedo
// Alguns trechos do código foram retirados do site www.geeksforgeeks.org e foram modificados de acordo com a necessidade do exercício

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#define TAM 1000

using namespace std;

class Grafo //grafo implementado por meio de classe
{
public:
    int cont;
    list<int> *LAdj;
    int quantVert;
    bool achouCiclo;
    char cor[TAM];

    Grafo(int numVert) //construtor do grafo
    {
        LAdj = new list<int>[numVert];
        quantVert = numVert;
        cont = 0;
        achouCiclo = false;

        for (int i = 0; i < numVert; i++)
        {
            cor[i] = 'B';
        }
    }

    void AdicionaArestas(int v, int w) //função que adiciona um vértice à lista de adjacência de outro vértice (grafo direcionado)
    {
        LAdj[v].push_back(w);
    }

    void
    DFS_VISIT(int x)
    {
        cor[x] = 'C';
        if (LAdj[x].empty() == false)
        {
            for (list<int>::iterator z = LAdj[x].begin(); z != LAdj[x].end(); z++) //percorre toda a lista de adjacência e checa se algum vértice já foi visitado, se sim, "seta" achouCiclo como true
            {
                int h = *z;
                if (cor[h] == 'B')
                {
                    cor[h] = 'C';
                    DFS_VISIT(h);
                }
                else
                {
                    achouCiclo = true;
                }
            }
            cont++;
        }
        cor[x] = 'P';
    }

    void DFS()
    { //função que chama a DFS_VISIT em cada vértice da lista de adjacência de um vértice não visitado e que tenha pelo menos 1 vizinho
        for (int i = 0; i < quantVert; i++)
        {
            if (cor[i] == 'B')
            {
                if (LAdj[i].empty() == false)
                {
                    for (list<int>::iterator z = LAdj[i].begin(); z != LAdj[i].end(); z++)
                    {
                        int h = *z;
                        if (cor[h] == 'B')
                        {
                            DFS_VISIT(i);
                        }
                    }
                    cont++;
                }
            }
        }

        if (achouCiclo == true)
        {
            cout << "-1" << endl;
        }
        else
        {
            cout << cont << endl;
        }
    }
};

int main()
{
    int v, num, v1;

    while (cin >> v)
    {
        Grafo grafo(v);

        for (int i = 0; i < v; i++)
        {
            cin >> num;

            if (num != 0)
            {
                for (int i = 0; i < num; i++)
                {
                    cin >> v1;
                    grafo.AdicionaArestas(v1 - 1, i);
                }
            }
        }
        grafo.DFS();
    }

    return 0;
}