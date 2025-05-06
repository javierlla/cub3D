/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:59:00 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:26:27 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	process_line_for_map(char *line, int line_nb, t_data *data)
{
	int	y;
	int	tmp_line_len;

	y = 0;
	tmp_line_len = ft_strlen(line);
	while (tmp_line_len > 0)
	{
		if ((line[y] == '0' || line[y] == '1')
			&& data->cub->file_lines_type[line_nb] != 'C'
			&& data->cub->file_lines_type[line_nb] != 'T')
		{
			data->cub->file_lines_type[line_nb] = 'M';
			return (1);
		}
		tmp_line_len--;
		y++;
	}
	return (0);
}

void	where_is_map(t_data *data)
{
	int	tmp_nb_lines_file;
	int	line_nb;

	tmp_nb_lines_file = data->cub->nb_lines_file;
	line_nb = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (ft_strlen(data->cub->file[line_nb]) > 0)
			process_line_for_map(data->cub->file[line_nb], line_nb, data);
		line_nb++;
		tmp_nb_lines_file--;
	}
}

int	is_map_defined(t_data *data)
{
	int	i;

	where_is_map(data);
	i = 0;
	while (data->cub->file_lines_type[i] != '\0')
	{
		if (data->cub->file_lines_type[i] == 'M')
		{
			return (1);
		}
		i++;
	}
	return (0);
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
	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read < 0)
		exit_with_error("Reading not possible");
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		process_buffer(data, buffer, bytes_read, &line_start);
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (bytes_read < 0)
			exit_with_error("Reading not possible");
	}
}
