# Juego en laberinto en C
 
 Este proyecto es un **juego de laberinto por niveles**, desarrolado en en el lenguaje c y diseñado para ejecutarse en Windows usando Dev-C. El jugador debe mover su avatar (`P`) hasta la salida (`E`) en tres niveles de dificultad creciente.
 
 ---
 
 # Como Jugar
 
 -Usa las teclas **W**, **A**, **S**, **D** para mover el jugador:
 	- `W`: Arriba 
 	- `A`: Izquierda
 	- `S`: Abajo
 	- `D`: Derecha
-El objetivo es llegar desde el punto de inicio (`P`) hasta la salida (`E´).
-Presiona **Q** para salir del juego en cualquier momento.

---

## Niveles 

Cada nivel tiene un laberinto diferente con mas complejidad.

---

## Controles y mecanica 

-Se cuentan los **pasos** dados por el jugador.
-Se mide el **tiempo** desde el primer movimiento hasta que se alcanza la salida.
-Al finalizar los tres niveles, se muestra un **resumen** con los pasos y el tiempo inveritdo en cada uno.

---

##Requisitos 

-Sistema operativo: **Windows**
-Compilador: Compatible con **Dev-c**
-Librerias utilizadas: 
    -`<stdio.h>`
    -`<conio.h>` (para captura de teclas sin Enter)
    -`<stdlib.h>`
    -`<time.h>`
    
