#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> arista; //peso | nodo1 | nodo2
typedef pair<int, int> arista_simple; //peso | nodo

int N, M, inf = 0x3f3f3f3f;

ofstream output_file;

vector<vector<arista_simple>> grafo, reves;
vector<arista> nuevas;

int minDistance(vector<int>& distancias, vector<bool>& visitados) {
    int minDist = inf;
    int minIndex = 0;

    for (int i = 1; i < distancias.size(); i++) {
        if (!visitados[i] && distancias[i] <= minDist) {
            minDist = distancias[i];
            minIndex = i;
        }
    }

    return minIndex;
}

vector<int> dijkstra(vector<vector<arista_simple>> &g, int s){
    vector<int> distancias;
    distancias.assign(N+1, inf);
    distancias[s] = 0;

    vector<bool> visitados = vector<bool>(N+1, false);

    for (int i = 1; i <= N - 1; i++) {
        int u = minDistance(distancias, visitados); // nodo con la distancia mínima
        visitados[u] = true;

        // Actualizar las distancias de los vecinos de u
        for (auto [w, v] : g[u]) {
            if (!visitados[v] && distancias[u] != inf && distancias[u] + w < distancias[v]) {
                distancias[v] = distancias[u] + w;
            }
        }
    }

    return distancias;
}

int costoOptimizado(int s, int t){
    vector<int> ds = dijkstra(grafo, s);
    vector<int> dt = dijkstra(reves, t);
    int dist = inf;

    for(int i = 0 ; i < nuevas.size() ; i++) {
        int u, v, d;
        tie(d,u,v) = nuevas[i];
        dist = min(ds[t], dist); //verificamos si no es infinito
        int temp = d + min(ds[u] + dt[v], ds[v] + dt[u]);
        if (temp < dist)
            dist = temp;
    }

    if (dist == inf) dist = -1; //en caso de que no exista camino devolvemos -1
    return dist;
}

double medirTiempo(int s, int t){
    auto start = chrono::high_resolution_clock::now();

    costoOptimizado(s, t);

    auto stop = chrono::high_resolution_clock::now();

    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    output_file.open("runtime_basic.csv", ios::app);
    int C, k, s, t;
    cin >> C;

    while (C--){
        cin >> N >> M >> k >> s >> t;
        reves.clear();
        grafo.clear();
        nuevas.clear();
        reves.resize(N+1);
        grafo.resize(N+1);
        for (int i = 0; i < M; i++){
            int d, c, l;
            cin >> d >> c >> l;
            grafo[d].push_back({l, c});
            reves[c].push_back({l, d});
        }

        for (int i = 0; i < k; i++){
            int uj, vj, qj;
            cin >> uj >> vj >> qj;
            nuevas.push_back({qj, uj, vj});
        }

        double tiempo = medirTiempo(s, t);

        output_file << M << "," << tiempo << "\n";
    }

    return 0;
}

