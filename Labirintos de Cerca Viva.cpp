// Daniel Figueiredo Macedo - 14A - 201820276
// Pedro Carvalho Pereira - 14A - 201820265
// A ser corrigido no perfil Daniel Macedo
// Alguns trechos do código foram retirados do site www.geeksforgeeks.org e foram modificados de acordo com a necessidade do exercício

#include <iostream>
#include <list>
#include <stack>
#define TAM 20000
using namespace std;

class Grafo
{
    int V;

    list<int> *adj; //lista de adjacência
    void encontraPontesAux(Grafo g2, int v, bool visitado[], int descoberto[], int menor[],
                           int parente[]);

public:
    Grafo(int V);
    void adicionaArestas(int v, int w);
    void encontraPontes(Grafo g2);
    int percorre(int s, int t);
};

Grafo::Grafo(int V) //construtor do grafo
{
    this->V = V;
    adj = new list<int>[TAM];
}

int Grafo::percorre(int s, int t) //função que checa se a sala inicial do labirinto se conecta com a sala final através de pontes
{
    int visitado[TAM];
    for (int i = 0; i < V; i++)
    {
        visitado[i] = false;
    }
    visitado[s] = true;

    stack<int> pilha;

    pilha.push(s);

    while (pilha.empty() == false)
    {
        s = pilha.top();
        pilha.pop();

        if (s == t)
        {
            return 1;
        }

        if (visitado[s] == false)
        {
            visitado[s] = true;
        }

        for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
            if (visitado[*i] == false)
                pilha.push(*i);
    }
    return 0;
}

void Grafo::adicionaArestas(int v, int w) //função que liga dois vértices entre si
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Grafo::encontraPontesAux(Grafo g2, int u, bool visitado[], int descoberto[], int menor[], int parente[]) //função iterativa que encontra as pontes e preenche o grafo g2 com elas
{

    static int tempo = 0;

    visitado[u] = true;

    descoberto[u] = menor[u] = ++tempo;

    for (list<int>::iterator i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;

        if (visitado[v] == false)
        {
            parente[v] = u;
            encontraPontesAux(g2, v, visitado, descoberto, menor, parente);

            menor[u] = min(menor[u], menor[v]);

            if (menor[v] > descoberto[u])
            {
                g2.adicionaArestas(u, v);
            }
        }

        else if (v != parente[u])
            menor[u] = min(menor[u], descoberto[v]);
    }
}

void Grafo::encontraPontes(Grafo g2) //função que chama a função encontraPontesAux para cada vértice não visitado, e que "seta" todos vértices inicialmente como não visitados (-1)

{

    bool *visitado = new bool[TAM];
    int *descoberto = new int[TAM];
    int *menor = new int[TAM];
    int *parente = new int[TAM];

    for (int i = 0; i < V; i++)
    {
        parente[i] = -1;
        visitado[i] = false;
    }
    for (int i = 0; i < V; i++)
        if (visitado[i] == false)
            encontraPontesAux(g2, i, visitado, descoberto, menor, parente);
}

int main()
{

    int r, c, q, a, b, s, t, resposta;
    cin >> r >> c >> q; //entrada da quantidade de vértices, arestas e consultas
    while (r != 0 and c != 0 and q != 0)
    {
        Grafo g1(TAM); //grafo g1 original
        Grafo g2(TAM); //grafo g2 com somente as pontes do grafo original

        for (int i = 0; i < c; i++)
        {
            cin >> a >> b; //entrada dos vértices que serão ligados entre si
            g1.adicionaArestas(a, b);
        }
        g1.encontraPontes(g2);
        for (int i = 0; i < q; i++)
        {
            cin >> s >> t; //entrada dos vértices que serão consultados se possuem somente um caminho simples
            resposta = g2.percorre(s, t);
            if (resposta == 1)
            {
                cout << 'Y' << endl;
            }
            else
            {
                cout << 'N' << endl;
            }
        }
        cout << '-' << endl;
        cin >> r >> c >> q;
    }

    return 0;
}