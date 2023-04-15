#include <iostream>
#include <vector>

using namespace std;

// Variable global
int N=0;

// Struct actividad para poder guardar además la posicion
struct Actividad {
    pair<int, int> horarios;
    int posicion;
    bool esNull=true;
};


vector<Actividad> sortDeActividades(vector<Actividad> actividades){
    // como el rango de horas está acotado por 2N uso Counting Sort
    
    vector<Actividad> ordenadas[(2*N)+1];

    for (int i=0; i<N; i++){

        ordenadas[actividades[i].horarios.second].push_back(actividades[i]);
    }

    int i = 0;
    for (int j=0; j<(2*N)+1; j++){
        if (ordenadas[j].size() != 0){
            for(int k=0; k<ordenadas[j].size(); k++){
                actividades[i]=ordenadas[j][k];
                i++;
            }     
        }
    }

    return actividades;
}


vector<Actividad> maximizarActividades(vector<Actividad> actividades){

    // Ordeno las actividades
    vector<Actividad> ordenadas = sortDeActividades(actividades);

    vector<Actividad> respuesta;
    respuesta.push_back(ordenadas[0]);
    Actividad* ultima = &respuesta.back();
    for (int i=1; i<N; i++){
        if (ordenadas[i].horarios.first >= ultima->horarios.second){
            respuesta.push_back(ordenadas[i]);
            ultima = &respuesta.back();
        }
    }

    return respuesta;
}


int main() {
    cin >> N;
    
    vector<Actividad> actividades;
    for (int i=0; i<N; i++){
        int s, t; cin >> s >> t;
        actividades.push_back({{s, t}, i+1, false});
    }

    vector<Actividad> respuesta = maximizarActividades(actividades);

    // Imprimir salida
    int length = respuesta.size();
    cout << length << endl;

    for (int i=0; i<length; i++){
        cout << respuesta[i].posicion;
        if(i!=length-1){
            cout<<" ";
        }
    }
    cout << endl;
    
    return 0;
}