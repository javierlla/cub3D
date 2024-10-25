/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:33:35 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/25 14:06:12 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define BUFFER_SIZE 1024

int	open_and_validate_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("Fallo al abrir el archivo .cub");
	return (fd);
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
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		process_buffer(data, buffer, bytes_read, &line_start);
	}
	if (bytes_read < 0)
		exit_with_error("Error al leer el archivo");
}

void	close_and_validate(int fd, t_data *data)
{
	close(fd);
	validate_map(data);
}

void	read_cub_file(t_data *data, const char *filename)
{
	int	fd;

	fd = open_and_validate_file(filename);
	read_and_process_file(data, fd);
	close_and_validate(fd, data);
}
