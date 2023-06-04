#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits.h>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> arista; //peso | nodo1 | nodo2
typedef pair<int, int> aristaSimple; //peso | nodo

long long N, M, inf = LLONG_MAX;

vector<vector<aristaSimple>> grafo, reves;
vector<arista> nuevas;

vector<long long> dijkstra(vector<vector<aristaSimple>> g, int s){
    vector<long long> distancias;
    vector<bool> visitados = vector<bool>(N+1, false);
    distancias.resize(N+1, inf);
    distancias[s] = 0;

    priority_queue<aristaSimple, vector<aristaSimple>, greater<aristaSimple>> min_heap;
    min_heap.push({0, s});

    while (!min_heap.empty()){
        int dist, u;
        tie(dist, u) = min_heap.top();
        min_heap.pop();

        if (visitados[u]){
            continue;
        }

        visitados[u] = true;

        for (auto [w, v] : g[u]){
            //relajacion
            if(distancias[u] != inf && distancias[v] > distancias[u] + w){
                distancias[v] = distancias[u] + w;
                min_heap.push({distancias[v], v});
            }
        }
    }

    return distancias;
}

long long costoOptimizado(int s, int t){
    vector<long long> ds = dijkstra(grafo, s);
    vector<long long> dt = dijkstra(reves, t);
    int dist = ds[t];

    for (auto [qj, uj, vj] : nuevas){
        if (ds[uj] + qj + dt[vj] < dist)
            dist = ds[uj] + qj + dt[vj];
    }

    return dist;
}

int main() {
    int C, k, s, t;
    cin >> C;

    while (C--){
        cin >> N >> M >> k >> s >> t;
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

        long long res = costoOptimizado(s, t);
        cout << res << endl;

        //complejidad final: O((N+M)logN)
    }

    return 0;
}
