#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef pair<int, int> arista;

long long N, M;
//g es la representacion del grafo
//se piensa como listas de adyacencias por cada vertice, espacio: O(N + M)
vector<arista> puentes;
vector<vector<int>> g;

vector<bool> visitados;
vector<int> tin, low;
int timer;

void dfsPuentes(int v, int padre = -1) {
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
            }
        }
    }
}

void buscarPuentes() {
    timer = 0;
    visitados.assign(N+1, false);
    tin.assign(N+1, -1);
    low.assign(N+1, -1);
    for (int i = 0; i < N; ++i) {
        if (!visitados[i])
            dfsPuentes(i);
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
    visitados.assign(N+1, false);

    for(int i = 1; i < N; i++){
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
        g[v].erase(find(g[v].begin(), g[v].end(), u));
    }

    //calcular componentes conexas y cantidad de vertices en cada una de ellas
    vector<int> verticesPorComponente;
    calcVerticesxComponente(verticesPorComponente);

    //ganadas = sumatoria de (Vi * (Vi - 1) / 2) de i = 1 a #componentes
    //donde Vi es la cantidad de vertices en la componente i
    long long jugadasGanadas = 0;
    for(int vi : verticesPorComponente){
        jugadasGanadas += vi * (vi - 1) / 2;
    }
    long long jugadasTotales = N * (N - 1) / 2;

    return (double)jugadasGanadas / (double)jugadasTotales;
}

int main() {
    cin >> N >> M;

    g.resize(N + 1, vector<int>(0));

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    double ganar = probaGanar();
    double res = 1.0 - ganar;

    cout << fixed;
    cout << setprecision(5) << res;

    return 0;
}