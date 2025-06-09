#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 10
#define COLS 20

// Definición de niveles
char laberinto_nivel1[FILAS][COLS + 1] = {
    "####################",
    "#P     #         # #",
    "# ### ##### ###   # ",
    "#   #     # #     # ",
    "### # ### # # ##### ",
    "#   # #   #   #   # ",
    "# ### # ##### # ### ",
    "#     #         E # ",
    "##### ### ### ##### ",
    "####################"
};

char laberinto_nivel2[FILAS][COLS + 1] = {
    "####################",
    "#P    #     #     ##",
    "### # ### ### ###  #",
    "#   #         #  # #",
    "# ### ### ##### ####",
    "# #     #         # ",
    "### ### ######### # ",
    "##      #   ##  E# ",
    "# ####    #    #### ",
    "####################"
};

// Nivel 3: Dificultad alta
char laberinto_nivel3[FILAS][COLS + 1] = {
    "####################",
    "#P ##   #  #   #  # ",
    "#   # # ##     # ## ",
    "# #   #   # # #   # ",
    "# ### ##### # ### # ",
    "#   #       # # # # ",
    "### ##### ##### # # ",
    "#       #  #   ##E# ",
    "##### # #    #    # ",
    "####################"
};

char laberinto[FILAS][COLS + 1];

int px, py; // Posición inicial del jugador
int pasos = 0;      // Contador de pasos
clock_t tiempo_inicio = 0; // Para guardar el tiempo de inicio
int empezo = 0;     // Bandera para saber si el jugador empezó a moverse
int nivel = 1;      // Nivel de juego actual

// Arrays para guardar pasos y tiempo de cada nivel
int pasos_niveles[3] = {0, 0, 0};
double tiempo_niveles[3] = {0, 0, 0};

void copiarLaberinto(char destino[FILAS][COLS + 1], char fuente[FILAS][COLS + 1]) {
    int i, j;
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS + 1; j++) {
            destino[i][j] = fuente[i][j];
        }
    }
}

// Busca la posición inicial del jugador 'P'
void buscarJugador() {
    int i, j;
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {
            if (laberinto[i][j] == 'P') {
                px = i;
                py = j;
                return;
            }
        }
    }
}

void imprimirLaberinto(clock_t tiempo_inicio, int empezo) {
    system("cls"); // Limpia la pantalla (en Windows)
    int i;
    double segundos = 0.0;
    if (empezo) {
        segundos = (double)(clock() - tiempo_inicio) / CLOCKS_PER_SEC;
    }
    printf("Nivel %d\n", nivel);
    for(i = 0; i < FILAS; i++) {
        printf("%s\n", laberinto[i]);
    }
    printf("Pasos dados: %d\n", pasos);
    printf("Tiempo transcurrido: %.1f segundos\n", segundos);
}

int moverJugador(char dir, int *empezo, clock_t *tiempo_inicio) {
    int nx = px, ny = py;
    switch(dir) {
        case 'w': nx--; break;
        case 's': nx++; break;
        case 'a': ny--; break;
        case 'd': ny++; break;
        default: return 0;
    }
    if(nx < 0 || nx >= FILAS || ny < 0 || ny >= COLS)
        return 0;
    if(laberinto[nx][ny] == ' ' || laberinto[nx][ny] == 'E') {
        if(!(*empezo)) {
            *tiempo_inicio = clock();
            *empezo = 1;
        }
        if(laberinto[nx][ny] == 'E') return 2; // Ganaste
        laberinto[px][py] = ' ';
        px = nx; py = ny;
        laberinto[px][py] = 'P';
        pasos++; // Aumenta el contador de pasos solo si se mueve
        return 1;
    }
    return 0;
}

// Reinicia variables y carga el laberinto del nivel
void iniciarNivel(int n) {
    pasos = 0;
    tiempo_inicio = 0;
    empezo = 0;
    if (n == 1) {
        copiarLaberinto(laberinto, laberinto_nivel1);
    } else if (n == 2) {
        copiarLaberinto(laberinto, laberinto_nivel2);
    } else if (n == 3) {
        copiarLaberinto(laberinto, laberinto_nivel3);
    }
    buscarJugador();
}

void mostrarResumen() {
    int i;
    printf("\n======= RESUMEN DEL JUEGO =======\n");
    for(i = 0; i < 3; i++) {
        printf("Nivel %d:\n", i+1);
        printf("  Pasos dados: %d\n", pasos_niveles[i]);
        printf("  Tiempo total: %.1f segundos\n", tiempo_niveles[i]);
    }
    printf("\n¡Felicidades! Completaste todos los niveles.\n");
    printf("Presiona cualquier tecla para salir.\n");
    getch();
}

int main() {
    char tecla;
    int estado;
    int jugando = 1;
    nivel = 1;
    iniciarNivel(nivel);

    while (jugando) {
        imprimirLaberinto(tiempo_inicio, empezo);
        printf("Usa W/A/S/D para moverte. Llega a la E para ganar! (q para salir)\n");
        tecla = getch();
        if(tecla == 'q') break;
        estado = moverJugador(tecla, &empezo, &tiempo_inicio);
        if(estado == 2) {
            pasos++; // Cuenta el paso final hacia la salida
            double segundos = empezo ? (double)(clock() - tiempo_inicio) / CLOCKS_PER_SEC : 0.0;
            pasos_niveles[nivel-1] = pasos;
            tiempo_niveles[nivel-1] = segundos;

            imprimirLaberinto(tiempo_inicio, empezo);
            printf("¡Ganaste el nivel %d!\n", nivel);
            printf("Total de pasos dados: %d\n", pasos);
            printf("Tiempo total: %.1f segundos\n", segundos);

            if (nivel == 1) {
                printf("\nPresiona cualquier tecla para avanzar al Nivel 2 (dificultad media)...\n");
                getch();
                nivel = 2;
                iniciarNivel(nivel);
            } else if (nivel == 2) {
                printf("\nPresiona cualquier tecla para avanzar al Nivel 3 (dificultad alta)...\n");
                getch();
                nivel = 3;
                iniciarNivel(nivel);
            } else {
                mostrarResumen();
                jugando = 0;
            }
        }
    }
    return 0;
}
