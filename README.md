# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

Juan Rodriguez Arias: Algoritmo de calculo en updateOrbitalSim, optimizaciones en updateOrbitalSim y View.cpp, bonus de phi = 0 y bonus de Alpha Centauri.
Bautista Mijalovich: creacion de clases en OrbitalSim.h, verificacion del timestep, bonus del agujero negro y bonus de Jupiter.

## Verificación del timestep

Haciendo 4 llamados a updateOrbitalSim en el bucle while de main.cpp, pudimos comprobar que el timestep utilizado (100 * SECONDS_PER_DAY o menor) tiene la precision necesaria como para que la simulacion sea precisa por tiempos extendidos.

## Verificación del tipo de datos float

Se ha cambiado el tipo de datos de float a double para asegurar una mayor precisión
en las variables que representan masas, distancias, velocidades y aceleraciones.

## Complejidad computacional con asteroides

La complejidad computacional para los calculos fisicos es O(n^2), ya que cada cuerpo interactúa con todos
los demás cuerpos, lo que resulta en un cálculo cuadrático en función del número total de cuerpos. La complejidad computacional para los graficos es O(n) multiplicado por el O grande de la funcion drawSphere. 

Estos son los dos cuellos de botella significativos que tiene la simulacion. Al agregar una gran cantidad de asteroides, causan que se ralentice la misma.

## Mejora de la complejidad computacional

La optimizacion que decidimos utilizar para los calculos de la fisica es hacer que los asteroides no interactuen entre si; reduciendoles asi la complejidad computacional de O(n^2) a O(n). Para los graficos, decidimos optimizar la complejidad al no graficar las asteroides como esferas sino como puntos. Tambien existe la opcion de graficarlas solo cuando estan a cierta distancia de la camara (opcion que dejamos comentada en view.cpp).

## Bonus points

(EASTER EGG) Poniendo phi = 0 en configureAsteroid, se puede lograr que los asteroides comiencen todos en fila y orbiten de forma coordinada alrededor del sol formando un espiral.

Adición del Black Hole. Se modificaron la masa y el radio del sol para operar en modo "agujero negro". Este succiona los planetas hacia si mismo y acelera drasticamente las orbitas de los asteroides. Recomendamos cambiar la constante de timeMultiplier en main.cpp a 0.1 para mejor visualizacion 

Cuando se hace a jupiter 1000x mas masivo, la orbita de todos los planetas (y el Sol en si) se desvian y comienzan a orbitar alrededor de jupiter

Agregamos Alpha Centauri (comentado en OrbitalSim.cpp). Para agregarlo, comentar el sistema solar y cambiar el valor de bodyCount a 2.
