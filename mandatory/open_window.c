/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:14:32 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/15 16:17:31 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

/* key_handler:
*		Input: keycode generated by mlx_mouse_hook.
*		
*		Works as an index for keyboard-related events.
*		Depending on the keycode (event identifier) received, 
*		key_handler will decide how the program should act
*		by calling to a function or to another.
*	
*		Managed events: 
*			53 : ESC
*			123 : Key Right
*			124 : Key Left
*			125 : Key Down
*			126 : Key Up
*/
int	key_handler(int keycode, t_mlx *mlx)
{
	printf("inside key_handler, keycode = %d\n", keycode);
    (void)mlx;
    // if (keycode == ESC || keycode == CLOSE)
	// {
	// 	close_handler(mlx);
	// 	return (0);
	// }
	if (keycode == W_MOVE_FORWARD)
        printf("W key pressed - Move FORWARD\n");
	if (keycode == S_MOVE_BACKWARDS)
        printf("S key pressed - Move BACKWARDS\n");
	if (keycode == A_MOVE_LEFT)
        printf("S key pressed - Move LEFT\n");
	if (keycode == D_MOVE_RIGHT)
        printf("D key pressed - Move RIGHT\n");
    if (keycode == ROTATE_LEFT)
        printf("Left arrow key pressed - Rotate LEFT\n");
    if (keycode == ROTATE_RIGHT)
    {
        printf("Left arrow key pressed - Rotate RIGHT\n");
    }
	//ft_render(mlx); //FP: Future Problem
	return (0);
}

//Javi's
int close_program(t_mlx *mlx)
{
    if (mlx && mlx->win_ptr)
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
    exit(EXIT_SUCCESS);
    return (0);
}

//Javi's
int handle_keypress(int keycode, t_mlx *mlx)
{
    if (keycode == 65307) // ESC boton 
        close_program(mlx);
    return (0);
}

void ft_events_init(t_mlx *mlx)
{
    /* 'x' closing button: evento 17 */
    mlx_hook(mlx->win_ptr, 17, 0, (int (*)(void *))close_program, mlx);//línea Javi
    //mlx_hook(mlx->win_ptr, 17, (1L << 17), &close_program, mlx); //también funciona, opción Uxue

    /* ESC */
    // Añadir un hook para cerrar con la tecla ESC (evento 2 para keypress)
    //usar 1L<<0 activa específicamente la máscara para el evento de KeyPress.
    mlx_hook(mlx->win_ptr, 2,  1L<<0, handle_keypress, mlx);

    /*Defines which is the function that is going to take care of keys: key_handler
    * When key is pressed, it will be sent to key_handler.
    *------------------------------------------------------------------------------*/
    mlx_key_hook(mlx->win_ptr, &key_handler, mlx);
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
    else
        printf("IMAGE_PTR successfully created = %p\n", mlx->image_ptr);
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
    // mlx->
    my_mlx_new_window(mlx, game_or_map);
    my_mlx_new_image(mlx, game_or_map);

    /* Get Address: whatever mlx_game of mlx_map, works for both */
    mlx->pixels_ptr = mlx_get_data_addr(mlx->image_ptr, &mlx->bpp, &mlx->line_len, &mlx->endian);

    /* Tenemos 1 instancia de cub. Hacemos que ambas ventanas (mlx) apunten a esta misma única instancia de cub*/
    mlx->cub = cub;
    
    /* Initialize events: key presses*/
    ft_events_init(mlx);

    if (game_or_map == MAP)
    {
        put_walls_in_map(mlx);
    }
    //mlx->cub = &cub;
}

/*   Keeps application running, continuously listening for events
*    like key presses, mouse movements, window close requests, etc.
*-------------------------------------------------------------------*/
void mlx_loop_mine(t_mlx *mlx)
{
    mlx_loop(mlx->mlx_ptr);
}

void init_all(t_mlx *mlx_game, t_mlx *mlx_map, t_cub *cub)
{
    /* Player's position is set in cub->map (x_index and y_index)*/
    init_player_position(cub);
    
    /*Init_window: links cub to mlx*/
    init_window(mlx_game, GAME, cub);
    init_window(mlx_map, MAP, cub);

    /* See results: */
    put_player_in_map(mlx_map); //As cub has already been linked to mlx_map in init_window, sending mlx_map as parameter should be enough
}
