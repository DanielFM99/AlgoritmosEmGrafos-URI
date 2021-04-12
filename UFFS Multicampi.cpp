// Daniel Figueiredo Macedo - 14A - 201820276
// Pedro Carvalho Pereira - 14A - 201820265
// A ser corrigido no perfil Daniel Macedo
// Alguns trechos do código foram retirados do site www.geeksforgeeks.org e do fóruns do URI e foram modificados de acordo com a necessidade do exercício

#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>

#define MAX 11000

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
map<int, vector<ii>> grafo;
vector<int> distancia;
bool visited[MAX][MAX];

queue<iii> fila;

int BFSAux(vector<int> &distancia)
{
    while (fila.empty() == false)
    {
        iii p = fila.front();
        int u = p.second.second;
        int l = p.second.first;
        int c = p.first;
        fila.pop();

        for (int i = 0; i < grafo[u].size(); i++)
        {
            ii x = grafo[u][i];
            int v = x.first;
            int linhat = x.second;
            if (linhat != l)
            {
                if (distancia[v] > c + 1)
                {
                    distancia[v] = c + 1;
                    fila.push(make_pair(c + 1, make_pair(linhat, v)));
                }
            }
            else
            {
                if (distancia[v] > c)
                {
                    distancia[v] = c;
                    fila.push(make_pair(c, make_pair(linhat, v)));
                }
            }
        }
    }
}

int BFS(int dest)
{
    distancia.assign(MAX, MAX);
    distancia[1] = 0;
    fila.push(make_pair(0, make_pair(-1, 1)));
    BFSAux(distancia);
    return distancia[dest];
}
void Print()
{
    int n, k, l, b;
    cin >> n >> k;

    for (int i = 0; i < k; i++)
    {
        cin >> l;
        int a = 0;
        for (int j = 0; j < l; j++)
        {
            cin >> b;
            if (a != 0)
            {
                if (visited[a][b] == false)
                {
                    grafo[a].push_back(make_pair(b, i));
                    grafo[b].push_back(make_pair(a, i));
                    visited[a][b] = true;
                }
            }
            a = b;
        }
    }
    cout << BFS(n) << endl;
}

int main()
{
    Print();
}