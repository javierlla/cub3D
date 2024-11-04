/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:44:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/01 18:07:37 by uxmancis         ###   ########.fr       */
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

	// printf(GREEN"we're in extract_path\n"RESET_COLOUR);
	// printf("line = %s", line);
	path = trim_whitespace(line);
	len = ft_strlen(path);
	// printf("path = %s, len = %d\n", path, len);
	if (len < 4 || ft_strncmp(path + len - 5, ".xpm", 4) != 0)
	{
		exit_with_error("Texture file must have a .xpm extension");
	}
	// printf(GREEN">> OK, good .xpm format\n\n\n"RESET_COLOUR);
	return (ft_strdup(path));
}

void	check_file_extension(const char *filename)
{
	const char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strcmp(ext, ".cub") != 0)
		exit_with_error("The map file must have a .cub extension");
}

char	*remove_spaces(char *line)
{
	char	*result;
	char	*ptr;
	size_t	len;

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
