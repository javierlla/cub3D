/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/25 12:24:12 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initialize(t_data *data, t_mlx *mlx, t_cub *cub)
{
	data->mlx = mlx;
	data->cub = cub;
	data->cub->mlx = mlx;
	data->cub->x_pos_dec = -1;
	data->cub->y_pos_dec = -1;
	data->cub->floor_color = -1;
	data->cub->ceiling_color = -1;
}

/* main
*
*  1. read_cub_file: Open arg[1] file
*  2. print_cub_data: Prints read result: textures, colours and 
*     map in 'cub' structure.
*  3. init_all: Initialize all variables in data structure.
*  4. load_textures: Load all textures in 'cub' structure.
*  5. mlx_loop_hook: Render next frame.
*/
int	main(int argc, char **argv)
{
	t_data	*data;
	t_cub	*cub;
	t_mlx	*mlx;

	if (argc != 2)
	{
		write(2, "Usage: ./cub3D <map.cub>\n", 26);
		return (EXIT_FAILURE);
	}
	data = malloc(sizeof(t_data));
	cub = malloc(sizeof(t_cub));
	mlx = malloc(sizeof(t_mlx));
	ft_memset(cub, 0, sizeof(t_cub));
	ft_memset(mlx, 0, sizeof(t_mlx));
	initialize(data, mlx, cub);
	read_cub_file(data, argv[1]);
	init_all(data);
	load_textures(data);
	mlx_loop_hook(mlx->mlx_ptr, ((void *)render_next_frame(data)), cub);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
