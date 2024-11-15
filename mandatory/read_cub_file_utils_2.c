/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:59:04 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 18:22:27 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_file_content(t_data *data)
{
	int	tmp_nb_lines_file;
	int	i;

	tmp_nb_lines_file = data->cub->nb_lines_file;
	i = 0;
	while (tmp_nb_lines_file > 0)
	{
		tmp_nb_lines_file--;
		i++;
	}
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
				return (0);
			}
		}
		tmp_nb_lines_file--;
		ind++;
	}
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
	if (are_four_textures_defined(data) == 1
		&& are_two_colours_defined(data) == 1
		&& is_map_defined(data) == 1
		&& no_other_content_found(data) == 1
		&& another_condition(data) == 1
		&& map_last(data) == 1)
		return ;
	else
		exit_with_error("Mandatory checks not passed");
}
