/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:44:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:54:10 by jllarena         ###   ########.fr       */
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
