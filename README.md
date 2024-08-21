# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

Juan Rodriguez Arias: Algoritmo de calculo en updateOrbitalSim y optimizaciones en View.cpp
Bautista Mijalovich: creacion de clases en OrbitalSim.h y verificacion del timestep


## Verificación del timestep

Multiplicamos por 100 años el timemultiplier aumentando el tiempo que transcurre en la simulación,
verificando que la simulación siga andando dentro de un futuro lejano.....

## Verificación del tipo de datos float

Se ha cambiado el tipo de datos de float a double para asegurar una mayor precisión
en las variables que representan masas, distancias, velocidades y aceleraciones.

## Complejidad computacional con asteroides

La complejidad computacional es O(n^2), ya que cada cuerpo interactúa con todos
los demás cuerpos, lo que resulta en un cálculo cuadrático en función del número total de cuerpos.
Para poder reducir la complejidad con los asteroides, se puede por ejemplo, dibujarlos como puntos
en vez de esferas.

## Mejora de la complejidad computacional

La optimizacion que decidimos utilizar es hacer que los asteroides no interactuen entre si; reduciendo asi la complejidad computacional de O(n^2) a O(n) para los planetas y el Sol (asumiendo n como el numero de asteroides).

## Bonus points

Poniendo phi = 0 en configureAsteroid, se puede lograr que los asteroides comiencen todos en fila 
Adición del Black Hole.
