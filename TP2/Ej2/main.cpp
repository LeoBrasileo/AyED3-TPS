#include <iostream>
#include <algorithm>
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

// Estos son sólo para hacer Kosaraju
vector<int> componente, orden;
vector<bool> visitados;

// Vector con los resultados
vector<int> res;

/*idea:
1- buscar vertices con grado de entrada 1 y tirarlos con DFS
2- buscar componentes fuertemente conexas (Kosaraju)
3- por cada ciclo encontrado, es decir cada comp fuertemente conexa, tirar las fichas con menor num de vertice
 */

void tirar_fichas(int v){
    fue_tirada[v] = true;
    for (int u : g[v]){
        if (!fue_tirada[u]){
            tirar_fichas(u);
        }
    }
}

void dfs1(int v){
    visitados[v] = true;
    for(int u : g[v]){
        if(!visitados[u]){
            dfs1(u);
        }
    }
    orden.push_back(v);
}

void dfs2(int v){
    visitados[v]=true;
    componente.push_back(v);
    for (int u : g_t[v]){
        if (!visitados[u]){
            dfs2(u);
        }
    }
}

void kosaraju(){
    visitados = vector<bool>(N + 1, false);
    for (int i = 1; i <= N; i++){
        if (!fue_tirada[i] && !visitados[i]){
            dfs1(i);
        }
    }

    reverse(orden.begin(), orden.end());
    visitados = vector<bool>(N + 1, false);

    //cosas para condensar
    vector<int> raices(N+1, 0);
    vector<int> raices_nodos;
    vector<bool> tiene_in_condensado(N+1, false);
    vector<vector<int>> condensado(N+1); //el grafo condensado jejox

    for (int v : orden){
        if(!visitados[v]){
            dfs2(v);

            //condensar
            //cuando se condensa ya se hace lexicograficamente
            int root = componente.front();
            for (auto u : componente)
                raices[u] = root;
            raices_nodos.push_back(root);

            componente.clear();
        }
    }

    //armado de grafo condensado
    for (int v = 1; v <= N; v++){
        for (auto u : g[v]) {
            int raiz_v = raices[v];
            int raiz_u = raices[u];

            if (raiz_u != raiz_v){
                condensado[raiz_v].push_back(raiz_u);
                tiene_in_condensado[raiz_u] = true;
            }
        }
    }

    //tiramos las fichas con grado de entrada 0 en el grafo de kosaraju
    //por como esta armado el grafo condensado, siempre agarramos el vertice minimo
    for (int raiz : raices_nodos){
        if(!tiene_in_condensado[raiz]){
            res.push_back(raiz);
            tirar_fichas(raiz);
        }
    }
}

void jugar(){
    // Tiro todas las que tienen grado de entrada 0
    for (int i = 1; i <= N; i++){
        if(!tiene_in[i]){
            res.push_back(i);
            tirar_fichas(i);
        }
    }

    //en este punto, todas las que quedan son fichas en componentes fuertemente conexas
    //kosaraju de https://cp-algorithms.com/graph/strongly-connected-components.html
    kosaraju();
}

int main() {
    cin >> N >> M;

    tiene_in.assign(N + 1, false);
    fue_tirada.assign(N + 1, false);

    g.resize(N + 1, vector<int>(0));
    g_t.resize(N + 1, vector<int>(0));

    while (M--) {
        int u, v;
        cin >> u >> v;  
        tiene_in[v]=true;
        g[u].push_back(v);
        g_t[v].push_back(u);
    }

    jugar();

    cout << res.size() << endl;
    sort(res.begin(), res.end());
    for(int i : res){
        cout << i << " ";
    }

    return 0;
}