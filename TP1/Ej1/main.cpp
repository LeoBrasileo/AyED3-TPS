#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, K, magicNum;
int k = 0;
vector <vector<int>> square;
vector<bool> usados;
vector<int> sumFila, sumCol;
int sumDiag = 0, sumAntidiag = 0;

bool filaMag(int row) {
    return sumFila[row] == magicNum;
}

bool columnaMag(int col) {
    return sumCol[col] == magicNum;
}

bool diagonalMag() {
    return sumDiag == magicNum;
}

bool antidiagonalMag() {
    return sumAntidiag == magicNum;
}

bool esMagico(){
    // Verifico que las sumas parciales de las filas y columnas sean iguales a la suma magica
    if (!diagonalMag() || !antidiagonalMag()) {
        return false;
    }
    for (int i = 0; i < N; i++) {
        if (!filaMag(i) || !columnaMag(i)) {
            return false;
        }
    }
    return true;
}


bool noUsado(int num) {
    return !usados[num - 1];
}

bool poda(int row, int col, int num) {
    bool completaFila = col == N - 1;
    bool completaCol = row == N - 1;
    bool esDiagonal = row == col;
    bool esAntiDiag = row + col == N - 1;

    if (esDiagonal)
        sumDiag += num;
    if (esAntiDiag)
        sumAntidiag += num;

    sumFila[row] += num;
    sumCol[col] += num;

    if(completaFila){return !filaMag(row);}
    if(completaCol){return !columnaMag(col);}

    //QVQ las sumas parciales en fila y columna son menor a la suma magica
    return sumFila[row] >= magicNum || sumCol[col] >= magicNum || sumDiag >= magicNum || sumAntidiag >= magicNum;
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
    //este orden tambien me permite respetar el orden lexicografico
    //si llego a la ultima columna, paso a la siguiente fila
    if (col == N) {
        col = 0;
        row++;
    }

    for (int num = 1; num <= N*N; num++) {
        if (noUsado(num)) {
            square[row][col] = num;
            usados[num - 1] = true;
            if (!poda(row, col, num)){
                if (armarCuadradoMagico(row, col + 1)) {
                    return true;
                }
            }
            //para que pueda probar con los demas numeros. backtrack
            square[row][col] = 0;
            usados[num - 1] = false;
            //si podo devuelvo las sums parciales a su estado original
            sumFila[row] -= num;
            sumCol[col] -= num;
            if (row == col)
                sumDiag -= num;
            if (row + col == N - 1)
                sumAntidiag -= num;
        }
    }
    return false;
}

void inicializar() {
    magicNum = (pow(N, 3) + N) / 2; //formula sacada de la guia
    square = vector<vector<int>>(N, vector<int>(N, 0));
    usados = vector<bool>(N*N,false);
    sumFila = vector<int>(N,0);
    sumCol = vector<int>(N,0);
}

int main() {
    // Leo la entrada
    cin >> N >> K;

    inicializar();

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