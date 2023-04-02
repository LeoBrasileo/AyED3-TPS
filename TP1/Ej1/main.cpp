#include <iostream>
#include <vector>
#include <cmath>
#include <list>

using namespace std;

int N, K, magicNum;
vector <vector<int>> squareFinal;

bool fila(int num, int row, vector <vector<int>> &square) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int casilla = square[row][i];
        sum += casilla;
    }
    return (sum + num) <= magicNum;
}

bool columna(int num, int col, vector <vector<int>> &square) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int casilla = square[i][col];
        sum += casilla;
    }
    return (sum + num) <= magicNum;
}

bool diagonal(int num, int row, int col, vector <vector<int>> &square) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int casilla = square[i][i];
        sum += casilla;
    }
    if(row == col && row == N-1)
        return sum + num == magicNum;
    else
        return (sum + num) <= magicNum;
}

bool antidiagonal(int num, int row, int col, vector <vector<int>> &square) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int casilla = square[i][N - i - 1];
        sum += casilla;
    }
    /*if (col == 0 && row == N-1)
        return sum + num == magicNum;
    else
        return (sum + num) <= magicNum;*/
    return (sum + num) <= magicNum;
}


bool utilizable(int num, int row, int col, vector <vector<int>> &actSquare, vector<int> &usados) {
    for (int i = 0; i < usados.size(); i++) {
        if (usados[i] == num) {
            return false;
        }
    }

    bool f = fila(num, row, actSquare);
    bool c = columna(num, col, actSquare);
    bool d = diagonal(num, row, col, actSquare);
    bool ad = antidiagonal(num, row, col, actSquare);
    return f && c && d && ad;
}

bool armarCuadradoMagico(vector<vector<int>> actSquare, vector<int> usados, int row, int col) {
    if (col == N) {
        col = 0;
        row++;
    }

    if (row == N) {
        squareFinal = actSquare;
        return true;
    }

    for (int num = 1; num <= N*N; num++) {
        if (utilizable(num, row, col, actSquare, usados)) {
            actSquare[row][col] = num;
            usados.push_back(num);
            if (armarCuadradoMagico(actSquare, usados, row, col + 1)) {
                return true;
            }
            //para que pueda probar con los demas numeros
            actSquare[row][col] = 0;
            usados.pop_back();
        }
    }
    return false;
}

int main() {
    // Leo la entrada
    cin >> N >> K;
    //formula sacada de la guia
    magicNum = (pow(N, 3) + N) / 2;

    squareFinal = vector<vector<int>>(N, vector<int>(N, 0));
    //imprimo la salida
    if (armarCuadradoMagico(squareFinal, vector<int>(0), 0, 0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << squareFinal[i][j] << " ";
            }
            cout << endl;
        }
    } else{
        cout << -1 << endl;
    }

    //cout << N << K;
    return 0;
}