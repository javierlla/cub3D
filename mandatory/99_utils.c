/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:17:09 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/12 21:06:27 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char *dst;
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
    {
        dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}