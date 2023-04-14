#include <iostream>
#include <vector>

using namespace std;

vector<int> operandos;
int n;
unsigned long long int r, m;
vector<vector<int>> cache; // <indice, acumulado>, resParcial
//la resParcial es -1 si aun no se sabe, 0 si es false, 1 si es true
vector<bool> respuestas;

unsigned long long int calcResto(unsigned long int act, int num){
    //no puede ser negativo
    int resta = act - num;
    if (resta < 0) {
        return calcResto(act, num - m);
    }
    return resta;
}

unsigned long long int mod_bin_exp(unsigned long long int x, unsigned long long int y) {
    if (y == 0)
        return 1;
    unsigned long long int half = mod_bin_exp(x, y / 2);

    if (y % 2 == 0)
        return half*half % m;
    if (y % 2 == 1)
        return (((half * half) % m) * x) % m;

    return 0;
}

bool buscarOpsAux(int indice, unsigned long long int acumulado){
    if (indice == n)
        return acumulado == r;

    if (cache[indice][acumulado] != -1)
        return cache[indice][acumulado] == 1;

    unsigned long long int num = operandos[indice];
    unsigned long long int mult = acumulado * num;

    bool res = buscarOpsAux(indice + 1, (acumulado + num) % m)
    || buscarOpsAux(indice + 1, calcResto(acumulado, num))
    || buscarOpsAux(indice + 1, mult % m)
    ||buscarOpsAux(indice + 1, mod_bin_exp(acumulado, num));

    cache[indice][acumulado] = res ? 1 : 0;
    return res;
}

int main() {
    int C;
    cin >> C;
    for(int i = 0; i < C; i++){
        cin >> n >> r >> m;
        if (r > m){
            respuestas.push_back(false);
            continue;
        }
        cache = vector<vector<int>>(n, vector<int>(m, -1));
        for(int j = 0; j < n; j++){
            int val;
            cin >> val;
            operandos.push_back(val);
        }
        bool res = buscarOpsAux(0, 0);
        respuestas.push_back(res);
        operandos.clear();
        cache.clear();
    }

    for(int i = 0; i < C; i++){
        if (respuestas[i])
            cout << "Si" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}
