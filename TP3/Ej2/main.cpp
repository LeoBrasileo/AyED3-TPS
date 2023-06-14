#include <iostream>
#include <vector>
#include <queue>

#define INF 2147483647

using namespace std;

int N, M;

int bfs(int s, int t, vector<int>& parent, vector<vector<int>> &g, vector<vector<int>> &capacidades) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flujo = q.front().second;
        q.pop();

        for (int next : g[cur]) {
            if (parent[next] == -1 && capacidades[cur][next]) {
                parent[next] = cur;
                int nuevo_flujo = min(flujo, capacidades[cur][next]);
                if (next == t)
                    return nuevo_flujo;
                q.push({next, nuevo_flujo});
            }
        }
    }

    return 0;
}

int flujoMaximo(vector<vector<int>> &g, vector<vector<int>> &capacidades){
    //algoritmo de Edmonds-Karp
    //https://cp-algorithms.com/graph/edmonds_karp.html#implementation
    int flujo = 0;
    vector<int> parent(N+2);
    int nuevo_flujo;

    int s = 0, t = N + 1;
    while (nuevo_flujo = bfs(s, t, parent, g, capacidades)) {
        flujo += nuevo_flujo;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacidades[prev][cur] -= nuevo_flujo;
            capacidades[cur][prev] += nuevo_flujo;
            cur = prev;
        }
    }

    return flujo;
}

void scan() {
    bool p;
    int temp, a, b;
    scanf("%d", &N);
    scanf("%d", &M);
    if (N == 0 && M == 0)
        return;

    //el nodo 0 es el nodo fuente (Prim)
    //de 1 a N son los nodos de los estudiantes
    //el nodo N+1 es el nodo sumidero (Kruskal)

    vector<vector<int>> g = vector<vector<int>>(N+2);
    vector<vector<int>> capacidades = vector<vector<int>>(N+2, vector<int>(N+2, 0));
    for (int i = 1; i <= N; i++) {
        scanf("%d", &temp);
        p = temp;
        if (p){
            g[0].push_back(i);
            capacidades[0][i] = 1;
        } else{
            g[i].push_back(N+1);
            capacidades[i][N+1] = 1;
        }
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &a);
        scanf("%d", &b);
        g[a].push_back(b);
        g[b].push_back(a);
        //las asmistades son bidireccionales
        capacidades[a][b] = 1;
        capacidades[b][a] = 1;
    }

    int corteMinimo = flujoMaximo(g, capacidades);
    printf("%d \n", corteMinimo);

    scan();
}

int main() {
    scan();
    return 0;
}
