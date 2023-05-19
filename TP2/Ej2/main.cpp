#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> arista;

long long N, M;
//g es la representacion del grafo
//se piensa como listas de adyacencias por cada vertice, espacio: O(N + M)
vector<vector<int>> g;

int main() {
    cin >> N >> M;

    g.resize(N + 1, vector<int>(0));

    while (M--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    return 0;
}