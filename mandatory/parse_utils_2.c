/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:05 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/01 18:18:48 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_commas(const char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == ',')
			count++;
		line++;
	}
	return (count);
}

int	parse_color(char *line)
{
	int	r;
	int	g;
	int	b;

	// printf(MAGENTA"we're in parse_color, line = %s\n"RESET_COLOUR, line);
	if (count_commas(line) != 2)
		exit_with_error("Color should be in format R,G,B");
	r = ft_atoi(line);
	// printf("r = %d\n", r);
	line = ft_strchr(line, ',') + 1;
	g = ft_atoi(line);
	// printf("g = %d\n", g);
	line = ft_strchr(line, ',') + 1;
	b = ft_atoi(line);
	// printf("b = %d\n", b);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_with_error("Color values must be in the range [0, 255]");
	return ((r << 16) | (g << 8) | b);
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
