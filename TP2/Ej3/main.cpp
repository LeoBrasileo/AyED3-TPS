#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> arista;
using ll = long long;
const ll inf = 1e18;

int N, R, W, U, V;
double costoUtp = 0, costoFibra = 0;
vector<tuple<double,int,int,bool>> E, AGM;
vector<vector<pair<int, double>>> g;

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
    //basado en implementacion vista en clase
    sort(E.begin(),E.end());
    int aristas = 0;
    DSU dsu(N);
    for(auto [c,u,v,utp] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            aristas++;
            AGM.push_back({c,u,v,utp});
        }
    }
    if(aristas == N-1) {
        //saco las W-1 aristas mas pesadas
        for (int i = 0; i < W-1; i++){
            AGM.pop_back();
        }

        for(auto [c,u,v,utp] : AGM){
            if (utp) costoUtp += c;
            else costoFibra += c;
        }
    }
}

double distancia(int v1, int u1, int v2, int u2){
    int distV = v1-v2;
    int distU = u1-u2;
    return sqrt(distV*distV + distU*distU);
}

int main() {
    int C;
    cin >> C;
    for (int i = 1; i <= C; i++) {
        cin >> N >> R >> W >> U >> V;
        g = vector<vector<pair<int, double>>>(N);
        vector<arista> aristas;
        for(int i = 0; i < N; i++){
            int x, y;
            cin >> x >> y;
            aristas.push_back({x,y});
        }

        //armado de aristas con pesos
        for(int i = 0; i < N; i++){
            for(int j = i+1; j < N; j++){
                arista a = aristas[i];
                arista b = aristas[j];
                double costo = distancia(a.first,a.second,b.first,b.second);
                bool utp = costo <= R;
                costo = costo <= R ? costo * U : costo * V; //si es menor a R, uso UTP, sino fibra optica
                E.push_back({costo,i,j, utp});
            }
        }

        kruskal();

        cout << "Caso #" << i << ": " << fixed << setprecision(3) << costoUtp << " " << costoFibra << "\n";

        //limpiar para prox test
        costoFibra = costoUtp = 0;
        AGM.clear();
        E.clear();
        g.clear();
    }

    return 0;
}