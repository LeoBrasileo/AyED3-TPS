#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef pair<int, int> arista;

long long N, M, jugadasTotales;
//g es la representacion del grafo
//se piensa como listas de adyacencias por cada vertice, espacio: O(N + M)
vector<arista> puentes;
vector<vector<int>> g;

vector<bool> visitados;
vector<int> tin, low;
int timer;

void dfsPuentes(int v, int padre) {
    visitados[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : g[v]) {
        if (to == padre) continue;
        if (visitados[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfsPuentes(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
            {
                puentes.push_back({v, to});
                puentes.push_back({to, v});
            }
        }
    }
}

void buscarPuentes() {
    timer = 0;
    visitados = vector<bool>(N+1, false);
    tin = vector<int>(N+1, -1);
    low = vector<int>(N+1, -1);
    for (int i = 1; i <= N; i++) {
        if (!visitados[i])
            dfsPuentes(i, 0);
    }
}

void dfsComponentes(int v, int &tamComponente){
    visitados[v] = true;
    tamComponente++;
    for (int u : g[v]) {
        if (!visitados[u]) {
            dfsComponentes(u, tamComponente);
        }
    }
}

void calcVerticesxComponente(vector<int> &verticesPorComponente){
    visitados = vector<bool>(N+1, false);

    for(int i = 1; i <= N; i++){
        if(!visitados[i]){
            int tamComponente = 0;
            dfsComponentes(i, tamComponente);
            verticesPorComponente.push_back(tamComponente);
        }
    }
}

double probaGanar() {
    //codigo dfsPuentes y busqueda de puentes de https://cp-algorithms.com/graph/bridge-searching.html#implementation
    //tambien se usa conocimiento de clase recorridos (BFS y DFS)
    buscarPuentes();

    //eliminar puentes del grafo original,
    //me quedo con un grafo en el que se que Tuki gana si elige 2 vertices de la misma componente
    for (arista puente : puentes){
        int u = puente.first;
        int v = puente.second;
        g[u].erase(find(g[u].begin(), g[u].end(), v));
    }

    //calcular componentes conexas y cantidad de vertices en cada una de ellas
    vector<int> verticesPorComponente;
    calcVerticesxComponente(verticesPorComponente);

    //ganadas = sumatoria de (Vi * (Vi - 1) / 2) de i = 1 a #componentes
    //donde Vi es la cantidad de vertices en la componente i
    long long jugadasGanadas = 0;
    for(long long vi : verticesPorComponente){
        if (vi > 1)
            jugadasGanadas += (vi * (vi - 1)) / 2;
    }

    return (double)jugadasGanadas / jugadasTotales;
}

int main() {
    cin >> N >> M;

    jugadasTotales = (N * (N - 1)) / 2;

    g.resize(N + 1, vector<int>(0));

    while (M--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    double res = 1.0 - probaGanar();

    cout << fixed;
    cout << setprecision(5) << res;

    return 0;
}