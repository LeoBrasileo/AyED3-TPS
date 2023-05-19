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

// Estos son sólo para hacer Kosaraju
vector<int> componente, orden;
vector<bool> usados;

// Vector con los resultados
vector<int> res;

void tirar_fichas(int v){
    fue_tirada[v] = true;
    for (int u : g[v]){
        if (!fue_tirada[u]){
            tirar_fichas(u);
        }
    }
}


void dfs1(int v){
    usados[v] = true;
    for(int u : g[v]){
        if(usados[u]){
            dfs1(u);
        }
    }
    orden.push_back(v);
}

void dfs2(int v){
    usados[v]=true;
    componente.push_back(v);
    for (int u : g_t[v]){
        if (!usados[u]){
            dfs2(u);
        }
    }
}


void kosaraju(){
    usados.resize(N+1, false);
    for (int i =1; i<N+1; i++){
        if (!fue_tirada[i] && !usados[i]){
            dfs1(i);
        }
    }
    reverse(orden.begin(), orden.end());
    usados.resize(N+1, false);

    for (int v :orden){
        if(!usados[v]){
            dfs2(v);
        
        // Acá tengo la componente

        res.push_back(min(componente));

        componente.clear();
        
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

    tiene_in.assign(N+1, false);
    fue_tirada.assign(N+1, false);
    cant_en_pie = N;

    g.resize(N + 1, vector<int>(0));
    g_t.resize(N + 1, vector<int>(0));

    while (M--) {
        int u, v;
        cin >> u >> v;  
        tiene_in[v]=true;
        g[u].push_back(v);
        g_t[v].push_back(u);
    }

    // Tiro todas las que tienen grado de entrada 0
    for (int i =1; i<N+1; i++){
        if(!tiene_in[i]){
            res.push_back(i);
            tirar_fichas(i);
        }
    }

    // Tenemos: Nodos tirados -> no nos importa hacer nada mas con ellos. 

    // A partir de acá sólo queda al menos una comp conexa con ciclo.

    kosaraju();

    res.sort();

    return 0;
}