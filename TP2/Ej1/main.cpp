#include <iostream>
#include <vector>

using namespace std;

int N, M;
//g es la representacion del grafo
//se piensa como map de vertices a vertices vecinos, espacio: O(N^2)
vector<vector<int>> g;

int main() {
    cin >> N >> M;
    g.resize(N+1, vector<int>(0, -1));

    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }

    return 0;
}