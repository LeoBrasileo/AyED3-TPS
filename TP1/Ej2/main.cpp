#include <iostream>
#include <vector>

using namespace std;

vector<int> operandos;
int n;
unsigned long long int r, m;
vector<vector<int>> cache; // <indice, acumulado>, resParcial
//la resParcial es -1 si aun no se sabe, 0 si es false, 1 si es true

int restoResta(unsigned long long int act, long long int num){
    //no puede ser negativo
    int resta = act - num;
    while (resta < 0)
        resta = resta + m;

    return resta % m;
}

int restoMult(long long int act, long long int num){
    unsigned long long mult = act * num;
    long long resto = mult % m;
    return (int) resto;
}

int mod_bin_exp(int x, int y) {
    if (y == 0)
        return 1;
    int half = mod_bin_exp(x, y / 2);

    if (y % 2 == 0)
        return half*half % m;
    if (y % 2 == 1)
        return (((half * half) % m) * x) % m;

    return 1; //no deberia llegar aca, es solo por los warnings
}

bool buscarOpsAux(int indice, unsigned long long int acumulado){
    if (indice == n)
        return acumulado == r;

    if (cache[indice][acumulado] != -1)
        return cache[indice][acumulado] == 1;

    unsigned long long int num = operandos[indice];

    bool res = buscarOpsAux(indice + 1, ((acumulado + num) % m))
    || buscarOpsAux(indice + 1, restoResta(acumulado, num))
    || buscarOpsAux(indice + 1, restoMult(acumulado, num))
    || buscarOpsAux(indice + 1, mod_bin_exp(acumulado, num));

    cache[indice][acumulado] = res ? 1 : 0;
    return res;
}

int main() {
    int C; cin >> C;
    for(int i = 0; i < C; i++){
        cin >> n >> r >> m;
        if (n == 0 && r == 0){
            cout << "Si" << endl;
            continue;
        }
        if (r >= m || (m == 0 && r != 0) || n == 0){
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
