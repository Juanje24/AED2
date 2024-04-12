#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<pair<string, int>> generadorPeorCaso(int numCasos, int longCadena, int valorM)
{
    vector<pair<string, int>> casosDePrueba;

    for (int i = 0; i < numCasos; ++i)
    {
        string cadenaPeorCaso;
        char charActual = 'z';
        bool esInicioDeZ = true;
        
		//

        while (cadenaPeorCaso.length() < longCadena)
        {
            if (charActual < 'c')
            { // Reinicia en 'z' si llega a 'b' o 'a'
                charActual = 'z';
                esInicioDeZ = true;
            }

			// Si el caracter actual es el del medio de una tripleta, debe ponerse 2 * (valorM / 2 - 1) veces, sino (valorM / 2 + 1)
            int repeticiones = (charActual == 'y' || charActual == 'v' || charActual == 's' ||
                                charActual == 'p' || charActual == 'm' || charActual == 'j' ||
                                charActual == 'g' || charActual == 'd')
                                   ? 2 * (valorM / 2 - 1)
                                   : (valorM / 2 + 1);

			// Si detectamos una z en el comienzo de un ciclo, la cambiamos por una a
            for (int j = 0; j < repeticiones && cadenaPeorCaso.length() < longCadena; ++j)
            {
                if (esInicioDeZ && charActual == 'z')
                {
                    if (j == 0)
                    {
                        cadenaPeorCaso += 'a'; // Sustituye la primera 'z' por 'a'
                        esInicioDeZ = false;
                        continue; // Continuar con el siguiente carácter sin decrementar j
                    }
                }
                cadenaPeorCaso += charActual;
            }

            charActual--; // Moverse hacia atrás en el alfabeto
            if (charActual < 'c')
            { // Evita que la lógica se aplique incorrectamente en el ciclo siguiente
                esInicioDeZ = true;
            }
        }

        casosDePrueba.emplace_back(cadenaPeorCaso, valorM);
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

    auto pruebas = generadorPeorCaso(numCasos, longCadena, valorM);

    for (auto &prueba : pruebas)
    {
        cout << prueba.first << " " << prueba.second << endl;
    }

    return 0;
}
