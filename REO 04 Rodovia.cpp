// Daniel Figueiredo Macedo - 14A - 201820276
// Pedro Carvalho Pereira - 14A - 201820265
// A ser corrigido no perfil Daniel Macedo

#include <iostream>

using namespace std;

int main()
{
    int grauEntrada[10000];
    int grauSaida[10000];
    int visitado[10000];
    int adjacente[10000];
    int n, v1, v2;
    int resposta = 0;
    int j = 1;
    bool check = true;

    cin >> n;

    for (int i = 1; i <= n; i++) //preenche as rodovias que ligam os pares de cidades
    {
        cin >> v1 >> v2;
        adjacente[v1] = v2;
        grauSaida[v1]++;
        grauEntrada[v2]++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (grauEntrada[i] > 1 or grauSaida[i] > 1) //se alguma cidade possuir mais de uma rodovia entrando ou saindo, então não é possível chegar a qualquer outra cidade usando só as novas "n" rodovias (quarta condição do exercício)
        {
            check = false;
        }
    }

    while (visitado[j] == false)
    {
        visitado[j] = true;
        j = adjacente[j];
        resposta++;
    }

    if (resposta < n) //se o caminho percorrido no laço acima não percorrer todas cidades, então não é possível chegar a qualquer outra cidade usando só as novas "n" rodovias (quarta condição do exercício)
    {
        check = false;
    }

    if (check == false)
    {
        cout << 'N' << endl; //endl usado pois sem ele o Uri acusava "Presentation error"
        return 0;
    }

    if (check == true)
    {
        cout << 'S' << endl; //endl usado pois sem ele o Uri acusava "Presentation error"
        return 0;
    }
}