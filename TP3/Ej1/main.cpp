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

vector<vector<aristaSimple>> grafo;
vector<arista> nuevas;
vector<vector<int>> ady; //lista de adyacencias

vector<long long> dijkstra(int s){
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

        for (auto [w, v] : grafo[u]){
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
    vector<long long> ds = dijkstra(s);
    int dist = ds[t];

    for (auto [qj, uj, vj] : nuevas){
        vector<long long> dv = dijkstra(vj);
        if (ds[uj] + qj + dv[t] < dist)
            dist = ds[uj] + qj + dv[t];
    }

    return dist;
}

int main() {
    int C, k, s, t;
    cin >> C;

    while (C--){
        cin >> N >> M >> k >> s >> t;
        ady.resize(N+1);
        grafo.resize(N+1);
        for (int i = 0; i < M; i++){
            int d, c, l;
            cin >> d >> c >> l;
            grafo[d].push_back({l, c});
            ady[d].push_back(c);
        }

        for (int i = 0; i < k; i++){
            int uj, vj, qj;
            cin >> uj >> vj >> qj;
            nuevas.push_back({qj, uj, vj});
        }

        long long res = costoOptimizado(s, t);
        cout << res << endl;

        //complejidad final: O(k(N+M)logN)
        //tomando k acotado < 300, seria O((N+M)logN)
    }

    return 0;
}
