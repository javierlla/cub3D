/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:08:00 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/14 12:15:23 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_render(t_cub *cub, t_mlx *mlx)
{
    t_coordinates window;

    (void)cub;
    (void)mlx;
    
    /*From left to right in the window*/
    window.x = 0;
    while (window.x < WIDTH_WINDOW)
    {
        window.y = 0;
        while (window.y < HEIGHT_WINDOW)
        {
            //ft_handle_pixel(window, cub);
            //get_player_map_position(cub); //cub->player_position.x and cub->player_position.y are assigned
            //my_mlx_pixel_put(mlx, window, 0x0000FF);
            window.y++;
        }
        window.x++;
    }
}
