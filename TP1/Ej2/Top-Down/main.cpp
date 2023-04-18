#include <iostream>
#include <vector>

using namespace std;

vector<int> operandos;
int n;
long long int r, m;
vector<vector<int>> cache; // <indice, acumulado>, resParcial
//la resParcial es -1 si aun no se sabe, 0 si es false, 1 si es true

long long int restoResta(long long int act, long long int num){
    long long int resta = act - num;
    //no puede ser negativo
    return ((resta % m) + m) % m;
}

long long int restoMult(long long int act, long long int num){
    long long int mult = act * num;
    long long int resto = ((mult % m) + m) % m;
    return resto;
}

long long int mod_bin_exp(long long int x, long long int y, int div) {
    if (y == 0)
        return 1;

    long long int half = mod_bin_exp(x, y / 2, div);
    long long int sq = half * half;
    if (y % 2 == 0)
        return sq % div;
    if (y % 2 == 1){
        long long int mult = ((sq % div) * x);
        return mult % div;
    }
}

bool buscarOpsAux(int indice, unsigned long long int acumulado){
    if (indice == n)
        return acumulado == r;

    if (cache[indice][acumulado] != -1)
        return cache[indice][acumulado] == 1;

    long long int num = operandos[indice];

    bool res = buscarOpsAux(indice + 1, (acumulado + num) % m)
    || buscarOpsAux(indice + 1, restoResta(acumulado, num))
    || buscarOpsAux(indice + 1, restoMult(acumulado, num))
    || buscarOpsAux(indice + 1, mod_bin_exp(acumulado, num, m));

    cache[indice][acumulado] = res ? 1 : 0;
    return res;
}

int main() {
    int C; cin >> C;
    for(int i = 0; i < C; i++){
        cin >> n >> r >> m;
        r = r == m ? 0 : r;
        if (n == 0 && r == 0){
            cout << "Si" << endl;
            continue;
        }
        if (r > m || (m == 0 && r != 0) || n == 0){
            cout << "No" << endl;
            continue;
        }
        cache.resize(n, vector<int>(m, -1));
        operandos.resize(n);
        for(int j = 0; j < n; j++){
            int val; cin >> val;
            operandos[j] = val;
        }

        if(buscarOpsAux(0, 0))
            cout << "Si" << endl;
        else
            cout << "No" << endl;

        operandos.clear();
        cache.clear();
    }

    return 0;
}
