/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:17:09 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/28 12:03:45 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < SCREENWIDTH && y >= 0 && y < SCREENHEIGHT)
	{
		dst = data->mlx->addr + (y * data->mlx->line_length
				+ x * (data->mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
