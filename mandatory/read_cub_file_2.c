/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:23:53 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/07 20:23:34 by uxmancis         ###   ########.fr       */
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
	int		i;
	char	**new_map;

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
	int	line_length;

	line_length = strlen(line);
	if (line_length > data->cub->map_width)
		data->cub->map_width = line_length;
	if (data->cub->map == NULL)
		allocate_initial_map(data);
	else
		reallocate_map(data);
	line = replace_initial_and_final_spaces_with_three(line);
	line = replace_internal_spaces_with_ones(line);
	data->cub->map[data->cub->map_height] = ft_strdup(line);
	if (!data->cub->map[data->cub->map_height])
		exit_with_error("Error de asignación de memoria en strdup");
	data->cub->map_height++;
}

void	validate_map_characters(t_data *data, int *player_count)
{
	int		i;
	int		j;
	char	current_char;

	i = 0;
	while (i < data->cub->map_height)
	{
		// printf("Processing line %d: %s\n", i, data->cub->map[i]);
		// printf("Processed line: '%s|' (length: %d)\n", data->cub->map[i], (int)strlen(data->cub->map[i]));
		j = 0;
		while (j < data->cub->map_width)
		{
			current_char = data->cub->map[i][j];
			if (current_char == '\0')
				break ;
			if (current_char == 'N' || current_char == 'S'
				|| current_char == 'E' || current_char == 'W')
				validate_player_position(data, player_count, i, j);
			else if (current_char != '1' && current_char != '0'
				&& current_char != ' ' && current_char != '3')
				exit_with_error("Invalid character in map");
			j++;
		}
		i++;
	}
}

void	finalize_map_validation(t_data *data, int player_count)
{
	int	i;

	if (player_count != 1)
		exit_with_error("There must be one and only one player.");
	fill_end_with_three(data->cub->map, data->cub->map_height, data->cub->map_width);
	printf("Mapa después de añadir los '3':\n");
	i = 0;
	while (i < data->cub->map_height)
	{
		printf("%s\n", data->cub->map[i]);
		i++;
	}
	validate_map_borders(data);
}

void	validate_map(t_data *data)
{
    int	player_count;

	player_count = 0;
	validate_map_characters(data, &player_count);
	finalize_map_validation(data, player_count);
}
