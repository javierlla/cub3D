/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:44:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/13 22:11:21 by uxmancis         ###   ########.fr       */
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

    printf(RED"trim_whitespace: str = %s"RESET_COLOUR, str);
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

int get_trimmed_len(char *str)
{
    int len_str;
    int len_trimmed_str;
    int i;
    int start;

    // printf(YELLOW"trim_whitespace_indexes: str = %s"RESET_COLOUR, str);
    len_str = ft_strlen(str);
    // printf("len_str = %d\n", len_str);
    len_trimmed_str = 0;
    i = 0;
    while (len_str > 0)
    {
        while(ft_isspace(str[i]) && str[i] != '\0')
        {
            i++;
            len_str--;
        }
        if (len_str > 0)
        {
            start = i;
            break;
        }
    }
    if (start > 0)
    {
        while (str[start] != '\0')
        {
            len_trimmed_str++;
            start++;
        }
    }
    return (len_trimmed_str);
    // printf("trimmed_len_str = %d\n", len_trimmed_str);
}

int get_index_start_trimmed(char *str)
{
    int len_str;
    int i;
    int start;

    // printf(YELLOW"trim_whitespace_indexes: str = %s"RESET_COLOUR, str);
    len_str = ft_strlen(str);
    // printf("len_str = %d\n", len_str);
    i = 0;
    while (len_str > 0)
    {
        while(ft_isspace(str[i]) && str[i] != '\0')
        {
            i++;
            len_str--;
        }
        if (len_str > 0)
        {
            start = i;
            break;
        }
    }
    return (start);
}

bool are_there_any_whitespaces_at_the_beginning(char *str)
{
    if (ft_isspace(str[0]))
        return (true);
    return (false);
}

char *trim_whitespace_indexes(char *str)
{
    int len_str;
    int len_trimmed_str;
    char *trimmed_str;
    int start_trimmed;
    int i;
    bool whitespaces_beginning;

    whitespaces_beginning = are_there_any_whitespaces_at_the_beginning(str);
    printf("whitespaces_beginning = %d\n", whitespaces_beginning);
    if (whitespaces_beginning)
    {
        // printf(YELLOW"trim_whitespace_indexes: str = %s"RESET_COLOUR, str);
        // printf("len_str = %ld\n", ft_strlen(str));
        len_trimmed_str = get_trimmed_len(str);
        trimmed_str = malloc(sizeof(char) * (len_trimmed_str + 1));
        printf(GREEN"trimmed_str = %p\n"RESET_COLOUR, trimmed_str);
        if (!trimmed_str)
            exit_with_error("malloc failed");
        trimmed_str[len_trimmed_str] = '\0';
        start_trimmed = get_index_start_trimmed(str);
        i = 0;
        // printf(BLUE"     >> start_trimmed = %d\n"RESET_COLOUR, start_trimmed);
        len_str = ft_strlen(str);
        while (start_trimmed < len_str)
        {
            trimmed_str[i] = str[start_trimmed];
            // printf("                  >> trimmed_str[%d] = %c\n", i, trimmed_str[i]);
            i++;
            start_trimmed++;
        }
        // printf("trimmed_len_str = %d\n", len_trimmed_str);
        printf("Return trimmed_str = %s\n", trimmed_str);
        return (trimmed_str);
    }
    else
    {
        printf(" ////////// No whitespaces at the beginning\n");
        printf("Return SAME: %s\n", str);
        return (str);
    }
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

char	*replace_initial_and_final_spaces_with_three(char *line)
{
	int	end;
	int	len;
	int	start;

	start = 0;
	len = ft_strlen(line);
	while (line[start] == ' ')
	{
		line[start] = '3';
		start++;
	}
	end = len - 1;
	while (end >= start && line[end] == ' ')
	{
		line[end] = '3';
		end--;
	}
	return (line);
}

/*void validate_map_borders(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < 1) 
    {
        validate_horizontal_border(data, 0);
        validate_horizontal_border(data, data->cub->map_height - 1);
        i++;
    }
    i = 0;
    while (i < 1) 
    {
        validate_vertical_border(data, 0);
        validate_vertical_border(data, data->cub->map_width - 1);
        i++;
    }
    i = 0;
    while (i < data->cub->map_height) 
    {
        j = 0;
        while (j < data->cub->map_width) 
        {
            if (data->cub->map[i][j] == '3') 
                validate_adjacent_to_3(data, i, j);
            j++;
        }
        i++;
    }
}*/

/*void	validate_map_borders(t_data *data)
{
    int i;
	int j;

    j = 0;
    while (j < data->cub->map_width) 
    {
        if (data->cub->map[0][j] != '1' && data->cub->map[0][j] != '3')
            exit_with_error("N border of map must be surrounded by walls (1)");
        if (data->cub->map[data->cub->map_height - 1][j] != '1'
			&& data->cub->map[data->cub->map_height - 1][j] != '3')
            exit_with_error("S border of map must be surrounded by walls (1)");
        j++;
    }
    i = 0;
    while (i < data->cub->map_height)
    {
        if (data->cub->map[i][0] != '1' && data->cub->map[i][0] != '3')
            exit_with_error("L border of map must be surrounded by walls (1)");
        if (data->cub->map[i][data->cub->map_width - 1] != '1'
			&& data->cub->map[i][data->cub->map_width - 1] != '3')
            exit_with_error("R border of map must be surrounded by walls (1)");
        i++;
    }

    i = 0;
    while (i < data->cub->map_height) 
    {
        j = 0;
        while (j < data->cub->map_width) 
        {
            if (data->cub->map[i][j] == '3') 
                validate_adjacent_to_3(data, i, j);
            j++;
        }
        i++;
    }
}*/

/*void validate_adjacent_to_3(t_data *data, int i, int j)
{
    char valid_chars[] = {' ', '1', '3'};
    
    int adjacent[4][2] = {
        {i - 1, j},    // Arriba
        {i + 1, j},    // Abajo
        {i, j - 1},    // Izquierda
        {i, j + 1}     // Derecha
    };
    int k = 0;
    while (k < 4)
    {
        int x = adjacent[k][0];
        int y = adjacent[k][1];

        // Verificar que la posición esté dentro del límite del mapa
        if (x >= 0 && x < data->cub->map_height
			&& y >= 0 && y < data->cub->map_width) {
            char adjacent_char = data->cub->map[x][y];
            int valid = 0;

            int v = 0;
            while (v < 3)
            {
                if (adjacent_char == valid_chars[v])
                {
                    valid = 1;
                    break;
                }
                v++;
            }
            if (!valid)
                exit_with_error("Map must be surrounded by walls (1).");
        }
        k++;
    }
}

void validate_map_borders(t_data *data)
{
    int j;
    int i;
    
    j = 0;
    while (j < data->cub->map_width) 
    {
        if (data->cub->map[0][j] != '1' && data->cub->map[0][j] != '3')
            exit_with_error("N border of map must be surrounded by walls (1)");
        if (data->cub->map[data->cub->map_height - 1][j] != '1'
			&& data->cub->map[data->cub->map_height - 1][j] != '3')
            exit_with_error("S border of map must be surrounded by walls (1)");
        j++;
    }
    i = 0;
    while (i < data->cub->map_height)
    {
        if (data->cub->map[i][0] != '1' && data->cub->map[i][0] != '3')
            exit_with_error("L boder of map must be surrounded by walls (1)");
        if (data->cub->map[i][data->cub->map_width - 1] != '1'
			&& data->cub->map[i][data->cub->map_width - 1] != '3')
            exit_with_error("R boder of map must be surrounded by walls (1)");
        i++;
    }
    i = 0;
    while (i < data->cub->map_height)
    {
        j = 0;
        while (j < data->cub->map_width)
        {
            if (data->cub->map[i][j] == '3')
                validate_adjacent_to_3(data, i, j);
            j++;
        }
        i++;
    }
}*/
