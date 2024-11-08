/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:05 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/08 21:23:56 by jllarena         ###   ########.fr       */
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
int is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
t_colour_rgb valid_colour_range (char *r_str, char *g_str, char *b_str)
{
	/*int r;
	int g;
	int b;*/
	t_colour_rgb colour;

	colour.r = -1;
	colour.g = -1;
	colour.b = -1;
	colour.r = ft_atoi(r_str);
	colour.g = ft_atoi(g_str);
	colour.b = ft_atoi(b_str);

	if (colour.r < 0 || colour.r > 255 || colour.g < 0 || colour.g > 255 || colour.b < 0 || colour.b > 255)
		exit_with_error("Color values must be in the range [0, 255]");
	return(colour);
}

char *get_colour_str(char *line, int start, int end)
{
	int i;
	int len;
	char *colour;
	int ind_is_colour;

	len = end - start + 1;
	// printf("line = %s, start = %d, end = %d\n", line, start, end);
	// printf(YELLOW"len = %d\n"RESET_COLOUR, len);
	colour = malloc(sizeof(char) * len + 1);
	colour[len] = '\0';
	// while (len > 0)
	// {
		
	// 	len--;
	// }
	
	i = 0;
	while (start <= end)
	{
		colour[i] = line[start];
		// printf("  > [%d] = %c\n", start, colour[i]);
		i++;
		start++;
	}
	i = 0;
	ind_is_colour = 0;
	while(colour[i] != '\0')
	{
		if(is_num(colour[i]))
			ind_is_colour = 1;
		i++;
	}
	if (ind_is_colour == 0)
		exit_with_error("Invalid colour");

	
	return (colour);
}

t_colour_rgb valid_colours (char *line, int ind_first_coma, int ind_sec_coma)
{
	char *r;
	char *g;
	char *b;
	t_colour_rgb colour;

	
	r = get_colour_str(line, 0, ind_first_coma - 1);
	g = get_colour_str(line, ind_first_coma + 1, ind_sec_coma - 1);
	b = get_colour_str(line, ind_sec_coma + 1, ft_strlen(line) - 1);

	// printf(RED"r = %s\n"RESET_COLOUR, r);
	// printf(GREEN"g = %s\n"RESET_COLOUR, g);
	// printf(BLUE"b = %s\n"RESET_COLOUR, b);
	colour = valid_colour_range (r, g, b);
	return (colour);
}

t_colour_rgb parse_colour_2(char *line)
{
	int ind_first_coma;
	int ind_sec_coma;
	int i;
	t_colour_rgb colour;

	i = 0;
	while(line[i] != ',')
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
	// printf("-------------------parsse_colour_2 -------------------\n");
	// printf("line = %s\n", line);
	// printf(MAGENTA"ind_first_coma = %d\n"RESET_COLOUR, ind_first_coma);
	// printf(MAGENTA"ind_sec_coma = %d\n"RESET_COLOUR, ind_sec_coma);
	// printf("-------------------------------------------------------\n");
	
	colour = valid_colours(line, ind_first_coma, ind_sec_coma);
	return (colour);
}

// 	r = ft_strdup_end_start(line);
	
// }

int	parse_color(char *line)
{
	// int	r;
	// int	g;
	// int	b;
	t_colour_rgb colour;
	int i = 0;

	//char nums[] = "0123456789";
	if (count_commas(line) != 2)
		exit_with_error("Color should be in format R,G,B. incorrect commas.");
	while(line[i])
	{
		if (line[i] == ' ' || is_num(line[i]) == 1 || line[i] == ',')
			i++;
		else
			exit_with_error("invalid color");
	}
	colour = parse_colour_2(line);	
	// r = ft_atoi(line);

	// line = ft_strchr(line, ',') + 1;
	// /*if (line != nums)
	// 	exit_with_error("Invalid color");*/
	// g = ft_atoi(line);
	// line = ft_strchr(line, ',') + 1;
	// /*if (line != nums)
	// 	exit_with_error("Invalid color");*/
	// b = ft_atoi(line);
	// printf("el valor de 'b' = %d\n\n", b);
	
	return ((colour.r << 16) | (colour.g << 8) | colour.b);
}

void	free_resources_2(t_data *data)
{
	int	tmp;
	int	index;

	tmp = data->cub->map_height;
	index = 0;
	while (tmp > 0)
	{
		free(data->cub->map[index]);
		tmp--;
		index++;
	}
	free(data->cub->south_texture);
	free(data->cub->north_texture);
	free(data->cub->west_texture);
	free(data->cub->east_texture);
	free(data->cub->map);
	free(data->cub);
	mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img);
	free(data->mlx->mlx_ptr);
	free(data->mlx->win_ptr);
	free(data->mlx);
	free(data);
}

void	free_resources(t_data *data)
{
	int	i;

	if (data)
	{
		i = 0;
		while (i < 4)
		{
			if (data->cub->textures[i])
			{
				mlx_destroy_image(data->mlx->mlx_ptr, data->cub->textures[i]);
				data->cub->textures[i] = NULL;
			}
			i++;
		}
		free(data->cub->textures);
		free(data->cub->textures_data);
		free_resources_2(data);
	}
}
