/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file_utils_80.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:23:36 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 18:27:22 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_last(t_data *data)
{
	int	index;
	int	len_file_type_content;
	int	map_already_found;

	len_file_type_content = ft_strlen(data->cub->file_lines_type);
	map_already_found = 0;
	index = len_file_type_content - 1;
	while (len_file_type_content > 0)
	{
		if (data->cub->file_lines_type[index] == 'M')
			map_already_found = 1;
		if (map_already_found == 0
			&& (data->cub->file_lines_type[index] == 'T'
				|| data->cub->file_lines_type[index] == 'C'))
			return (0);
		index--;
		len_file_type_content--;
	}
	return (1);
}
