#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

vector<int> operandos;
int resto, divisor;
map<pair<int,int>, bool> cache; // <indice, acumulado>, resParcial

int calcResto(int num){
    return num % divisor;
}

bool buscarOpsAux(int indice, unsigned long int acumulado){
    int n = operandos.size();
    pair<int,int> key = make_pair(indice, acumulado);

    if (indice == n)
        return acumulado == resto;

    if (cache.find(key) != cache.end())
        return cache[key];

    int num = operandos[indice];

    bool res = buscarOpsAux(indice + 1, calcResto(acumulado + num))
    || buscarOpsAux(indice + 1, calcResto(acumulado - num))
    || buscarOpsAux(indice + 1, calcResto(acumulado * num))
    ||buscarOpsAux(indice + 1, calcResto(pow(acumulado, num)));

    cache[key] = res;
    return res;
}

bool buscarOperaciones(){
    bool res = buscarOpsAux(0, 0);
    operandos.clear();
    cache.clear();
    return res;
}

int main() {
    int C;
    cin >> C;
    for(int i = 0; i < C; i++){
        int n;
        cin >> n >> resto >> divisor;
        for(int j = 0; j < n; j++){
            int val;
            cin >> val;
            operandos.push_back(val);
        }
        if (buscarOperaciones())
            cout << "Si" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}
