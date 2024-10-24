/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:43:44 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/24 17:21:42 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*  Index-decimal range: both x and y [0-21]
*   Pixel range: both x and y [0-840], defined in .h
*
*   21.00 ---------------- 840
*   (whatever) ----------- result
*
*   Total nb of vertical boxes (width) ---------- WIDTH_MAP px
*   1 box ------------------------------ decimal px (position
*                              in 2d map, based on map indexes,
*                              but decimal format, +0.5).
*
*
*	Returns -1 = Error, not expected result
*/
int	decimal_to_pixel(t_data *data, float decimal,
	enum width_or_height indicator)
{
	int	height_column;
	int	width_row;

	if (indicator == X_PX)
	{
		width_row = data->cub->map_width;
		return (decimal * WIDTH_MAP / width_row);
	}
	else if (indicator == Y_PX)
	{
		height_column = data->cub->map_height;
		return (decimal * HEIGHT_MAP / height_column);
	}
	else
		return (-1);
}

/* set_initial_pixel_in_window
*
*     MAPMAPM**********
*     APMAPMA**********
*     PMAPMAP**********
*     *****************
*     *****************
*     *****************
*     *****************
*     *****************
*
*     MAP starts in (1720, 600) in whole window
*
*     That's why we need to sum 1720 and 600 to the pixel position
*     in order to get the pixel position in the whole window.
*/
void	set_initial_pixel_in_window(t_data *data)
{
	data->cub->x_pos_pixel = decimal_to_pixel(data, data->cub->x_pos_dec, X_PX);
	data->cub->y_pos_pixel = decimal_to_pixel(data, data->cub->y_pos_dec, Y_PX);
}

void	set_initial_decimal_in_2d_map(t_cub *cub,
	int x_map_index, int y_map_index)
{
	cub->x_pos_dec = (float)x_map_index + 0.5;
	cub->y_pos_dec = (float)y_map_index + 0.5;
}

void	set_initial_player_direction(t_cub *cub,
	int x_map_index, int y_map_index)
{
	cub->direction = cub->map[y_map_index][x_map_index];
}

void	set_initial_index_in_2d_map(t_cub *cub,
	int x_map_index, int y_map_index)
{
	cub->x_pos_ind = x_map_index;
	cub->y_pos_ind = y_map_index;
}

void	set_player_position_2(t_data *data, int x_map_index, int y_map_index)
{
	set_initial_index_in_2d_map(data->cub, x_map_index, y_map_index);
	set_initial_player_direction(data->cub, x_map_index, y_map_index);
	set_initial_decimal_in_2d_map(data->cub, x_map_index, y_map_index);
	set_initial_pixel_in_window(data);
}

/*  Checks whether if x-y passed coordinate in map indicates
*   player's position or not.
*
*   Player's position is indicated with 'N', 'S', 'W', 'E'.
*/
int	is_player_position(t_cub *cub, int x, int y)
{
	if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
		|| cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
	{
		return (1);
	}
	return (0);
}

/* Checks whether if x-y passed as parameter
*  are part of map.
*----------------------------------------------------------*/
int	is_map(t_cub *cub, int x, int y)
{
	if (cub->map[y][x] == '1' || cub->map[y][x] == '0'
		|| cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
		|| cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
		return (1);
	return (0);
}

void	set_player_position(t_data *data)
{
	int	x_map_index;
	int	y_map_index;

	y_map_index = 0;
	while (y_map_index < data->cub->map_height)
	{
		x_map_index = 0;
		while (is_map(data->cub, x_map_index, y_map_index))
		{
			if (is_player_position(data->cub, x_map_index, y_map_index))
			{
				set_player_position_2(data, x_map_index, y_map_index);
				break ;
			}
			x_map_index++;
		}
		y_map_index++;
	}
}

void	init_all_default(t_data *data)
{
	data->cub->x_pos_ind = 0;
	data->cub->y_pos_ind = 0;
	data->cub->direction = 'X';
	data->cub->angle_degree = 0;
	data->cub->angle_radian = 0;
	data->cub->x_satellite_pixel = 0;
	data->cub->y_satellite_pixel = 0;
}

/*
*   360 degrees    ------------------  2 * π radians
*   angle degree   ------------------  result radians
*/
float	deg_to_rad(t_data *data)
{
	data->cub->angle_radian = data->cub->angle_degree * (PI / 180);
	return (data->cub->angle_radian);
}

/* We first set it in DEGREES */
void	get_initial_angle(t_data *data)
{
	if (data->cub->direction == 'N')
		data->cub->angle_degree = 270;
	if (data->cub->direction == 'S')
		data->cub->angle_degree = 90;
	if (data->cub->direction == 'W')
		data->cub->angle_degree = 180;
	if (data->cub->direction == 'E')
		data->cub->angle_degree = 0;
}

void	angle_to_rad(t_data *data)
{
	float	angle_radian;

	angle_radian = deg_to_rad(data);
	if (angle_radian < 0)
		angle_radian += 2 * PI;
	else if (angle_radian >= 2 * PI)
		angle_radian -= 2 * PI;
	data->cub->x_dir_dec = cos(angle_radian);
	data->cub->y_dir_dec = sin(angle_radian);
	data->cub->planeX = 0.66 * sin(angle_radian);
	data->cub->planeY = 0.66 * -cos(angle_radian);
}

/*void angle_to_rad(t_data *data)
{
    data->cub->x_dir_dec = cos(deg_to_rad(data));
    data->cub->y_dir_dec = sin(deg_to_rad(data));
}*/
void	set_player_direction_vector(t_data *data)
{
	get_initial_angle(data);
	angle_to_rad(data);
}

void	set_initial_satellite_pixel_in_window(t_data *data)
{
	data->cub->x_satellite_pixel = data->cub->x_pos_pixel
		+ (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
	data->cub->y_satellite_pixel = data->cub->y_pos_pixel
		+ (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;
}

void	init_all(t_data *data)
{
	init_all_default(data);
	set_player_position(data);
	set_player_direction_vector(data);
	set_initial_satellite_pixel_in_window(data);
	init_window(data->mlx);
	ft_events_init(data);
}
