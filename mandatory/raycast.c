/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:14:15 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/19 19:13:18 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

/* get_ray_dir
*
*  If conditionals are used to limit rayDirX and rayDirY to avoid
*  division by zero or extreme values.
*/
void	get_ray_dir(t_data *data, t_raycast_vars *r, int x)
{
	r->cameraX = normalize_minus_one_one(x);
	r->rayDirX = data->cub->x_dir_dec + data->cub->planeX * r->cameraX;
	r->rayDirY = data->cub->y_dir_dec + data->cub->planeY * r->cameraX;

	if (fabs(r->rayDirX) < 0.0001)
		r->rayDirX = 0.0001;
    if (fabs(r->rayDirY) < 0.0001)
		r->rayDirY = 0.0001;
}

void	set_initial_ray_pos(t_data *data, t_raycast_vars *r)
{
	r->mapX = (int)data->cub->x_pos_dec;
	r->mapY = (int)data->cub->y_pos_dec;
}

/* calculate_delta_dist
*
*	fabs is used to make sure distance is positive.
*
*	deltaDistX and deltaDistY represent the distance
*   the ray has to travel from one x or y-side to the
*	next x or y-side.
*
*	Example:
*   If rayDirX = 1, then deltaDistX = 1
*   If rayDirX = -1, then deltaDistX = 1
*   If rayDirX = 0.5, then deltaDistX = 2
*   If rayDirX = -0.5, then deltaDistX = 2
*
*   Summary:
*
*
*
*   Explanation of logic behind operation: 
*    - We only care about when ray crosses a grid line
*
*
*  7 ---|---|---|---|---|-         P (1, 6): 1 unit in X direction,
*  6 ---P---|---|---|---|-         6 units in Y direction for every 
*  4 ---|---|---|---|---|-         step along ray's path.
*  5 ---|---|---|---|---|-         
*  3 ---|---|---|---|---|-      rayDirX = 1;  deltaDistX = 1 / rayDirX = 1 / 1 = 1
*  2 ---|---|---|---|---|-      rayDirY = 6;  deltaDistY = 1 / rayDirY = 1 / 6 = 0.166666
*  1 ---|---|---|---|---|-         
*  0   1   2   3   4   5
*
*
* R (3, 2) P is more vertical than horizontalR is more horizontal than vertical
*/
void calculate_delta_dist(t_raycast_vars *r)
{
	r->deltaDistX = fabs(1 / r->rayDirX);
	r->deltaDistY = fabs(1 / r->rayDirY);
}

void	define_ray_dir(t_data *data, t_raycast_vars *r)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (data->cub->x_pos_dec - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - data->cub->x_pos_dec) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (data->cub->y_pos_dec - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - data->cub->y_pos_dec) * r->deltaDistY;
	}
}

void dda (t_data *data, t_raycast_vars *r)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		// Avanza en la dirección del rayo
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0; // 0 significa que se golpeó una pared vertical
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1; // 1 significa que se golpeó una pared horizontal
		}
		// Asegúrate de que mapX y mapY estén dentro de los límites
		if (r->mapX < 0 || r->mapX >= data->cub->map_width || r->mapY < 0 || r->mapY >= data->cub->map_height)
		{
			hit = 1; // Terminar el bucle si el rayo sale del mapa
			break;
		}
		// Comprobar si el rayo ha golpeado un muro
		if (data->cub->map[r->mapY][r->mapX] > '0')
			hit = 1; // El rayo ha golpeado un muro
	}
}

void get_perp_wall_dist(t_data *data, t_raycast_vars *r)
{
	if (r->side == 0)
		r->perpWallDist = (r->mapX - data->cub->x_pos_dec
				+ (1 - r->stepX) / 2) / r->rayDirX;
	else
		r->perpWallDist = (r->mapY - data->cub->y_pos_dec
				+ (1 - r->stepY) / 2) / r->rayDirY;

	// Evitar valores muy pequeños o negativos en perpWallDist
        if (r->perpWallDist <= 0.01)
            r->perpWallDist = 0.01;
}

void get_wall_height_in_window(t_raycast_vars *r)
{
	r->lineHeight = (int)(screenHeight / r->perpWallDist);
	if (r->lineHeight > screenHeight)
		r->lineHeight = screenHeight; // Limitar el tamaño máximo de la pared
}

void set_draw_start_and_end(t_raycast_vars *r)
{
	r->drawStart = -r->lineHeight / 2 + screenHeight / 2;
	if (r->drawStart < 0)
		r->drawStart = 0;
	r->drawEnd = r->lineHeight / 2 + screenHeight / 2;
	if (r->drawEnd >= screenHeight)
		r->drawEnd = screenHeight - 1;
}

void get_texture_coordinates(t_data *data, t_raycast_vars *r)
{
	if (r->side == 0)
		r->wallX = data->cub->y_pos_dec + r->perpWallDist * r->rayDirY;
	else
		r->wallX = data->cub->x_pos_dec + r->perpWallDist * r->rayDirX;
	r->wallX -= floor(r->wallX); // Asegurar que esté entre 0 y 1
}

void verify_wallX_zero_one(t_raycast_vars *r)
{
	if (r->wallX < 0 || r->wallX > 1)
	{
		printf("Warning: wallX fuera de rango. Valor actual: %f\n", r->wallX);
		r->wallX = fmod(r->wallX + 1, 1); // Normalizar wallX
	}
}

void texture_coordinates(t_raycast_vars *r)
{
	// Coordenadas de textura
	r->texX = (int)(r->wallX * (double)TEX_WIDTH);
	if (r->side == 0 && r->rayDirX > 0)
		r->texX = TEX_WIDTH - r->texX - 1;
	if (r->side == 1 && r->rayDirY < 0)
		r->texX = TEX_WIDTH - r->texX - 1;

	// Asegúrate de que texX esté dentro de los límites y luego imprímelo
	if (r->texX < 0)
		r->texX = 0;
	if (r->texX >= TEX_WIDTH)
		r->texX = TEX_WIDTH - 1;

    // Obtener la textura correspondiente a la pared golpeada
    r->texNum = (r->side == 0) ? ((r->rayDirX < 0) ? 2 : 3) : ((r->rayDirY < 0) ? 0 : 1); // 0: Norte, 1: Sur, 2: Oeste, 3: Este
}

void paint_wall_line (t_data *data, t_raycast_vars *r, int x)
{
    int y;
    unsigned int colour;
    
    y = r->drawStart;
    while (y < r->drawEnd)
    {
        r->d = y * 256 - screenHeight * 128 + r->lineHeight * 128; // 256 es una escala para evitar punto flotante
        r->texY = ((r->d * TEX_HEIGHT) / r->lineHeight) / 256; // Texto Y correspondiente
            
        // Limitar la altura de la textura
        if (r->texY < 0)
            r->texY = 0;
        if (r->texY >= TEX_HEIGHT)
            r->texY = TEX_HEIGHT - 1;
            
        // Obtener el color de la textura
        colour = get_texture_color(data, r->texNum, r->texX, r->texY); // Obtener el color de la textura
        my_mlx_pixel_put(data, x, y, colour);
        y++;
    }
}

/* raycast
*/
void raycast(t_data *data)
{
	t_raycast_vars	*r;
	int x;
	
    if (data->cub->map == NULL) {
        printf("Error: El mapa no está inicializado.\n");
        return;
    }

	r = malloc(sizeof(t_raycast_vars));
    x = 0; // Inicializar x para el bucle while
    while (x < screenWidth)
    {
        get_ray_dir(data, r, x); // Calcular la dirección del rayo
		set_initial_ray_pos(data, r); // Posición inicial del rayo en la cuadrícula del mapa
		calculate_delta_dist(r); // Calcular las distancias para la dirección del rayo
		define_ray_dir(data, r);
		dda(data, r);
		get_perp_wall_dist(data, r);
		get_wall_height_in_window(r);
		set_draw_start_and_end(r);
		get_texture_coordinates(data, r);
		verify_wallX_zero_one(r);
		texture_coordinates(r);
        paint_wall_line(data, r, x);
        x++;
    }
}
