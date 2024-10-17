/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:40:50 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/17 18:24:13 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void move_forward(t_data *data)
{
  
    data->cub->x_pos_dec = data->cub->x_pos_dec - data->cub->x_dir_dec * SPEED_MOVE * (-1);
    data->cub->y_pos_dec = data->cub->y_pos_dec - data->cub->y_dir_dec * SPEED_MOVE * (-1);

   
    data->cub->x_pos_pixel = decimal_to_pixel(data, data->cub->x_pos_dec, X_PX);
    data->cub->y_pos_pixel = decimal_to_pixel(data, data->cub->y_pos_dec, Y_PX);

   
    data->cub->x_pos_ind = (int)data->cub->x_pos_dec;
    data->cub->y_pos_ind = (int)data->cub->y_pos_dec;

   
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;
    
    
    render_next_frame(data);
        
}

//I must calculate the new position in decimals, then convert it to pixels
void move_backward(t_data *data)
{   
   
    data->cub->x_pos_dec = data->cub->x_pos_dec - data->cub->x_dir_dec * SPEED_MOVE; //to me, this one should be *(-1), but for some reason it works on the other direction
    data->cub->y_pos_dec = data->cub->y_pos_dec - data->cub->y_dir_dec * SPEED_MOVE;

    
    data->cub->x_pos_pixel = decimal_to_pixel(data, data->cub->x_pos_dec, X_PX);
    data->cub->y_pos_pixel = decimal_to_pixel(data, data->cub->y_pos_dec, Y_PX);

   
    data->cub->x_pos_ind = (int)data->cub->x_pos_dec;
    data->cub->y_pos_ind = (int)data->cub->y_pos_dec;

    
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;

    
    render_next_frame(data);

}

void move_right(t_data *data)
{    
    double x_perp = data->cub->y_dir_dec;  
    double y_perp = -data->cub->x_dir_dec;

    double new_x = data->cub->x_pos_dec + (x_perp * SPEED_MOVE);
    double new_y = data->cub->y_pos_dec + (y_perp * SPEED_MOVE);

    // Verificar si la nueva posición es una pared
    if (data->cub->map[(int)new_y][(int)new_x] == '0') {
        data->cub->x_pos_dec = new_x;
        data->cub->y_pos_dec = new_y;
    }

    // Actualizar posiciones de píxeles
    data->cub->x_pos_pixel = decimal_to_pixel(data, data->cub->x_pos_dec, X_PX);
    data->cub->y_pos_pixel = decimal_to_pixel(data, data->cub->y_pos_dec, Y_PX);
    
    render_next_frame(data);
}

void move_left(t_data *data)
{
    double x_perp = data->cub->y_dir_dec;  
    double y_perp = -data->cub->x_dir_dec;

    double new_x = data->cub->x_pos_dec - (x_perp * SPEED_MOVE);
    double new_y = data->cub->y_pos_dec - (y_perp * SPEED_MOVE);

    // Verificar si la nueva posición es una pared
    if (data->cub->map[(int)new_y][(int)new_x] == '0') {
        data->cub->x_pos_dec = new_x;
        data->cub->y_pos_dec = new_y;
    }

    // Actualizar posiciones de píxeles
    data->cub->x_pos_pixel = decimal_to_pixel(data, data->cub->x_pos_dec, X_PX);
    data->cub->y_pos_pixel = decimal_to_pixel(data, data->cub->y_pos_dec, Y_PX);
    
    render_next_frame(data);
}

void update_direction_vector(t_data *data, int direction)
{
    // Actualizar el ángulo según la dirección
    if (direction == ROTATE_RIGHT) {
        data->cub->angle_degree += SPEED_ROTATE;  // Rota a la derecha (horario)
    } else if (direction == ROTATE_LEFT) {
        data->cub->angle_degree -= SPEED_ROTATE;  // Rota a la izquierda (antihorario)
    }

    // Ajustar el ángulo para que se mantenga dentro del rango de 0 a 360 grados
    data->cub->angle_degree = fmod(data->cub->angle_degree + 360, 360); // Esto siempre da un resultado positivo

    // Convertir grados a radianes
    angle_to_rad(data);

    // Actualizar el vector de dirección
    data->cub->x_dir_dec = cos(data->cub->angle_radian);
    data->cub->y_dir_dec = sin(data->cub->angle_radian);

    // Imprimir valores para depuración
    printf("Ángulo: %.2f grados, %.2f radianes\n", data->cub->angle_degree, data->cub->angle_radian);
    printf("Vector de dirección: x = %.2f, y = %.2f\n", data->cub->x_dir_dec, data->cub->y_dir_dec);
}


void rotate_right(t_data *data)
{
    update_direction_vector(data, ROTATE_RIGHT);

    // Actualiza la posición en el mapa
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;

    // Renderizar el siguiente frame
    render_next_frame(data);
}

void rotate_left(t_data *data)
{
    update_direction_vector(data, ROTATE_LEFT);

    // Actualiza la posición del "satélite"
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec) * DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec) * DISTANCE_BLUE_CIRCLE;

    // Renderizar el siguiente frame
    render_next_frame(data);
}

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
        
    if (keycode == ROTATE_LEFT)
    {
        // printf("Left arrow key pressed - Rotate LEFT\n");
        rotate_right(data);
    }

    if (keycode == ROTATE_RIGHT)
    {
        // printf("Right arrow key pressed - Rotate RIGHT\n");
        //Update player direction vector
        //Print direction vector
        rotate_left(data);
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
    mlx_hook(data->mlx->win_ptr, 17, 0, (int (*)(void *))close_program, data->mlx);//línea Javi

    mlx_hook(data->mlx->win_ptr, 2, 1L << 0, key_handler, data); //previous implementatioin, when key press/release was not handled
}
