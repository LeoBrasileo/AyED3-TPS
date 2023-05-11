#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

enum NODO_ESTADO {
    NO_LO_VI = -1, EMPECE_A_VER = 0, TERMINE_DE_VER = 1
};

int N, M;
//g es la representacion del grafo
//se piensa como map de vertices a vertices vecinos, espacio: O(N^2)
vector<vector<int>> g;
vector<int> estado;
vector<vector<int>> treeEdges;
vector<int> backConExtremoInferiorEn;
vector<int> backConExtremoSuperiorEn;
vector<int> memo;

void dfs(int v, int padre = -1) {
    estado[v] = EMPECE_A_VER;

    for (int u: g[v]) {
        if (estado[u] == NO_LO_VI) {
            treeEdges[v].push_back(u);
            dfs(u, v);
        } else if (u != padre) {
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }

    estado[v] = TERMINE_DE_VER;
}

int cubren(int v, int p = -1) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for (int hijo: treeEdges[v])
        if (hijo != p) {
            res += cubren(hijo, v);
        }
    memo[v] = res;
    return res;
}

double calcularJugadas() {
    int totales = N * (N - 1) / 2;

    int componentes = 0;
    for (int i = 1; i < N; i++) {
        if (estado[i] == NO_LO_VI) {
            dfs(i);
            componentes++;
        }
    }
    int puentes = 0;
    for (int i = 1; i < N; i++) {
        if (cubren(i) == 0) {
            puentes++;
        }
    }

    return 1 / (double) totales;
}

int main() {
    cin >> N >> M;
    backConExtremoInferiorEn.resize(N + 1, 0);
    backConExtremoSuperiorEn.resize(N + 1, 0);
    g.resize(N + 1, vector<int>(0));
    estado.resize(N + 1, NO_LO_VI);
    memo.resize(N + 1, -1);
    treeEdges.resize(N + 1, vector<int>(0));

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    double res = calcularJugadas();

    cout << fixed;
    cout << setprecision(5) << res;

    return 0;
}