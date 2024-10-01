/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_read_cub_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:33:35 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/01 12:31:58 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define BUFFER_SIZE 1024

void exit_with_error(const char *message)
{
    write(2, "Error\n", 6);
    write(2, message, strlen(message));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}

int parse_color(char *line) 
{
    int r, g, b;

    r = ft_atoi(line);
    line = ft_strchr(line, ',') + 1;
    g = ft_atoi(line);
    line = ft_strchr(line, ',') + 1;
    b = ft_atoi(line);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        exit_with_error("Color values must be in the range [0, 255]");
        
    return ((r << 16) | (g << 8) | b);
}

char *trim_whitespace(char *str)
{
    while (*str == ' ' || *str == '\t')
        str++;
    return (str);
}

char *extract_path(char *line)
{
    line = trim_whitespace(line);
    int len = ft_strlen(line);
    char *path = (char *)malloc(len + 1);
    if (!path)
        exit_with_error("Memory allocation failed");
    ft_strcpy(path, line);
    return path;
}

//incrementamos la altura del mapa por cada nueva linea
void parse_map_line(t_cub *cub, char *line)
{
	char	**new_map;
	int		i;

    if(cub->map == NULL)
    {
        cub->map_height = 0;
        cub->map = (char **)malloc(sizeof(char *) * (/*cub->map_height*/+ 1));
        if (!cub->map)
            exit_with_error("Memory allocation failed");
    }
    else
    {
        new_map = (char **)malloc(sizeof(char *) * (cub->map_height + 1));
        if(!new_map)
            exit_with_error("Memory allocation failed");
		i = 0;
        while (i < cub->map_height)
		{
            new_map[i] = cub->map[i];
			i++;
		}
        free(cub->map);
        cub->map = new_map;
    }
    cub->map[cub->map_height] = ft_strdup(line);
    if(!cub->map[cub->map_height])
        exit_with_error("Memory allocation failed");
    cub->map_height++;
}


//valido que solo haya un jugador, que no haya caracter invalidos y que los bordes sean 1
//hay que hacer más pruebas
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
                player_count++;
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

/*
*   1) Gets texture and colours' paths:
*           > Textures: North-South-West-East
*           > Colours: Floor-Ceiling
*
*   2) 
*/
void parse_line(t_cub *cub, char *line)
{
    line = trim_whitespace(line);

    if (ft_strncmp(line, "NO ", 3) == 0)
        cub->north_texture = extract_path(line + 3);
    else if (ft_strncmp(line, "SO ", 3) == 0)
        cub->south_texture = extract_path(line + 3);
    else if (ft_strncmp(line, "WE ", 3) == 0)
        cub->west_texture = extract_path(line + 3);
    else if (ft_strncmp(line, "EA ", 3) == 0)
        cub->east_texture = extract_path(line + 3);
    else if (ft_strncmp(line, "F ", 2) == 0)
        cub->floor_color = parse_color(line + 2);
    else if (ft_strncmp(line, "C ", 2) == 0)
        cub->ceiling_color = parse_color(line + 2);
    else if (line[0] == '1' || line[0] == ' ') 
    {
        parse_map_line(cub, line);
    } 
    else if (*line != '\0')
    {
        exit_with_error("Invalid line in .cub file");
    }
}
/*me fala gestionar que argv[1] = mapname.cub
gestionar que haya mapa, texturas y colores.
buscar mas errores de mapas no gestionados
*/
void read_cub_file(t_cub *cub, const char *filename)
{
	
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit_with_error("Failed to open .cub");

    char buffer[BUFFER_SIZE];
    char *line;
    ssize_t bytes_read;
    int i = 0;
    int line_start = 0;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
        buffer[bytes_read] = '\0';

        i = 0;
        while (i < bytes_read)
        {
            if (buffer[i] == '\n' || buffer[i] == '\0')
			{
                buffer[i] = '\0';
                line = trim_whitespace(&buffer[line_start]);
                if (*line != '\0')
                    parse_line(cub, line); //
                line_start = i + 1;
            }
            i++;
        }
    }
    if (bytes_read < 0)
        exit_with_error("Error reading file");
    close(fd);
    validate_map(cub);
}

//funcion chatgpt para comprobar el parseo
void print_cub_data(t_cub *cub)
{
    printf("North Texture: %s\n", cub->north_texture ? cub->north_texture : "Not Set");
    printf("South Texture: %s\n", cub->south_texture ? cub->south_texture : "Not Set");
    printf("West Texture: %s\n", cub->west_texture ? cub->west_texture : "Not Set");
    printf("East Texture: %s\n", cub->east_texture ? cub->east_texture : "Not Set");

    printf("Floor Color: R=%d, G=%d, B=%d\n", 
        (cub->floor_color >> 16) & 0xFF,
        (cub->floor_color >> 8) & 0xFF,
        cub->floor_color & 0xFF);

    printf("Ceiling Color: R=%d, G=%d, B=%d\n", 
        (cub->ceiling_color >> 16) & 0xFF,
        (cub->ceiling_color >> 8) & 0xFF,
        cub->ceiling_color & 0xFF);

    printf("Map:\n");
    int i = 0;
    while (i < cub->map_height)
	{
        printf("%s\n", cub->map[i]);
        i++;
    }
}
