#include <bits/stdc++.h>

using namespace std;

typedef tuple<long long, long long, long long> arista; //peso | nodo1 | nodo2
typedef pair<long long, long long> arista_simple; //peso | nodo

long long N, M, inf = LLONG_MAX;

vector<vector<arista_simple>> grafo, reves;
vector<arista> nuevas;

vector<long long> dijkstra(vector<vector<arista_simple>> g, long long s){
    vector<long long> distancias;
    vector<bool> visitados = vector<bool>(N+1, false);
    distancias.resize(N+1, inf);
    distancias[s] = 0;

    priority_queue<arista_simple, vector<arista_simple>, greater<arista_simple>> min_heap;
    min_heap.push({0, s});

    while (!min_heap.empty()){
        long long dist, u;
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

long long costoOptimizado(long long s, long long t){
    vector<long long> ds = dijkstra(grafo, s);
    vector<long long> dt = dijkstra(reves, t);
    long long dist = ds[t];

    for (auto [qj, uj, vj] : nuevas){
        if (ds[uj] != inf && dt[vj] != inf && ds[uj] + qj + dt[vj] < dist)
            dist = ds[uj] + qj + dt[vj];
    }

    if (dist == inf) dist = -1; //en caso de que no exista camino devolvemos -1
    return dist;
}

int main() {
    long long C, k, s, t;
    cin >> C;

    while (C--){
        cin >> N >> M >> k >> s >> t;
        reves.resize(N+1);
        grafo.resize(N+1);
        for (long long i = 0; i < M; i++){
            long long d, c, l;
            cin >> d >> c >> l;
            grafo[d].push_back({l, c});
            reves[c].push_back({l, d});
        }

        for (long long i = 0; i < k; i++){
            long long uj, vj, qj;
            cin >> uj >> vj >> qj;
            nuevas.push_back({qj, uj, vj});
        }

        long long res = costoOptimizado(s, t);
        cout << res << endl;

        reves.clear();
        grafo.clear();
        nuevas.clear();

        //complejidad final: O((N+M)logN)
    }

    return 0;
}
