#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<double, double> iPair;

struct Graph
{
    int V, E;
    vector<pair<double, iPair>> aresta;

    Graph(int V, int E) // construtor do grafo
    {
        this->V = V;
        this->E = E;
    }

    void adicionaAresta(int u, int v, double w) // método que liga um vértice ao outro com um peso
    {
        aresta.push_back({w, {u, v}});
    }

    double distance(double x1, double y1, double x2, double y2) // pegar a distância de um vértice x1y1 ao vértice x2y2
    {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    double kruskal();
};

struct DisjointSets
{
    int *parent, *rnk;
    int n;

    DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];

        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            parent[i] = i;
        }
    }

    int find(int u)
    {

        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

double Graph::kruskal()
{
    double mst_wt = 0;

    sort(aresta.begin(), aresta.end());

    DisjointSets ds(V);

    vector<pair<double, iPair>>::iterator it;
    for (it = aresta.begin(); it != aresta.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {

            mst_wt += it->first;

            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}

int main()
{
    int casoTeste;
    cin >> casoTeste;

    for (int i = 0; i < casoTeste; i++)
    {
        int vertice, aresta;
        double cordX, cordY;

        cin >> vertice;

        aresta = (vertice * (vertice - 1)) / 2;

        Graph g(vertice, aresta);

        double matriz[2][vertice];

        for (int i = 0; i < vertice; i++)
        {
            cin >> cordX >> cordY;
            matriz[0][i] = cordX;
            matriz[1][i] = cordY;
        }

        for (int i = 0; i < vertice; i++)
        {
            for (int j = i + 1; j < vertice; j++)
            {
                g.adicionaAresta(i, j, g.distance(matriz[0][i], matriz[1][i], matriz[0][j], matriz[1][j]));
            }
        }

        double mst_wt = g.kruskal();

        cout << fixed << setprecision(2) << mst_wt / 100 << endl;
    }

    return 0;
}