/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_read_cub_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:33:35 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/24 19:37:37 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define BUFFER_SIZE 1024

void	allocate_initial_map(t_data *data)
{
	data->cub->map_height = 0;
	data->cub->map_width = 0;
	data->cub->map = malloc(sizeof(char *) * 1);
	if (!data->cub->map)
		exit_with_error("Fallo en la asignación de memoria para el mapa");
}

void	reallocate_map(t_data *data)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (data->cub->map_height + 1));
	if (!new_map)
		exit_with_error("Fallo en la asignación de memoria para el mapa");
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
		exit_with_error("failure in memory allocation for the map line");
	data->cub->map_height++;
	free(trimmed_line);
}

/*
*                  1
*   (0,0)          N
*                  |
*                  |
*                  |
*                  |
*  -1 W __________________________ E   1
*                  |
*                  |
*                  |
*                  |
*                  |
*                  S
*                 -1
*
*/

void	set_orientation_north(t_data *data)
{
	data->cub->x_dir_dec = 0;
	data->cub->y_dir_dec = -1;
	data->cub->planeX = 0.66;
	data->cub->planeY = 0;
}

void	set_orientation_south(t_data *data)
{
	data->cub->x_dir_dec = 0;
	data->cub->y_dir_dec = 1;
	data->cub->planeX = -0.66;
	data->cub->planeY = 0;
}

void	set_orientation_east(t_data *data)
{
	data->cub->x_dir_dec = 1;
	data->cub->y_dir_dec = 0;
	data->cub->planeX = 0;
	data->cub->planeY = 0.66;
	printf("\n\nx_dir_dec en E = %2f\n\n", data->cub->x_dir_dec);
}

void	set_orientation_west(t_data *data)
{
	data->cub->x_dir_dec = -1;
	data->cub->y_dir_dec = 0;
	data->cub->planeX = 0;
	data->cub->planeY = -0.66;
	printf("\n\nx_dir_dec en W = %2f\n\n", data->cub->x_dir_dec);
}

void	validate_player_position(t_data *data, int *player_count, int i, int j)
{
	char	orientation;

	orientation = data->cub->map[i][j];
	if (*player_count == 0)
	{
		data->cub->x_pos_dec = j + 0.5;
		data->cub->y_pos_dec = i + 0.5;
		if (orientation == 'N')
			set_orientation_north(data);
		else if (orientation == 'S')
			set_orientation_south(data);
		else if (orientation == 'E')
			set_orientation_east(data);
		else if (orientation == 'W')
			set_orientation_west(data);
		(*player_count)++;
	}
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

void	parse_texture(char *line,
	const char *letter, char **texture)
{
	if (*texture)
		exit_with_error(ft_strjoin("Textura duplicada: ", letter));
	*texture = extract_path(line + ft_strlen(letter));
}

void	parse_color_line(char *line, const char *prefix, int *color)
{
	if (*color != -1)
		exit_with_error("Color duplicado");
	*color = parse_color(line + ft_strlen(prefix));
}

void	parse_line(t_data *data, char *line)
{
	line = trim_whitespace(line);
	printf("Procesando línea: '%s'\n", line);  // Depuració
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(line, "NO ", &data->cub->north_texture);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(line, "SO ", &data->cub->south_texture);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(line, "WE ", &data->cub->west_texture);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(line, "EA ", &data->cub->east_texture);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color_line(line, "F ", &data->cub->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color_line(line, "C ", &data->cub->ceiling_color);
	else if (line[0] == '1' || line[0] == ' ')
		parse_map_line(data, line);
	else if (*line != '\0')
		exit_with_error("Línea inválida en el archivo .cub");
}

void	process_line(t_data *data, char *buffer, int start, int end)
{
	char	*line;

	buffer[end] = '\0';
	line = trim_whitespace(&buffer[start]);
	if (*line != '\0')
		parse_line(data, line);
}

int	open_and_validate_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("Fallo al abrir el archivo .cub");
	return (fd);
}

void	process_buffer(t_data *data, char *buffer,
	ssize_t bytes_read, int *line_start)
{
	int	i;

	i = 0;
	while (i < bytes_read)
	{
		if (buffer[i] == '\n')
		{
			process_line(data, buffer, *line_start, i);
			*line_start = i + 1;
		}
		i++;
	}
	if (*line_start < bytes_read)
		process_line(data, buffer, *line_start, bytes_read);
	*line_start = 0;
}

void	read_and_process_file(t_data *data, int fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		line_start;

	line_start = 0;
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		process_buffer(data, buffer, bytes_read, &line_start);
	}
	if (bytes_read < 0)
		exit_with_error("Error al leer el archivo");
}

void	close_and_validate(int fd, t_data *data)
{
	close(fd);
	validate_map(data);
}

void	read_cub_file(t_data *data, const char *filename)
{
	int	fd;

	fd = open_and_validate_file(filename);
	read_and_process_file(data, fd);
	close_and_validate(fd, data);
}
