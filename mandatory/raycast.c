/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:14:15 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/25 12:39:00 by jllarena         ###   ########.fr       */
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
*     (result) ------------------ (whatever)
*
*  2) -1 to get inside [-1,1] range
*		Convertir (result) de [0-2] a [-1,1]
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
	r->cameraX = -normalize_minus_one_one(x);
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
*  3 ---|---|---|---|---|-  rayDirX = 1;  deltaDistX = 1 / rayDirX = 1 / 1 = 1
*  2 ---|---|---|---|---|-rayDirY = 6;  deltaDistY= 1 / rayDirY= 1 / 6= 0.166666
*  1 ---|---|---|---|---|-         
*  0   1   2   3   4   5
*
*
* R (3, 2) P is more vertical than horizontalR is more horizontal than vertical
*/
void	calculate_delta_dist(t_raycast_vars *r)
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

void	dda_step(t_data *data, t_raycast_vars *r, int *hit)
{
	if (r->sideDistX < r->sideDistY)
	{
		r->sideDistX += r->deltaDistX;
		r->mapX += r->stepX;
		r->side = 0;
	}
	else
	{
		r->sideDistY += r->deltaDistY;
		r->mapY += r->stepY;
		r->side = 1;
	}
	if (r->mapX < 0 || r->mapX >= data->cub->map_width
		|| r->mapY < 0 || r->mapY >= data->cub->map_height)
	{
		*hit = 1;
	}
	else if (data->cub->map[r->mapY][r->mapX] == '1')
	{
		*hit = 1;
	}
}

void	dda(t_data *data, t_raycast_vars *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		dda_step(data, r, &hit);
	}
}

void	get_perp_wall_dist(t_data *data, t_raycast_vars *r)
{
	if (r->side == 0)
		r->perpWallDist = (r->mapX - data->cub->x_pos_dec
				+ (1 - r->stepX) / 2) / r->rayDirX;
	else
		r->perpWallDist = (r->mapY - data->cub->y_pos_dec
				+ (1 - r->stepY) / 2) / r->rayDirY;
	if (r->perpWallDist <= 0.01)
		r->perpWallDist = 0.01;
}

void	get_wall_height_in_window(t_raycast_vars *r)
{
	r->lineHeight = (int)(screenHeight / r->perpWallDist);
	if (r->lineHeight > screenHeight)
		r->lineHeight = screenHeight;
}

void	set_draw_start_and_end(t_raycast_vars *r)
{
	r->drawStart = -r->lineHeight / 2 + screenHeight / 2;
	if (r->drawStart < 0)
		r->drawStart = 0;
	r->drawEnd = r->lineHeight / 2 + screenHeight / 2;
	if (r->drawEnd >= screenHeight)
		r->drawEnd = screenHeight - 1;
}

void	get_texture_coordinates(t_data *data, t_raycast_vars *r)
{
	if (r->side == 0)
		r->wallX = data->cub->y_pos_dec + r->perpWallDist * r->rayDirY;
	else
		r->wallX = data->cub->x_pos_dec + r->perpWallDist * r->rayDirX;
	r->wallX -= floor(r->wallX);
}

void	verify_wallx_zero_one(t_raycast_vars *r)
{
	if (r->wallX < 0 || r->wallX > 1)
	{
		printf("Warning: wallX fuera de rango. Valor actual: %f\n", r->wallX);
		r->wallX = fmod(r->wallX + 1, 1);
	}
}

void	texture_coordinates(t_raycast_vars *r)
{
	r->texX = (int)(r->wallX * (double)TEX_WIDTH);
	if (r->side == 0 && r->rayDirX > 0)
		r->texX = TEX_WIDTH - r->texX - 1;
	if (r->side == 1 && r->rayDirY < 0)
		r->texX = TEX_WIDTH - r->texX - 1;
	if (r->texX < 0)
		r->texX = 0;
	if (r->texX >= TEX_WIDTH)
		r->texX = TEX_WIDTH - 1;
	if (r->side == 0)
	{
		if (r->rayDirX < 0)
			r->texNum = 2;
		else
			r->texNum = 3;
	}
	else
	{
		if (r->rayDirY < 0)
			r->texNum = 0;
		else
			r->texNum = 1;
	}
}

void	paint_wall_line(t_data *data, t_raycast_vars *r, int x)
{
	int				y;
	unsigned int	colour;

	y = r->drawStart;
	while (y < r->drawEnd)
	{
		r->d = y * 256 - screenHeight * 128 + r->lineHeight * 128;
		r->texY = ((r->d * TEX_HEIGHT) / r->lineHeight) / 256;
		if (r->texY < 0)
			r->texY = 0;
		if (r->texY >= TEX_HEIGHT)
			r->texY = TEX_HEIGHT - 1;
		colour = get_texture_color(data, r->texNum, r->texX, r->texY);
		my_mlx_pixel_put(data, x, y, colour);
		y++;
	}
}

void	raycast_column(t_data *data, t_raycast_vars *r, int x)
{
	get_ray_dir(data, r, x);
	set_initial_ray_pos(data, r);
	calculate_delta_dist(r);
	define_ray_dir(data, r);
	dda(data, r);
	get_perp_wall_dist(data, r);
	get_wall_height_in_window(r);
	set_draw_start_and_end(r);
	get_texture_coordinates(data, r);
	verify_wallx_zero_one(r);
	texture_coordinates(r);
	paint_wall_line(data, r, x);
}

void	raycast(t_data *data)
{
	t_raycast_vars	*r;
	int				x;

	if (data->cub->map == NULL)
	{
		printf("Error: El mapa no está inicializado.\n");
		return ;
	}
	r = malloc(sizeof(t_raycast_vars));
	if (r == NULL)
	{
		printf("Error: Memoria no asignada para raycasting.\n");
		return ;
	}
	x = 0;
	while (x < screenWidth)
	{
		raycast_column(data, r, x);
		x++;
	}
	free(r);
}
