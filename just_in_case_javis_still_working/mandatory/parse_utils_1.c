/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:44:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/01 13:54:50 by jllarena         ###   ########.fr       */
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

char *replace_spaces_with_ones(char *line)
{
    char *result;
    int i = 0;
    int length = strlen(line);

    result = malloc(length + 1);
    if (!result)
        exit_with_error("memory failed");
    while (line[i] != '\0')
    {
        if (line[i] == ' ')
            result[i] = '1';
        else
            result[i] = line[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}


char *replace_initial_spaces_with_two(char *line, int target_width)
{
    int len = strlen(line);
    char *result = malloc(target_width + 1);
    if (!result)
        exit_with_error("Error de asignación de memoria para eliminar espacios");

    int i = 0;
    int padding_length = target_width - len;

    for (int j = 0; j < padding_length; j++) {
        result[i++] = '2';
    }
    strcpy(&result[i], line);
    
    printf("Linea original: \"%s\"\nLinea modificada: \"%s\"\n", line, result);
    return result;
}

/*
void print_cub_data(t_cub *cub)
{
    printf("North Texture: %s\n", cub->north_texture
		? cub->north_texture : "Not Set");
    printf("South Texture: %s\n", cub->south_texture
		? cub->south_texture : "Not Set");
    printf("West Texture: %s\n", cub->west_texture
		? cub->west_texture : "Not Set");
    printf("East Texture: %s\n", cub->east_texture
		? cub->east_texture : "Not Set");

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
}*/