//Daniel Figueiredo Macedo - 14A - 201820276
//Pedro Carvalho Pereira - 14A - 201820265

#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
#define MAX 1000

class Grafo
{
private:
    int quantVert;
    int vertices[MAX][MAX] = {0};
    int *amigos;

public:
    Grafo(int numVert)
    {
        quantVert = numVert;
        amigos = new int[numVert];

        for (int i = 0; i < numVert; i++)
        {
            amigos[i] = 0;
        }
    }

    void adicionarAresta(int v1, int v2)
    {
        amigos[v1]++;
        amigos[v2]++;
        vertices[v1][v2] = vertices[v2][v1] = 1;
    }

    list<int> BuscaProfundidade(int k)
    {
        bool entrou = false;
        list<int> resultado;
        if (k == 0)
        {
            for (int i = 0; i < quantVert; i++)
            {
                resultado.push_back(i + 1); //é incrementado +1 para que a saída esteja de acordo com a entrada
            }
        }
        else
        {
            for (int i = 0; i < quantVert; i++)
            {
                if (amigos[i] > 0 && amigos[i] < k)
                {
                    remove(k, i); //pessoa que não pode entrar na festa é removida
                }
            }

            for (int i = 0; i < quantVert; i++)
            {
                if (amigos[i] > 0)
                {
                    entrou = true;              //checa se pelo menos 1 pessoa pode entrar na festa
                    resultado.push_back(i + 1); //adiciona na lista as pessoas que podem entrar na festa
                }
            }
            if (entrou == false) //se ninguém pode entrar na festa, o resultado retorna 0
            {
                resultado.push_back(0);
            }
        }
        return resultado;
    }

private:
    void remove(int k, int a)
    {
        amigos[a] = 0;
        for (int i = 0; i < quantVert; i++)
        {
            if (vertices[a][i] != 0)
            {
                vertices[a][i] = vertices[i][a] = 0;

                amigos[i]--;

                if (amigos[i] > 0 && amigos[i] < k)
                {
                    remove(k, i);
                }
            }
        }
    }
};

int main()
{
    int n; // número de pessoas na comunidade (vertices)
    int m; // número de relações de amizade (arestas)
    int k; // número mínimo de amigos convidados uma pessoa precisa ter para ser convidada

    while (cin >> n >> m >> k)
    {
        list<int> convidados;
        Grafo grafo(n);
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--; //para que o vetor amigos[] da classe Grafo use a posição 0, é decrementado 1 da entrada "a" e "b" para que entre corretamente na função adicionarAresta
            grafo.adicionarAresta(a, b);
        }
        convidados = grafo.BuscaProfundidade(k);
        bool comeco = true;
        for (auto i = convidados.begin(); i != convidados.end(); ++i)
        {
            if (comeco)
            {
                cout << *i;
                comeco = false;
            }
            else
            {
                cout << " " << *i;
            }
        }
        cout << endl;
    }
    return 0;
}