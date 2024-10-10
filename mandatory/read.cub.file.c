/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.cub.file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:33:35 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/10 13:27:35 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define BUFFER_SIZE 1024

void parse_map_line(t_cub *cub, char *line)
{
    char *trimmed_line = remove_spaces(line);
    int line_length = ft_strlen(trimmed_line);
    
    // Actualiza el ancho del mapa
    if (line_length > cub->map_width)
        cub->map_width = line_length;
    // Asigna memoria para el mapa si es la primera línea
    if (cub->map == NULL)
    {
        cub->map_height = 0;
        cub->map_width = 0; 
        cub->map = malloc(sizeof(char *) * 1);
        if (!cub->map)
            exit_with_error("Fallo en la asignación de memoria para el mapa");
    } else {
        char **new_map = realloc(cub->map, sizeof(char *) * (cub->map_height + 1));
        if (!new_map)
            exit_with_error("Fallo en la asignación de memoria para el mapa");
        cub->map = new_map;
    }
    
    cub->map[cub->map_height] = ft_strdup(trimmed_line);
    if (!cub->map[cub->map_height])
        exit_with_error("Fallo en la asignación de memoria para la línea del mapa");
    cub->map_height++;
    free(trimmed_line);
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
            {
                if (player_count == 0) {
                    // Guardar la posición inicial del jugador
                    cub->posX = j + 0.5;  // Añadir 0.5 para posicionar en el centro del bloque
                    cub->posY = i + 0.5;

                    // Configurar la orientación del jugador
                    if (cub->map[i][j] == 'N') {
                        cub->dirX = -1;
                        cub->dirY = 0;
                        cub->planeX = 0;
                        cub->planeY = 0.66;
                    } else if (cub->map[i][j] == 'S') {
                        cub->dirX = 1;
                        cub->dirY = 0;
                        cub->planeX = 0;
                        cub->planeY = -0.66;
                    } else if (cub->map[i][j] == 'E') {
                        cub->dirX = 0;
                        cub->dirY = 1;
                        cub->planeX = 0.66;
                        cub->planeY = 0;
                    } else if (cub->map[i][j] == 'W') {
                        cub->dirX = 0;
                        cub->dirY = -1;
                        cub->planeX = -0.66;
                        cub->planeY = 0;
                    }
                    player_count++;
                }
            }
            else if (cub->map[i][j] != '1' && cub->map[i][j] != '0' && cub->map[i][j] != ' ')
                exit_with_error("Invalid character in map");
            j++;
        }
        i++;
    }
    if (player_count != 1)
        exit_with_error("There must be exactly one player start position (N, S, E, W)");
    
    i = 0;
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

void parse_line(t_cub *cub, char *line)
{
    line = trim_whitespace(line);

    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        if (cub->north_texture)
            exit_with_error("Textura del Norte duplicada");
        cub->north_texture = extract_path(line + 3);
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        if (cub->south_texture)
            exit_with_error("Textura del Sur duplicada");
        cub->south_texture = extract_path(line + 3);
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        if (cub->west_texture)
            exit_with_error("Textura del Oeste duplicada");
        cub->west_texture = extract_path(line + 3);
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        if (cub->east_texture)
            exit_with_error("Textura del Este duplicada");
        cub->east_texture = extract_path(line + 3);
    }
    else if (ft_strncmp(line, "F ", 2) == 0)
    {
        if (cub->floor_color != -1)
            exit_with_error("Color del suelo duplicado");
        cub->floor_color = parse_color(line + 2);
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        if (cub->ceiling_color != -1)
            exit_with_error("Color del techo duplicado");
        cub->ceiling_color = parse_color(line + 2);
    }
    else if (line[0] == '1' || line[0] == ' ') 
    {
        parse_map_line(cub, line);
    } 
    else if (*line != '\0')
    {
        exit_with_error("Línea inválida en el archivo .cub");
    }
}

void read_cub_file(t_cub *cub, const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit_with_error("Fallo al abrir el archivo .cub");

    char buffer[BUFFER_SIZE];
    char *line;
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
                buffer[i] = '\0';
                line = trim_whitespace(&buffer[line_start]);
                if (*line != '\0')
                    parse_line(cub, line);
                line_start = i + 1;
            }
            i++;
        }

        // Maneja la última línea
        if (line_start < bytes_read)
        {
            line = trim_whitespace(&buffer[line_start]);
            if (*line != '\0')
                parse_line(cub, line);
        }
        line_start = 0;
    }

    if (bytes_read < 0)
        exit_with_error("Error al leer el archivo");

    close(fd);
    validate_map(cub);
}
