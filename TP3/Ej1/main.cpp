#include <iostream>
#include <tuple>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

typedef tuple<int, int, int> arista; //peso | nodo1 | nodo2
typedef pair<int, int> arista_simple; //peso | nodo

int N, M, inf = 0x3f3f3f3f;

vector<vector<arista_simple>> grafo, reves;
vector<arista> nuevas;

vector<int> dijkstra(vector<vector<arista_simple>> &g, int s){
    vector<int> distancias;
    distancias.assign(N+1, inf);
    distancias[s] = 0;

    priority_queue<arista_simple, vector<arista_simple>, greater<arista_simple>> min_heap;
    min_heap.push({0, s});

    while (!min_heap.empty()){
        int dist, u;
        tie(dist, u) = min_heap.top();
        min_heap.pop();

        if (distancias[u] < dist){
            continue;
        }

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

int main() {
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

        int res = costoOptimizado(s, t);
        cout << res << endl;

        //complejidad final: O((N+M)logN)
    }

    return 0;
}
