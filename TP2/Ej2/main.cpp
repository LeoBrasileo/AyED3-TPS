#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> arista;

long long N, M;
//g es la representacion del grafo
//se piensa como listas de adyacencias por cada vertice, espacio: O(N + M)
vector<vector<int>> g;
vector<vector<int>> g_t; //traspuesta
vector<bool> tiene_in;
vector<bool> fue_tirada;

void tirar_fichas(int v){
    fue_tirada[v] = true;
    for (int u : g[v]){
        if (!fue_tirada[u]){
            tirar_fichas(u);
        }
    }
}


/*idea:
1- buscar vertices con grado de entrada 1 y tirarlos con DFS
2- buscar componentes fuertemente conexas (Kosaraju)
3- por cada ciclo encontrado, es decir cada comp fuertemente conexa, tirar las fichas con menor num de vertice
 */

int main() {
    cin >> N >> M;

    tiene_in.assign(N, false);
    fue_tirada.assign(N, false);
    cant_en_pie = N;

    g.resize(N + 1, vector<int>(0));

    while (M--) {
        int u, v;
        cin >> u >> v;
        tiene_in[v]=true;
        g[u].push_back(v);
    }

    // Tiro todas las que tienen grado de entrada 0
    for (int i =0; i<N; i++){
        if(!tiene_in[i]){
            tirar_fichas(i);
        }
    }

    // A partir de acá sólo queda al menos una comp conexa con ciclo.

    

    return 0;
}