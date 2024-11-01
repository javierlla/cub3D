/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:23:53 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/01 14:26:30 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void allocate_initial_map(t_data *data)
{
    data->cub->map_height = 0;
    data->cub->map_width = 0;
    data->cub->map = malloc(sizeof(char *) * 1);
    if (!data->cub->map)
        exit_with_error("Failure in memory allocation for the map line");
}

void reallocate_map(t_data *data)
{
    char **new_map = malloc(sizeof(char *) * (data->cub->map_height + 1));
    if (!new_map)
        exit_with_error("Failure in memory allocation for the map line");
    
    int i = 0;
    while (i < data->cub->map_height)
	{
        new_map[i] = data->cub->map[i];
        i++;
    }
    free(data->cub->map);
    data->cub->map = new_map;
}

void parse_map_line(t_data *data, char *line)
{
    int line_length = strlen(line);
    printf("Processing line: '%s' (length: %d)\n", line, line_length);
    if (line_length > data->cub->map_width)
        data->cub->map_width = line_length;
    if (data->cub->map == NULL)
        allocate_initial_map(data);
	else
        reallocate_map(data);
    data->cub->map[data->cub->map_height] = strdup(line);
    if (!data->cub->map[data->cub->map_height])
        exit_with_error("Error de asignación de memoria en strdup");
    data->cub->map_height++;
}

void validate_map_walls(t_cub *cub)
{
    int j = 0;

    while (j < cub->map_width)
	{
        if (cub->map[0][j] != '1')
            exit_with_error("El borde superior debe estar rodeado por paredes (1).");
        j++;
    }
    j = 0; 
    while (j < cub->map_width)
	{
        if (cub->map[cub->map_height - 1][j] != '1')
            exit_with_error("El borde inferior debe estar rodeado por paredes (1).");
        j++;
    }

    int i = 0;
    while (i < cub->map_height)
	{
        if (cub->map[i][0] != '1' || cub->map[i][cub->map_width - 1] != '1') {
            exit_with_error("Todos los bordes deben estar rodeados por paredes (1).");
        }
        i++;
    }
}

void validate_map(t_data *data)
{
    int player_count = 0;
    int i = 0;

    while (i < data->cub->map_height) {
        printf("Processing line %d: %s\n", i, data->cub->map[i]);
        int j = 0;
        while (j < data->cub->map_width) {
            char current_char = data->cub->map[i][j];
            if (current_char == '\0')
                break ;
            if (current_char == 'N' || current_char == 'S' ||
                current_char == 'E' || current_char == 'W')
				{
                validate_player_position(data, &player_count, i, j);
            	} 
			else if (current_char != '1' && current_char != '0' && current_char != ' ') {
                printf("Invalid character '%c' found at line %d, column %d\n", current_char, i, j);
                exit_with_error("Invalid character in map");
            }
            j++;
        }
        i++;
    }
    printf("Altura del mapa: %d, Ancho del mapa: %d\n", data->cub->map_height, data->cub->map_width);
    if (player_count != 1) {
        exit_with_error("There is more than one player");
    }
    validate_map_walls(data->cub);
}
