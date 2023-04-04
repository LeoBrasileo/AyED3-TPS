#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> operandos;
int resto, divisor;

bool buscarOpsAux(int indice, int acumulado){
    if (indice == operandos.size()){
        return (acumulado % divisor == resto);
    }

    int num = operandos[indice];

    bool suma = buscarOpsAux(indice + 1, acumulado + num);
    bool resta = buscarOpsAux(indice + 1, acumulado - num);
    bool mult = buscarOpsAux(indice + 1, acumulado * num);
    bool pot = buscarOpsAux(indice + 1, pow(acumulado, num));

    return suma || resta || mult || pot;
}

bool buscarOperaciones(){
    bool res = buscarOpsAux(0, 0);
    operandos.clear();
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