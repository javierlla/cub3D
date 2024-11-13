/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:33:35 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/13 19:28:06 by jllarena         ###   ########.fr       */
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

int	open_and_validate_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("File opening not possible");
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

void	close_and_validate(int fd, t_data *data)
{
	close(fd);
	validate_map(data);
}

int	open_close_first_to_count(const char *filename)
{
	int		fd;
	char	*nl;
	int		nb_lines_file;

	fd = open_and_validate_file(filename);
	nl = get_next_line(fd);
	nb_lines_file = 0;
	printf("Get next line, 1st read: \n");
	while (nl)
	{
		printf("nl = %s", nl);
		if (nl)
			free (nl);
		nl = get_next_line(fd);
		nb_lines_file++;
	}
	printf("\n-----------------------------------\n");
	printf("Result: nb_lines_file = %d\n", nb_lines_file);
	printf("\n-----------------------------------\n");
	close(fd);
	return (nb_lines_file);
}

void	put_file_content(t_data *data)
{
	int	tmp_nb_lines_file;
	int	i;

	tmp_nb_lines_file = data->cub->nb_lines_file;
	i = 0;
	while (tmp_nb_lines_file > 0)
	{
		printf("file_content_line[%d] = %c\n",
			i + 1, data->cub->file_lines_type[i]);
		tmp_nb_lines_file--;
		i++;
	}
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
	printf(BLUE"After copying to our FILE variable: \n");
	while (nl)
	{
		data->cub->file[ind_line_file] = ft_strdup(nl);
		printf(BLUE"file[%d] = %s"RESET_COLOUR,
			ind_line_file + 1, data->cub->file[ind_line_file]);
		if (nl)
			free (nl);
		nl = get_next_line(fd);
		ind_line_file++;
	}
	close(fd);
}

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
		{
			data->cub->file[ind] = trim_whitespace(data->cub->file[ind]);
		}
		tmp_nb_lines_file--;
		ind++;
	}
	printf(MAGENTA"After trimming: \n");
	tmp_nb_lines_file = data->cub->nb_lines_file;
	ind = 0;
	while (tmp_nb_lines_file > 0)
	{
		printf("file[%d] = %s", ind, data->cub->file[ind]);
		tmp_nb_lines_file--;
		ind++;
	}
	printf(RESET_COLOUR"\n");
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
			printf("> M: Map defined - "GREEN"OK\n"RESET_COLOUR);
			printf("About file lines'content: %s (%d lines in total)\n\n",
				data->cub->file_lines_type, data->cub->nb_lines_file);
			return (1);
		}
		i++;
	}
	printf("> M: Map NOT defined - "RED"KO\n"RESET_COLOUR);
	return (0);
}

void	gen_file_line_info(t_data *data)
{
	data->cub->file_lines_type = malloc(sizeof(char)
			* (data->cub->nb_lines_file + 1));
	ft_memset(data->cub->file_lines_type, 'X', data->cub->nb_lines_file);
	data->cub->file_lines_type[data->cub->nb_lines_file] = '\0';
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
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

int	process_line_for_colour(char *line, char colour, t_data *data, int x)
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
		if (y < line_len && line[y] == colour && line[y + 1] == ' ')
		{
			data->cub->file_lines_type[x] = 'C';
			return (1);
		}
		y++;
	}
	return (0);
}

int	is_colour_defined(char colour, t_data *data)
{
	int	x;
	int	tmp_nb_lines_file;
	int	counter;

	x = 0;
	tmp_nb_lines_file = data->cub->nb_lines_file;
	counter = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (process_line_for_colour(data->cub->file[x], colour, data, x))
		{
			counter++;
		}
		x++;
		tmp_nb_lines_file--;
	}
	return (counter);
}

/* four_textures_defined
*
*	Makes sure:
*        · NO - SO - WE - EA textures are defined
*        · Each (NO - SO - WE - EA) is defined only once
*		 · 4 texture paths are correct
*	
*/
int	are_four_textures_defined(t_data *data)
{
	int	nb_textures_defined;
	int	nb_no;
	int	nb_so;
	int	nb_we;
	int	nb_ea;

	nb_no = is_texture_defined("NO", data);
	nb_so = is_texture_defined("SO", data);
	nb_we = is_texture_defined("WE", data);
	nb_ea = is_texture_defined("EA", data);
	nb_textures_defined = nb_no + nb_so + nb_we + nb_ea;
	if (nb_textures_defined == 4)
		printf("> 4: nb_textures_defined = %d - "GREEN"OK\n"RESET_COLOUR,
			nb_textures_defined);
	else
		printf("> 4: nb_textures_defined = %d - "RED"KO\n"RESET_COLOUR,
			nb_textures_defined);
	if (nb_textures_defined != 4)
	{
		printf("Error: incorrect amount of textures defined\n");
		return (0);
	}
	printf("About file lines'content: %s (%d lines in total)\n\n",
		data->cub->file_lines_type, data->cub->nb_lines_file);
	return (1);
}

int	are_two_colours_defined(t_data *data)
{
	int	nb_colours_defined;
	int	nb_f;
	int	nb_c;

	nb_f = is_colour_defined('F', data);
	nb_c = is_colour_defined('C', data);
	nb_colours_defined = nb_f + nb_c;
	if (nb_colours_defined == 2)
		printf("> 2: nb_colours_defined = %d - "GREEN"OK\n"RESET_COLOUR,
			nb_colours_defined);
	else
		printf("> 2: nb_colours_defined = %d - "RED"KO\n"RESET_COLOUR,
			nb_colours_defined);
	if (nb_colours_defined != 2)
	{
		printf("Error: incorrect amount of floor/ceiling colours defined\n");
		return (0);
	}
	printf("About file lines'content: %s (%d lines in total)\n\n",
		data->cub->file_lines_type, data->cub->nb_lines_file);
	return (1);
}

int	no_other_content_found(t_data *data)
{
	int	tmp_nb_lines_file;
	int	ind;

	put_file_content(data);
	tmp_nb_lines_file = data->cub->nb_lines_file;
	ind = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (data->cub->file_lines_type[ind] == 'X')
		{
			if (data->cub->file[ind][0] != '\n'
				&& ft_strlen(data->cub->file[ind]) > 1)
			{
				printf("Error: unexpected content found, line %d\n", ind + 1);
				return (0);
			}
		}
		tmp_nb_lines_file--;
		ind++;
	}
	printf("> X: No other content found - "GREEN"OK\n"RESET_COLOUR);
	printf("About file lines'content: %s (%d lines in total)\n\n",
		data->cub->file_lines_type, data->cub->nb_lines_file);
	return (1);
}

int	process_line_type(int line_type, int *map_started, int *found_blank_line)
{
	if (line_type == 'M')
	{
		if (*found_blank_line)
			return (0);
		*map_started = 1;
	}
	else if (line_type == 'X')
	{
		if (*map_started)
			*found_blank_line = 1;
	}
	return (1);
}

int	another_condition(t_data *data)
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
		if (!process_line_type(line_type, &map_started, &found_blank_line))
		{
			exit_with_error("invalid position map");
			return (0);
		}
		i++;
	}
	return (1);
}

/* is_basic_info 
*
*	Checks:
*		1) 4 textures YES are defined, and only once each
*		2) 2 colours YES are defined, and only once each
*		3) Map YES is defined, there is at least one line with 0s and 1s
*		4) No other content found, only textures-colours-map lines, nothing else.
*          No other content.
* 
*/
void	mandatory_checks(t_data *data)
{
	printf("\nMandatory checks: ------------------------ \n");
	if (are_four_textures_defined(data) == 1
		&& are_two_colours_defined(data) == 1
		&& is_map_defined(data) == 1
		&& no_other_content_found(data) == 1
		&& another_condition(data) == 1)
		return ;
	else
		exit(EXIT_FAILURE);
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
	printf(GREEN"perfect - now lets read_and_process_file\n"RESET_COLOUR);
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