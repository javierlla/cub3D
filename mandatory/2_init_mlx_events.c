/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_mlx_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:58:24 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/05 21:00:24 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void put_dot_in_map(t_data *data)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size

    relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    data->mlx_map->image_ptr = mlx_xpm_file_to_image(data->mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel); //0,0 --> position where we're gonna put the image
}

/*    840 px -------------- 21.00 height-width
*  Result px -------------- (whatever) height-width
*
*   Right now as width and height are the same, we can use the same function.
*/ //ESTO NADAAAAAAAAAAAAAAAAAA, DECIMAL A PIXEL PERDEMOS PRECISIÓN, PERDEMOSS EL FLOAT. AL REVÉS
//SIEMPRE!!! DE PIXXEL A DECIMAL. LO DEJO AQUÍ PARA FUTURE SELF DE UXU/JAVI.
// int decimal_to_pixel_map(float decimal)
// {
//     int px;

//     printf("decimal = %.2f\n", decimal);
//     px = decimal * 840 / 21;
//     printf("px = %d\n", px);
//     return (px);
// }

void put_satellite_in_map(t_data *data)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size

    relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    data->mlx_map->image_ptr = mlx_xpm_file_to_image(data->mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, data->cub->player_direction_vector->x_satellite_pixel, data->cub->player_direction_vector->y_satellite_pixel); //0,0 --> position where we're gonna put the image
}

void put_circle_around_player(t_data *data)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size
    int i;
    
    /* Vector de dirección del círculo azul 360 grados */
    float direction_vector_x;
    float direction_vector_y;

    int put_blue_x_px;
    int put_blue_y_px;

    relative_path = "./textures/others/blue_dot.xpm";
    
    i = 0;
    while (i < 360)
    {
        direction_vector_x = cos((i*PI)/180); //i * PI / 180 = deg to rad
        direction_vector_y = sin((i*PI)/180);//i * PI / 180 = deg to rad

        put_blue_x_px = data->cub->player_position->x_pixel + (direction_vector_x)*10;
        put_blue_y_px = data->cub->player_position->y_pixel + (direction_vector_y)*10;
        
        data->mlx_map->image_ptr = mlx_xpm_file_to_image(data->mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
        mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, put_blue_x_px, put_blue_y_px);
        i++;
    }
}

/* Satellite_case:
*       0: No satellite
*       1: Satellite
**/
void render_update_2d_map(t_data *data, int satellite_case)
{
    printf(GREEN"render_update_2d_map\n"RESET_COLOUR);
    mlx_clear_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr);
    mlx_destroy_image(data->mlx_map->mlx_ptr, data->mlx_map->image_ptr);
    //free(data->mlx_map->image_ptr); //Liberar la imagen anterior
    data->mlx_map->image_ptr = mlx_new_image(data->mlx_map->mlx_ptr, HEIGHT_MAP, WIDTH_MAP); //Crear nueva imagen
    
    /* Draw in image */
    put_walls_in_map(data->mlx_map); //Pintar las paredes
    put_dot_in_map(data); //Pintar al jugador: red dot
    put_circle_around_player(data); //Pintar al jugador: circle
    if (satellite_case == 1)
        put_satellite_in_map(data); //Pintar satélite (dirección)

    /* Put image to window*/
    mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, 0, 0); //0,0 --> position where we're gonna put the image
}


/* Updates player position info stored in cub. Both mlx-s get data from 
*   cub. This means by updated cub directly, the info both mlx are getting
*    is updated.
*
*   When moving forward: (pixel language) x stays the same, y is decreased. Because (0,0) in pixels 
* starts up on the left and increases by going right/down on the window (pixel language)*/
void move_forward(t_data *data)
{
    /* To paint direction vector in while - to small to see anything*/
    // float tmp_x;
    // float tmp_y;
    
    printf(MAGENTA"------------------------------ W - move_forward ------------------------------\n"RESET_COLOUR);
    printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    data->cub->player_position->y_pixel -= 1; //Decreases 1 pixel (minimum movement option in 2d map window);
    data->cub->player_position->y_decimal = pixel_to_decimal_map(data->cub->player_position->y_pixel, Y_HEIGHT);
    printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    
    render_update_2d_map(data, 0);
        
    printf(YELLOW"🧍Player info"RESET_COLOUR": Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->x_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}

void move_backward(t_data *data)
{
    /* To paint direction vector in while - to small to see anything*/
    // float tmp_x;
    // float tmp_y;
    
    printf(MAGENTA"------------------------------ W - move_forward ------------------------------\n"RESET_COLOUR);
    printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    data->cub->player_position->y_pixel += 1; //Decreases 1 pixel (minimum movement option in 2d map window);
    data->cub->player_position->y_decimal = pixel_to_decimal_map(data->cub->player_position->y_pixel, Y_HEIGHT);
    printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    
    
    render_update_2d_map(data, 0);
    
    //mlx_put_image_to_window(mlx_2->mlx_ptr, mlx_2->win_ptr, mlx_2->image_ptr, 5000, 5000); //0,0 --> position where we're gonna put the image
    

    printf(YELLOW"🧍Player info"RESET_COLOUR": Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->x_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}

void move_right(t_data *data)
{
    printf(MAGENTA"------------------------------ W - move_forward ------------------------------\n"RESET_COLOUR);
    printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    data->cub->player_position->x_pixel += 1; //Decreases 1 pixel (minimum movement option in 2d map window);
    data->cub->player_position->x_decimal = pixel_to_decimal_map(data->cub->player_position->y_pixel, Y_HEIGHT);
    printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    render_update_2d_map(data, 0);
}

void move_left(t_data *data)
{
    printf(MAGENTA"------------------------------ W - move_forward ------------------------------\n"RESET_COLOUR);
    printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    data->cub->player_position->x_pixel -= 1; //Decreases 1 pixel (minimum movement option in 2d map window);
    data->cub->player_position->x_decimal = pixel_to_decimal_map(data->cub->player_position->y_pixel, Y_HEIGHT);
    printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    render_update_2d_map(data, 0);
}

void update_direction_vector(t_data *data, int direction)
{
    /* #1 Update angle in degrees*/
    if (direction == ROTATE_RIGHT)
        data->cub->player_direction_vector->angle_degree -= 1;
    else if (direction == ROTATE_LEFT)
        data->cub->player_direction_vector->angle_degree += 1;
    
    /* #2 Update angle in radians */
    angle_to_rad(data);
    
    /* #3 Update direction vector */
    data->cub->player_direction_vector->x = cos(data->cub->player_direction_vector->angle_radian);
    data->cub->player_direction_vector->y = sin(data->cub->player_direction_vector->angle_radian);
    
    
    // float tmp_x;
    // float tmp_y;
    
    // tmp_x = player_direction_vector->x;
    // tmp_y = player_direction_vector->y;
    
    // if (direction == ROTATE_RIGHT)
    // {
    //     player_direction_vector->x = tmp_x * cos(ROTATE_ANGLE) - tmp_y * sin(ROTATE_ANGLE);
    //     player_direction_vector->y = tmp_x * sin(ROTATE_ANGLE) + tmp_y * cos(ROTATE_ANGLE);
    // }
    // else if (direction == ROTATE_LEFT)
    // {
    //     player_direction_vector->x = tmp_x * cos(-ROTATE_ANGLE) - tmp_y * sin(-ROTATE_ANGLE);
    //     player_direction_vector->y = tmp_x * sin(-ROTATE_ANGLE) + tmp_y * cos(-ROTATE_ANGLE);
    // }
}



/* rotate_right updates player's direction vector by rotating to the right
*  where the player is looking at.
*
*  Also it is shown in 2d map visually.*/
void rotate_right(t_data *data)
{
    printf("------------------------------ "YELLOW"Right arrow - rotate_right"RESET_COLOUR" ------------------------------\n");
    printf("Before: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
    update_direction_vector(data, ROTATE_RIGHT);
    printf("After: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    /* Show in 2D map */
    printf(YELLOW">> Where to show satelite?\n"RESET_COLOUR);
    // char *relative_path;
    // int img_width; //We store here image size
    // int img_height;//We store here image size

    // float tmp_x_dir; //Where to put satelite? (vector dirección)
    // float tmp_y_dir;//Where to put satelite? (vector dirección)
    
    printf(" Input 1 - Player position (DECIMAL): x = %.2f, y = %.2f\n", data->cub->player_position->x_decimal, data->cub->player_position->y_decimal);
    printf(" Input 2 - Player position (PIXELS in 2D Map): x = %d, y = %d\n\n", data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);
    printf(" Input 3 - Direction vector: x = %.2f, y = %.2f\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    data->cub->player_direction_vector->x_satellite_pixel = data->cub->player_position->x_pixel + (data->cub->player_direction_vector->x)*10;
    data->cub->player_direction_vector->y_satellite_pixel = data->cub->player_position->y_pixel + (data->cub->player_direction_vector->y)*10;
    
    render_update_2d_map(data, 1);
    
    // tmp_x_dir = data->cub->player_position->x_pixel + data->cub->player_direction_vector->x;
    // tmp_y_dir = data->cub->player_position->y_pixel + data->cub->player_direction_vector->y;
    
    
    // printf("Satellite position (DECIMAL): x = %.2f, y = %.2f\n", tmp_x_dir, tmp_y_dir);
    // put_walls_in_map(data->mlx_map);
    // relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    // data->mlx_map->image_ptr = mlx_xpm_file_to_image(data->mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    // mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, tmp_x_dir, tmp_y_dir); //0,0 --> position where we're gonna put the image
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
// int	key_handler(int keycode, t_mlx *mlx)
int key_handler(int keycode, t_data *data)
{
	printf("inside key_handler, keycode = %d\n", keycode);
    // if (keycode == ESC || keycode == CLOSE)
	// {
	// 	close_handler(mlx);
	// 	return (0);
	// }
    if (keycode == 65307) // ESC button
    {
        close_program(data->mlx_game); //should close_program not only destroy window, but also free memory?? destroy image??
        close_program(data->mlx_map);
    }
	if (keycode == W_MOVE_FORWARD)
    {
        printf("W key pressed - Move FORWARD\n");
        move_forward(data);
    }
	if (keycode == S_MOVE_BACKWARDS)
    {
        printf("S key pressed - Move BACKWARDS\n");
        move_backward(data);
    }
	if (keycode == A_MOVE_LEFT)
    {
        printf("S key pressed - Move LEFT\n");
        move_left(data);
    }
        
	if (keycode == D_MOVE_RIGHT)
    {
        printf("D key pressed - Move RIGHT\n");
        move_right(data);
    }
        

    /* Se actualiza el vector de dirección */
    if (keycode == ROTATE_LEFT)
        printf("Left arrow key pressed - Rotate LEFT\n");
    if (keycode == ROTATE_RIGHT)
    {
        printf("Right arrow key pressed - Rotate RIGHT\n");
        //Update player direction vector
        //Print direction vector
        rotate_right(data);
    }
	//ft_render(mlx); //FP: Future Problem
	// printf(GREEN"After each KEY_HANDLER call:--------------------------------\n"RESET_COLOUR);
    // printf("            | mlx_game   |  mlx_map  |\n");
    // printf("x_index     |    %d       |    %d      |\n", data->mlx_game->cub->player_position->x_index, data->mlx_map->cub->player_position->x_index);
    // printf("x_decimal   |    %.2f    |    %.2f   |\n", data->mlx_game->cub->player_position->x_decimal, data->mlx_map->cub->player_position->x_decimal);
    // printf("x_pixel     |    %d      |    %d     |\n", data->mlx_game->cub->player_position->x_pixel, data->mlx_map->cub->player_position->x_pixel);
    // printf("y_index     |    %d      |    %d     |\n", data->mlx_game->cub->player_position->y_index, data->mlx_map->cub->player_position->y_index);
    // printf("y_decimal   |   %.2f    |   %.2f   |\n", data->mlx_game->cub->player_position->y_decimal, data->mlx_map->cub->player_position->y_decimal);
    // printf("y_pixel     |    %d      |    %d     |\n", data->mlx_game->cub->player_position->x_pixel, data->mlx_map->cub->player_position->x_pixel);
    return (0);
}

/* Keyboard is pressed and according flags are set to 1.
*  As a consequence, the player will move.
*----------------------------------------------------------*/
int	key_press(int keycode, t_data *data)
{
	printf("keypress | keycode = %d\n", keycode);
    // if (keycode == 65307)
	// {
	// 	mlx_destroy_image(g->mlx, g->render->img_ptr);
	// 	mlx_destroy_window(g->mlx, g->mlx_win);
	// 	exit(EXIT_SUCCESS);
	// }
    if (keycode == 65307) // ESC boton
    {
        close_program(data->mlx_game); //should close_program not only destroy window, but also free memory?? destroy image??
        close_program(data->mlx_map);
    }
	if (keycode != ROTATE_RIGHT && keycode != ROTATE_LEFT && keycode != W_MOVE_FORWARD
		&& keycode != A_MOVE_LEFT && keycode != D_MOVE_RIGHT && keycode != S_MOVE_BACKWARDS)
		return (1);
	else if (keycode == ROTATE_RIGHT)
		data->cub->keyboard_flags->r_flag = 1;
	else if (keycode == ROTATE_LEFT)
		data->cub->keyboard_flags->l_flag = 1;
	else if (keycode == W_MOVE_FORWARD)
		data->cub->keyboard_flags->w_flag = 1;
	else if (keycode == A_MOVE_LEFT)
		data->cub->keyboard_flags->a_flag = 1;
	else if (keycode == D_MOVE_RIGHT)
		data->cub->keyboard_flags->d_flag = 1;
	else if (keycode == S_MOVE_BACKWARDS)
		data->cub->keyboard_flags->s_flag = 1;
	return (keycode);
}

/* Keyboard is pressed and according flags are set to 0.
*  As a consequence, the player won't move until the key is pressed again.
*----------------------------------------------------------*/
int	key_release(int keycode, t_data *data)
{
	printf("keyrelease | keycode = %d\n", keycode);
    if (keycode != ROTATE_RIGHT && keycode != ROTATE_LEFT && keycode != W_MOVE_FORWARD
		&& keycode != A_MOVE_LEFT && keycode != D_MOVE_RIGHT && keycode != S_MOVE_BACKWARDS)
		return (1);
	else if (keycode == ROTATE_RIGHT)
		data->cub->keyboard_flags->r_flag = 0;
	else if (keycode == ROTATE_LEFT)
		data->cub->keyboard_flags->l_flag = 0;
	else if (keycode == W_MOVE_FORWARD)
		data->cub->keyboard_flags->w_flag = 0;
	else if (keycode == A_MOVE_LEFT)
		data->cub->keyboard_flags->a_flag = 0;
	else if (keycode == D_MOVE_RIGHT)
		data->cub->keyboard_flags->d_flag = 0;
	else if (keycode == S_MOVE_BACKWARDS)
		data->cub->keyboard_flags->s_flag = 0;
	return (keycode);
}

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
    // mlx_hook(data->mlx_game->win_ptr, 2,  1L<<0, handle_keypress, data->mlx_game); //No more needed, now handled inside key_press
    // mlx_hook(data->mlx_map->win_ptr, 2,  1L<<0, handle_keypress, data->mlx_map);

    /*Defines which is the function that is going to take care of keys: key_handler
    * When key is pressed, it will be sent to key_handler.
    *   Aim: with 2 lines, both windows can get key presses and cub will be updated for both
    *------------------------------------------------------------------------------*/
    mlx_hook(data->mlx_game->win_ptr, 2, 1L << 0, key_handler, data); //previous implementatioin, when key press/release was not handled
    //mlx_key_hook(data->mlx_game->win_ptr, &key_handler, data); //previous implementatioin, when key press/release was not handled
    //mlx_key_hook(data->mlx_map->win_ptr, &key_handler, data); //previous implementatioin, when key press/release was not handled
    
    /* Flagmanagement to handle key press/release management.
    / New implementation based on xbasabe's input*/
    // mlx_hook(data->mlx_game->win_ptr, 2, 1L << 0, key_press, data);
	// mlx_hook(data->mlx_game->win_ptr, 3, 1L << 1, key_release, data);

    /*function 'move_player' is called in loop*/
    mlx_loop_hook(data->mlx_game->mlx_ptr, move_player, data); 
    /*now move_player, but idea is to call to EVERYTHING function that will include (move, raycasting, rendering)*/
}