/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:33:35 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/11 16:36:56 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define BUFFER_SIZE 1024

void allocate_initial_map(t_cub *cub)
{
    cub->map_height = 0;
    cub->map_width = 0; 
    cub->map = malloc(sizeof(char *) * 1);
    if (!cub->map)
        exit_with_error("Fallo en la asignación de memoria para el mapa");
}

void reallocate_map(t_cub *cub)
{
    char **new_map;
    int i;

    new_map = malloc(sizeof(char *) * (cub->map_height + 1));
    if (!new_map)
        exit_with_error("Fallo en la asignación de memoria para el mapa");
    i = 0;
    while (i < cub->map_height)
    {
        new_map[i] = cub->map[i];
        i++;
    }
    free(cub->map);
    cub->map = new_map;
}

void parse_map_line(t_cub *cub, char *line)
{
    char *trimmed_line = remove_spaces(line);
    int line_length = ft_strlen(trimmed_line);
    
    if (line_length > cub->map_width)
        cub->map_width = line_length;

    if (cub->map == NULL)
        allocate_initial_map(cub);
    else
        reallocate_map(cub);
    
    cub->map[cub->map_height] = ft_strdup(trimmed_line);
    if (!cub->map[cub->map_height])
        exit_with_error("Fallo en la asignación de memoria para la línea del mapa");

    cub->map_height++;
    free(trimmed_line);
}

void validate_player_position(t_cub *cub, int *player_count, int i, int j)
{
    if (*player_count == 0)
    {
        cub->posX = j + 0.5;
        cub->posY = i + 0.5;

        if (cub->map[i][j] == 'N')
        {
            cub->dirX = -1;
            cub->dirY = 0;
            cub->planeX = 0;
            cub->planeY = 0.66;
        }
        else if (cub->map[i][j] == 'S')
        {
            cub->dirX = 1;
            cub->dirY = 0;
            cub->planeX = 0;
            cub->planeY = -0.66;
        }
        else if (cub->map[i][j] == 'E')
        {
            cub->dirX = 0;
            cub->dirY = 1;
            cub->planeX = 0.66;
            cub->planeY = 0;
        }
        else if (cub->map[i][j] == 'W')
        {
            cub->dirX = 0;
            cub->dirY = -1;
            cub->planeX = -0.66;
            cub->planeY = 0;
        }
        (*player_count)++;
    }
}

void validate_map_walls(t_cub *cub)
{
    int i = 0;
    while (i < cub->map_height)
    {
        if (cub->map[i][0] != '1' || cub->map[i][ft_strlen(cub->map[i]) - 1] != '1')
            exit_with_error("Map must be surrounded by walls (1)");
        i++;
    }

    int j = 0;
    while (cub->map[0][j] != '\0')
    {
        if (cub->map[0][j] != '1' || cub->map[cub->map_height - 1][j] != '1')
            exit_with_error("Map must be surrounded by walls (1)");
        j++;
    }
}

void validate_map(t_cub *cub)
{
    int player_count = 0;
    int i = 0;

    while (i < cub->map_height)
    {
        int j = 0;
        while (cub->map[i][j] != '\0')
        {
            if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' || cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
                validate_player_position(cub, &player_count, i, j);
            else if (cub->map[i][j] != '1' && cub->map[i][j] != '0' && cub->map[i][j] != ' ')
                exit_with_error("Invalid character in map");
            j++;
        }
        i++;
    }
    
    if (player_count != 1)
        exit_with_error("There must be exactly one player start position (N, S, E, W)");

    validate_map_walls(cub);
}

void parse_texture(char *line, const char *letter, char **texture)
{
    if (*texture)
        exit_with_error("Textura duplicada");
    *texture = extract_path(line + ft_strlen(letter));
}

void parse_color_line(char *line, const char *prefix, int *color)
{
    if (*color != -1)
        exit_with_error("Color duplicado");
    *color = parse_color(line + ft_strlen(prefix));
}

void parse_line(t_cub *cub, char *line)
{
    line = trim_whitespace(line);

    if (ft_strncmp(line, "NO ", 3) == 0)
        parse_texture(line, "NO ", &cub->north_texture);
    else if (ft_strncmp(line, "SO ", 3) == 0)
        parse_texture(line, "SO ", &cub->south_texture);
    else if (ft_strncmp(line, "WE ", 3) == 0)
        parse_texture(line, "WE ", &cub->west_texture);
    else if (ft_strncmp(line, "EA ", 3) == 0)
        parse_texture(line, "EA ", &cub->east_texture);
    else if (ft_strncmp(line, "F ", 2) == 0)
        parse_color_line(line, "F ", &cub->floor_color);
    else if (ft_strncmp(line, "C ", 2) == 0)
        parse_color_line(line, "C ", &cub->ceiling_color);
    else if (line[0] == '1' || line[0] == ' ') 
        parse_map_line(cub, line);
    else if (*line != '\0')
        exit_with_error("Línea inválida en el archivo .cub");
}

void process_line(t_cub *cub, char *buffer, int start, int end)
{
    buffer[end] = '\0';
    char *line = trim_whitespace(&buffer[start]);
    if (*line != '\0')
        parse_line(cub, line);
}

void read_cub_file(t_cub *cub, const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit_with_error("Fallo al abrir el archivo .cub");

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    int line_start = 0;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        int i = 0;

        while (i < bytes_read)
        {
            if (buffer[i] == '\n')
            {
                process_line(cub, buffer, line_start, i);
                line_start = i + 1;
            }
            i++;
        }
        if (line_start < bytes_read)
            process_line(cub, buffer, line_start, bytes_read);
        
        line_start = 0;
    }

    if (bytes_read < 0)
        exit_with_error("Error al leer el archivo");

    close(fd);
    validate_map(cub);
}
