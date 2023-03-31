#include "gtest/gtest.h"
#include "../ejercicios/ej1.cpp"

using namespace std;

TEST(CuadradoMagicoTEST, cuadradoSimple){
    int cuadrado[3][3];
    cuadrado[0][0] = 2;
    cuadrado[0][1] = 7;
    cuadrado[0][2] = 6;
    cuadrado[1][0] = 9;
    cuadrado[1][1] = 5;
    cuadrado[1][2] = 1;
    cuadrado[2][0] = 4;
    cuadrado[2][1] = 3;
    cuadrado[2][2] = 8;

    vector<vector<int>> calculado = cuadradoMagico(3, 1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(cuadrado[i][j], calculado[i][j]);
        }
    }
}