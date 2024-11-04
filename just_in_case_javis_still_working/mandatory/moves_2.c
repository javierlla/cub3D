/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:03:10 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 11:15:10 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->cub->x_pos_dec
		- data->cub->x_dir_dec * SPEED_MOVE * (-1);
	new_y = data->cub->y_pos_dec
		- data->cub->y_dir_dec * SPEED_MOVE * (-1);
	apply_move_and_render(data, new_x, new_y);
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->cub->x_pos_dec - data->cub->x_dir_dec * SPEED_MOVE;
	new_y = data->cub->y_pos_dec - data->cub->y_dir_dec * SPEED_MOVE;
	apply_move_and_render(data, new_x, new_y);
}

void	move_left(t_data *data)
{
	double	x_perp;
	double	y_perp;
	double	new_x;
	double	new_y;

	x_perp = data->cub->y_dir_dec;
	y_perp = -data->cub->x_dir_dec;
	new_x = data->cub->x_pos_dec + (x_perp * SPEED_MOVE);
	new_y = data->cub->y_pos_dec + (y_perp * SPEED_MOVE);
	apply_move_and_render(data, new_x, new_y);
}

void	move_right(t_data *data)
{
	double	x_perp;
	double	y_perp;
	double	new_x;
	double	new_y;

	x_perp = data->cub->y_dir_dec;
	y_perp = -data->cub->x_dir_dec;
	new_x = data->cub->x_pos_dec - (x_perp * SPEED_MOVE);
	new_y = data->cub->y_pos_dec - (y_perp * SPEED_MOVE);
	apply_move_and_render(data, new_x, new_y);
}
