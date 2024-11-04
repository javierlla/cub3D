/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:03:46 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 11:15:07 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall_collision(t_data *data, float tmp_x_2_check, float tmp_y_2_check)
{
	if (data->cub->map[(int)tmp_y_2_check][(int)tmp_x_2_check] == '1')
		return (1);
	return (0);
}

void	update_pixel_and_satellite_position(t_data *data)
{
	data->cub->x_pos_pixel = decimal_to_pixel(data, data->cub->x_pos_dec, X_PX);
	data->cub->y_pos_pixel = decimal_to_pixel(data, data->cub->y_pos_dec, Y_PX);
	data->cub->x_pos_ind = (int)data->cub->x_pos_dec;
	data->cub->y_pos_ind = (int)data->cub->y_pos_dec;
	data->cub->x_satellite_pixel = data->cub->x_pos_pixel
		+ (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
	data->cub->y_satellite_pixel = data->cub->y_pos_pixel
		+ (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;
}

bool	check_collision_and_limits(t_data *data, double new_x, double new_y)
{
	if (is_map_limit(data, new_x, new_y))
		return (true);
	if (is_wall_collision(data, new_x, new_y))
		return (true);
	return (false);
}

void	move_to_new_position(t_data *data, double new_x, double new_y)
{
	char	next_pos;

	next_pos = data->cub->map[(int)new_y][(int)new_x];
	if (next_pos == '0' || next_pos == ' ' || next_pos == 'N'
		|| next_pos == 'S' || next_pos == 'E' || next_pos == 'W')
	{
		data->cub->x_pos_dec = new_x;
		data->cub->y_pos_dec = new_y;
	}
}

void	apply_move_and_render(t_data *data, double new_x, double new_y)
{
	if (check_collision_and_limits(data, new_x, new_y))
		return ;
	move_to_new_position(data, new_x, new_y);
	update_pixel_and_satellite_position(data);
	render_next_frame(data);
}
