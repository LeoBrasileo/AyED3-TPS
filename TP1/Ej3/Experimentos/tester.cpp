#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

struct Actividad {
    int inicio;
    int final;
    int posicion;
};

// Variable global
int N=0;
vector<Actividad> actividades;

void sortDeActividades(){
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
}


vector<Actividad> maximizarActividades(){

    // Ordeno las actividades
    sortDeActividades();

    vector<Actividad> respuesta;
    respuesta.push_back(actividades[0]);
    Actividad* ultima = &respuesta.back();
    for (int i=1; i<N; i++){
        if (actividades[i].inicio >= ultima->final){
            respuesta.push_back(actividades[i]);
            ultima = &respuesta.back();
        }
    }

    return respuesta;
}


int main() {
    ofstream output_file; output_file.open("runtime.csv", ios::app);
    int C; cin >> C;
    while (C--)
    {
        cin >> N;
    
        actividades.resize(N);
        for (int i=0; i<N; i++){
            int s, t; cin >> s >> t;
            actividades[i].inicio = s;
            actividades[i].final = t;
            actividades[i].posicion = i+1;
        }

        int repeat = 10;
        double counter = 0;

        for (int ignore=0; ignore<repeat; ignore++){
            auto start = chrono::high_resolution_clock::now();
            vector<Actividad> respuesta = maximizarActividades();
            auto stop = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = stop - start;
            counter += diff.count();
        }

        output_file << N << ", " << counter / repeat << "\n";
    }
    
    return 0;
}