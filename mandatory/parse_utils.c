/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:44:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/16 10:57:31 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void exit_with_error(const char *message)
{
    write(2, "Error\n", 6);
    write(2, message, strlen(message));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}

int count_commas(const char *line)
{
    int count = 0;
    while (*line)
    {
        if (*line == ',')
            count++;
        line++;
    }
    return count;
}

int parse_color(char *line) 
{
    int r, g, b;

    if (count_commas(line) != 2)
        exit_with_error("Color should be in format R,G,B");

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
    char	*end;
	
    while (*str == ' ' || *str == '\t')
        str++;
    if (*str == '\0')
        return str;
    end = str + ft_strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;
    
    *(end + 1) = '\0';
    
    return (str);
}

char *extract_path(char *line)
{
    char *path = trim_whitespace(line);

    int len = ft_strlen(path);
    if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
    {
        exit_with_error("Texture file must have a .xpm extension");
    }
    return (ft_strdup(path));
}

void free_resources(t_data *data)
{
    int i;
    
    if (data)
    {
        i = 0;
        while(i < 4)
        {
            if (data->cub->textures[i])
                mlx_destroy_image(data->mlx->mlx_ptr, data->cub->textures[i]);
            i++;
        }
        free(data->cub->textures);
        free(data->cub->textures_data);
        free(data->cub);
        free(data->mlx);
        free(data);
    }
}


void check_file_extension(const char *filename)
{
    const char *ext = ft_strrchr(filename, '.');
    if (!ext || ft_strcmp(ext, ".cub") != 0)
        exit_with_error("The map file must have a .cub extension");
}

char *remove_spaces(char *line)
{
    char *result;
    char *ptr;
    size_t len;
    
    len = 0;
    ptr = line;
    while (*ptr)
    {
        if (*ptr != ' ')
            len++;
        ptr++;
    }
    result = (char *)malloc(len + 1);
    if (!result)
        exit_with_error("Memory allocation failed");
    ptr = line;
    while (*ptr)
    {
        if (*ptr != ' ')
            *result++ = *ptr;
        ptr++;
    }
    *result = '\0';

    return (result - len);
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
