/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:23:53 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/29 18:25:35 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	allocate_initial_map(t_data *data)
{
	data->cub->map_height = 0;
	data->cub->map_width = 0;
	data->cub->map = malloc(sizeof(char *) * 1);
	if (!data->cub->map)
		exit_with_error("Failure in memory allocation for the map line");
}

void	reallocate_map(t_data *data)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (data->cub->map_height + 1));
	if (!new_map)
		exit_with_error("Failure in memory allocation for the map line");
	i = 0;
	while (i < data->cub->map_height)
	{
		new_map[i] = data->cub->map[i];
		i++;
	}
	free(data->cub->map);
	data->cub->map = new_map;
}

void	parse_map_line(t_data *data, char *line)
{
	char	*trimmed_line;
	int		line_length;

	trimmed_line = remove_spaces(line);
	line_length = ft_strlen(trimmed_line);
	if (line_length > data->cub->map_width)
		data->cub->map_width = line_length;
	if (data->cub->map == NULL)
		allocate_initial_map(data);
	else
		reallocate_map(data);
	data->cub->map[data->cub->map_height] = ft_strdup(trimmed_line);
	if (!data->cub->map[data->cub->map_height])
		exit_with_error("Failure in memory allocation for the map line");
	data->cub->map_height++;
	free(trimmed_line);
}

void	validate_map_walls(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_height)
	{
		if (cub->map[i][0] != '1' ||
			cub->map[i][ft_strlen(cub->map[i]) - 1] != '1')
			exit_with_error("Map must be surrounded by walls (1)");
		i++;
	}
	j = 0;
	while (cub->map[0][j] != '\0')
	{
		if (cub->map[0][j] != '1' || cub->map[cub->map_height - 1][j] != '1')
			exit_with_error("Map must be surrounded by walls (1)");
		j++;
	}
}

void	validate_map(t_data *data)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (i < data->cub->map_height)
	{
		j = 0;
		while (data->cub->map[i][j] != '\0')
		{
			if (data->cub->map[i][j] == 'N' || data->cub->map[i][j] == 'S'
				|| data->cub->map[i][j] == 'E' || data->cub->map[i][j] == 'W')
				validate_player_position(data, &player_count, i, j);
			else if (data->cub->map[i][j] != '1' && data->cub->map[i][j] != '0'
					&& data->cub->map[i][j] != ' ')
				exit_with_error("Invalid character in map");
			j++;
		}
		i++;
	}
	if (player_count != 1)
		exit_with_error("There is more than one player");
	validate_map_walls(data->cub);
}
