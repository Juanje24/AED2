#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<pair<string, int>> generador(int numCasos, int longCadena, int valorM)
{
    vector<pair<string, int>> casosDePrueba;
    srand(static_cast<unsigned>(time(nullptr))); // Inicializa la semilla de números aleatorios una sola vez.

    for (int i = 0; i < numCasos; ++i)
    {
        string randomCadena;
        for (int j = 0; j < longCadena; ++j)
        {
            char randomChar = 'a' + rand() % 26; // Genera un carácter aleatorio.
            randomCadena += randomChar;          // Añade el carácter a la cadena.
        }

        // Como 'm' es ahora un valor único, no necesitamos generar un valor aleatorio para 'm'.
        casosDePrueba.emplace_back(randomCadena, valorM); // Añade el par a la lista de casos de prueba.
    }

    return casosDePrueba;
}

int main()
{
    int numCasos, longCadena, valorM;

    cerr << "Ingrese el número de casos: "; // Imprimido desde la salida de error para que en caso de redireccionar
    // la salida a un fichero no se escriba en el fichero
    cin >> numCasos;
    cerr << "Ingrese la longitud de las cadenas: ";
    cin >> longCadena;
    valorM = longCadena / 1000;

    auto pruebas = generador(numCasos, longCadena, valorM);

    // Imprime los casos de prueba generados.
    for (auto &prueba : pruebas)
    {
        cout << prueba.first << " " << prueba.second << endl;
    }

    return 0;
}
