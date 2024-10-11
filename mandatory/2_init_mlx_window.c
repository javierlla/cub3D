/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_mlx_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:55:13 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/11 18:50:02 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_window(t_data *data)
{
    data->mlx->mlx_ptr = mlx_init();
    if (!data->mlx->mlx_ptr)
    {
        exit_with_error("Failed to initialize mlx");
        free (data->mlx->mlx_ptr);
        free (data->mlx);
    }

    /* Create New Window: mlx_new_window*/
    data->mlx->win_ptr = mlx_new_window(data->mlx->mlx_ptr, WIDTH_WINDOW, HEIGHT_WINDOW, "Cub3D");
    data->mlx->image_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH_WINDOW, HEIGHT_WINDOW);

    /* Get Address: whatever mlx_game of mlx_map, works for both */
    data->mlx->pixels_ptr = mlx_get_data_addr(data->mlx->image_ptr, &data->mlx->bpp, &data->mlx->line_len, &data->mlx->endian);
}