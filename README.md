# Práctica DyV
# Algoritmos y Estructuras de Datos II
# Juan Jesús Ortiz García - Gonzalo Vicente Pérez
## Curso 2023-2024. Subgrupo 2.3

### Descripción de los ficheros

**makefile**: fichero que incluye las reglas de compilación.


**casos.txt**: un fichero de texto con 50 casos de n=10000 generado por el generador estándar.


**comprobacion.txt**: un fichero de texto con la solución de los 50 casos en casos.txt, tanto por DyV como por solución directa.

**generador.cpp**: generador aleatorio de casos, pide el número de casos a generar y la n.

**generadorMejor.cpp**: generador de mejores casos, pide el número de casos a generar y la n.

**generadorPeor.cpp**: generador de peoores casos, pide el número de casos a generar y la n.

**main.cpp**: fichero que contiene la solución del algoritmo que hemos implementado. Dentro de él hay 4 modos de ejecución, se puede comentar o descomentar el modo deseado, aunque por defecto está en el modo más útil, pues devuelve la solución tanto por DyV como por Solución Directa, lo que permite comprobar que es correcto.

**Memoria.pdf**: Memoria de la práctica en PDF.


**README.md**:Fichero con las instrucciones de uso y descripción de ficheros.


### Instrucciones de uso.
Primero se debe ejecutar el make, que compila tanto los 3 generadores como el fichero main del algoritmo. Luego los 3 generadores funcionan igual, simplemente hay que indicar el número de casos y la longitud de la cadena, y se puede redireccionar a un fichero para mayor comodidad (con el carácter >). El código main tiene varios modos de ejecución (se puede cambiar yendo al main.cpp y descomentando y comentando el modo deseado). Por defecto está en el modo 3, que lee de la entrada estándar (es conveniente que sea un fichero redireccionado con el carácter <) y devuelve la solución por DyV y por solución directa. Aquí va un ejemplo:


**juanje@juanje-Lenovo-ideapad-110-15ISK:~/2cuatri/AED2/DyV$** make


g++ main.cpp -o main


g++ generadorPeor.cpp -o generadorPeor


g++ generadorMejor.cpp -o generadorMejor


g++ generador.cpp -o generador


**juanje@juanje-Lenovo-ideapad-110-15ISK:~/2cuatri/AED2/DyV$** ./generador > c.txt


Ingrese el número de casos: 10


Ingrese la longitud de las cadenas: 10000




**juanje@juanje-Lenovo-ideapad-110-15ISK:~/2cuatri/AED2/DyV$** ./main < c.txt

*salida generada por el programa*

# Práctica Voraz y Backtracking
# Algoritmos y Estructuras de Datos II
# Juan Jesús Ortiz García - Gonzalo Vicente Pérez
## Curso 2023-2024. Subgrupo 2.3


**AR.cpp**: Programa que resuelve el problema propuesto mediante avance rápido.

**BT.cpp**: Programa que resuelve el problema propuesto mediante backtracking.

**Memoria-AR_BT**: Memoria de la práctica.
