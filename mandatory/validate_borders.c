/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_borders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:30:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/13 19:54:31 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	validate_north_and_south_borders(t_data *data)
{
	validate_horizontal_border(data, 0);
	validate_horizontal_border(data, data->cub->map_height - 1);
}

void	validate_west_and_east_borders(t_data *data)
{
	validate_vertical_border(data, 0);
	validate_vertical_border(data, data->cub->map_width - 1);
}

void	validate_all_map_borders(t_data *data)
{
	validate_north_and_south_borders(data);
	validate_west_and_east_borders(data);
}

void	validate_walls_around_3(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->cub->map_height)
	{
		j = 0;
		while (j < data->cub->map_width)
		{
			if (data->cub->map[i][j] == '3')
				validate_adjacent_to_3(data, i, j);
			j++;
		}
		i++;
	}
}

void	validate_map_borders(t_data *data)
{
	validate_all_map_borders(data);
	validate_walls_around_3(data);
}
