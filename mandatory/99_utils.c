/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:17:09 by uxmancis          #+#    #+#             */
/*   Updated: 2024/11/15 17:19:26 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < SCREENWIDTH && y >= 0 && y < SCREENHEIGHT)
	{
		dst = data->mlx->addr + (y * data->mlx->line_length
				+ x * (data->mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	free_resources_3(t_data *data)
{
	free(data->cub->file);
	free(data->cub->file_lines_type);
	free(data->cub->south_texture);
	free(data->cub->north_texture);
	free(data->cub->west_texture);
	free(data->cub->east_texture);
	free(data->cub->map);
	free(data->cub);
	mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img);
	free(data->mlx->mlx_ptr);
	free(data->mlx->win_ptr);
	free(data->mlx);
	free(data);
}

void	free_resources_2(t_data *data)
{
	int	tmp;
	int	index;

	tmp = data->cub->map_height;
	index = 0;
	while (tmp > 0)
	{
		free(data->cub->map[index]);
		tmp--;
		index++;
	}
	tmp = data->cub->nb_lines_file;
	index = 0;
	while (tmp > 0)
	{
		free(data->cub->file[index]);
		tmp--;
		index++;
	}
	free_resources_3(data);
}

void	free_resources(t_data *data)
{
	int	i;

	if (data)
	{
		i = 0;
		while (i < 4)
		{
			if (data->cub->textures[i])
			{
				mlx_destroy_image(data->mlx->mlx_ptr, data->cub->textures[i]);
				data->cub->textures[i] = NULL;
			}
			i++;
		}
		free(data->cub->textures);
		free(data->cub->textures_data);
		free_resources_2(data);
	}
}
