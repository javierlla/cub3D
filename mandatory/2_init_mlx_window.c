/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_mlx_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:55:13 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/22 13:22:12 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void ft_events_init(t_mlx *mlx)
void ft_events_init(t_data *data)
{
    /* 'x' closing button: evento 17 */
    mlx_hook(data->mlx_game->win_ptr, 17, 0, (int (*)(void *))close_program, data->mlx_game);//línea Javi
    mlx_hook(data->mlx_map->win_ptr, 17, 0, (int (*)(void *))close_program, data->mlx_map);//línea Javi
    //mlx_hook(mlx->win_ptr, 17, (1L << 17), &close_program, mlx); //también funciona, opción Uxue

    /* ESC */
    // Añadir un hook para cerrar con la tecla ESC (evento 2 para keypress)
    //usar 1L<<0 activa específicamente la máscara para el evento de KeyPress.
    mlx_hook(data->mlx_game->win_ptr, 2,  1L<<0, handle_keypress, data->mlx_game);
    mlx_hook(data->mlx_map->win_ptr, 2,  1L<<0, handle_keypress, data->mlx_map);

    /*Defines which is the function that is going to take care of keys: key_handler
    * When key is pressed, it will be sent to key_handler.
    *   Aim: with 2 lines, both windows can get key presses and cub will be updated for both
    *------------------------------------------------------------------------------*/
    mlx_key_hook(data->mlx_game->win_ptr, &key_handler, data);
    mlx_key_hook(data->mlx_map->win_ptr, &key_handler, data);
}

/*  Initializes window with different size (height & width) depending
*   on wether if window is for Cub3D game window (mlx_game) or
*   for maze map window (mlx_map).
*/
void my_mlx_new_window(t_mlx *mlx, enum window_type game_or_map)
{
    //printf(GREEN"my_mlx_new_window\n");
    mlx->win_ptr = NULL;
    if (game_or_map == GAME)
        mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, HEIGHT_WINDOW, WIDTH_WINDOW, "Cub3D");
    else if (game_or_map == MAP)
        mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, HEIGHT_MAP, WIDTH_MAP, "Map - Debugging purposes");
    if (!mlx->win_ptr)
        exit_with_error("Failed to create window\n");
}

/*  Initializes image with different size (height & width) depending
*   on wether if image is for Cub3D game window (mlx_game) or
*   for maze map window (mlx_map).
*/
void my_mlx_new_image(t_mlx *mlx, enum window_type game_or_map)
{
    //printf("image_ptr = %p\n", mlx->image_ptr);
    mlx->image_ptr = NULL;
    if (game_or_map == GAME)
        mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, HEIGHT_WINDOW, WIDTH_WINDOW);
    else if (game_or_map == MAP)
        mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, HEIGHT_MAP, WIDTH_MAP);
    if (!mlx->image_ptr)
        exit_with_error("Failed to create image\n");
    //else
        //printf("IMAGE_PTR successfully created = %p\n", mlx->image_ptr);
    //printf(MAGENTA"my_mlx_new_image\n");
}

void init_window(t_mlx *mlx, enum window_type game_or_map, t_cub *cub)
{
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
    {
        exit_with_error("Failed to initialize mlx");
        free (mlx->mlx_ptr);
        free (mlx);
    }

    /* Create New Window: mlx_new_window*/
    my_mlx_new_window(mlx, game_or_map);
    my_mlx_new_image(mlx, game_or_map);

    /* Get Address: whatever mlx_game of mlx_map, works for both */
    mlx->pixels_ptr = mlx_get_data_addr(mlx->image_ptr, &mlx->bpp, &mlx->line_len, &mlx->endian);
    //printf(YELLOW"mlx->pixels_ptr = %p\n"RESET_COLOUR, mlx->pixels_ptr);

    /* Tenemos 1 instancia de cub. Hacemos que ambas ventanas (mlx) apunten a esta misma única instancia de cub*/
    mlx->cub = cub;
    
    /* Initialize events: key presses*/
    // ft_events_init(mlx);

    if (game_or_map == MAP)
    {
        put_walls_in_map(mlx);
    }
    //mlx->cub = &cub;
}