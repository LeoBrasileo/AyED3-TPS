#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> oficina;

int N, R, W, U, V;
double costoUtp = 0, costoFibra = 0;
//g es matriz de adyacencias, indicado por pesos
vector<vector<double>> g;

vector<double> costos;

ofstream output_file;

void kruskal() {
    //basado en Kruskal de https://fedelebron.com/a-dense-version-of-kruskals-algorithm

    vector<bool> vistos(N, false);

    //inicializar
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            costos[i] = min(costos[i], g[i][j]);
        }
    }

    int aristas = N - 1;
    while (aristas + 1 > W) {
        //buscar minimo
        int idx = 0;
        while (vistos[idx]) idx++;
        for (int i = idx + 1; i < N; i++) {
            if (vistos[i]) continue;
            if (costos[i] < costos[idx]) idx = i;
        }
        double costo = costos[idx];
        int destino = 0;
        for (int i = 0; i < N; ++i) {
            if (vistos[i]) continue;
            if (g[idx][i] == costo) {
                destino = i;
                break;
            }
        }

        pair<double, pair<int, int>> minimo = make_pair(costo, make_pair(idx, destino));

        //calcular costos
        if (minimo.first/U <= R && minimo.first/V <= R)
            costoUtp += minimo.first;
        else
            costoFibra += minimo.first;

        //unificar
        int u = minimo.second.first, // nuevo padre
        v = minimo.second.second; // nuevo hijo
        vistos[v] = true;
        costos[u] = INFINITY;
        for (int i = 0; i < N; ++i) {
            if (vistos[i]) continue;
            if (i == u) continue;
            g[i][u] = g[u][i] = min(g[u][i], g[v][i]);
            costos[u] = min(costos[u], g[u][i]);
        }

        aristas--;
    }
}

double distancia(int v1, int u1, int v2, int u2) {
    int distV = v1 - v2;
    int distU = u1 - u2;
    return sqrt(distV * distV + distU * distU);
}

double medirTiempo() {
    int repeat = 10;
    double counter = 0;

    for (int ignore = 0; ignore < repeat; ignore++){
        auto start = chrono::high_resolution_clock::now();

        kruskal();

        //para prox test
        costoUtp = costoFibra = 0;
        costos.resize(N, INFINITY);

        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = stop - start;
        counter += diff.count();
    }
    
    return counter / repeat;
}

int main() {
    output_file.open("runtime_dense.csv", ios::app);
    int C;
    cin >> C;
    for (int i = 1; i <= C; i++) {
        cin >> N >> R >> W >> U >> V;
        g.resize(N, vector<double>(N, INFINITY));
        costos.resize(N, INFINITY);
        vector<oficina> oficinas;
        for (int j = 0; j < N; j++) {
            int x, y;
            cin >> x >> y;
            oficinas.push_back({x, y});
        }

        //armado de aristas con pesos
        for (int ii = 0; ii < N; ii++) {
            for (int j = ii + 1; j < N; j++) {
                oficina a = oficinas[ii];
                oficina b = oficinas[j];
                double costo = distancia(a.first, a.second, b.first, b.second);
                bool utp = costo <= R;
                costo = utp ? costo * U : costo * V;
                g[ii][j] = g[j][ii] = costo;
            }
        }

        double t = medirTiempo();

        output_file << N << "," << t << "\n";

        //limpiar para prox test
        g.clear();
        costos.clear();
    }

    return 0;
}