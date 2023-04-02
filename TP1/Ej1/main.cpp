#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, K, magicNum;
int k = 0;
vector <vector<int>> square;
vector<int> usados;

bool filaMag(int row) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += square[row][i];
    }
    return sum == magicNum;
}

bool columnaMag(int col) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += square[i][col];
    }
    return sum == magicNum;
}

bool diagonalMag() {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += square[i][i];
    }
    return sum == magicNum;
}

bool antidiagonalMag() {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += square[i][N - i - 1];
    }
    return sum == magicNum;
}

bool esMagico(){
    for (int i = 0; i < N; i++) {
        if (!filaMag(i) || !columnaMag(i)) {
            return false;
        }
    }
    if (!diagonalMag() || !antidiagonalMag()) {
        return false;
    }
    return true;
}


bool utilizable(int num) {
    for (int i = 0; i < usados.size(); i++) {
        if (usados[i] == num) {
            return false;
        }
    }
    return true;
}

bool armarCuadradoMagico(int row, int col) {
    if (col == N && row == N-1){
        if (esMagico()){
            k++;
            if (k == K){
                return true;
            }
        }
    }

    //recorro la matriz de izquierda a derecha y de arriba a abajo
    //si llego a la ultima columna, paso a la siguiente fila
    if (col == N) {
        col = 0;
        row++;
    }

    for (int num = 1; num <= N*N; num++) {
        if (utilizable(num)) {
            square[row][col] = num;
            usados.push_back(num);
            if (armarCuadradoMagico(row, col + 1)) {
                return true;
            }
            //para que pueda probar con los demas numeros. backtrack
            square[row][col] = 0;
            usados.pop_back();
        }
    }
    return false;
}

int main() {
    // Leo la entrada
    cin >> N >> K;

    magicNum = (pow(N, 3) + N) / 2; //formula sacada de la guia
    square = vector<vector<int>>(N, vector<int>(N, 0));

    //imprimo la salida
    if (armarCuadradoMagico(0, 0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << square[i][j] << " ";
            }
            cout << endl;
        }
    } else{
        cout << -1 << endl;
    }

    return 0;
}