#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef pair<int, int> arista;

int N, M;
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
    visitados.assign(N, false);

    for(int i = 1; i < N; i++){
        if(!visitados[i]){
            int tamComponente = 0;
            dfsComponentes(i, tamComponente);
            verticesPorComponente.push_back(tamComponente);
        }
    }
}

void buscarPuentes() {
    timer = 0;
    visitados.assign(N, false);
    tin.assign(N, -1);
    low.assign(N, -1);
    for (int i = 0; i < N; ++i) {
        if (!visitados[i])
            dfsPuentes(i);
    }
}

int calcularJugadasGanadas() {
    //codigo dfsPuentes y busqueda de puentes de https://cp-algorithms.com/graph/bridge-searching.html#implementation
    //tambien se usa conocimiento de clase recorridos (BFS y DFS)
    buscarPuentes();

    //eliminar puentes del grafo original,
    //me quedo con un grafo en el que se que Tuki gana si elige 2 vertices de la misma componente
    for (int i = 0; i < puentes.size(); i++){
        int u = puentes[i].first;
        int v = puentes[i].second;
        g[u].erase(find(g[u].begin(), g[u].end(), v));
        g[v].erase(find(g[v].begin(), g[v].end(), u));
    }

    //calcular componentes conexas y cantidad de vertices en cada una de ellas
    vector<int> verticesPorComponente;
    calcVerticesxComponente(verticesPorComponente);

    //ganadas = sumatoria de (Vi * (Vi - 1) / 2) de i = 1 a #componentes
    //donde Vi es la cantidad de vertices en la componente i
    int ganadas = 0;
    for(int i = 0; i < verticesPorComponente.size(); i++){
        int vi = verticesPorComponente[i];
        ganadas += vi * (vi - 1) / 2;
    }

    return ganadas;
}

double probaPerder(int jugadasGanadas){
    int jugadasTotales = N * (N - 1) / 2;

    return 1 - (double)jugadasGanadas / jugadasTotales;
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

    int ganadas = calcularJugadasGanadas();
    double res = probaPerder(ganadas);

    cout << fixed;
    cout << setprecision(5) << res;

    return 0;
}