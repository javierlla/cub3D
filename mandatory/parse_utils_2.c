/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:05 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 14:02:27 by jllarena         ###   ########.fr       */
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

	if (count_commas(line) != 2)
		exit_with_error("Color should be in format R,G,B");
	r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	b = ft_atoi(line);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_with_error("Color values must be in the range [0, 255]");
	return ((r << 16) | (g << 8) | b);
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
		free(data->cub);
		free(data->mlx);
		free(data);
	}
}

