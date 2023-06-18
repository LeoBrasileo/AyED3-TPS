#include <bits/stdc++.h>
//importar Boost para usar la implementacion fibonacci. https://www.boost.org/
#include <boost/heap/fibonacci_heap.hpp>

using namespace std;

typedef tuple<int, int, int> arista; //peso | nodo1 | nodo2
typedef pair<int, int> arista_simple; //peso | nodo

int N, M, inf = 0x3f3f3f3f;

ofstream output_file;

vector<vector<arista_simple>> grafo, reves;
vector<arista> nuevas;

vector<int> dijkstra(vector<vector<arista_simple>> &g, int s){
    vector<int> distancias;
    distancias.assign(N+1, inf);
    distancias[s] = 0;

    boost::heap::fibonacci_heap<arista_simple, boost::heap::compare<std::greater<arista_simple>>> fib_heap;
    fib_heap.push({0, s});

    while (!fib_heap.empty()){
        int dist, u;
        tie(dist, u) = fib_heap.top();
        fib_heap.pop();

        if (distancias[u] < dist){
            continue;
        }

        for (auto [w, v] : g[u]){
            //relajacion
            if(distancias[u] != inf && distancias[v] > distancias[u] + w){
                distancias[v] = distancias[u] + w;
                fib_heap.push({distancias[v], v});
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
    int repeat = 10;
    double counter = 0;

    for (int ignore = 0; ignore < repeat; ignore++){
        auto start = chrono::high_resolution_clock::now();

        costoOptimizado(s, t);

        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = stop - start;
        counter += diff.count();
    }

    return counter / repeat;
}

int main() {
    output_file.open("runtime_fibonacci.csv", ios::app);
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

        int tiempo = medirTiempo(s, t);

        output_file << N << "," << tiempo << "\n";
    }

    return 0;
}
