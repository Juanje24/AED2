#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura para guardar los índices
struct Resultado
{
    int inicio, tam; // inicio es el índice donde comienza la subcadena, y tam el tamaño
};

// Función para comprobar si el problema es lo suficientemente pequeño
bool Pequeno(int p, int q, int m)
{
    return (q - p + 1) <= m;
}

// Función que retorna la solución directa al problema
Resultado SolucionDirecta(const string &A, int p, int q)
{
    Resultado result = {p, 1};
    int longitudAct = 1; // La inicializo a 1 porque inicialmente cada subsolucion es de 1 caracter

    // Iterar sobre la cadena para encontrar la subcadena ascendente más larga
    for (int i = p + 1; i <= q; ++i)
    {
        if (A[i] >= A[i - 1])
        {
            longitudAct++;
        }
        else
        {
            if (longitudAct > result.tam)
            {
                result = {i - longitudAct, longitudAct};
            }
            longitudAct = 1;
        }
    }
    // Esto es por si la subcadena más larga termina en el último caracter
    if (longitudAct > result.tam)
    {
        result = {q - longitudAct + 1, longitudAct};
    }
    return result;
}

// Función que divide el problema en subproblemas más pequeños
int Dividir(int p, int q)
{

    return (p + q) / 2;
}

// Función que extiende hacia la izquierda en caso de haber una posible subcadena más larga
Resultado extenderIzquierda(const string &A, const Resultado &S, int limite, int m)
{
    int inicio = S.inicio;
    int cuentaTam = S.tam;
    while (inicio > limite && A[inicio - 1] <= A[inicio] && cuentaTam < m)
    {
        --inicio;
        ++cuentaTam;
    }
    Resultado r = {inicio, cuentaTam};
    return r;
}

// Función que extiende hacia la derecha en caso de haber una posible subcadena más larga
Resultado extenderDerecha(const string &A, const Resultado &S, int limite, int m)
{
    int inicio = S.inicio;
    int cuentaTam = 1;
    while (inicio < limite && A[inicio] <= A[inicio + 1] && cuentaTam < m)
    {
        ++inicio;
        ++cuentaTam;
    }
    Resultado r = {S.inicio, cuentaTam};
    return r;
}

// Función que crea la subcadena ascendente más larga a partir del punto medio de la cadena
Resultado cadFrontera(const string &A, int p, int q, int mid, int m)
{
    Resultado r = {mid, 2};
    Resultado r1 = extenderIzquierda(A, r, p, m);
    Resultado r2 = extenderDerecha(A, r1, q, m);
    return r2;
}

// Función que combina dos resultados distintos
Resultado Combinar(const Resultado &S1, const Resultado &S2, const string &A, int p, int q, int m, int mid)
{

    if (S1.tam == m || S2.tam == m)
    {
        return (S1.tam >= S2.tam) ? S1 : S2;
    }

    // Si no hay continuidad en la frontera
    if (A[mid] > A[mid + 1])
    {
        return (S1.tam >= S2.tam) ? S1 : S2;
    }

    else
    {
        // Si S1 llega a la frontera
        if (S1.inicio + S1.tam - 1 == mid)
        {
            // Si S2 llega a la frontera
            if (S2.inicio == mid + 1)
            {
                Resultado r = {S1.inicio, (S1.tam + S2.tam)};
                // En caso de que la concatenación devuelva una subcadena mayor que m, devolver una de tamaño máximo m
                if (r.tam > m)
                {
                    r.tam = m;
                }
                return r;
            }
            // Si S2 no toca la frontera, extender S1 y comprobar si la cadena resultante es más larga que S2
            else
            {
                Resultado r = extenderDerecha(A, S1, q, m);
                return (r.tam >= S2.tam) ? r : S2;
            }
        }
        // Si S1 no llega a la frontera
        else
        {
            // Si S2 toca la frontera, extender S2 y comprobar si la cadena resultante es más larga que S1
            if (S2.inicio == mid + 1)
            {
                Resultado r = extenderIzquierda(A, S2, p, m);
                return (r.tam >= S1.tam) ? r : S1;
            }
            // Si S1 y S2 no tocan frontera, extender a derecha e izquierda la cadena formada por mid, mid+1 y comprobar si esta es más larga que S1 y S2
            else
            {
                Resultado r = cadFrontera(A, p, q, mid, m);
                Resultado r1 = (S1.tam >= S2.tam) ? S1 : S2;
                return (r.tam >= r1.tam) ? r : r1;
            }
        }
    }
}

// Función que resuelve el problema y representa al algoritmo
Resultado DivideVenceras(const string &A, int p, int q, int m)
{
    if (Pequeno(p, q, m))
    {
        return SolucionDirecta(A, p, q);
    }
    else
    {
        int mid = Dividir(p, q);
        Resultado S1 = DivideVenceras(A, p, mid, m);
        Resultado S2 = DivideVenceras(A, mid + 1, q, m);
        return Combinar(S1, S2, A, p, q, m, mid);
    }
}

vector<pair<string, int>> generador(int numCasos, int longMin, int longMax, int mMin, int mMax)
{
    vector<pair<string, int>> casosDePrueba;

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < numCasos; ++i)
    {
        int longCadena = longMin + rand() % (longMax - longMin + 1);

        string randomCadena;
        for (int j = 0; j < longCadena; ++j)
        {
            char randomChar = 'a' + rand() % 26;
            randomCadena += randomChar;
        }

        int m = mMin + rand() % (mMax - mMin + 1);

        casosDePrueba.emplace_back(randomCadena, m);
    }

    return casosDePrueba;
}

int main()
{

    // MODO 1: PRUEBA CON GENERADOR DE CASOS
    /*
// El primer argumento es el número de cadenas a generar, el segundo y tercero número MIN y MAX de caracteres de la cadena; y el cuarto y quinto
// son el valor MIN y MAX que puede tomar m aleatoriamente para cada cadena
auto pruebas = generador(1, 1000000, 1000000, 1000, 1000);
for (auto& prueba : pruebas) {
    cout << "Caso de prueba: " << prueba.first << ", m = " << prueba.second << endl;
}


for (auto& [cadena, m] : pruebas) {
    int n = cadena.length() - 1;
    auto resultado = DivideVenceras(cadena, 0, n, m);
    auto resultado2 = SolucionDirecta(cadena, 0, n);
    string subcadenaDetectada = cadena.substr(resultado.inicio, resultado.tam);
    string subcadenaDetectada2 = cadena.substr(resultado2.inicio, resultado2.tam);
    cout << "Cadena: " << cadena << "\n";
    cout << "Posición de inicio: " << resultado.inicio << ", ";
    cout << "Número de caracteres en la mayor subcadena ascendente: " << resultado.tam << "\n";
    cout << "Subcadena ascendente detectada: " << subcadenaDetectada << "\n\n";
    cout << "Subcadena ascendente detectada: " << subcadenaDetectada2 << "\n\n";

}

*/

    // MODO 2: PRUEBA DE CASOS PARTICULARES
    /*

   // Cadena sin subcadenas ascendentes
     string cadena7 = "xgdcba";

     // Cadena con la subcadena ascendente más larga íntegra en S1
     string cadena1 = "xyzgba";

     // Cadena con la subcadena ascendente más larga íntegra en S2
     string cadena2 = "vqmabc";

     // Cadena con S1 y S2 llegando a la frontera
     string cadena3 = "qabcab";

     // Cadena en la que S1 no llega a la frontera pero S2 sí
     string cadena4 = "uvhija";

     // Cadena en la que S2 no llega a la frontera pero S1 sí
     string cadena5 = "qabcda";

     // Cadena en la que S1 y S2 no llegan a la frontera pero la cadena más larga se forma a partir de esta
     string cadena6 = "ijkefghabc";

     vector<string> cadenas = {cadena7, cadena1, cadena2, cadena3, cadena4, cadena5};

     for (const auto& cadena : cadenas) {
         auto resultado = DivideVenceras(cadena, 0, cadena.length()-1, 3);
         string subcadenaDetectada = cadena.substr(resultado.inicio, resultado.tam);

         cout << "Cadena: " << cadena << "\n";
         cout << "Posición de inicio: " << resultado.inicio << ", ";
         cout << "Número de caracteres en la mayor subcadena ascendente: " << resultado.tam << "\n";
         cout << "Subcadena ascendente detectada: " << subcadenaDetectada << "\n\n";
     }
     */

    // MODO 3: PRUEBA DE UN CASO PARTICULAR

    /*
    string cadena = "abbbcdddeffghhhijkkkkklmnoppqrsssttuuuvvwxyyzabcdefffghiiiijkklllmnnnopppqrsttttuuuvwwwxxyyzabbbbbcddefgghhijkklmmmnnopqrrsttuvvwwwxyzzzaaabccddeefghijjjklmmnnnnop";
    auto resultado = DivideVenceras(cadena, 0, cadena.length()-1, 10);
    string subcadenaDetectada = cadena.substr(resultado.inicio, resultado.tam);
    cout << "Cadena: " << cadena << "\n";
    cout << "Posición de inicio: " << resultado.inicio << ", ";
    cout << "Número de caracteres en la mayor subcadena ascendente: " << resultado.tam << "\n";
    cout << "Subcadena ascendente detectada: " << subcadenaDetectada << "\n\n";
    */

    // MODO 4: LEER DE LA ENTRADA ESTÁNDAR CON SALIDA INDICANDO TANTO DYV COMO SOLDIR

    string cadena;
    int m;
    int i = 1;
    while (cin >> cadena >> m)
    {
        // Aquí se procesa cada caso de prueba.
        int n = cadena.length() - 1;
        auto resultado = DivideVenceras(cadena, 0, n, m);
        auto resultado2 = SolucionDirecta(cadena, 0, n);
        string subcadenaDetectada = cadena.substr(resultado.inicio, resultado.tam);
        string subcadenaDetectada2 = cadena.substr(resultado2.inicio, resultado2.tam);

        cout << "Cadena " << i << "\n";
        cout << "m = " << m << "\n";
        cout << "Posición de inicio (Divide y Vencerás): " << resultado.inicio << ", ";
        cout << "Número de caracteres en la mayor subcadena ascendente: " << resultado.tam << "\n";
        cout << "Subcadena ascendente detectada (Divide y Vencerás): " << subcadenaDetectada << "\n\n";

        cout << "Posición de inicio (Solución Directa): " << resultado2.inicio << ", ";
        cout << "Número de caracteres en la mayor subcadena ascendente (Solución Directa): " << resultado2.tam << "\n";
        cout << "Subcadena ascendente detectada (Solución Directa): " << subcadenaDetectada2 << "\n";
        cout << "---------------------------------------\n";

        i = i + 1;
    }

    // MODO 5: LEER DE LA ENTRADA ESTÁNDAR CON SALIDA INDICANDO SOLO DYV

    /*
       string cadena;
       int m;
       int i=1;
       while (cin >> cadena >> m) {
           // Aquí se procesa cada caso de prueba.
           int n = cadena.length() - 1;
           auto resultado = DivideVenceras(cadena, 0, n, m);
           string subcadenaDetectada = cadena.substr(resultado.inicio, resultado.tam);


           cout << "Cadena " << i << "\n";
           cout << "m = " << m << "\n";
           cout << "Posición de inicio (Divide y Vencerás): " << resultado.inicio << ", ";
           cout << "Número de caracteres en la mayor subcadena ascendente: " << resultado.tam << "\n";
           cout << "Subcadena ascendente detectada (Divide y Vencerás): " << subcadenaDetectada << "\n\n";


           i=i+1;

       }
   */

    return 0;
}