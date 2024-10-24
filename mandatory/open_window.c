/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:14:32 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/24 17:25:50 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_program(t_mlx *mlx)
{
	if (mlx && mlx->win_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->win_ptr = NULL;
	}
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		close_program(mlx);
	return (0);
}

void	init_window(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		exit_with_error("Failed to initialize mlx");
		free(mlx->mlx_ptr);
		free(mlx);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			screenWidth, screenHeight, "Cub3D");
	if (!mlx->win_ptr)
		exit_with_error("Failed to create window");
	mlx->img = mlx_new_image(mlx->mlx_ptr, screenWidth, screenHeight);
	if (!mlx->img)
		exit_with_error("Failed to create image.\n");
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		exit_with_error("Failed to get image address.\n");
	mlx_hook(mlx->win_ptr, 17, 0, (int (*)(void *))close_program, mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, handle_keypress, mlx);
}
