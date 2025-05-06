/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:33:35 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:54:28 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_and_validate_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("File opening not possible");
	return (fd);
}

int	open_close_first_to_count(const char *filename)
{
	int		fd;
	char	*nl;
	int		nb_lines_file;

	fd = open_and_validate_file(filename);
	nl = get_next_line(fd);
	nb_lines_file = 0;
	while (nl)
	{
		if (nl)
			free (nl);
		nl = get_next_line(fd);
		nb_lines_file++;
	}
	close(fd);
	return (nb_lines_file);
}

void	open_close_second_to_copy(t_data *data, const char *filename)
{
	int		fd;
	char	*nl;
	int		ind_line_file;

	data->cub->file = malloc(sizeof(char *) * data->cub->nb_lines_file);
	fd = open_and_validate_file(filename);
	nl = get_next_line(fd);
	ind_line_file = 0;
	while (nl)
	{
		data->cub->file[ind_line_file] = ft_strdup(nl);
		if (nl)
			free (nl);
		nl = get_next_line(fd);
		ind_line_file++;
	}
	free (nl);
	close(fd);
}

void	gen_file_line_info(t_data *data)
{
	data->cub->file_lines_type = malloc(sizeof(char)
			* (data->cub->nb_lines_file + 1));
	ft_memset(data->cub->file_lines_type, 'X', data->cub->nb_lines_file);
	data->cub->file_lines_type[data->cub->nb_lines_file] = '\0';
}

void	read_cub_file(t_data *data, const char *filename)
{
	int	fd;
	int	lenght;

	lenght = ft_strlen(filename);
	if (lenght < 4 || ft_strcmp(".cub", filename + lenght - 4) != 0)
		exit_with_error("the file extension must be:.cub");
	fd = open_and_validate_file(filename);
	data->cub->nb_lines_file = open_close_first_to_count(filename);
	open_close_second_to_copy(data, filename);
	gen_file_line_info(data);
	mandatory_checks(data);
	trim_when_necessary(data);
	read_and_process_file(data, fd);
	close_and_validate(fd, data);
}
/*int another_condition(t_data *data)
{
    int		i;
    int		map_started;
    int		found_blank_line;
	char	line_type;

	i = 0;
	map_started = 0;
	found_blank_line = 0;
    while (i < data->cub->nb_lines_file)
	{
    	line_type = data->cub->file_lines_type[i];
    	if (line_type == 'M')
    	{
			if (found_blank_line)
			{
				exit_with_error("invalid position map");
				return (0);
			}
			map_started = 1;
		}
		else if (line_type == 'X')
		{
			if (map_started)
			found_blank_line = 1;
		}
		i++;
	}
	return (1);
}*/
/*int is_colour_defined(char colour, t_data *data)
{
	int		x;
	int 	y;
	int		tmp_nb_lines_file;
	int		counter;
	int 	line_len;

	x = 0;
	y = 0;
	tmp_nb_lines_file = data->cub->nb_lines_file;
	counter = 0;
	while (tmp_nb_lines_file > 0)
	{
		y = 0;
		line_len = ft_strlen(data->cub->file[x]);
		while (line_len > 0)
		{
			while (ft_isspace(data->cub->file[x][y]
				&& data->cub->file[x][y] != '\0'))
			{
				y++;
				line_len--;
			}
			if (data->cub->file[x][y] == colour
				&& data->cub->file[x][y + 1] == ' ')
			{
				counter++;
				data->cub->file_lines_type[x] = 'C';
				break; //por cada línea quiero que me pueda contar solo 1 vez
			}
			y++;
			line_len--;
		}
		x++;
		tmp_nb_lines_file--;
	}
	return (counter);
}*/
/*int is_texture_defined(char *direction, t_data *data)
{
	int		x;
	int 	y;
	int		tmp_nb_lines_file;
	int		counter;
	int 	line_len;

	x = 0;
	y = 0;
	tmp_nb_lines_file = data->cub->nb_lines_file;
	counter = 0;
	while (tmp_nb_lines_file > 0)
	{
		y = 0;
		line_len = ft_strlen(data->cub->file[x]);
		while (line_len > 0)
		{
			while (ft_isspace(data->cub->file[x][y]
				&& data->cub->file[x][y] != '\0'))
			{
				y++;
				line_len--;
			}
			if (data->cub->file[x][y] == direction[0]
				&& data->cub->file[x][y + 1] == direction[1]
					&& data->cub->file[x][y + 2] == ' ')
			{
				counter++;
				data->cub->file_lines_type[x] = 'T';
				break;
			}
			y++;
			line_len--;
		}
		x++;
		tmp_nb_lines_file--;
	}
	return (counter);
}*/