/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:40:50 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/28 20:02:56 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_direction_vector(t_data *data, int direction)
{
	if (direction == ROTATE_RIGHT)
	{
		data->cub->angle_degree += SPEED_ROTATE;
	}
	else if (direction == ROTATE_LEFT)
	{
		data->cub->angle_degree -= SPEED_ROTATE;
	}
	data->cub->angle_degree = fmod(data->cub->angle_degree + 360, 360);
	angle_to_rad(data);
	data->cub->x_dir_dec = cos(data->cub->angle_radian);
	data->cub->y_dir_dec = sin(data->cub->angle_radian);
}

void	rotate_right(t_data *data)
{
	update_direction_vector(data, ROTATE_RIGHT);
	data->cub->x_satellite_pixel = data->cub->x_pos_pixel
		+ (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
	data->cub->y_satellite_pixel = data->cub->y_pos_pixel
		+ (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;
	render_next_frame(data);
}

void	rotate_left(t_data *data)
{
	update_direction_vector(data, ROTATE_LEFT);
	data->cub->x_satellite_pixel = data->cub->x_pos_pixel
		+ (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
	data->cub->y_satellite_pixel = data->cub->y_pos_pixel
		+ (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;
	render_next_frame(data);
}

int	key_handler(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_program(data);
	if (keycode == W_MOVE_FORWARD)
		move_forward(data);
	if (keycode == S_MOVE_BACKWARDS)
		move_backward(data);
	if (keycode == A_MOVE_LEFT)
		move_left(data);
	if (keycode == D_MOVE_RIGHT)
		move_right(data);
	if (keycode == ROTATE_LEFT)
		rotate_right(data);
	if (keycode == ROTATE_RIGHT)
		rotate_left(data);
	return (0);
}

void	ft_events_init(t_data *data)
{
	mlx_hook(data->mlx->win_ptr, 17, (1L << 17),
		&close_program, data);
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, key_handler, data);
}
