/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_mlx_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:57:25 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/06 12:52:36 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Javi's
int close_program(t_mlx *mlx)
{
    if (mlx && mlx->win_ptr)
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
    exit(EXIT_SUCCESS);
    return (0);
}

//Javi's
/* No more needed, not it's inside keypress*/
// int handle_keypress(int keycode, t_mlx *mlx)
// {
//     if (keycode == 65307) // ESC boton 
//         close_program(mlx);
//     return (0);
// }

/*   Keeps application running, continuously listening for events
*    like key presses, mouse movements, window close requests, etc.
*-------------------------------------------------------------------*/
void mlx_loop_mine(t_mlx *mlx)
{
    mlx_loop(mlx->mlx_ptr);
}

/* close_handler: ESC or x (window) are pressed
*   from: Uxu's fractol
*/
int	close_handler(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_connection, mlx->mlx_ptr);
	mlx_destroy_window(mlx->mlx_connection, mlx->win_ptr);
	free(mlx->mlx_connection);
	exit(EXIT_SUCCESS);
}