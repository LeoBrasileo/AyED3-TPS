#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> arista;

long long N, M;
//g es la representacion del grafo
//se piensa como listas de adyacencias por cada vertice, espacio: O(N + M)
vector<vector<int>> g;
vector<vector<int>> g_t; //traspuesta
vector<bool> tieneIn0;

/*idea:
1- buscar vertices con grado de entrada 1 y tirarlos con DFS
2- buscar componentes fuertemente conexas (Kosaraju)
3- por cada ciclo encontrado, es decir cada comp fuertemente conexa, tirar las fichas con menor num de vertice
 */

int main() {
    cin >> N >> M;

    g.resize(N + 1, vector<int>(0));

    while (M--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g_t[v].push_back(u);
    }

    return 0;
}