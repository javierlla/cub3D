/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:34:22 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/25 14:48:09 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
