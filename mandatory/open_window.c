/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:14:32 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 20:04:04 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_program(t_data *data)
{
	if (data != NULL && data->mlx != NULL && data->mlx->win_ptr != NULL)
	{
		mlx_destroy_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
		data->mlx->win_ptr = NULL;
	}
	free_resources(data);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_program(data);
	return (0);
}

void	init_window(t_data *data)
{
	data->mlx->mlx_ptr = mlx_init();
	if (!data->mlx->mlx_ptr)
	{
		exit_with_error("Failed to initialize mlx");
		free(data->mlx->mlx_ptr);
		free(data->mlx);
	}
	data->mlx->win_ptr = mlx_new_window(data->mlx->mlx_ptr,
			SCREENWIDTH, SCREENHEIGHT, "Cub3D");
	if (!data->mlx->win_ptr)
		exit_with_error("Failed to create window");
	data->mlx->img = mlx_new_image(data->mlx->mlx_ptr,
			SCREENWIDTH, SCREENHEIGHT);
	if (!data->mlx->img)
		exit_with_error("Failed to create image.\n");
	data->mlx->addr = mlx_get_data_addr(data->mlx->img,
			&data->mlx->bits_per_pixel,
			&data->mlx->line_length, &data->mlx->endian);
	if (!data->mlx->addr)
		exit_with_error("Failed to get image address.\n");
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, handle_keypress, data);
}
