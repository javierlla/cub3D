/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:14:32 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/15 20:27:06 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*int close_program(t_mlx *mlx)
{
    if (mlx && mlx->win_ptr)
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
    exit(EXIT_SUCCESS);
    return (0);
}

int handle_keypress(int keycode, t_mlx *mlx)
{
    if (keycode == 65307) // ESC boton 
        close_program(mlx);
    return (0);
}

void init_window(t_mlx *mlx)
{
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
    {
        exit_with_error("Failed to initialize mlx");
        free (mlx->mlx_ptr);
        free (mlx);
    }
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 800, 600, "Cub3D");
    if (!mlx->win_ptr)
        exit_with_error("Failed to create window");
    // evento 17 para cerrar con la "x"
    mlx_hook(mlx->win_ptr, 17, 0, (int (*)(void *))close_program, mlx);
    // Añadir un hook para cerrar con la tecla ESC (evento 2 para keypress)
    //usar 1L<<0 activa específicamente la máscara para el evento de KeyPress.
    mlx_hook(mlx->win_ptr, 2,  1L<<0, handle_keypress, mlx);
}

void mlx_loop_mine(t_mlx *mlx)
{
    mlx_loop(mlx->mlx_ptr);
}*/

int close_program(t_mlx *mlx)
{
    if (mlx && mlx->win_ptr)
    {
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
        mlx->win_ptr = NULL;
    }
    exit(EXIT_SUCCESS);
}

int handle_keypress(int keycode, t_mlx *mlx)
{
    if (keycode == 65307) // ESC botón
        close_program(mlx);
    return (0);
}

void init_window(t_mlx *mlx)
{
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
    {
        exit_with_error("Failed to initialize mlx");
        free(mlx->mlx_ptr);
        free(mlx);
    }
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, screenWidth, screenHeight, "Cub3D");
    if (!mlx->win_ptr)
        exit_with_error("Failed to create window");
        
    mlx->img = mlx_new_image(mlx->mlx_ptr, screenWidth, screenHeight);
    if (!mlx->img)
        exit_with_error("Failed to create image.\n");

    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
    if (!mlx->addr)
        exit_with_error("Failed to get image address.\n");

    /* 'x' closing button: evento 17 */
    mlx_hook(mlx->win_ptr, 17, 0, (int (*)(void *))close_program, mlx);

    /* 'ESC' */
    mlx_hook(mlx->win_ptr, 2, 1L<<0, handle_keypress, mlx);
    
}