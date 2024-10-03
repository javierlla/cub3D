#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void raycast() {
    double posX = 22, posY = 12;  // Posición inicial del jugador
    double dirX = -1, dirY = 0;   // Dirección inicial (mirando hacia la izquierda)
    double planeX = 0, planeY = 0.66; // Plano de la cámara (campo de visión)

    for (int x = 0; x < screenWidth; x++)
    {
        double cameraX = 2 * x / (double)screenWidth - 1; // Coordenada X en espacio de cámara
        double rayDirX = dirX + planeX * cameraX; /*un rayo por cada pixel del mapa
        cada rayo va en una direccion diferente*/
        double rayDirY = dirY + planeY * cameraX;

        // Posición actual del mapa
        int mapX = (int)posX;
        int mapY = (int)posY;

        // Distancia desde la posición del rayo hasta la siguiente intersección en X o Y
        double sideDistX, sideDistY;

        // Distancia de un lado al siguiente en X o Y
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        /*
        deltaDistX: La distancia en el eje X que el rayo necesita recorrer para pasar de una línea de cuadrícula X a la siguiente.
        deltaDistY: Lo mismo, pero para el eje Y.
        */

        int stepX, stepY;
        int hit = 0; // ¿Se ha golpeado una pared?
        int side;    // ¿Se golpeó un muro en el lado X o Y?

        // Calculamos el paso y la distancia inicial hacia el lado más cercano
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } 
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        /*
        stepX y stepY: Indican la dirección en la que avanza el rayo en el mapa (X o Y).
        sideDistX y sideDistY: Nos dicen cual lejos está la primera intersección
                               con una línea de la cuadrícula (en los ejes X e Y).
        */


        /////////////////////////////////////////////////////////////////////////////
        // Algoritmo DDA
        while (hit == 0) {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }
        /*
        sideDistX < sideDistY: Comparamos qué dirección está más cerca de golpear una línea de la cuadrícula.

Si sideDistX es menor, significa que la intersección más cercana es en el eje X (una línea vertical).
Si sideDistY es menor, la intersección más cercana es en el eje Y (una línea horizontal).
Actualización de sideDistX o sideDistY:

Si la intersección más cercana está en el eje X (sideDistX es menor), aumentamos sideDistX sumándole deltaDistX (el tamaño del siguiente paso en X) y actualizamos mapX (cambiamos de celda en el eje X).
Si la intersección más cercana está en el eje Y (sideDistY es menor), aumentamos sideDistY sumándole deltaDistY (el tamaño del siguiente paso en Y) y actualizamos mapY (cambiamos de celda en el eje Y).
side = 0 o side = 1:

Guardamos si el rayo golpea una pared en el eje X (side = 0) o en el eje Y (side = 1). Esto es importante para luego determinar qué tan lejos está la pared y de qué lado viene.
hit = 1:

El bucle se detiene cuando encontramos una pared. Esto ocurre cuando worldMap[mapX][mapY] > 0 (lo que indica que en la celda actual hay una pared).
        */




        // Después de que el rayo golpea una pared, necesitamos calcular la distancia perpendicular entre el jugador y esa pared.
        //Esta distancia es necesaria para corregir la perspectiva y evitar distorsiones.
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else    
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
        /*
        Cuando el rayo golpea una pared, calculamos la distancia perpendicular del jugador a esa pared.
        Esto es necesario para corregir la perspectiva y evitar distorsiones de los objetos lejanos.

        Cálculo de la Distancia:
        if (side == 0)
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        Dependiendo de si el rayo golpeó una línea vertical (side == 0) o una horizontal (side == 1),
        la fórmula varía ligeramente.
        */




        // Calculamos la altura de la línea a dibujar en la pantalla
        //Esta fórmula usa la distancia para determinar cuántos píxeles ocupará la pared en la pantalla.
        int lineHeight = (int)(screenHeight / perpWallDist);
        /*
        Altura de la pared (lineHeight): La altura de la pared se calcula dividiendo la altura de la pantalla por la distancia a la pared.
        Esto funciona porque, a mayor distancia, la pared se verá más pequeña (perspectiva),
        y a menor distancia, se verá más grande.
        */



        // Calculamos los límites de la línea (donde comienza y donde termina la pared)
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
        /*
        después de calcular la altura de la pared, debemos determinar dónde empezará y
        terminará en la pantalla (en términos de píxeles).
        Queremos dibujar la pared de forma que se vea centrada y no deformada.
        */

        // Aquí dibujaríamos la línea vertical para la columna x
        printf("Columna: %d, Altura de línea: %d\n", x, lineHeight);
    }
}

int main() {
    raycast();
    return 0;
}
