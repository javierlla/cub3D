/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:40:50 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/22 18:04:25 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	pixel_to_decimal_map(int pixel, enum width_or_height indicator)
{
	if (indicator == X_WIDTH)
		return ((float)pixel * 21.00 / WIDTH_MAP);
	else if (indicator == Y_HEIGHT)
		return ((float)pixel * 21.00 / HEIGHT_MAP);
	else
		return (-1);
}

int	is_map_limit(t_data *data, float tmp_x_2_check, float tmp_y_2_check)
{
	if (tmp_x_2_check < 0 || tmp_x_2_check > data->cub->map_width || tmp_y_2_check < 0 || tmp_y_2_check > data->cub->map_height)
		return (1);
	return (0);
}

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
	data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
	data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;
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
	if (next_pos == '0' || next_pos == ' ' || next_pos == 'N' || next_pos == 'S' || next_pos == 'E' || next_pos == 'W')
	{
		data->cub->x_pos_dec = new_x;
		data->cub->y_pos_dec = new_y;
	}
}

void	apply_move_and_render(t_data *data, double new_x, double new_y)
{
	if (check_collision_and_limits(data, new_x, new_y))
		return;
	move_to_new_position(data, new_x, new_y);
	update_pixel_and_satellite_position(data);
	render_next_frame(data);
}

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->cub->x_pos_dec - data->cub->x_dir_dec * SPEED_MOVE * (-1);
	new_y = data->cub->y_pos_dec - data->cub->y_dir_dec * SPEED_MOVE * (-1);
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

void	move_right(t_data *data)
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

void	move_left(t_data *data)
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
	data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
	data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;
	render_next_frame(data);
}

void	rotate_left(t_data *data)
{
	update_direction_vector(data, ROTATE_LEFT);
	data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
	data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;
	render_next_frame(data);
}

int	key_handler(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_program(data->mlx); // should close_program not only destroy window, but also free memory?? destroy image??
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
	mlx_hook(data->mlx->win_ptr, 17, 0, (int (*)(void *))close_program, data->mlx);
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, key_handler, data);
}
