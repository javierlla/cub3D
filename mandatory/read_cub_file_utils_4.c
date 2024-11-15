/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_utils_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:59:11 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:51:33 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	trim_when_necessary(t_data *data)
{
	int	tmp_nb_lines_file;
	int	ind;

	tmp_nb_lines_file = data->cub->nb_lines_file;
	ind = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (data->cub->file_lines_type[ind] == 'T'
			|| data->cub->file_lines_type[ind] == 'C')
			data->cub->file[ind] = trim_space_index(data->cub->file[ind]);
		tmp_nb_lines_file--;
		ind++;
	}
	tmp_nb_lines_file = data->cub->nb_lines_file;
	ind = 0;
	while (tmp_nb_lines_file > 0)
	{
		tmp_nb_lines_file--;
		ind++;
	}
}

int	process_line_for_texture(char *line, char *direction, t_data *data, int x)
{
	int	y;
	int	line_len;

	y = 0;
	line_len = ft_strlen(line);
	while (y < line_len)
	{
		while (y < line_len && ft_isspace(line[y]) && line[y] != '\0')
		{
			y++;
		}
		if (y < line_len && line[y] == direction[0] && line[y + 1]
			== direction[1] && line[y + 2] == ' ')
		{
			data->cub->file_lines_type[x] = 'T';
			return (1);
		}
		y++;
	}
	return (0);
}

int	is_texture_defined(char *direction, t_data *data)
{
	int	x;
	int	tmp_nb_lines_file;
	int	counter;

	x = 0;
	tmp_nb_lines_file = data->cub->nb_lines_file;
	counter = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (process_line_for_texture(data->cub->file[x], direction, data, x))
		{
			counter++;
		}
		x++;
		tmp_nb_lines_file--;
	}
	return (counter);
}

void	close_and_validate(int fd, t_data *data)
{
	close(fd);
	validate_map(data);
}

void	allocate_initial_map(t_data *data)
{
	data->cub->map_height = 0;
	data->cub->map_width = 0;
	data->cub->map = malloc(sizeof(char *) * 1);
	if (!data->cub->map)
		exit_with_error("Failure in memory allocation for the map line");
}
