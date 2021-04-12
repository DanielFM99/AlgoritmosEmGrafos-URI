/*
NOME: Pedro Carvalho Pereira
Matricula: 201820265
NOME: Daniel Figueiredo Macedo
Matricula: 201820276
*/

#include <iostream>
#include <queue>

#define INFINITO 100000
using namespace std;

int main()
{
    int n, m;

    while (cin >> n >> m)
    {

        int matriz_adj[n + 1][n + 1] = {{0}}; #OK

        char cor[n + 1]; #OK //cores B= branco(não foi descoberto), C= cinza(descoberto que está na fila), P= preto(ja foi visitado), T= trancado(a sala do castelo não está aberta) 
        for (int i = 1; i < n + 1; i++) #OK
        {
            cor[i] = 'T'; #OK
        }
        cor[1] = 'C'; #OK //cor da sala inicial é setada para cinza, pois sempre estará aberta e é por aqui onde sempre começamos

        /*int dist[n + 1];
        for (int i = 1; i < n + 1; i++)
        {
            dist[i] = INFINITO;
        }
        dist[1] = 0; //distância da sala inicial sempre será 0*/

        int vertice1;
        int vertice2;

        for (int i = 0; i < m; i++) #OK
        { //completando a matriz de adjacência
            cin >> vertice1 >> vertice2;
            matriz_adj[vertice1][vertice2] = 1;
            matriz_adj[vertice2][vertice1] = 1;
        }

        int salaQseraDestrancada[n];
        int salaDaChave;

        for (int i = 2; i < n + 1; i++)
        { //completando o vetor com a posição das chaves para destrancar as salas
            cin >> salaDaChave;
            salaQseraDestrancada[i] = salaDaChave;
        }

        queue<int> verticesExplorados;
        queue<int> verticesAntigos;
        verticesExplorados.push(1);

        int u;
        int auxiliar = 1;
        for (int i = 2; i < n + 1; i++)
        {
            if (salaQseraDestrancada[i] == auxiliar)
            {
                cor[i] = 'B';
            }
        }
        while (verticesExplorados.empty() == false)
        {
            u = verticesExplorados.front();
            verticesAntigos.push(verticesExplorados.front());
            verticesExplorados.pop();

            while (auxiliar < n + 1)
            {
                if (matriz_adj[u][auxiliar] == 1)
                {

                    if (cor[auxiliar] == 'B')
                    {
                        cor[auxiliar] = 'C';

                        for (int i = 2; i < n + 1; i++)
                        {
                            if (salaQseraDestrancada[i] == auxiliar)
                            {
                                cor[i] = 'B';
                                while (verticesAntigos.empty() == false)
                                {
                                    verticesExplorados.push(verticesAntigos.front());
                                    verticesAntigos.pop();
                                }
                                verticesExplorados.push(u);
                            }
                        }

                        dist[auxiliar] = dist[u] + 1;
                        verticesExplorados.push(auxiliar);
                    }
                }
                auxiliar++;
            }
            auxiliar = 1;
            cor[u] = 'P';
        }

        int correto = 0;
        for (int i = 1; i < n + 1; i++)
        {
            if (cor[i] == 'P')
            {
                correto++;
            }
        }
        if (correto == n)
        {
            cout << "sim" << endl;
        }
        else
        {
            cout << "nao" << endl;
        }
    }
}