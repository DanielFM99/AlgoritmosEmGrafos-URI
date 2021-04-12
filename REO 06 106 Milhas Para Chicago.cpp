// Daniel Figueiredo Macedo - 14A - 201820276
// Pedro Carvalho Pereira - 14A - 201820265
// A ser corrigido no perfil Daniel Macedo
// Alguns trechos do código foram retirados do site www.geeksforgeeks.org e adaptados ao exercício

#include <iostream>
#include <iomanip> // para usar fixed e setprecision

using namespace std;

void floydWarshall(int V, double dist[][101]) // algoritmo de Floyd-Warshall com uma modificação no final, alterando a operação de soma por multiplicação e a comparação de menor para maior
{
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
            {
                if (dist[i][k] * dist[k][j] > dist[i][j])
                    dist[i][j] = dist[i][k] * dist[k][j];
            }
}

int main()
{
    int n, m; // vértices e arestas

    double dist[101][101]; // matriz com o tamanho máximo especificado na atividade

    while (cin >> n >> m)
    {
        for (int i = 0; i < 101; i++) // inicializa a matriz com 0 em todas posições
        {
            for (int j = 0; j < 101; j++)
            {
                dist[i][j] = 0;
            }
        }

        for (int i = 0; i < m; ++i)
        {
            int a, b, p; // vértice 1, vertice 2 e peso
            cin >> a >> b >> p;
            dist[a - 1][b - 1] = p * 0.01; // peso da aresta que liga o vértice 1 ao vértice 2 multiplicado por 0.01 por se tratar de porcentagem
            dist[b - 1][a - 1] = p * 0.01; // como especificado na atividade, todas as arestas são nas duas direções
        }

        floydWarshall(n, dist);

        cout << fixed << setprecision(6) << dist[0][n - 1] * 100 << ' ' << "percent" << endl; // fixed e setprecision(6) para formatar a saída para ter sempre 6 casas decimais
    }
}