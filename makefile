main generador generadorMejor generadorPeor: main.cpp generador.cpp generadorMejor.cpp generadorPeor.cpp
	g++ main.cpp -o main
	g++ generadorPeor.cpp -o generadorPeor
	g++ generadorMejor.cpp -o generadorMejor
	g++ generador.cpp -o generador
limpiar:
	rm -f generador
	rm -f generadorPeor
	rm -f generadorMejor
	rm -f main

