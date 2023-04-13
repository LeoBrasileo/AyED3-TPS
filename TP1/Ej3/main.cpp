#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> actividades;
vector<pair<int, int>> elegidas;
vector<bool> usados;
vector<int> soluciones;
int N, maxTareas;

bool seSolapan(pair<int, int> act1, pair<int, int> act2){
    return act1.second > act2.first && act1.first < act2.second;
}

bool seSolapa(pair<int, int> actividad){
    for (int i = 0; i < elegidas.size(); i++){
        pair<int, int> actividadAct = elegidas[i];
        if (actividadAct == actividad)
            continue;
        if (seSolapan(actividad, actividadAct))
            return true;
    }
    return false;
}


void max_actividades(int i){
    if (i == N){ return;}

    pair<int, int> minAct = make_pair(0, 2 * N + 1);
    int indice = -1;
    for(int j = 0; j < N; j++){
        //buscar valor mas chico que no este en solucion
        if (actividades[j].second < minAct.second && !usados[j]){
            minAct = actividades[j];
            indice = j;
        }
    }
    //agregar valor obtenido en ciclo
    if (indice != -1 && !seSolapa(minAct)){
        elegidas.push_back(minAct);
        soluciones.push_back(indice + 1);
        usados[indice] = true;
    }
    max_actividades(i+1);
}



int main() {
    cin >> N;
    usados.resize(N, false);
    for(int i = 0; i < N; i++){
        int ci, ti; cin >> ci >> ti;
        actividades.push_back(make_pair(ci, ti));
    }

    //calcular
    max_actividades(0);
    //imprimir salida
    cout << maxTareas << endl;
    for (int i = 0; i < soluciones.size(); i++){
        cout << soluciones[i];
    }
    return 0;
}