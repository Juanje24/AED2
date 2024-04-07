#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<pair<string, int>> generadorMejorCaso(int numCasos, int longCadena, int valorM)
{
    vector<pair<string, int>> casosDePrueba;

    for (int i = 0; i < numCasos; ++i)
    {
        string cadenaA(longCadena, 'a');             // Crea una cadena de longitud longCadena compuesta solo por 'a's.
        casosDePrueba.emplace_back(cadenaA, valorM); // Añade el par a la lista de casos de prueba.
    }

    return casosDePrueba;
}

int main()
{
    int numCasos, longCadena, valorM;

    cerr << "Ingrese el número de casos: ";
    cin >> numCasos;
    cerr << "Ingrese la longitud de las cadenas: ";
    cin >> longCadena;
    valorM = longCadena / 1000;

    auto pruebas = generadorMejorCaso(numCasos, longCadena, valorM);

    // Imprime los casos de prueba generados.
    for (auto &prueba : pruebas)
    {
        cout << prueba.first << " " << prueba.second << endl;
    }

    return 0;
}
