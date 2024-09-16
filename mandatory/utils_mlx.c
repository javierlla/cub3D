/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:48:11 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/14 16:47:08 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* my_mlx_pixel_put: Puts a pixel in our image.*/
void	my_mlx_pixel_put(t_mlx *mlx, t_integer_position pixel_window, int colour)
{
	char	*dst;

	dst = mlx->pixels_ptr + (pixel_window.y * mlx->line_len + pixel_window.x * (mlx->bpp / 8));
	*(unsigned int *)dst = colour;
}

void ft_handle_pixel(t_coordinates window, t_cub *cub, int colour)
{
    (void)window;
    (void)cub;
    (void)colour;
}