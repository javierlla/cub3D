/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:48:11 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/21 18:05:56 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* my_mlx_pixel_put: Puts a pixel in our image.*/
void	my_mlx_pixel_put(t_mlx *mlx, int x_pixel, int y_pixel, int colour)
{
	char	*dst;

    // printf(RED"mlx->pixels_ptr = %p\n", mlx->pixels_ptr);
    // printf("mlx->line_len = %d\n", mlx->line_len);
    // printf("mlx->bpp = %d\n", mlx->bpp);
    // printf("x_pixel = %d\n", x_pixel);
    // printf("y_pixel = %d\n"RESET_COLOUR, y_pixel);
	dst = mlx->pixels_ptr + (y_pixel * mlx->line_len + x_pixel * (mlx->bpp / 8));
	*(unsigned int *)dst = colour;
}

void ft_handle_pixel(t_coordinates window, t_cub *cub, int colour)
{
    (void)window;
    (void)cub;
    (void)colour;
}