/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:24:01 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:47:54 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	is_not_map_line(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
	{
		return (1);
	}
	return (0);
}

void	parse_line(t_data *data, char *line)
{
	if (is_not_map_line(line))
	{
		while (ft_isspace(*line))
			line++;
		if (*line == '\0')
			return ;
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
	}
	else
	{
		line = replace_initial_and_final_spaces_with_three(line);
		line = replace_internal_spaces_with_ones(line);
		parse_map_line(data, line);
	}
}

void	process_line(t_data *data, char *buffer, int start, int end)
{
	char	*line;

	buffer[end] = '\0';
	line = &buffer[start];
	if (*line != '\0')
		parse_line(data, line);
}
