/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:35:13 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:20:41 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_trimmed_len(char *str)
{
	int	start;
	int	len_trimmed_str;

	start = find_first_non_space(str);
	len_trimmed_str = 0;
	while (str[start] != '\0')
	{
		len_trimmed_str++;
		start++;
	}
	return (len_trimmed_str);
}

int	get_index_start_trimmed(char *str)
{
	int	len_str;
	int	i;
	int	start;

	len_str = ft_strlen(str);
	i = 0;
	while (len_str > 0)
	{
		while (ft_isspace(str[i]) && str[i] != '\0')
		{
			i++;
			len_str--;
		}
		if (len_str > 0)
		{
			start = i;
			break ;
		}
	}
	return (start);
}

bool	are_there_any_whitespaces_at_the_beginning(char *str)
{
	if (ft_isspace(str[0]))
		return (true);
	return (false);
}

char	*copy_trimmed_str(char *str, int start_trimmed, int len_trimmed_str)
{
	int		i;
	char	*trimmed_str;

	trimmed_str = malloc(sizeof(char) * (len_trimmed_str + 1));
	if (!trimmed_str)
		exit_with_error("malloc failed");
	i = 0;
	while (str[start_trimmed] != '\0')
	{
		trimmed_str[i] = str[start_trimmed];
		i++;
		start_trimmed++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}

char	*trim_space_index(char *str)
{
	int		len_trimmed_str;
	int		start_trimmed;
	bool	whitespaces_beginning;
	char	*trimmed_str;

	whitespaces_beginning = are_there_any_whitespaces_at_the_beginning(str);
	if (whitespaces_beginning)
	{
		len_trimmed_str = get_trimmed_len(str);
		start_trimmed = get_index_start_trimmed(str);
		trimmed_str = copy_trimmed_str(str, start_trimmed, len_trimmed_str);
		free(str);
		return (trimmed_str);
	}
	return (str);
}
