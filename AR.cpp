#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Calcular el incremento en diversidad si se agrega un nuevo candidato
int calcularIncremento(const vector<int>& seleccionados, const vector<vector<int>>& distancias, int candidato) {
    int incremento = 0;
    for (size_t elemento = 0; elemento < seleccionados.size(); ++elemento) {
        incremento += distancias[seleccionados[elemento]][candidato] + distancias[candidato][seleccionados[elemento]];
    }
    return incremento;
}

// Función para seleccionar el elemento inicial basado en la suma máxima de distancias a otros nodos
int seleccionarCandidatoInicial(const vector<vector<int>>& distancias, int n) {
    int sumaMax = -1, candidato = 0;
    for (int i = 0; i < n; ++i) {
        int sumaActual = 0;
        for (int j = 0; j < n; ++j) {
            sumaActual += distancias[i][j];
        }
        if (sumaActual > sumaMax) {
            sumaMax = sumaActual;
            candidato = i;
        }
    }
    return candidato;
}

// Seleccionar el mejor candidato posible a continuación del primero y siguientes
int Seleccionar(const vector<int>& seleccionados, const vector<vector<int>>& distancias, const vector<bool>& estaSeleccionado) {
    int incrementoMax = -1;
    int siguienteCandidato = -1;
    for (size_t i = 0; i < distancias.size(); ++i) {
        if (!estaSeleccionado[i]) {
            int incrementoActual = calcularIncremento(seleccionados, distancias, i);
            if (incrementoActual > incrementoMax) {
                incrementoMax = incrementoActual;
                siguienteCandidato = i;
            }
        }
    }
    return siguienteCandidato;
}

// Verificar si es factible agregar un nuevo candidato
bool Factible(const vector<int>& seleccionados, int m) {
    return seleccionados.size() < static_cast<size_t>(m);
}

// Insertar un nuevo candidato en el conjunto solución
void Insertar(vector<int>& seleccionados, vector<bool>& estaSeleccionado, int candidato) {
    seleccionados.push_back(candidato);
    estaSeleccionado[candidato] = true;
}

// Función para verificar si se ha formado una solución completa.
bool Solucion(const vector<int>& seleccionados, int m) {
    return seleccionados.size() == static_cast<size_t>(m);
}

pair<int, vector<int>> diversidadVoraz(int n, int m, const vector<vector<int>>& distancias) {
    vector<int> seleccionados;
    vector<bool> estaSeleccionado(n, false);

    // Seleccionar el candidato inicial
    int inicial = seleccionarCandidatoInicial(distancias, n);
    Insertar(seleccionados, estaSeleccionado, inicial);

    // Algoritmo voraz para seleccionar los siguientes candidatos
    while (!Solucion(seleccionados, m)) {
        int candidato = Seleccionar(seleccionados, distancias, estaSeleccionado);
        if (Factible(seleccionados, m)) {
            Insertar(seleccionados, estaSeleccionado, candidato);
        }
    }

    // Calcular la diversidad final
    int diversidadMaxima = 0;
    for (size_t i = 0; i < seleccionados.size(); ++i) {
        for (size_t j = i + 1; j < seleccionados.size(); ++j) {
            diversidadMaxima += distancias[seleccionados[i]][seleccionados[j]] + distancias[seleccionados[j]][seleccionados[i]];
        }
    }

    vector<int> vectorSolucion(n, 0);
    for (int i : seleccionados) {
        vectorSolucion[i] = 1;
    }

    return {diversidadMaxima, vectorSolucion};
}

int main() {
    int T, n, m;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        vector<vector<int>> distancias(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> distancias[i][j];
            }
        }

        pair<int, vector<int>> resultado = diversidadVoraz(n, m, distancias);
        cout << resultado.first << endl;
        for (int i : resultado.second) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
