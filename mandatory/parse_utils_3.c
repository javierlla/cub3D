/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:53:41 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/13 21:34:17 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_colour_rgb	valid_colour_range(char *r_str, char *g_str, char *b_str)
{
	t_colour_rgb		colour;

	colour.r = -1;
	colour.g = -1;
	colour.b = -1;
	colour.r = ft_atoi(r_str);
	colour.g = ft_atoi(g_str);
	colour.b = ft_atoi(b_str);
	if (colour.r < 0 || colour.r > 255 || colour.g < 0
		|| colour.g > 255 || colour.b < 0 || colour.b > 255)
		exit_with_error("Color values must be in the range [0, 255]");
	return (colour);
}

char	*copy_substring(char *line, int start, int end)
{
	int		len;
	char	*colour;
	int		i;

	len = end - start + 1;
	colour = malloc(sizeof(char) * (len + 1));
	if (!colour)
		exit_with_error("Memory allocation failed");
	i = 0;
	while (start <= end)
	{
		colour[i] = line[start];
		i++;
		start++;
	}
	colour[i] = '\0';
	return (colour);
}

void	validate_colour(char *colour)
{
	int	i;
	int	ind_is_colour;

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
}

char	*get_colour_str(char *line, int start, int end)
{
	char	*colour;

	colour = copy_substring(line, start, end);
	validate_colour(colour);
	return (colour);
}

t_colour_rgb	valid_colours(char *line, int ind_first_coma, int ind_sec_coma)
{
	char			*r;
	char			*g;
	char			*b;
	t_colour_rgb	colour;

	r = get_colour_str(line, 0, ind_first_coma - 1);
	g = get_colour_str(line, ind_first_coma + 1, ind_sec_coma - 1);
	b = get_colour_str(line, ind_sec_coma + 1, ft_strlen(line) - 1);
	colour = valid_colour_range (r, g, b);
	free(r);
	free(g);
	free(b);
	return (colour);
}
