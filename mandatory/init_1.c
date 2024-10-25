/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:43:44 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/25 14:42:49 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	init_window(data);
	ft_events_init(data);
}
