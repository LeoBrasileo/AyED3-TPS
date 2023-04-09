#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    // Inicializar el generador de números aleatorios con la hora actual
    srand(time(NULL));
    
    for (int i = 0; i < n; i++) {
        int num = rand() % 1001;  // Generar número aleatorio entre 0 y 1000
        cout << num << " ";
    }
    
    return 0;
}
