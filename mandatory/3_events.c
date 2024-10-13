/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:40:50 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/13 16:27:16 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*  Index-decimal range: both x and y [0-21]
*   Pixel range: both x and y [0-840], defined in .h
*
*   21.00 ---------------- 840 px
*   Result ----------- (whatever)
*
*	Returns -1 = Error, not expected result
*/
float pixel_to_decimal_map(int pixel, enum width_or_height indicator)
{
	//printf("📍pixel_to_decimal_map | Before: pixel(int) = %d\n", pixel);
    if (indicator == X_WIDTH)
		return ((float)pixel * 21.00 / WIDTH_MAP); //instead of 21.00 it should be as a defined in .h as well ideally
	else if (indicator == Y_HEIGHT)
		return ((float)pixel * 21.00 / HEIGHT_MAP);//instead of 21.00 it should be as a defined in .h as well ideally
	else
		return (-1);
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
    
    // printf(MAGENTA"------------------------------ W - move_forward ------------------------------\n"RESET_COLOUR);
    // printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    // printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    
    
    /* Calculate new position: in pixels based on 2D Map Window's pixels*/
    data->cub->x_pos_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec) * SPEED_MOVE;
    data->cub->y_pos_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec) * SPEED_MOVE;

    /* Get decimal position updated */
    data->cub->x_pos_dec = pixel_to_decimal_map(data->cub->x_pos_pixel, X_WIDTH);
    data->cub->y_pos_dec = pixel_to_decimal_map(data->cub->y_pos_pixel, Y_HEIGHT);

    /* Get map index updated */
    data->cub->x_pos_ind = (int)data->cub->x_pos_dec;
    data->cub->y_pos_ind = (int)data->cub->y_pos_dec;

    /* Satellite position must be updated as well */
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;
    
    // printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->x_pos_dec, data->cub->x_pos_pixel, data->cub->y_pos_dec, data->cub->y_pos_pixel);
    
    render_next_frame(data);
        
    // printf(YELLOW"🧍Player info"RESET_COLOUR": Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->x_pos_dec, data->cub->y_pos_dec, data->cub->x_dir_dec, data->cub->y_dir_dec);
}

void move_backward(t_data *data)
{   
    // printf(MAGENTA"------------------------------ S - move_backward ------------------------------\n"RESET_COLOUR);
    // printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    // printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    /* Calculate new position: in pixels based on 2D Map Window's pixels*/
    data->cub->x_pos_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec) * SPEED_MOVE * (-1);
    data->cub->y_pos_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec) * SPEED_MOVE * (-1);

    /* Get decimal position updated */
    data->cub->x_pos_dec = pixel_to_decimal_map(data->cub->x_pos_pixel, X_WIDTH);
    data->cub->y_pos_dec = pixel_to_decimal_map(data->cub->y_pos_pixel, Y_HEIGHT);

    /* Satellite position must be updated as well */
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;

    // printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    
    render_next_frame(data);

    // printf(YELLOW"🧍Player info"RESET_COLOUR": Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->x_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}

void move_right(t_data *data)
{
    // printf(MAGENTA"------------------------------ W - move_forward ------------------------------\n"RESET_COLOUR);
    // printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    // printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    
    /* Calculate new position: in pixels based on 2D Map Window's pixels*/
    data->cub->x_pos_pixel = data->cub->x_pos_pixel + (data->cub->y_dir_dec) * SPEED_MOVE * (-1);
    data->cub->y_pos_pixel = data->cub->y_pos_pixel + (data->cub->x_dir_dec) * SPEED_MOVE;

    /* Get decimal position updated */
    data->cub->x_pos_dec = pixel_to_decimal_map(data->cub->x_pos_pixel, X_WIDTH);
    data->cub->y_pos_dec = pixel_to_decimal_map(data->cub->y_pos_pixel, Y_HEIGHT);
    // printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);


    /* Satellite position must be updated as well */
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;
    
    render_next_frame(data);
}

void move_left(t_data *data)
{
    // printf(MAGENTA"------------------------------ W - move_forward ------------------------------\n"RESET_COLOUR);
    // printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    // printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    /* Calculate new position: in pixels based on 2D Map Window's pixels*/
    data->cub->x_pos_pixel = data->cub->x_pos_pixel + (data->cub->y_dir_dec) * SPEED_MOVE;
    data->cub->y_pos_pixel = data->cub->y_pos_pixel + (data->cub->x_dir_dec) * SPEED_MOVE * (-1);

    /* Get decimal position updated */
    data->cub->x_pos_dec = pixel_to_decimal_map(data->cub->x_pos_pixel, X_WIDTH);
    data->cub->y_pos_dec = pixel_to_decimal_map(data->cub->y_pos_pixel, Y_HEIGHT);
    // printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    /* Satellite position must be updated as well */
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;
    
    render_next_frame(data);
}

void update_direction_vector(t_data *data, int direction)
{
    // printf(BLUE"update_direction_vector\n");
    // printf("> Before: Direction vector: x = %.2f, y = %.2f\n"RESET_COLOUR, data->cub->x_dir_dec, data->cub->y_dir_dec);
    
    /* #1 Update angle in degrees*/
    if (direction == ROTATE_RIGHT)
        data->cub->angle_degree += SPEED_ROTATE;
    else if (direction == ROTATE_LEFT)
        data->cub->angle_degree -= SPEED_ROTATE;
    
    /* #2 Update angle in radians */
    angle_to_rad(data);
    
    /* #3 Update direction vector */
    data->cub->x_dir_dec = cos(data->cub->angle_radian);
    data->cub->y_dir_dec = sin(data->cub->angle_radian);
    // printf("> After: Direction vector: x = %.2f, y = %.2f\n", data->cub->x_dir_dec, data->cub->y_dir_dec);
    
}

/* rotate_right updates player's direction vector by rotating to the right
*  where the player is looking at.
*
*  Also it is shown in 2d map visually.
*
*  data->cub->player_position->x_pixel already takes into account +1720 and +600
*  as it is the position in the 2D map window.
*/
void rotate_right(t_data *data)
{
    // printf("------------------------------ "YELLOW"Right arrow - rotate_right"RESET_COLOUR" ------------------------------\n");
    // printf("Before: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
    update_direction_vector(data, ROTATE_RIGHT);
    // printf("After: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    /* Show in 2D map */
    // printf(YELLOW">> Where to show satelite?\n"RESET_COLOUR);
    // printf(" Input 1 - Player position (DECIMAL): x = %.2f, y = %.2f\n", data->cub->player_position->x_decimal, data->cub->player_position->y_decimal);
    // printf(" Input 2 - Player position (PIXELS in 2D Map): x = %d, y = %d\n\n", data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);
    // printf(" Input 3 - Direction vector: x = %.2f, y = %.2f\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;
    
    render_next_frame(data);
}

/* rotate_right updates player's direction vector by rotating to the right
*  where the player is looking at.
*
*  Also it is shown in 2d map visually.*/
void rotate_left(t_data *data)
{
    // printf("------------------------------ "YELLOW"Left arrow - rotate_left"RESET_COLOUR" ------------------------------\n");
    // printf("Before: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
    update_direction_vector(data, ROTATE_LEFT);
    // printf("After: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    /* Show in 2D map */
    // printf(YELLOW">> Where to show satelite?\n"RESET_COLOUR);
    // printf(" Input 1 - Player position (DECIMAL): x = %.2f, y = %.2f\n", data->cub->player_position->x_decimal, data->cub->player_position->y_decimal);
    // printf(" Input 2 - Player position (PIXELS in 2D Map): x = %d, y = %d\n\n", data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);
    // printf(" Input 3 - Direction vector: x = %.2f, y = %.2f\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;
    
    render_next_frame(data);
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
	// printf("inside key_handler, keycode = %d\n", keycode);
    // if (keycode == ESC || keycode == CLOSE)
	// {
	// 	close_handler(mlx);
	// 	return (0);
	// }
    if (keycode == 65307) // ESC button
    {
        close_program(data->mlx); //should close_program not only destroy window, but also free memory?? destroy image??
        // close_program(data->mlx_map);
    }
	if (keycode == W_MOVE_FORWARD)
    {
        // printf("W key pressed - Move FORWARD\n");
        move_forward(data);
    }
	if (keycode == S_MOVE_BACKWARDS)
    {
        // printf("S key pressed - Move BACKWARDS\n");
        move_backward(data);
    }
	if (keycode == A_MOVE_LEFT)
    {
        // printf("S key pressed - Move LEFT\n");
        move_left(data);
    }
        
	if (keycode == D_MOVE_RIGHT)
    {
        // printf("D key pressed - Move RIGHT\n");
        move_right(data);
    }
        
    /* Se actualiza el vector de dirección */
    if (keycode == ROTATE_LEFT)
    {
        // printf("Left arrow key pressed - Rotate LEFT\n");
        rotate_left(data);
    }
    if (keycode == ROTATE_RIGHT)
    {
        // printf("Right arrow key pressed - Rotate RIGHT\n");
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

// void ft_events_init(t_mlx *mlx)
void ft_events_init(t_data *data)
{
    /* 'x' closing button: evento 17 */
    mlx_hook(data->mlx->win_ptr, 17, 0, (int (*)(void *))close_program, data->mlx);//línea Javi

    /*Defines which is the function that is going to take care of keys: key_handler
    * When key is pressed, it will be sent to key_handler.
    *   Aim: with 2 lines, both windows can get key presses and cub will be updated for both
    *------------------------------------------------------------------------------*/
    mlx_hook(data->mlx->win_ptr, 2, 1L << 0, key_handler, data); //previous implementatioin, when key press/release was not handled
    
    /* Flagmanagement to handle key press/release management.
    / New implementation based on xbasabe's input*/
    // mlx_hook(data->mlx_game->win_ptr, 2, 1L << 0, key_press, data);
	// mlx_hook(data->mlx_game->win_ptr, 3, 1L << 1, key_release, data);

    /*function 'move_player' is called in loop*/
    //mlx_loop_hook(data->mlx_game->mlx_ptr, move_player, data); 
    /*now move_player, but idea is to call to EVERYTHING function that will include (move, raycasting, rendering)*/
}