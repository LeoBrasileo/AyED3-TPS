#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int N, M;
//g es la representacion del grafo
//se piensa como map de vertices a vertices vecinos, espacio: O(N^2)
vector<vector<int>> g;
vector<bool> visitado;
vector<vector<int>> caminos; //cada camino es una lista de vertices

void dfsCaminosAux(int v, int w, vector<int> camino){
    visitado[v] = true;

    if (v == w){ //cierro camino
        camino.pop_back();
        caminos.push_back(camino);
    } else{
        // basicamente un DFS
        for (int u : g[v]){
            if (!visitado[u]){
                camino.push_back(u);
                dfsCaminosAux(u, w, camino);
                camino.pop_back();
            }
        }
    }

    visitado[v] = false;
}

void dfsCaminos(int v, int w){
    //devolvemos la lista de vertices que forman un camino entre v y w
    //obs: no se devuelven v y w como parte del camino, solo los vertices internos
    dfsCaminosAux(v, w, vector<int>(0));
}
bool hasRepeatedNumber(const vector<vector<int>>& vecs) {
    if (vecs.empty())
        return false;

    for (int i = 0; i < vecs[0].size(); i++) {
        int num = vecs[0][i];

        bool found = true;
        for (int j = 1; j < vecs.size(); j++) {
            bool curFound = false;
            for (int k = 0; k < vecs[j].size(); k++) {
                if (vecs[j][k] == num) {
                    curFound = true;
                    break;
                }
            }
            if (!curFound) {
                found = false;
                break;
            }
        }
        if (found) {
            return true;
        }
    }

    return false;
}


double calcularJugadas(){
    int perdidas = 0;
    int totales = 0;
    //cada posible jugada
    for (int i = 1; i <= N; i++){
        for (int j = i+1; j <= N; j++){
            totales++;
            dfsCaminos(i, j);

            if (caminos.size() <= 1){
                perdidas++;
                caminos.clear();
                continue;
            }

            if (hasRepeatedNumber(caminos)){
                perdidas++;
            }

            caminos.clear();
        }
    }

    return perdidas / (double)totales;
}

int main() {
    cin >> N >> M;
    g.resize(N+1, vector<int>(0, -1));
    visitado.resize(N+1, false);

    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    double res = calcularJugadas();

    cout << fixed;
    cout << setprecision(5) << res;

    return 0;
}