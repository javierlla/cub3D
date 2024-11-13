/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:05 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/13 18:10:50 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_commas(const char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == ',')
			count++;
		line++;
	}
	return (count);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

t_colour_rgb	parse_colour_2(char *line)
{
	int				ind_first_coma;
	int				ind_sec_coma;
	int				i;
	t_colour_rgb	colour;

	i = 0;
	while (line[i] != ',')
		i++;
	if (line[i] == ',')
	{
		ind_first_coma = i;
		i++;
	}
	while (line[i] != ',')
		i++;
	if (line[i] == ',')
	{
		ind_sec_coma = i;
		i++;
	}
	colour = valid_colours(line, ind_first_coma, ind_sec_coma);
	return (colour);
}

int	parse_color(char *line)
{
	t_colour_rgb	colour;
	int				i;

	i = 0;
	if (count_commas(line) != 2)
		exit_with_error("Color should be in format R,G,B. incorrect commas.");
	while (line[i])
	{
		if (line[i] == ' ' || is_num(line[i]) == 1 || line[i] == ',')
			i++;
		else
			exit_with_error("invalid color");
	}
	colour = parse_colour_2(line);
	return ((colour.r << 16) | (colour.g << 8) | colour.b);
}

/*char	*get_colour_str(char *line, int start, int end)
{
	int		i;
	int		len;
	char	*colour;
	int		ind_is_colour;

	len = end - start + 1;
	colour = malloc(sizeof(char) * len + 1);
	colour[len] = '\0';
	i = 0;
	while (start <= end)
	{
		colour[i] = line[start];
		i++;
		start++;
	}
	i = 0;
	ind_is_colour = 0;
	while (colour[i] != '\0')
	{
		if (is_num(colour[i]))
			ind_is_colour = 1;
		i++;
	}
	if (ind_is_colour == 0)
		exit_with_error("Invalid colour");
	return (colour);
}*/