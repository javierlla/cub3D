/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_borders_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:32:36 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/13 19:54:23 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*replace_internal_spaces_with_ones(char *line)
{
	int	len;
	int	i;

	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if (line[i] == ' ')
			line[i] = '1';
		i++;
	}
	return (line);
}

void	fill_end_with_three(char **map, int map_height, int target_width)
{
	int		i;
	char	*new_line;
	int		line_length;

	i = 0;
	while (i < map_height)
	{
		line_length = ft_strlen(map[i]);
		if (line_length < target_width)
		{
			new_line = malloc(target_width + 1);
			if (!new_line)
				exit_with_error("padding error");
			ft_strcpy(new_line, map[i]);
			ft_memset(new_line + line_length, '3', target_width - line_length);
			new_line[target_width] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
}

void	validate_adjacent_to_3(t_data *data, int i, int j)
{
	if (i > 0 && data->cub->map[i - 1][j] != '1'
		&& data->cub->map[i - 1][j] != ' ' && data->cub->map[i - 1][j] != '3')
		exit_with_error("map must be surrounded by walls (1)");
	if (i < data->cub->map_height - 1 && data->cub->map[i + 1][j] != '1'
		&& data->cub->map[i + 1][j] != ' ' && data->cub->map[i + 1][j] != '3')
		exit_with_error("map must be surrounded by walls (1)");
	if (j > 0 && data->cub->map[i][j - 1] != '1'
		&& data->cub->map[i][j - 1] != ' ' && data->cub->map[i][j - 1] != '3')
		exit_with_error("map must be surrounded by walls (1)");
	if (j < data->cub->map_width - 1 && data->cub->map[i][j + 1] != '1'
		&& data->cub->map[i][j + 1] != ' ' && data->cub->map[i][j + 1] != '3')
		exit_with_error("map must be surrounded by walls (1)");
}

void	validate_horizontal_border(t_data *data, int row)
{
	int	j;

	j = 0;
	while (j < data->cub->map_width)
	{
		if (data->cub->map[row][j] != '1' && data->cub->map[row][j] != '3')
		{
			exit_with_error("Border must be surrounded by walls (1)");
		}
		j++;
	}
}

void	validate_vertical_border(t_data *data, int col)
{
	int		i;

	i = 0;
	while (i < data->cub->map_height)
	{
		if (data->cub->map[i][col] != '1' && data->cub->map[i][col] != '3')
		{
			exit_with_error("Border must be surrounded by walls (1)");
		}
		i++;
	}
}
