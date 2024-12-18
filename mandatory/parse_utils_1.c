/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:44:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/07 20:26:05 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_with_error(const char *message)
{
	write(2, "Error\n", 6);
	write(2, message, strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

char	*trim_whitespace(char *str)
{
	char	*end;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	return (str);
}

char	*extract_path(char *line)
{
	char	*path;
	int		len;

	path = trim_whitespace(line);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		exit_with_error("Texture file must have a .xpm extension");
	}
	return (ft_strdup(path));
}

void	check_file_extension(const char *filename)
{
	const char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strcmp(ext, ".cub") != 0)
		exit_with_error("The map file must have a .cub extension");
}

char *replace_initial_and_final_spaces_with_three(char *line)
{
    int end;
    int len;
    int start;

    start = 0;
    len = ft_strlen(line);
    while (line[start] == ' ')
    {
        line[start] = '3';
        start++;
    }
    end = len - 1;
    while (end >= start && line[end] == ' ')
    {
        line[end] = '3';
        end--;
    }
    return (line);
}


char *replace_internal_spaces_with_ones(char *line)
{
    int len;
    int i;

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

void fill_end_with_three(char **map, int map_height, int target_width)
{
    int i = 0;
    while (i < map_height)
    {
        int line_length = ft_strlen(map[i]);
        if (line_length < target_width)
        {
            char *new_line = malloc(target_width + 1);
            if (!new_line)
                exit_with_error("Error de asignación de memoria al rellenar con '3'");
            ft_strcpy(new_line, map[i]);
            ft_memset(new_line + line_length, '3', target_width - line_length);
            new_line[target_width] = '\0';
            free(map[i]);
            map[i] = new_line;
        }
        i++;
    }
}

void validate_adjacent_to_3(t_data *data, int i, int j)
{
    char    valid_chars[] = {' ', '1', '3'};
    
    int adjacent[4][2] = {
        {i - 1, j},    // Arriba
        {i + 1, j},    // Abajo
        {i, j - 1},    // Izquierda
        {i, j + 1}     // Derecha
    };
    int k = 0;
    while (k < 4) {
        int x = adjacent[k][0];
        int y = adjacent[k][1];

        // Verificar que la posición esté dentro del límite del mapa
        if (x >= 0 && x < data->cub->map_height && y >= 0 && y < data->cub->map_width) {
            char adjacent_char = data->cub->map[x][y];
            int valid = 0;

            int v = 0;
            while (v < 3)
            {
                if (adjacent_char == valid_chars[v])
                {
                    valid = 1;
                    break;
                }
                v++;
            }
            if (!valid)
                exit_with_error("Map must be surrounded by walls (1).");
        }
        k++;
    }
}

void validate_map_borders(t_data *data)
{
    int j;
    int i;
    printf("Penultima fila del mapa antes de la validación: '%s'\n", data->cub->map[data->cub->map_height - 2]);
    printf("Última fila del mapa antes de la validación: '%s'\n", data->cub->map[data->cub->map_height - 1]);
    j = 0;
    while (j < data->cub->map_width) 
    {
        if (data->cub->map[0][j] != '1' && data->cub->map[0][j] != '3')
            exit_with_error("North border of map must be surrounded by walls (1)");
        if (data->cub->map[data->cub->map_height - 1][j] != '1' && data->cub->map[data->cub->map_height - 1][j] != '3')
            exit_with_error("South border of map must be surrounded by walls (1)");
        j++;
    }
    i = 0;
    while (i < data->cub->map_height)
    {
        if (data->cub->map[i][0] != '1' && data->cub->map[i][0] != '3')
            exit_with_error("Left boder of map must be surrounded by walls (1)");
        if (data->cub->map[i][data->cub->map_width - 1] != '1' && data->cub->map[i][data->cub->map_width - 1] != '3')
            exit_with_error("Right boder of map must be surrounded by walls (1)");
        i++;
    }
    i = 0;
    while (i < data->cub->map_height)
    {
        j = 0;
        while (j < data->cub->map_width)
        {
            if (data->cub->map[i][j] == '3')
                validate_adjacent_to_3(data, i, j);
            j++;
        }
        i++;
    }
}
