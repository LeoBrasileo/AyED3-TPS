#include <iostream>
#include <vector>

using namespace std;

vector<int> operandos;
int n;
long long int r, m;
vector<vector<bool>> cache; // <indice, acumulado>, resParcial>

int mod_bin_exp(long long int x, long long int y, int mod) {
    if (y == 0)
        return 1;

    long long int half = mod_bin_exp(x, y / 2, mod);
    long long int sq = half * half;

    if (y % 2 == 0)
        return sq % mod;

    if (y % 2 == 1){
        long long int mult = ((sq % mod) * x);
        return mult % mod;
    }
}

bool buscarOps(){
    cache[0][0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!cache[i][j]) continue;

            long long int num = operandos[i];
            long long int mult = j * num;
            long long int suma = j + num;
            long long int resta = j - num;

            cache[i + 1][suma % m] = true;
            cache[i + 1][((resta % m) + m) % m] = true;
            cache[i + 1][mult % m] = true;
            cache[i + 1][mod_bin_exp(j, num, m)] = true;
        }
    }

    return cache[n][r];
}

int main() {
    int C; cin >> C;
    for(int i = 0; i < C; i++){
        cin >> n >> r >> m;
        r = r == m ? 0 : r;
        cache = vector<vector<bool>>(n + 1, vector<bool>(m, false));
        operandos.resize(n);
        for(int j = 0; j < n; j++){
            int val; cin >> val;
            operandos[j] = val;
        }
        if (n == 0 && r == 0){
            cout << "Si" << endl;
            continue;
        }
        if (r > m || (m == 0 && r != 0) || n == 0){
            cout << "No" << endl;
            continue;
        }

        if(buscarOps())
            cout << "Si" << endl;
        else
            cout << "No" << endl;

        operandos.clear();
        cache.clear();
    }

    return 0;
}