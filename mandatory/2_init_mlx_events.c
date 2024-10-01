/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_mlx_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:58:24 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/01 12:35:06 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*    840 px -------------- 21.00 height-width
*  Result px -------------- (whatever) height-width
*
*   Right now as width and height are the same, we can use the same function.
*/
int decimal_to_pixel_map(float decimal)
{
    int px;

    printf("decimal = %.2f\n", decimal);
    px = decimal * 840 / 21;
    printf("px = %d\n", px);
    return (px);
}

/* Updates player position info stored in cub. Both mlx-s get data from 
*   cub. This means by updated cub directly, the info both mlx are getting
*    is updated.
*
*   When moving forward: (pixel language) x stays the same, y is decreased. Because (0,0) in pixels 
* starts up on the left and increases by going right/down on the window (pixel language)*/
void move_forward(t_data *data)
{
    /* To paint direction vector in while*/
    float tmp_x;
    float tmp_y;
    
    printf(MAGENTA"------------------------------ W - move_forward ------------------------------\n"RESET_COLOUR);
    printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    data->cub->player_position->y_pixel -= 1; //Decreases 1 pixel (minimum movement option in 2d map window);
    data->cub->player_position->y_decimal = pixel_to_decimal_map(data->cub->player_position->y_pixel, Y_HEIGHT);
    printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);
    
    //I can't see anything: too small
    //my_mlx_pixel_put(data->mlx_map, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel, 0x00FF0000); //As I don't manage to see it because of how small it is, I have used mlx_xpm_file_to_image.
    
    tmp_x = data->cub->player_position->x_pixel;
    tmp_y = data->cub->player_position->y_pixel;
    
    while((tmp_x <= 840 && tmp_x >= 0) && (tmp_y <= 840 && tmp_y >= 0))
    {
        //printf("Direction vector is painted: (%.2f, %.2f)\n", tmp_x, tmp_y);
        my_mlx_pixel_put(data->mlx_map, tmp_x, tmp_y, 0xFF0000);
        tmp_x += data->cub->player_direction_vector->x;
        tmp_y += data->cub->player_direction_vector->y;
    }
    
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size

    
    //printf(YELLOW"IMAGE_PTR = %p - put_each_wall (put_walls_map.c)\n"RESET_COLOUR, mlx_2->image_ptr);
    //printf(YELLOW"WIN_PTR = %p\n"RESET_COLOUR, mlx_2->win_ptr);
    //printf(YELLOW"MLX_PTR = %p\n"RESET_COLOUR, mlx_2->mlx_ptr);
    //BEFORE: mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, scale_x((int)data->cub->player_position->x_decimal), scale_y((int)data->cub->player_position->y_decimal)); //0,0 --> position where we're gonna put the image
    put_walls_in_map(data->mlx_map);
    relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    data->mlx_map->image_ptr = mlx_xpm_file_to_image(data->mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel); //0,0 --> position where we're gonna put the image
    
    
    //mlx_put_image_to_window(mlx_2->mlx_ptr, mlx_2->win_ptr, mlx_2->image_ptr, 5000, 5000); //0,0 --> position where we're gonna put the image
    

    printf(YELLOW"🧍Player info"RESET_COLOUR": Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->x_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}

// void move_backward(t_data *data)
// {
    
// }

void move_backward(t_data *data)
{
    float tmp_x;
    float tmp_y;
    
    printf(MAGENTA"------------------------------ S - move_backward ------------------------------\n"RESET_COLOUR);
    printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    data->cub->player_position->y_pixel += 1; // Aumentar el valor de y_pixel para moverse hacia abajo
    data->cub->player_position->y_decimal = pixel_to_decimal_map(data->cub->player_position->y_pixel, Y_HEIGHT);

    printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    tmp_x = data->cub->player_position->x_pixel;
    tmp_y = data->cub->player_position->y_pixel;
    
    while((tmp_x <= 840 && tmp_x >= 0) && (tmp_y <= 840 && tmp_y >= 0))
    {
        my_mlx_pixel_put(data->mlx_map, tmp_x, tmp_y, 0xFF0000);
        tmp_x -= data->cub->player_direction_vector->x;
        tmp_y -= data->cub->player_direction_vector->y;
    }

    put_walls_in_map(data->mlx_map);
    char *relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    int img_width, img_height;
    data->mlx_map->image_ptr = mlx_xpm_file_to_image(data->mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);

    printf(YELLOW"🧍Player info"RESET_COLOUR": Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->y_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}

void move_left(t_data *data)
{
    float tmp_x;
    float tmp_y;
    
    printf(MAGENTA"------------------------------ A - move_left ------------------------------\n"RESET_COLOUR);
    printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    data->cub->player_position->x_pixel -= 1; // Disminuir el valor de x_pixel para moverse hacia la izquierda
    data->cub->player_position->x_decimal = pixel_to_decimal_map(data->cub->player_position->x_pixel, X_WIDTH);

    printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    tmp_x = data->cub->player_position->x_pixel;
    tmp_y = data->cub->player_position->y_pixel;
    
    while((tmp_x <= 840 && tmp_x >= 0) && (tmp_y <= 840 && tmp_y >= 0))
    {
        my_mlx_pixel_put(data->mlx_map, tmp_x, tmp_y, 0xFF0000);
        tmp_x -= data->cub->player_direction_vector->y; // Cambiamos el vector para moverse horizontalmente
        tmp_y += data->cub->player_direction_vector->x;
    }

    put_walls_in_map(data->mlx_map);
    char *relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    int img_width, img_height;
    data->mlx_map->image_ptr = mlx_xpm_file_to_image(data->mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);

    printf(YELLOW"🧍Player info"RESET_COLOUR": Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->y_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}


/* rotate_right updates player's direction vector by rotating to the right
*  where the player is looking at.
*
*  Also it is shown in 2d map visually.*/
/*void rotate_right(t_data *data)
{
    printf("------------------------------ "YELLOW"Right arrow - rotate_right"RESET_COLOUR" ------------------------------\n");
    printf("Before: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    printf("After: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}*/

void rotate_right(t_data *data)
{
    printf("------------------------------ "YELLOW"Right arrow - rotate_right"RESET_COLOUR" ------------------------------\n");
    printf("Before: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    // Ángulo de rotación en radianes (90 grados)
    float angle = -PI / 180; // -1 grado en radianes para rotar a la derecha

    // Guardar la dirección actual
    float old_x = data->cub->player_direction_vector->x;
    float old_y = data->cub->player_direction_vector->y;

    // Calcular la nueva dirección después de rotar a la derecha
    data->cub->player_direction_vector->x = old_x * cos(angle) - old_y * sin(angle);
    data->cub->player_direction_vector->y = old_x * sin(angle) + old_y * cos(angle);

    printf("After: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}


void rotate_left(t_data *data)
{
    printf("------------------------------ "YELLOW"Left arrow - rotate_left"RESET_COLOUR" ------------------------------\n");
    printf("Before: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);

    float angle = PI / 180; // 1 grado en radianes

    float old_x = data->cub->player_direction_vector->x;
    float old_y = data->cub->player_direction_vector->y;

    // Calcular la nueva dirección después de rotar a la izquierda
    data->cub->player_direction_vector->x = old_x * cos(angle) - old_y * sin(angle);
    data->cub->player_direction_vector->y = old_x * sin(angle) + old_y * cos(angle);

    printf("After: Direction vector: (%.2f, %.2f)\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}


void move_right(t_data *data)
{
    float tmp_x;
    float tmp_y;
    
    printf(MAGENTA"------------------------------ D - move_right ------------------------------\n"RESET_COLOUR);
    printf("            |  x_decimal|  x_pixel  |  y_decimal  |  y_pixel  |\n");
    printf("> Before    |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    data->cub->player_position->x_pixel += 1; // Aumentar el valor de x_pixel para moverse hacia la derecha
    data->cub->player_position->x_decimal = pixel_to_decimal_map(data->cub->player_position->x_pixel, X_WIDTH);

    printf("> After     |  %.2f     |     %d    |     %.2f    |     %d    |\n", data->cub->player_position->x_decimal, data->cub->player_position->x_pixel, data->cub->player_position->y_decimal, data->cub->player_position->y_pixel);

    tmp_x = data->cub->player_position->x_pixel;
    tmp_y = data->cub->player_position->y_pixel;
    
    while((tmp_x <= 840 && tmp_x >= 0) && (tmp_y <= 840 && tmp_y >= 0))
    {
        my_mlx_pixel_put(data->mlx_map, tmp_x, tmp_y, 0xFF0000);
        tmp_x += data->cub->player_direction_vector->y; // Cambiamos el vector para moverse horizontalmente
        tmp_y -= data->cub->player_direction_vector->x;
    }

    put_walls_in_map(data->mlx_map);
    char *relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    int img_width, img_height;
    data->mlx_map->image_ptr = mlx_xpm_file_to_image(data->mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_map->mlx_ptr, data->mlx_map->win_ptr, data->mlx_map->image_ptr, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);

    printf(YELLOW"🧍Player info"RESET_COLOUR": Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->y_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
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
/*int key_handler(int keycode, t_data *data)
{
	printf("inside key_handler, keycode = %d\n", keycode);
    // if (keycode == ESC || keycode == CLOSE)
	// {
	// 	close_handler(mlx);
	// 	return (0);
	// }
	if (keycode == W_MOVE_FORWARD)
    {
        printf("W key pressed - Move FORWARD\n");
        move_forward(data);
    }
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
}*/

int key_handler(int keycode, t_data *data)
{
    printf("inside key_handler, keycode = %d\n", keycode);

    if (keycode == W_MOVE_FORWARD)
        move_forward(data);
    else if (keycode == S_MOVE_BACKWARDS)
        move_backward(data);
    else if (keycode == A_MOVE_LEFT)
        move_left(data);
    else if (keycode == D_MOVE_RIGHT)
        move_right(data);
    else if (keycode == ROTATE_LEFT)
    {
       // printf("Left arrow key pressed - Rotate LEFT\n");
        rotate_left(data);
    }
    else if (keycode == ROTATE_RIGHT)
        rotate_right(data);

    return (0);
}
