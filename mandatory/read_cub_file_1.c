/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:33:35 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/01 18:30:53 by uxmancis         ###   ########.fr       */
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

// void	process_buffer(t_data *data, char *buffer,
// 	ssize_t bytes_read, int *line_start)
// {
// 	int	i;

// 	i = 0;
// 	while (i < bytes_read) //Recorrer todo el buffer
// 	{
// 		if (buffer[i] == '\n') //Cada línea
// 		{
// 			process_line(data, buffer, *line_start, i);
// 			*line_start = i + 1;
// 		}
// 		i++;
// 	}
// 	if (*line_start < bytes_read)
// 		process_line(data, buffer, *line_start, bytes_read);
// 	*line_start = 0;
// }

/* line_is_map
*
*	Returns:
*		· 1: line is a map line
*		· 0: line is NOT a map line
*/
int	line_is_map(char *line)
{
	if (line[0] == '1')
		return (1);
	return (0);
}

/* Returns number of lines of file. Info we need to malloc file variable*/
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
	return(nb_lines_file);
}

void open_close_second_to_copy(t_data *data, const char *filename)
{
	int		fd;
	char	*nl;
	int		ind_line_file;

	data->cub->file = malloc(sizeof(char *) * data->cub->nb_lines_file);
	// data->cub->file[tmp_nb_lines_file + 1][0] = '\0';
	fd = open_and_validate_file(filename);
	nl = get_next_line(fd);
	ind_line_file = 0;
	printf(BLUE"After copying to our FILE variable: \n");
	while (nl)
	{
		data->cub->file[ind_line_file] = ft_strdup(nl);
		printf(BLUE"file[%d] = %s"RESET_COLOUR, ind_line_file + 1, data->cub->file[ind_line_file]);
		if (nl)
			free (nl);
		nl = get_next_line(fd);
		ind_line_file++;
	}
	close(fd);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}


int	ft_strncmp_2(char *line, int start, char *direction, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)line;
	str2 = (unsigned char *)direction;
	i = 0;
	while ((str1[start] || str2[i]) && (i < n))
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}

int is_texture_defined(char *direction, t_data *data)
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
	// printf("\ndirection = %s\n", direction);
	while (tmp_nb_lines_file > 0)
	{
		//printf(MAGENTA"\nfile[%d] = %s"RESET_COLOUR, x, data->cub->file[x]);
		y = 0;
		//printf("x = %d, y = %d\n", x, y);
		line_len = ft_strlen(data->cub->file[x]);
		//printf("line_len = %d\n", line_len);
		while (line_len > 0)
		{
			//printf("seguimos en linea\n");
			while (ft_isspace(data->cub->file[x][y] && data->cub->file[x][y] != '\0'))
			{
				y++;
				line_len--;
			}
			//else if (ft_strncmp_2(data->cub->file[x][y], y, direction, 3) == 0)
			if (data->cub->file[x][y] == direction[0] && data->cub->file[x][y + 1] == direction[1] && data->cub->file[x][y + 2] == ' ')
			{
				counter++;
				data->cub->file_lines_type[x] = 'T';
				// printf(RED"   > counter++, y = %d, :)\n"RESET_COLOUR, y);
				break;
			}
			y++;
			line_len--;
			//printf(YELLOW"y = %d, file[%d][%d] = %c\n"RESET_COLOUR, y, x, y, data->cub->file[x][y]);
			
		}
		x++;
		tmp_nb_lines_file--;
		//printf(YELLOW"x = %d\n"RESET_COLOUR, x);
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
int are_four_textures_defined(t_data *data)
{
	int nb_textures_defined;
	int nb_no;
	int nb_so;
	int nb_we;
	int nb_ea;

	
	nb_no = is_texture_defined("NO", data);
	nb_so = is_texture_defined("SO", data);
	nb_we = is_texture_defined("WE", data);
	nb_ea = is_texture_defined("EA", data);
	
	// printf("nb_no = %d\n", nb_no);
	// printf("nb_so = %d\n", nb_so);
	// printf("nb_we = %d\n", nb_we);
	// printf("nb_ea = %d\n", nb_ea);
	
	nb_textures_defined = nb_no + nb_so + nb_we + nb_ea;
		
	if (nb_textures_defined == 4)
		printf("> 4: nb_textures_defined = %d - "GREEN"OK\n"RESET_COLOUR, nb_textures_defined);
	else
		printf("> 4: nb_textures_defined = %d - "RED"KO\n"RESET_COLOUR, nb_textures_defined);

	if (nb_textures_defined != 4)
	{
		printf("Error: incorrect amount of textures defined\n");
		return (0);
	}
	printf("About file lines'content: %s (%d lines in total)\n\n", data->cub->file_lines_type, data->cub->nb_lines_file);
	return (1);
}

int is_colour_defined(char colour, t_data *data)
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
			while (ft_isspace(data->cub->file[x][y] && data->cub->file[x][y] != '\0'))
			{
				y++;
				line_len--;
			}
			if (data->cub->file[x][y] == colour && data->cub->file[x][y + 1] == ' ')
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
}

int are_two_colours_defined(t_data *data)
{
	int nb_colours_defined;
	int nb_f;
	int nb_c;
	
	nb_f = is_colour_defined('F', data);
	nb_c = is_colour_defined('C', data);
	
	// printf("nb_no = %d\n", nb_no);
	// printf("nb_so = %d\n", nb_so);
	// printf("nb_we = %d\n", nb_we);
	// printf("nb_ea = %d\n", nb_ea);
	
	nb_colours_defined = nb_f + nb_c;

	if (nb_colours_defined == 2)
		printf("> 2: nb_colours_defined = %d - "GREEN"OK\n"RESET_COLOUR, nb_colours_defined);
	else
		printf("> 2: nb_colours_defined = %d - "RED"KO\n"RESET_COLOUR, nb_colours_defined);
	
	if (nb_colours_defined != 2)
	{
		printf("Error: incorrect amount of floor/ceiling colours defined\n");
		return (0);
	}
	printf("About file lines'content: %s (%d lines in total)\n\n", data->cub->file_lines_type, data->cub->nb_lines_file);
	return (1);
}

void where_is_map(t_data *data)
{
	int tmp_nb_lines_file;
	int line_nb;
	int y;
	int tmp_line_len;

	tmp_nb_lines_file = data->cub->nb_lines_file;
	line_nb = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (ft_strlen(data->cub->file[line_nb]) > 0)
		{
			y = 0;
			tmp_line_len = ft_strlen(data->cub->file[line_nb]);
			while (tmp_line_len > 0)
			{
				if (data->cub->file[line_nb][y] == '0' || data->cub->file[line_nb][y] == '1')
				{
					data->cub->file_lines_type[line_nb] = 'M';
					//printf("data->cub->file_lines_type[%d] = %c\n", line_nb, data->cub->file_lines_type[line_nb]);
					break;
				}
				tmp_line_len--;
			}
		}
		line_nb++;
		tmp_nb_lines_file--;
	}
}

int is_map_defined(t_data *data)
{
	int i; 
	
	where_is_map(data);
	i = 0;
	while (data->cub->file_lines_type[i] != '\0')
	{
		if (data->cub->file_lines_type[i] == 'M')
		{
			printf("> M: Map defined - "GREEN"OK\n"RESET_COLOUR);
			printf("About file lines'content: %s (%d lines in total)\n\n", data->cub->file_lines_type, data->cub->nb_lines_file);
			return (1);
		}
		i++;
	}
	printf("> M: Map NOT defined - "RED"KO\n"RESET_COLOUR);
	return (0);
}

int no_other_content_found (t_data *data)
{
	int tmp_nb_lines_file;
	int ind;
	// int tmp_len_line;

	tmp_nb_lines_file = data->cub->nb_lines_file;
	ind = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (data->cub->file_lines_type[ind] == 'X')
		{
			// printf("we're here, file nb %d, len = %ld\n", ind, ft_strlen(data->cub->file[ind]));
			if (data->cub->file[ind][0] != '\n' && ft_strlen(data->cub->file[ind]) > 1)
			{
				printf("Error: unexpected content found\n");
				return (0);
			}
		}
		tmp_nb_lines_file--;
		ind++;
	}
	printf("> X: No other content found - "GREEN"OK\n"RESET_COLOUR);
	printf("About file lines'content: %s (%d lines in total)\n\n", data->cub->file_lines_type, data->cub->nb_lines_file);
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
void mandatory_checks(t_data *data)
{
	printf("\nMandatory checks: ------------------------ \n");
	if (are_four_textures_defined(data) == 1
		&& are_two_colours_defined(data) == 1
		&& is_map_defined(data) == 1
		&& no_other_content_found(data) == 1)
		return;
	else
		exit(EXIT_FAILURE);
}

void is_correct_texture_path(t_data *data)
{
	int tmp_nb_lines_file;
	int ind;

	tmp_nb_lines_file = data->cub->nb_lines_file;
	ind = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (data->cub->file_lines_type[ind] == 'T')
		{
			if (ft_strncmp(data->cub->file[ind], "NO ", 3) == 0)
			{
				// printf(BLUE"north\n"RESET_COLOUR);
				parse_texture(data->cub->file[ind], "NO ", &data->cub->north_texture);
			}
			if (ft_strncmp(data->cub->file[ind], "SO ", 3) == 0)
			{
				// printf(BLUE"south\n"RESET_COLOUR);
				parse_texture(data->cub->file[ind], "SO ", &data->cub->north_texture);
			}
			if (ft_strncmp(data->cub->file[ind], "WE ", 3) == 0)
			{
				// printf(BLUE"west\n"RESET_COLOUR);
				parse_texture(data->cub->file[ind], "WE ", &data->cub->north_texture);
			}
			if (ft_strncmp(data->cub->file[ind], "EA ", 3) == 0)
			{
				// printf(BLUE"east\n"RESET_COLOUR);
				parse_texture(data->cub->file[ind], "EA ", &data->cub->north_texture);
			}
				
		}
		tmp_nb_lines_file--;
		ind++;
	}
	printf("> textures format is "GREEN"OK\n"RESET_COLOUR);
}

/*
*	file_lines_type variable will be informed:
*
*	· 'T' for texture lines
*	· 'C' for colour lines
*	· 'M' for map lines
*	· 'X' for other lines
*/
void gen_file_line_info(t_data *data)
{
	data->cub->file_lines_type = malloc(sizeof(char) * (data->cub->nb_lines_file + 1));
	ft_memset(data->cub->file_lines_type, 'X', data->cub->nb_lines_file);
	data->cub->file_lines_type[data->cub->nb_lines_file] = '\0';
}

void trim_when_necessary(t_data *data)
{
	int tmp_nb_lines_file;
	int ind;

	tmp_nb_lines_file = data->cub->nb_lines_file;
	ind = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (data->cub->file_lines_type[ind] == 'T' || data->cub->file_lines_type[ind] == 'C')
		{
			data->cub->file[ind] = trim_whitespace(data->cub->file[ind]);
		}
		tmp_nb_lines_file--;
		ind++;
	}

	printf(MAGENTA"After trimming: \n"); //debugging purposes
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

void is_correct_colour_format(t_data *data)
{
	int tmp_nb_lines_file;
	int ind;

	ind = 0;
	tmp_nb_lines_file = data->cub->nb_lines_file;
	while (tmp_nb_lines_file > 0)
	{
		if (data->cub->file_lines_type[ind] == 'C' )
		{
			if (ft_strncmp(data->cub->file[ind], "F ", 2) == 0
				|| ft_strncmp(data->cub->file[ind], "C ", 2) == 0)
				parse_color(data->cub->file[ind]);
		}
		tmp_nb_lines_file--;
		ind++;
	}
	printf("> colours format is "GREEN"OK\n"RESET_COLOUR);
}

void mandatory_checks_format(t_data *data)
{
	is_correct_texture_path(data);
	is_correct_colour_format(data);
}

int get_map_nb_lines(t_data *data)
{
	int tmp_nb_lines_file;
	int ind;
	int counter;

	ind = 0;
	tmp_nb_lines_file = data->cub->nb_lines_file;
	counter = 0;
	while (tmp_nb_lines_file > 0)
	{
		if (data->cub->file_lines_type[ind] == 'M')
			counter++;
		ind++;
		tmp_nb_lines_file--;
	}
	return (counter);
}

void put_map(t_data *data)
{
	int tmp_height_map;
	int ind;

	tmp_height_map = data->cub->map_height;
	ind = 0;
	printf(GREEN"Our MAP variable: \n"RESET_COLOUR);
	while (tmp_height_map > 0)
	{
		printf("map[%d] = %s", ind, data->cub->map[tmp_height_map - 1]);
		tmp_height_map--;
		ind++;
	}
}

void get_map(t_data *data)
{
	int counter_map_lines;
	int tmp_nb_lines_file;
	int ind_line_file;
	int ind_map;
	
	counter_map_lines = get_map_nb_lines(data);
	data->cub->map_height = counter_map_lines;
	data->cub->map = malloc(sizeof(char *) * (counter_map_lines + 1));
	ind_line_file = 0;
	ind_map = 0;
	tmp_nb_lines_file = data->cub->nb_lines_file;
	while (tmp_nb_lines_file > 0)
	{
		if (data->cub->file_lines_type[ind_line_file] == 'M')
		{
			data->cub->map[ind_map] = ft_strdup(data->cub->file[ind_line_file]);
			ind_map++;
		}
		ind_line_file++;
		tmp_nb_lines_file--;
	}

	put_map(data); //debugging purposes
}

void	read_and_process_file(t_data *data, const char *filename/*, int fd*/)
{
	// char	*nl;
	// int		nb_lines_file;
	// int		nb_lines_map;
	// int		fd;
	// int 	ind_line_file;

	(void)data;
	/* Get file as it is*/
	//#1 apertura de archivo, para contar longitud --> para malloc
	data->cub->nb_lines_file = open_close_first_to_count(filename);
	
	//#2 apertura de archivo, para copiar líneas en data->cub->file: Get file as it is
	open_close_second_to_copy(data, filename);

	gen_file_line_info(data);
	

	
	// (void)nb_lines_map;

	// Asegurar unos mínimos: mandatory_checks
	mandatory_checks(data);
			//Las 4 texturas sí están definidas (solo 1 de cada)
			//Los 2 colores techo/suelo sí están definidos (solo 1 de cada)
			//Sí hay mapa (hay alguna línea con 0s y 1s)
			//Solo hay texturas-colores-mapa lines, nada más (ninguna otra línea con contenido)
	trim_when_necessary(data);
	mandatory_checks_format(data);
	printf("\nAbout file lines'content: %s (%d lines in total)\n", data->cub->file_lines_type, data->cub->nb_lines_file);

	get_map(data);
	
	/* Make little changes in file so that it is correct */
				//Quitar espacios cuando aplique (NO-SO-WE-EA-F-C)✅
				//LÍNEAS MAPA --> sustituir ' ' por '1'
	


	/* Parseito */
	        //Contar nb_lines_map









	/* Previous version */
	// while (bytes_read > 0)
	// {
	// 	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	// 	if (bytes_read < 0)
	// 		exit_with_error("Reading not possible");
	// 	buffer[bytes_read] = '\0';
	// 	process_buffer(data, buffer, bytes_read, &line_start);
	// 	printf("buffer = %s\n", buffer);
	// }
}

void	close_and_validate(int fd, t_data *data)
{
	close(fd);
	validate_map(data);
}

void	read_cub_file(t_data *data, const char *filename)
{
	//int	fd;

	//fd = open_and_validate_file(filename);
	read_and_process_file(data, filename);
	//close_and_validate(fd, data);
}
