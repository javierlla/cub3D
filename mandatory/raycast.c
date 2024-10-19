/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:14:15 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/19 17:23:56 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*void raycast(t_data *data)
{
    if (data->cub->map == NULL) {
        printf("Error: El mapa no está inicializado.\n");
        return;
    }

    int x = 0; // Inicializar x para el bucle while

    while (x < screenWidth) {
        // Calcular la dirección del rayo
        double cameraX = 2 * x / (double)screenWidth - 1; // Coordenada de cámara
        double rayDirX = data->cub->x_dir_dec + data->cub->planeX * cameraX; // Añadir desplazamiento de cámara
        double rayDirY = data->cub->y_dir_dec + data->cub->planeY * cameraX;

        // Posición inicial del rayo en la cuadrícula del mapa
        int mapX = (int)data->cub->x_pos_dec;
        int mapY = (int)data->cub->y_pos_dec;

        // Longitud del rayo en el espacio
        double sideDistX, sideDistY;

        // Calcular las distancias para la dirección del rayo
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        int stepX, stepY;

        int hit = 0; // Variable para saber si el rayo ha colisionado
        int side;    // Variable para saber desde qué lado se ha golpeado

        // Determinar la dirección del rayo y calcular las distancias iniciales
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (data->cub->x_pos_dec - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->cub->x_pos_dec) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (data->cub->y_pos_dec - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->cub->y_pos_dec) * deltaDistY;
        }

        // Bucle de DDA (Digital Differential Analyzer)
        while (hit == 0) {
            // Avanza en la dirección del rayo
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // 0 significa que se golpeó una pared vertical
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // 1 significa que se golpeó una pared horizontal
            }

            // Asegúrate de que mapX y mapY estén dentro de los límites
            if (mapX < 0 || mapX >= data->cub->map_width || mapY < 0 || mapY >= data->cub->map_height) {
                hit = 1; // Terminar el bucle si el rayo sale del mapa
                break;   // O puedes manejar esto como prefieras
            }

            // Comprobar si el rayo ha golpeado un muro
            if (data->cub->map[mapY][mapX] > '0') {
                hit = 1; // El rayo ha golpeado un muro
            }
        }

        // Calcular la distancia perpendicular desde el jugador a la pared
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - data->cub->x_pos_dec + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - data->cub->y_pos_dec + (1 - stepY) / 2) / rayDirY;

        if (perpWallDist <= 0)
            perpWallDist = 1; // Asegúrate de evitar la división por cero

        // Calcular la altura de la pared en la pantalla
        int lineHeight = (int)(screenHeight / perpWallDist);
        if (lineHeight > screenHeight)
            lineHeight = screenHeight; // Limitar el tamaño máximo de la pared

        // Determinar el inicio y el final de la línea a dibujar
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
       
        // Calcular las coordenadas de textura
    double wallX;
    if (side == 0) {
        wallX = data->cub->y_pos_dec + perpWallDist * rayDirY;
    } else {
        wallX = data->cub->x_pos_dec + perpWallDist * rayDirX;
    }
    wallX -= floor(wallX); // Asegurar que esté entre 0 y 1

    // Verifica que wallX esté correctamente entre 0 y 1
    if (wallX < 0 || wallX > 1)
    {
        printf("Warning: wallX fuera de rango. Valor actual: %f\n", wallX);
        wallX = fmod(wallX + 1, 1); // Normalizar wallX
    }
        // Coordenadas de textura
        int texX = (int)(wallX * (double)TEX_WIDTH);
        if (side == 0 && rayDirX > 0) texX = TEX_WIDTH - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEX_WIDTH - texX - 1;

        // Asegurarse de que las coordenadas de textura estén dentro de los límites
        if (texX < 0) texX = 0;
        if (texX >= TEX_WIDTH) texX = TEX_WIDTH - 1;
        
        // Obtener la textura correspondiente a la pared golpeada
        int texNum = (side == 0) ? ((rayDirX < 0) ? 2 : 3) : ((rayDirY < 0) ? 0 : 1); // 0: Norte, 1: Sur, 2: Oeste, 3: Este

        // Dibujar la pared línea por línea
        int y = drawStart;
        while (y < drawEnd) {
            // Ajuste mejorado para texY
            int d = y * 256 - screenHeight * 128 + lineHeight * 128; // 256 es una escala para evitar punto flotante
            int texY = ((d * TEX_HEIGHT) / lineHeight) / 256; // Texto Y correspondiente
            
            // Limitar la altura de la textura
            if (texY < 0) texY = 0;
            if (texY >= TEX_HEIGHT) texY = TEX_HEIGHT - 1;
            printf("texY es = %d\n y d es = %d\n", texY, d);

            // Obtener el color de la textura
           
            unsigned int color = get_texture_color(data->cub, texNum, texX, texY); // Obtener el color de la textura

            my_mlx_pixel_put(data, x, y, color);
            y++;
        }

        // Aumentar x para el siguiente rayo
        x++;
    }
}*/


/* normalize_minus_one_one
*
*  Before: x is an integer inside [0-ScreenWidth] range
*
*  After: x is a double inside [-1,1] range
*
*  Purpose: whatever the ScreenWidth may vary, for us we 
*           want work with a range of [-1,1], from left to rigt
*           of the screen.
*
*           -1 ------------------ 0 ------------------ 1
*
*  How?

*  1) Rule of 3 to get double [0-2]
*
*     2 (total) ------------------ ScreenWidth
*     (whatever) ------------------ (result)
*
*  2) -1 to get inside [-1,1] range
*/
double	normalize_minus_one_one(int x)
{
	double	result;

	result = x * 2 / (double)screenWidth;
	result = result -1;
	return (result);
}


/* raycast
*
*
*
*/
void raycast(t_data *data)
{
    if (data->cub->map == NULL) {
        printf("Error: El mapa no está inicializado.\n");
        return;
    }

    int x = 0; // Inicializar x para el bucle while

    while (x < screenWidth)
    {
        // Calcular la dirección del rayo
        double cameraX;
        
        cameraX = normalize_minus_one_one(x);
        double rayDirX = data->cub->x_dir_dec + data->cub->planeX * cameraX; // Añadir desplazamiento de cámara
        double rayDirY = data->cub->y_dir_dec + data->cub->planeY * cameraX;

        // Limitar rayDirX y rayDirY para evitar divisiones por cero o valores extremos
        if (fabs(rayDirX) < 0.0001) rayDirX = 0.0001;
        if (fabs(rayDirY) < 0.0001) rayDirY = 0.0001;

        // Imprimir los valores de rayDirX y rayDirY para cada rayo
        //printf("Ray %d -> rayDirX: %f, rayDirY: %f\n", x, rayDirX, rayDirY);

        // Posición inicial del rayo en la cuadrícula del mapa
        int mapX = (int)data->cub->x_pos_dec;
        int mapY = (int)data->cub->y_pos_dec;

        // Longitud del rayo en el espacio
        double sideDistX, sideDistY;

        // Calcular las distancias para la dirección del rayo
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        int stepX, stepY;

        int hit = 0; // Variable para saber si el rayo ha colisionado
        int side;    // Variable para saber desde qué lado se ha golpeado

        // Determinar la dirección del rayo y calcular las distancias iniciales
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (data->cub->x_pos_dec - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->cub->x_pos_dec) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (data->cub->y_pos_dec - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->cub->y_pos_dec) * deltaDistY;
        }

        // Bucle de DDA (Digital Differential Analyzer): wall hit detection
        while (hit == 0) {
            // Avanza en la dirección del rayo
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // 0 significa que se golpeó una pared vertical
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // 1 significa que se golpeó una pared horizontal
            }

            // Asegúrate de que mapX y mapY estén dentro de los límites
            if (mapX < 0 || mapX >= data->cub->map_width || mapY < 0 || mapY >= data->cub->map_height) {
                hit = 1; // Terminar el bucle si el rayo sale del mapa
                break;
            }

            // Comprobar si el rayo ha golpeado un muro
            if (data->cub->map[mapY][mapX] > '0') {
                hit = 1; // El rayo ha golpeado un muro
            }
        }

        // Calcular la distancia perpendicular desde el jugador a la pared
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - data->cub->x_pos_dec + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - data->cub->y_pos_dec + (1 - stepY) / 2) / rayDirY;

        // Evitar valores muy pequeños o negativos en perpWallDist
        if (perpWallDist <= 0.01)
            perpWallDist = 0.01;

        // Calcular la altura de la pared en la pantalla
        int lineHeight = (int)(screenHeight / perpWallDist);
        if (lineHeight > screenHeight)
            lineHeight = screenHeight; // Limitar el tamaño máximo de la pared

        // Determinar el inicio y el final de la línea a dibujar
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Calcular las coordenadas de textura: perpendicular wall distance
        double wallX;
        if (side == 0) {
            wallX = data->cub->y_pos_dec + perpWallDist * rayDirY;
        } else {
            wallX = data->cub->x_pos_dec + perpWallDist * rayDirX;
        }
        wallX -= floor(wallX); // Asegurar que esté entre 0 y 1

        // Verifica que wallX esté correctamente entre 0 y 1: wall height calculation
        if (wallX < 0 || wallX > 1) {
            printf("Warning: wallX fuera de rango. Valor actual: %f\n", wallX);
            wallX = fmod(wallX + 1, 1); // Normalizar wallX
        }

        // Imprimir el valor de wallX
        //printf("Ray %d -> wallX: %f\n", x, wallX);

       /* Texturas */

        // Coordenadas de textura
        int texX = (int)(wallX * (double)TEX_WIDTH);
        if (side == 0 && rayDirX > 0) texX = TEX_WIDTH - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEX_WIDTH - texX - 1;

        // Asegúrate de que texX esté dentro de los límites y luego imprímelo
        if (texX < 0) texX = 0;
        if (texX >= TEX_WIDTH) texX = TEX_WIDTH - 1;

        // Imprimir el valor de texX
        //printf("Ray %d -> texX: %d\n", x, texX);

        // Obtener la textura correspondiente a la pared golpeada
        int texNum = (side == 0) ? ((rayDirX < 0) ? 2 : 3) : ((rayDirY < 0) ? 0 : 1); // 0: Norte, 1: Sur, 2: Oeste, 3: Este

        // Dibujar la pared línea por línea
        int y = drawStart;
        while (y < drawEnd) {
            int d = y * 256 - screenHeight * 128 + lineHeight * 128; // 256 es una escala para evitar punto flotante
            int texY = ((d * TEX_HEIGHT) / lineHeight) / 256; // Texto Y correspondiente
            
            // Limitar la altura de la textura
            if (texY < 0) texY = 0;
            if (texY >= TEX_HEIGHT) texY = TEX_HEIGHT - 1;

            // Obtener el color de la textura
            unsigned int color = get_texture_color(data, texNum, texX, texY); // Obtener el color de la textura

            my_mlx_pixel_put(data, x, y, color);
            y++;
        }

        // Aumentar x para el siguiente rayo
        x++;
    }
}


/*void raycast(t_data *data)
{
    if (data->cub->map == NULL) {
        printf("Error: El mapa no está inicializado.\n");
        return;
    }

    int x = 0; // Inicializar x para el bucle while

    while (x < screenWidth) {
        // Calcular la dirección del rayo
        double cameraX = 2 * x / (double)screenWidth - 1; // Coordenada de cámara
        double rayDirX = data->cub->x_dir_dec + data->cub->planeX * cameraX; // Añadir desplazamiento de cámara
        double rayDirY = data->cub->y_dir_dec + data->cub->planeY * cameraX;

        // Posición inicial del rayo en la cuadrícula del mapa
        int mapX = (int)data->cub->x_pos_dec;
        int mapY = (int)data->cub->y_pos_dec;

        // Longitud del rayo en el espacio
        double sideDistX, sideDistY;

        // Calcular las distancias para la dirección del rayo
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        int stepX, stepY;

        int hit = 0; // Variable para saber si el rayo ha colisionado
        int side;    // Variable para saber desde qué lado se ha golpeado

        // Determinar la dirección del rayo y calcular las distancias iniciales
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (data->cub->x_pos_dec - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->cub->x_pos_dec) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (data->cub->y_pos_dec - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->cub->y_pos_dec) * deltaDistY;
        }

        // Bucle de DDA (Digital Differential Analyzer)
        while (hit == 0) {
            // Avanza en la dirección del rayo
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // 0 significa que se golpeó una pared vertical
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // 1 significa que se golpeó una pared horizontal
            }

            // Asegúrate de que mapX y mapY estén dentro de los límites
            if (mapX < 0 || mapX >= data->cub->map_width || mapY < 0 || mapY >= data->cub->map_height) {
                hit = 1; // Terminar el bucle si el rayo sale del mapa
                break;
            }

            // Comprobar si el rayo ha golpeado un muro
            if (data->cub->map[mapY][mapX] > '0') {
                hit = 1; // El rayo ha golpeado un muro
            }
        }

        // Calcular la distancia perpendicular desde el jugador a la pared
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - data->cub->x_pos_dec + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - data->cub->y_pos_dec + (1 - stepY) / 2) / rayDirY;

        if (perpWallDist <= 0)
            perpWallDist = 1; // Asegúrate de evitar la división por cero

        // Calcular la altura de la pared en la pantalla
        int lineHeight = (int)(screenHeight / perpWallDist);
        if (lineHeight > screenHeight)
            lineHeight = screenHeight; // Limitar el tamaño máximo de la pared

        // Determinar el inicio y el final de la línea a dibujar
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Calcular las coordenadas de textura
        double wallX;
        if (side == 0) {
            wallX = data->cub->y_pos_dec + perpWallDist * rayDirY;
        } else {
            wallX = data->cub->x_pos_dec + perpWallDist * rayDirX;
        }
        wallX -= floor(wallX); // Asegurar que esté entre 0 y 1

        // Verifica que wallX esté correctamente entre 0 y 1
        if (wallX < 0 || wallX > 1) {
            printf("Warning: wallX fuera de rango. Valor actual: %f\n", wallX);
            wallX = fmod(wallX + 1, 1); // Normalizar wallX
        }

        // Coordenadas de textura
        int texX = (int)(wallX * (double)TEX_WIDTH);
        if (side == 0 && rayDirX > 0) texX = TEX_WIDTH - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEX_WIDTH - texX - 1;

        // Asegurarse de que las coordenadas de textura estén dentro de los límites
        if (texX < 0) texX = 0;
        if (texX >= TEX_WIDTH) texX = TEX_WIDTH - 1;

        // Obtener la textura correspondiente a la pared golpeada
        int texNum = (side == 0) ? ((rayDirX < 0) ? 2 : 3) : ((rayDirY < 0) ? 0 : 1); // 0: Norte, 1: Sur, 2: Oeste, 3: Este

        // Dibujar la pared línea por línea
        int y = drawStart;
        while (y < drawEnd) {
            int d = y * 256 - screenHeight * 128 + lineHeight * 128; // 256 es una escala para evitar punto flotante
            int texY = ((d * TEX_HEIGHT) / lineHeight) / 256; // Texto Y correspondiente
            
            // Limitar la altura de la textura
            if (texY < 0) texY = 0;
            if (texY >= TEX_HEIGHT) texY = TEX_HEIGHT - 1;

            // Obtener el color de la textura
            unsigned int color = get_texture_color(data, texNum, texX, texY); // Obtener el color de la textura

            my_mlx_pixel_put(data, x, y, color);
            y++;
        }

        // Aumentar x para el siguiente rayo
        x++;
    }
}*/
