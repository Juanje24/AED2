#include <iostream>
#include <cmath>

using namespace std;

// Variables globales para manejar el contexto del problema
int N; // Número total de casos a procesar
int M; // Presupuesto máximo disponible
int C; // Número de categorías de prendas disponibles
int** tablaPrecios; // Matriz que almacena los precios por modelo y categoría
int* configuracionActual; // Array que almacena los índices de la configuración actual de modelos

int* mejorConfiguracion; // Almacena la mejor configuración encontrada
bool* configuracionValida; // Indica si una configuración es válida

bool procesado; // Bandera para control de flujo de procesamiento

int tact; // Costo total acumulado de la configuración actual
int voa; // Valor óptimo alcanzado hasta el momento

// Función para actualizar la configuración actual de modelos
void Generar(int nivel, int configuracionActual[]){
    if (configuracionActual[nivel-1] > 0)
        tact -= tablaPrecios[nivel-1][configuracionActual[nivel-1]];
    configuracionActual[nivel-1]++;
    tact += tablaPrecios[nivel-1][configuracionActual[nivel-1]];
}

// Función para verificar si la configuración actual cumple con el presupuesto
bool Solucion(int nivel, int configuracionActual[]){
    procesado = true;
    if ((nivel == C) && (tact <= M)){
        configuracionValida[nivel-1] = true;
        return true;
    }
    return false;
}

// Función para determinar si se puede seguir explorando soluciones en el nivel actual
bool Criterio(int nivel, int configuracionActual[]){
    return (nivel < C) && (tact <= M);
}

// Función para verificar si existen más configuraciones posibles en el nivel actual
bool MasHermanos(int nivel, int configuracionActual[]){
    if (nivel == 0)
        return false;
    if (!procesado && tablaPrecios[nivel-1][configuracionActual[nivel-1]] < mejorConfiguracion[nivel-1])
        mejorConfiguracion[nivel-1] = tablaPrecios[nivel-1][configuracionActual[nivel-1]];
    procesado = false;
    return (configuracionActual[nivel-1] < tablaPrecios[nivel-1][0]);
}

// Función para retroceder a un nivel anterior en el proceso de búsqueda
void Retroceder(int& nivel, int configuracionActual[]){
    tact -= tablaPrecios[nivel-1][configuracionActual[nivel-1]];
    configuracionActual[nivel-1] = 0;
    if (!configuracionValida[nivel-1] && nivel-1 > 0){
        mejorConfiguracion[nivel-2] = configuracionActual[nivel-2];
    }
    else if (nivel-1 > 0){
        configuracionValida[nivel-2] = true;
    }
    nivel--;
}

// Implementa el algoritmo de backtracking para encontrar la mejor configuración posible
void Backtracking(int configuracionActual[]){
    int nivel = 1;
    tact = 0;
    voa = 0;
    bool fin = false;
    int soa[C];
    procesado = false;
    for (int i = 0; i < C; i++) {
        configuracionActual[i] = 0;
        soa[i] = 0;
        configuracionValida[i] = false;
    }
    while (!fin && nivel != 0) {
        Generar(nivel, configuracionActual);
        if (Solucion(nivel, configuracionActual) && tact > voa){
            voa = tact;
            for (int i = 0; i < C; i++)
                soa[i] = configuracionActual[i];
        }
        if (Criterio(nivel, configuracionActual))
            nivel++;
        else if (voa == M)
            fin = true;
        else
            while (!MasHermanos(nivel, configuracionActual) && nivel > 0)
                Retroceder(nivel, configuracionActual);
    }

    for (int i = 0; i < C; i++)
        configuracionActual[i] = soa[i];
}

int main(){
    cin >> N;
    for (int k = 0; k < N; k++) {
        cin >> M >> C;
        tablaPrecios = new int*[C];
        for (int i = 0; i < C; i++) {
            tablaPrecios[i] = new int[21]; // Suponemos un máximo de 20 modelos por categoría
        }

        for (int i = 0; i < C; i++) {
            cin >> tablaPrecios[i][0];
            for (int j = 1; j <= tablaPrecios[i][0]; j++)
                cin >> tablaPrecios[i][j];
        }

        configuracionActual = new int[C];
        mejorConfiguracion = new int[C];
        configuracionValida = new bool[C];
        Backtracking(configuracionActual);

        if (configuracionActual[0] == 0)
            cout << "no solution\n";
        else {
            int total = 0;
            for (int i = 0; i < C; i++)
                total += tablaPrecios[i][configuracionActual[i]];
            cout << total << '\n';
        }

        for (int i = 0; i < C; i++)
            delete[] tablaPrecios[i];
        delete[] tablaPrecios;
        delete[] configuracionActual;
        delete[] mejorConfiguracion;
        delete[] configuracionValida;
    }
}

