// Daniel Figueiredo Macedo - 14A - 201820276
// Pedro Carvalho Pereira - 14A - 201820265
// A ser corrigido no perfil Daniel Macedo
// Alguns trechos do código foram retirados do site www.geeksforgeeks.org e adaptados ao exercício

#include <iostream>
#include <list> //
#include <queue>
#define INFINITO 9999999999 //valor muito alto para representar o infinito do algoritmo de Dijkstra e também pelo fato do Uri acusar Wrong Answer (5%) para o quando o valor não é extremamente grande

using namespace std;

class Grafo
{
private:
    int V;

    list<pair<int, int>> *adj; //lista de pair usada para associar um vértice ao outro na lista de adjacência juntamente com o respectivo custo da aresta

public:
    Grafo(int V) //construtor do grafo
    {
        this->V = V;

        adj = new list<pair<int, int>>[V];
    }

    void addAresta(int v1, int v2, int custo) //função que liga os vértices entre si e associa um peso à sua respectiva aresta (direcionada, v1 -> v2)
    {
        adj[v1].push_back(make_pair(v2, custo));
    }

    int dijkstra(int orig, int dest) //algoritmo de Dijkstra
    {

        int dist[V]; //vetor que guarda as distâncias

        int visitados[V]; //vetor para guardar se o vértice já foi visitado

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //fila de prioridade para os vértices a serem visitados (equivalente a uma heap mínima)

        for (int i = 0; i < V; i++) //por padrão, a distância começa como infinito e todos os vértices como não visitados
        {
            dist[i] = INFINITO;
            visitados[i] = false;
        }

        dist[orig] = 0; //o vértice origem, como exceção, inicia como 0

        pq.push(make_pair(dist[orig], orig)); //o primeiro vértice na fila de prioridade é a origem

        while (pq.empty() == false) //enquanto a fila de prioriodade não está vazia, executa o loop
        {
            pair<int, int> p = pq.top(); //associa o primeiro elemento da fila de prioridade à uma variável "p"
            int u = p.second;            //associa o vértice desse pair à uma variável "u"
            pq.pop();                    //remove este pair da fila de prioridade

            if (visitados[u] == false) //se o vértice que foi extraído acima não foi visitado ainda, executa a condição

            {
                visitados[u] = true; //marca o vértice como visitado

                list<pair<int, int>>::iterator i; //iterador para lista

                for (i = adj[u].begin(); i != adj[u].end(); i++) //percorre todos os vértices adjacentes a "u"
                {
                    int v = i->first;  //associa o vértice adjacente à uma variável "v"
                    int w = i->second; //associa o custo da aresta que liga ao vértice adjacente à uma variável "w"

                    if (dist[v] > (dist[u] + w)) //se a distância associada ao vértice "v" (inicialmente infinita) for maior que a distância associada ao vértice "u" (inicialmente 0) somado à distância da aresta "w", executa a condição
                    {
                        //relaxamento
                        dist[v] = dist[u] + w;          //troca a distância associada à "v" (inicialmente infinita) pela distância associada ao vértice "u" (inicialmente 0) somado ao custo da aresta "w" que liga "u" à "v"
                        pq.push(make_pair(dist[v], v)); //insere o vértice "v" e seu respectivo custo à fila de prioridade
                    }
                }
            }
        }

        return dist[dest]; //retorna apenas a distância mínima até o destino
    }
};

int main()
{

    int numVert, numAresta, vert1, vert2, transporte, custo, custoOnibus, custoAviao;
    while (cin >> numVert >> numAresta)
    {

        Grafo gOnibus(numVert); //grafo com apenas os caminhos percorridos por ônibus
        Grafo gAviao(numVert);  //grafo com apenas os caminhos percorridos por avião

        for (int i = 0; i < numAresta; i++)
        {
            cin >> vert1 >> vert2 >> transporte >> custo;
            if (transporte == 0) //valor 0 associado ao transporte por ônibus
            {
                gOnibus.addAresta(vert1 - 1, vert2 - 1, custo);
            }
            else //valor 1 associado ao transporte por avião
            {
                gAviao.addAresta(vert1 - 1, vert2 - 1, custo);
            }
        }

        custoOnibus = gOnibus.dijkstra(0, numVert - 1); //distância mínima percorrida de pelo ônibus do vértice de origem até o destino
        custoAviao = gAviao.dijkstra(0, numVert - 1);   //distância mínima percorrida de pelo avião do vértice de origem até o destino

        if (custoOnibus > custoAviao) //condição para comparar qual dos transportes percorreu o menor caminho a partir do vértice de origem até o destino
        {
            cout << custoAviao << endl;
        }
        else
        {
            cout << custoOnibus << endl;
        }
    }

    return 0;
}