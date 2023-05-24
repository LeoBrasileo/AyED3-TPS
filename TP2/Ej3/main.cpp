#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> arista;
using ll = long long;
const ll inf = 1e18;

int N, R, W, U, V;
vector<tuple<ll,int,int>> E;
vector<vector<int>> g;

struct DSU{
    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }
    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }
    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }
    vector<int> padre;
    vector<int> rank;
};

void kruskal(){
    sort(E.begin(),E.end());
    ll res = 0;
    int aristas = 0;
    DSU dsu(N);
    for(auto [c,u,v] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            aristas++;
            g[u].push_back(v);
            g[v].push_back(u);
            res += c;
        }
    }
    if(aristas == N-1) cout<<res<<endl;
    else cout<<"IMPOSSIBLE\n";
}

double distancia(int v1, int u1, int v2, int u2){
    int distV = v1-v2;
    int distU = u1-u2;
    return sqrt(distV*distV + distU*distU);
}

int main() {
    int C;
    cin >> C;
    while (C--){
        cin >> N >> R >> W >> U >> V;
        g = vector<vector<int>>(N);
        vector<arista> aristas;
        for(int i = 0; i < N; i++){
            int x, y;
            cin >> x >> y;
            aristas.push_back({x,y});
        }

        //armado de aristas con pesos
        for(int i = 0; i < N; i++){
            for(int j = i+1; j < N; j++){
                double dist = distancia(aristas[i].first,aristas[i].second,aristas[j].first,aristas[j].second);
                E.push_back({dist,i,j});
            }
        }
        kruskal();

        //limpiar para prox test
        E.clear();
        g.clear();
    }

    return 0;
}