/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:33:59 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 12:59:55 by jllarena         ###   ########.fr       */
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
	enum e_width_or_height indicator)
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
	data->cub->plane_x = 0.66 * sin(angle_radian);
	data->cub->plane_y = 0.66 * -cos(angle_radian);
}
