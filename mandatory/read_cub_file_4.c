/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:24:29 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/25 14:24:30 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_orientation_north(t_data *data)
{
	data->cub->x_dir_dec = 0;
	data->cub->y_dir_dec = -1;
	data->cub->planeX = 0;
	data->cub->planeY = 0.66;
}

void	set_orientation_south(t_data *data)
{
	data->cub->x_dir_dec = 0;
	data->cub->y_dir_dec = 1;
	data->cub->planeX = 0;
	data->cub->planeY = -0.66;
}

void	set_orientation_east(t_data *data)
{
	data->cub->x_dir_dec = 1;
	data->cub->y_dir_dec = 0;
	data->cub->planeX = 0.66;
	data->cub->planeY = 0;
	printf("\n\nx_dir_dec en E = %2f\n\n", data->cub->x_dir_dec);
}

void	set_orientation_west(t_data *data)
{
	data->cub->x_dir_dec = -1;
	data->cub->y_dir_dec = 0;
	data->cub->planeX = -0.66;
	data->cub->planeY = 0;
	printf("\n\nx_dir_dec en W = %2f\n\n", data->cub->x_dir_dec);
}

void	validate_player_position(t_data *data, int *player_count, int i, int j)
{
	char	orientation;

	orientation = data->cub->map[i][j];
	if (*player_count == 0)
	{
		data->cub->x_pos_dec = j + 0.5;
		data->cub->y_pos_dec = i + 0.5;
		if (orientation == 'N')
			set_orientation_north(data);
		else if (orientation == 'S')
			set_orientation_south(data);
		else if (orientation == 'E')
			set_orientation_east(data);
		else if (orientation == 'W')
			set_orientation_west(data);
		(*player_count)++;
	}
}
