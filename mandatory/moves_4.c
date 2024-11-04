/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:03:59 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 12:54:49 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	pixel_to_decimal_map(int pixel, enum e_width_or_height indicator)
{
	if (indicator == X_WIDTH)
		return ((float)pixel * 21.00 / WIDTH_MAP);
	else if (indicator == Y_HEIGHT)
		return ((float)pixel * 21.00 / HEIGHT_MAP);
	else
		return (-1);
}

int	is_map_limit(t_data *data, float tmp_x_2_check, float tmp_y_2_check)
{
	if (tmp_x_2_check < 0 || tmp_x_2_check > data->cub->map_width
		|| tmp_y_2_check < 0 || tmp_y_2_check > data->cub->map_height)
		return (1);
	return (0);
}
