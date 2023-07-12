#include <iostream>
#include <vector>

using namespace std;

struct Actividad {
    int inicio;
    int final;
    int posicion;
};

// Variable global
int N = 0;
vector<Actividad> actividades;

void sortDeActividades(vector<Actividad> &actividades){
    // como el rango de horas está acotado por 2N uso Counting Sort

    vector<Actividad> ordenadas[(2*N)+1];

    for (int i=0; i<N; i++){
        ordenadas[actividades[i].final].push_back(actividades[i]);
    }

    int i = 0;
    for (int j = 0; j < (2*N) + 1; j++){
        if (ordenadas[j].size() != 0){
            for(int k = 0; k < ordenadas[j].size(); k++){
                actividades[i] = ordenadas[j][k];
                i++;
            }
        }
    }

    return;
}


vector<Actividad> maximizarActividades(){

    // Ordeno las actividades
    sortDeActividades(actividades);

    vector<Actividad> respuesta;
    respuesta.push_back(actividades[0]);
    Actividad* ultima = &respuesta.back();
    for (int i = 1; i < N; i++){
        if (actividades[i].inicio >= ultima->final){
            respuesta.push_back(actividades[i]);
            ultima = &respuesta.back();
        }
    }

    return respuesta;
}


int main() {
    cin >> N;

    actividades.resize(N);
    for (int i = 0; i < N; i++){
        int s, t; cin >> s >> t;
        actividades[i].inicio = s;
        actividades[i].final = t;
        actividades[i].posicion = i+1;
    }

    vector<Actividad> respuesta = maximizarActividades();

    // Imprimir salida
    int length = respuesta.size();
    cout << length << endl;

    for (int i = 0; i < length; i++){
        cout << respuesta[i].posicion;
        if(i != length-1){
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}