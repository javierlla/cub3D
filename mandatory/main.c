/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/10 13:40:24 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*double calculate_perpendicular_distance(t_cub *cub, int mapX, int mapY, double rayDirX, double rayDirY, int stepX, int stepY)
{
    double perpWallDist;

    if (stepX == 1) {
        perpWallDist = (mapX + 1 - cub->posX) / rayDirX;
    } else {
        perpWallDist = (mapX - cub->posX) / rayDirX;
    }

    if (stepY == 1) {
        perpWallDist = (mapY + 1 - cub->posY) / rayDirY;
    } else {
        perpWallDist = (mapY - cub->posY) / rayDirY;
    }

    return perpWallDist;
}*/

/*double calculate_perpendicular_distance(t_cub *cub, int mapX, int mapY, double rayDirX, double rayDirY, int stepX, int stepY) {
    double perpWallDistX = (rayDirX != 0) ? ((stepX == 1) ? (mapX + 1 - cub->posX) / rayDirX : (mapX - cub->posX) / rayDirX) : 1e30;
    double perpWallDistY = (rayDirY != 0) ? ((stepY == 1) ? (mapY + 1 - cub->posY) / rayDirY : (mapY - cub->posY) / rayDirY) : 1e30;

    // Return the shortest perpendicular distance
    return (perpWallDistX < perpWallDistY) ? perpWallDistX : perpWallDistY;
}



int calculate_draw_start(int lineHeight) {
    int drawStart = -lineHeight / 2 + screenHeight / 2;
    if (drawStart < 0) {
        drawStart = 0;
    }
    return drawStart;
}

int calculate_draw_end(int lineHeight) {
    int drawEnd = lineHeight / 2 + screenHeight / 2;
    if (drawEnd >= screenHeight) {
        drawEnd = screenHeight - 1;
    }
    return drawEnd;
}

int determine_texture_side(double rayDirX, double rayDirY, int side) {
    int texNum;
    if (side == 0) {
        texNum = (rayDirX < 0) ? 2 : 3;
    } else {
        texNum = (rayDirY < 0) ? 0 : 1;
    }
    return texNum;
}

double calculate_wallX(t_cub *cub, double perpWallDist, double rayDirX, double rayDirY, int side) {
    double wallX;
    if (side == 0) {
        wallX = cub->posY + perpWallDist * rayDirY;
    } else {
        wallX = cub->posX + perpWallDist * rayDirX;
    }
    wallX -= floor(wallX);
    return wallX;
}

void raycast(t_cub *cub) {
    // Initialize player position and direction
    cub->posX = 2;
    cub->posY = 2;
    cub->dirX = -1;
    cub->dirY = 0;
    cub->planeX = 0;
    cub->planeY = 0.66;

    if (cub->map == NULL) {
        fprintf(stderr, "Error: El mapa no está inicializado.\n");
        return;
    }

    for (int x = 0; x < screenWidth; x++) {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = cub->dirX + cub->planeX * cameraX;
        double rayDirY = cub->dirY + cub->planeY * cameraX;

        int mapX = (int)cub->posX;
        int mapY = (int)cub->posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        int stepX = (rayDirX < 0) ? -1 : 1;
        int stepY = (rayDirY < 0) ? -1 : 1;

        // Calculate the side distances
        sideDistX = (rayDirX < 0) ? (cub->posX - mapX) * deltaDistX : (mapX + 1.0 - cub->posX) * deltaDistX;
        sideDistY = (rayDirY < 0) ? (cub->posY - mapY) * deltaDistY : (mapY + 1.0 - cub->posY) * deltaDistY;

        int hit = 0;
        int side = 0;

        // DDA algorithm
        while (hit == 0) {
            hit = perform_dda(cub, &mapX, &mapY, &side, &sideDistX, &sideDistY, stepX, stepY, deltaDistX, deltaDistY);
        }

        double perpWallDist = calculate_perpendicular_distance(cub, mapX, mapY, rayDirX, rayDirY, stepX, stepY);
        if (perpWallDist > 0)
        { // Ensure we have a valid distance
            int lineHeight = (int)(screenHeight / perpWallDist);
            int drawStart = calculate_draw_start(lineHeight);
            int drawEnd = calculate_draw_end(lineHeight);

            int texNum = determine_texture_side(rayDirX, rayDirY, side);
            double wallX = calculate_wallX(cub, perpWallDist, rayDirX, rayDirY, side);

            int texX = (int)(wallX * (double)TEX_WIDTH);
            if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0)) {
                texX = TEX_WIDTH - texX - 1;
            }

            int y = drawStart;
            while (y < drawEnd) {
                int d = (y * 256) - (screenHeight * 128) + (lineHeight * 128);
                int texY = (d * TEX_HEIGHT) / lineHeight / 256; // Calculate texture y-coordinate
                if (texY >= 0 && texY < TEX_HEIGHT) { // Ensure texY is within bounds
                    unsigned int color = get_texture_color(cub, texNum, texX, texY);
                    my_mlx_pixel_put(cub->mlx, x, y, color);
                }
                y++;
            }
        }
        printf("Ray X: %d, Perpendicular distance: %f, Line Height: %d\n", x, perpWallDist, lineHeight);

      //  printf("TexNum: %d, TexX: %d, TexY: %d\n", texNum, texX, texY);
    }
}


int perform_dda(t_cub *cub, int *mapX, int *mapY, int *side, double *sideDistX, double *sideDistY, int stepX, int stepY, double deltaDistX, double deltaDistY) {
    // Check for out-of-bounds
    if (*mapX < 0 || *mapX >= cub->map_width || *mapY < 0 || *mapY >= cub->map_height) {
        return 0; // Out of bounds
    }

    // Check for wall hit
    if (cub->map[*mapY][*mapX] > 0) {
        return 1; // Wall hit
    }

    // Advance in the direction of the smallest side distance
    if (*sideDistX < *sideDistY) {
        *sideDistX += deltaDistX;
        *mapX += stepX;
        *side = 0; // Hit on the X side
    } else {
        *sideDistY += deltaDistY;
        *mapY += stepY;
        *side = 1; // Hit on the Y side
    }

    return 0; // No hit
}*/

/*void raycast(t_cub *cub)
{
    if (cub->map == NULL)
    {
        printf("Error: El mapa no está inicializado.\n");
        return;
    }
    for (int x = 0; x < screenWidth; x++)
    {
        // Calcular la dirección del rayo
        double cameraX = 2 * x / (double)screenWidth - 1; // Coordenada de cámara
        double rayDirX = cub->dirX + cub->planeX * cameraX; // Añadir desplazamiento de cámara
        double rayDirY = cub->dirY + cub->planeY * cameraX;

        // Calcular la posición inicial del rayo
        int mapX = (int)cub->posX;
        int mapY = (int)cub->posY;

        // Longitud del rayo en el espacio
        double sideDistX;
        double sideDistY;

        // Calcular las distancias para la dirección del rayo
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        int stepX, stepY;

        int hit = 0; // Variable para saber si el rayo ha colisionado
        int side; // Variable para saber desde qué lado se ha golpeado

        // Detección de las direcciones del rayo
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (cub->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - cub->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (cub->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - cub->posY) * deltaDistY;
        }
        // Bucle de DDA (Digital Differential Analyzer)
        while (hit == 0)
        {
        // Si el rayo ha golpeado el lado X primero
            if (sideDistX < sideDistY)
            {
               sideDistX += deltaDistX;
               mapX += stepX;
                side = 0; // 0 significa que el rayo ha golpeado un lado vertical
            }
            else 
            { // Si el rayo ha golpeado el lado Y primero
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // 1 significa que el rayo ha golpeado un lado horizontal
            }

            // Asegúrate de que mapX y mapY estén dentro de los límites
            if (mapX < 0 || mapX >= cub->map_width || mapY < 0 || mapY >= cub->map_height)
            {
                hit = 1; // Terminar el bucle si el rayo sale del mapa
                break; // O puedes manejar esto como prefieras
            }
            // Aquí debes comprobar si el mapa tiene una colisión
            if (cub->map[mapY][mapX] > '0')
            { // Cambia a cub->map y comprueba si hay colisión
                hit = 1; // El rayo ha golpeado un objeto
            }
        }

        // Calcular la longitud del rayo (distancia desde la posición del jugador hasta la colisión)
        // Calcular la longitud del rayo (distancia desde la posición del jugador hasta la colisión)
        double perpWallDist;
        if (side == 0)
        {
            perpWallDist = (mapX - cub->posX + (1 - stepX) / 2) / rayDirX; // Distancia desde el jugador hasta la pared
        }   
        else
        {
            perpWallDist = (mapY - cub->posY + (1 - stepY) / 2) / rayDirY;
        }
    
        if (perpWallDist <= 0)
        {
            perpWallDist = 1; // Asegúrate de que nunca sea 0 para evitar división por cero 
        }
    
        // Altura del rayo en la pantalla
        printf("perpWallDist: %f\n", perpWallDist);
        int lineHeight = (int)(screenHeight / perpWallDist);

        // Determinar el inicio y el final de la línea a dibujar
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
         
        printf("perpWallDist: %f, lineHeight: %d\n", perpWallDist, lineHeight);
        printf("drawStart: %d, drawEnd: %d\n", drawStart, drawEnd);

        
        // Calcular las coordenadas de textura
        int texNum; // Determina qué textura usar (0-3)
        
        if (side == 0) {
            texNum = (rayDirX < 0) ? 2 : 3; // 2: pared oeste, 3: pared este
        } else {
            texNum = (rayDirY < 0) ? 0 : 1; // 0: pared norte, 1: pared sur
        }

        // Posición de la textura

        double wallX;
        if (side == 0) {
            wallX = cub->posY + perpWallDist * rayDirY;
        } else {
            wallX = cub->posX + perpWallDist * rayDirX;
        }
        wallX -= floor(wallX); // Obtiene la parte fraccionaria

        // Coordenadas de textura
        int texX = (int)(wallX * TEX_WIDTH);
        int texY;

        // Calcular texY asegurándose de que se mantenga dentro de límites válidos
        if (lineHeight > 0) {
            texY = (drawStart - screenHeight / 2 + lineHeight / 2) * TEX_HEIGHT / lineHeight;
        } else {
            texY = 0; // Asignar un valor por defecto si lineHeight es 0
        }

        // Comprobar límites
        if (texX < 0) texX = 0;
        if (texX >= TEX_WIDTH) texX = TEX_WIDTH - 1;
       // if (texX < 0 || texX >= TEX_WIDTH || texY < 0 || texY >= TEX_HEIGHT)
            //{
                //printf("Error: Coordenadas de textura fuera de límites: texX=%d, texY=%d\n", texX, texY);
                if (texX < 0) texX = 0;
                if (texX >= TEX_WIDTH) texX = TEX_WIDTH - 1;
                if (texY < 0) texY = 0;
                if (texY >= TEX_HEIGHT) texY = TEX_HEIGHT - 1;
           // }
        if (texY < 0) texY = 0;
        if (texY >= TEX_HEIGHT) texY = TEX_HEIGHT - 1;

        // Imprimir información de depuración
        printf("TexX: %d, TexY: %d, TEX_WIDTH: %d, TEX_HEIGHT: %d\n", texX, texY, TEX_WIDTH, TEX_HEIGHT);
        printf("bits_per_pixel: %d, line_length: %d\n", cub->bits_per_pixel, cub->line_length);

        // Continuar con el procesamiento de la textura
        unsigned int color = get_texture_color(cub, texNum, texX, texY);

        // Dibuja el color en el pixel correspondiente
        // Usar mlx_pixel_put o similar para dibujar el color en el pixel (x, y)
        for (int y = drawStart; y < drawEnd; y++)
        {
           // mlx_pixel_put(cub->mlx->mlx_ptr, cub->mlx->win_ptr, x, y, color);
            my_mlx_pixel_put(cub->mlx, x, y, color);
        }
    }
}*/

void my_mlx_pixel_put(t_mlx *data, int x, int y, unsigned int color)
{
    char *dst;
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
    {
        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}

void raycast(t_cub *cub)
{
    if (cub->map == NULL)
    {
        printf("Error: El mapa no está inicializado.\n");
        return;
    }

    int x = 0; // Inicializar x para el bucle while

    while (x < screenWidth)
    {
        // Calcular la dirección del rayo
        double cameraX = 2 * x / (double)screenWidth - 1; // Coordenada de cámara
        double rayDirX = cub->dirX + cub->planeX * cameraX; // Añadir desplazamiento de cámara
        double rayDirY = cub->dirY + cub->planeY * cameraX;

        // Posición inicial del rayo en la cuadrícula del mapa
        int mapX = (int)cub->posX;
        int mapY = (int)cub->posY;

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
            sideDistX = (cub->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - cub->posX) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (cub->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - cub->posY) * deltaDistY;
        }

        // Bucle de DDA (Digital Differential Analyzer)
        while (hit == 0)
        {
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
            if (mapX < 0 || mapX >= cub->map_width || mapY < 0 || mapY >= cub->map_height) {
                hit = 1; // Terminar el bucle si el rayo sale del mapa
                break;   // O puedes manejar esto como prefieras
            }

            // Comprobar si el rayo ha golpeado un muro
            if (cub->map[mapY][mapX] > '0') {
                hit = 1; // El rayo ha golpeado un muro
            }
        }

        // Calcular la distancia perpendicular desde el jugador a la pared
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - cub->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - cub->posY + (1 - stepY) / 2) / rayDirY;

        if (perpWallDist <= 0)
            perpWallDist = 1; // Asegúrate de evitar la división por cero

        // Calcular la altura de la pared en la pantalla
        int lineHeight = (int)(screenHeight / perpWallDist);

        // Determinar el inicio y el final de la línea a dibujar
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Calcular las coordenadas de textura
        double wallX;
        if (side == 0) {
            wallX = cub->posY + perpWallDist * rayDirY;
        } else {
            wallX = cub->posX + perpWallDist * rayDirX;
        }
        wallX -= floor(wallX); // Obtener solo la parte fraccionaria

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
        while (y < drawEnd)
        {
            // Ajuste mejorado para texY
            int d = y * 256 - screenHeight * 128 + lineHeight * 128; // Calcular 'd' para evitar artefactos
            int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;         // Ajuste para la coordenada texY

            // Asegurarse de que texY esté dentro de los límites
            if (texY < 0) texY = 0;
            if (texY >= TEX_HEIGHT) texY = TEX_HEIGHT - 1;

            unsigned int color = get_texture_color(cub, texNum, texX, texY); // Obtener el color de la textura

            // Dibuja el color en el pixel correspondiente
            my_mlx_pixel_put(cub->mlx, x, y, color);

            y++; // Incrementar y
        }

        x++; // Incrementar x
    }
}



void render_sky_and_floor(t_cub *cub)
{
    unsigned int floor_color = cub->floor_color;
    unsigned int ceiling_color = cub->ceiling_color;
	int x;
    int y = 0;
    
    while (y < screenHeight / 2) 
	{
        x = 0;
        while (x < screenWidth)
		{
            my_mlx_pixel_put(cub->mlx, x, y, ceiling_color);
            x++;
        }
        y++;
    }
    while (y < screenHeight)
	{
        x = 0;
        while (x < screenWidth)
		{
            my_mlx_pixel_put(cub->mlx, x, y, floor_color);
            x++;
        }
        y++;
    }
}

unsigned int get_texture_color(t_cub *cub, int texNum, int texX, int texY)
{
    if (texNum < 0 || texNum >= 4)
    {
        printf("Error: texturas fuera de límites: %d\n", texNum);
        return 0;
    }
    if (cub->textures_data[texNum] == NULL)
    {
        printf("Error: La textura %d no está cargada.\n", texNum);
        return 0;
    }

    if (texX < 0 || texX >= TEX_WIDTH || texY < 0 || texY >= TEX_HEIGHT)
    {
        printf("Error: Coordenadas de textura fuera de límites: texX=%d, texY=%d\n", texX, texY);
        return 0;
    }
    unsigned int color = *(unsigned int *)(cub->textures_data[texNum] + (texY * cub->line_length + texX * (cub->bits_per_pixel / 8)));
    return color;
}

int load_texture(t_cub *cub, int index, char *texture_path)
{
    int width = TEX_WIDTH;
    
    int height = TEX_HEIGHT;

    if (index < 0 || index >= 4) {
        printf("Error: Índice de textura fuera de límites: %d\n", index);
        return -1;
    }

    if (!texture_path) {
        printf("Error: Ruta de la textura es nula para el índice %d.\n", index);
        return -1;
    }
    //printf("%p\n",  cub->textures[index]);
    cub->textures[index] = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, texture_path, &width, &height);
        
    if (cub->textures[index])
        printf("%p\n",  cub->textures[index]);
    if (!(cub->textures[index])) {
        printf("Error: No se pudo cargar la textura en %s\n", texture_path);
        return -1;
    }

    cub->textures_data[index] = mlx_get_data_addr(cub->textures[index], &cub->bits_per_pixel, &cub->line_length, &cub->endian);
    if (!cub->textures_data[index])
    {
        printf("Error: No se pudo obtener los datos de la textura en %s\n", texture_path);
        return -1;
    }

    return 0;
}

void load_textures(t_cub *cub)
{
    cub->textures = malloc(sizeof(void *) * 4);
    cub->textures_data = malloc(sizeof(char *) * 4);

    if (!cub->textures || !cub->textures_data)
    {
        printf("Error: No se pudo asignar memoria para las texturas.\n");
        exit(EXIT_FAILURE);
    }
    int i; 
    
    i = 0;
    while (i < 4)
    {
        cub->textures[i] = NULL;
        cub->textures_data[i] = NULL;
        i++;
    }
    if (load_texture(cub, 0, cub->north_texture))
        printf("Error: No se pudo cargar la textura del Norte: %s\n", cub->north_texture);
    if (load_texture(cub, 1, cub->south_texture))
        printf("Error: No se pudo cargar la textura del Sur: %s\n", cub->south_texture);
    if (load_texture(cub, 2, cub->west_texture))
        printf("Error: No se pudo cargar la textura del Oeste: %s\n", cub->west_texture);
    if (load_texture(cub, 3, cub->east_texture))
        printf("Error: No se pudo cargar la textura del Este: %s\n", cub->east_texture);
    i = 0;
    while (i < 4)
    {
        if (!cub->textures[i] || !cub->textures_data[i])
        {
            printf("Error: La textura %d no se ha cargado correctamente.\n", i);
            return;
        }
        i++;
    }
}

int *render_next_frame(t_mlx *mlx, t_cub *cub)
{
    if (!mlx || !cub)
    {
        printf("Error: Puntero a mlx o cub es nulo.\n");
        return (NULL);
    }

    render_sky_and_floor(cub);
    raycast(cub);

    if (mlx->mlx_ptr && mlx->win_ptr)
    {
        mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
    }
    return 0;
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        write(2, "Usage: ./cub3D <map.cub>\n", 26);
        return EXIT_FAILURE;
    }

    t_cub cub;
    t_mlx mlx;

    ft_memset(&cub, 0, sizeof(t_cub));
    ft_memset(&mlx, 0, sizeof(t_mlx));

    cub.floor_color = -1;
    cub.ceiling_color = -1;
    cub.posX = -1;
    cub.posY = -1;
    read_cub_file(&cub, argv[1]);
    
    if (!cub.north_texture || !cub.south_texture || !cub.west_texture || !cub.east_texture ||
    cub.floor_color == -1 || cub.ceiling_color == -1 || cub.map == NULL ||
    cub.posX == -1 || cub.posY == -1) 
        exit_with_error("Missing textures, colors, map or player start position");


    print_cub_data(&cub);

    init_window(&mlx);
    mlx.img = mlx_new_image(mlx.mlx_ptr, screenWidth, screenHeight);
    if (!mlx.img)
    {
        printf("Error: No se pudo crear la imagen.\n");
        return -1;
    }
    mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
    if (!mlx.addr)
    {
        printf("Error: No se pudo obtener la dirección de la imagen.\n");
        return -1;
    }

    cub.mlx = &mlx;
    load_textures(&cub); 

    mlx_loop_hook(mlx.mlx_ptr, ((void *)render_next_frame(&mlx, &cub)), &cub); 
    mlx_loop(mlx.mlx_ptr); 

    return 0;
}



