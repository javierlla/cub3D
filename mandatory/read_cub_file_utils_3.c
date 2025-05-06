/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_utils_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:59:07 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:19:00 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
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
	if (nb_textures_defined != 4)
	{
		exit_with_error("incorrect amount of textures defined\n");
		return (0);
	}
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
	if (nb_colours_defined != 2)
	{
		exit_with_error("incorrect amount of floor/ceiling colours defined\n");
		return (0);
	}
	return (1);
}
