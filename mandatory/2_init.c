/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:43:44 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/12 20:40:42 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*  Index-decimal range: both x and y [0-21]
*   Pixel range: both x and y [0-840], defined in .h
*
*   21.00 ---------------- 840
*   (whatever) ----------- result
*
*	Returns -1 = Error, not expected result
*/
int decimal_to_pixel(float decimal, enum width_or_height indicator)
{
	if (indicator == X_WIDTH)
		return (decimal * WIDTH_MAP / 21.00); //instead of 21.00 it should be as a defined in .h as well ideally
	else if (indicator == Y_HEIGHT)
		return (decimal * HEIGHT_MAP / 21.00);//instead of 21.00 it should be as a defined in .h as well ideally
	else
		return (-1);
}

/* set_initial_pixel_in_window
*
*     *****************
*     *****************
*     *****************
*     *****************
*     *****************
*     **********MAPMAPM
*     **********APMAPMA
*     **********PMAPMAP
*
*     MAP starts in (1720, 600) in whole window
*
*     That's why we need to sum 1720 and 600 to the pixel position
*     in order to get the pixel position in the whole window.
*/
void set_initial_pixel_in_window(t_data *data)
{
    int tmp_x_pixel;
    int tmp_y_pixel;

    
    /* If 2D Map were a single window itself, the pixel positions would be the following: */
    tmp_x_pixel = decimal_to_pixel(data->cub->x_pos_dec, X_WIDTH);
    tmp_y_pixel = decimal_to_pixel(data->cub->y_pos_dec, Y_HEIGHT);

    // printf(YELLOW"Before regla 3, x_pixel = %d\n"RESET_COLOUR, tmp_x_pixel);
    // printf(YELLOW"Before regla 3, y_pixel = %d\n"RESET_COLOUR, tmp_y_pixel);

    /* Taking into account 2D Map is located in a particular part of window, which starts in 
    (1720, 600) in whole window, rule of 3 must be implemented.*/
    data->cub->x_pos_pixel = 1720 + tmp_x_pixel;
    data->cub->y_pos_pixel = 600 + tmp_y_pixel;

    // printf(BLUE"regla 3, x_pixel = %d\n"RESET_COLOUR, data->cub->player_position->x_pixel);
    // printf(BLUE"regla 3, y_pixel = %d\n"RESET_COLOUR, data->cub->player_position->y_pixel);
    //my_mlx_pixel_put(data->mlx_map, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel, 0x00FF0000); //ez dogu inprimiduko ze oindiok initializau gabe dago punterua
}    

void set_initial_decimal_in_2d_map(t_cub *cub, int x_map_index, int y_map_index)
{
    cub->x_pos_dec = (float)x_map_index + 0.5; //1 box = 1 unit. Position begins we set it in the middle of the [ x ] index position they're set at the beginning.
    cub->y_pos_dec = (float)y_map_index + 0.5;
}

void set_initial_player_direction(t_cub *cub, int x_map_index, int y_map_index)
{
    cub->direction = cub->map[y_map_index][x_map_index];
}

void set_initial_index_in_2d_map(t_cub *cub, int x_map_index, int y_map_index)
{
    //printf("set_initial_index_checeker, x_indexPTR = %p, y_indexPTR = %p\n", &cub->player_position->x_index, &cub->player_position->y_index);
    cub->x_pos_ind = x_map_index;
    cub->y_pos_ind = y_map_index;
}

void set_player_position_2(t_data *data, int x_map_index, int y_map_index)
{
	printf(MAGENTA"set_player_position result (Position in 2D Map):\n"RESET_COLOUR);
    set_initial_index_in_2d_map(data->cub, x_map_index, y_map_index);
	printf("> Player's position (INDEX_2D_MAP): x = %d, y = %d\n", data->cub->x_pos_ind, data->cub->y_pos_ind);

    set_initial_player_direction(data->cub, x_map_index, y_map_index);
    printf("> Player direction: %c\n"RESET_COLOUR, data->cub->direction); //We set it now, but print if later in sset_player_directioin_vector, as it makes more sense
    
    // /*Initial decimal and pixel refer to same info. Will be printed in set_initial_pixel_in_map function*/
    set_initial_decimal_in_2d_map(data->cub, x_map_index, y_map_index);
	printf("> Player's position (DECIMAL_2D_MAP): x = %.2f, y = %.2f\n", data->cub->x_pos_dec, data->cub->y_pos_dec);
    
    set_initial_pixel_in_window(data);
	printf("> Player's position (PIXELS_WINDOW): x = %d, y = %d\n", data->cub->x_pos_pixel, data->cub->y_pos_pixel);
	            
    //printf(BLUE"----------------------------------------------*/\n"RESET_COLOUR);
}

/*  Checks whether if x-y passed coordinate in map indicates
*   player's position or not.
*
*   Player's position is indicated with 'N', 'S', 'W', 'E'.
*/
int is_player_position(t_cub *cub, int x, int y)
{
    if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
        || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
    {
        //printf(GREEN "Yes player's here\n"RESET_COLOUR);
        return (1);
    }
    return (0);
}

/* Checks whether if x-y passed as parameter
*  are part of map.
*----------------------------------------------------------*/
int is_map(t_cub *cub, int x, int y)
{
    if (cub->map[y][x] == '1' || cub->map[y][x] == '0'
        || cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
        || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
        return (1);
    return (0);
}

void set_player_position(t_data *data)
{
    int x_map_index;
    int y_map_index;
    
    //printf(MAGENTA"set_player_position\n"RESET_COLOUR);
    //printf("cub->map_height = %d\n", data->cub->map_height);
    
    y_map_index = 0;
    while (y_map_index < data->cub->map_height)
    {
        x_map_index = 0;
        while (is_map(data->cub, x_map_index, y_map_index))
        {
            if (is_player_position(data->cub, x_map_index, y_map_index))
            {
                set_player_position_2(data, x_map_index, y_map_index);
                break;
            }
            x_map_index++;
        }
        y_map_index++;
    }
}

void init_all_default(t_data *data)
{
    /* Player's position */
    // data->cub->x_pos_dec = 0; //DO NOT SET TO 0, AS IT WILL BE SET LATER >> OTHERWISE STRANGE VISUALIZATION
    // data->cub->y_pos_dec = 0; //DO NOT SET TO 0, AS IT WILL BE SET LATER >> OTHERWISE STRANGE VISUALIZATION
    data->cub->x_pos_ind = 0;
    data->cub->y_pos_ind = 0;

    /* Direction vector */
    // data->cub->x_dir_dec = 0; //DO  NOT SET TO 0,  AS IT WILL BE SET LATER >> OTHERWISE STRANGE VISUALIZATION
    // data->cub->y_dir_dec = 0; //DO NOT SET TO 0, AS IT WILL BE SET LATER >> OTHERWISE STRANGE VISUALIZATION

    /* Initial direction */
    data->cub->direction = 'X';
    data->cub->angle_degree = 0;
    data->cub->angle_radian = 0;
    data->cub->x_satellite_pixel = 0;
    data->cub->y_satellite_pixel = 0;
    
}

/*
*   360 degrees    ------------------  2 * π radians
*   angle degree   ------------------  result radians
*/
float deg_to_rad(t_data *data)
{
    //printf("Before angle (DEGREE) = %f\n", angle);
    data->cub->angle_radian = data->cub->angle_degree * PI / 180;
    //printf("After angle (RADIANS)= %f\n", angle);
    return (data->cub->angle_radian);
}

/* We first set it in DEGREES */
void get_initial_angle(t_data *data)
{
    if(data->cub->direction == 'N')
        data->cub->angle_degree = 90;
    if(data->cub->direction == 'S')
        data->cub->angle_degree = 270;
    if(data->cub->direction == 'W')
        data->cub->angle_degree = 180;
    if(data->cub->direction == 'E')
        data->cub->angle_degree = 0;
    printf("Direction angle in degrees: %.2f\n", data->cub->angle_degree);
}

void angle_to_rad(t_data *data)
{
    data->cub->x_dir_dec = cos(deg_to_rad(data));
    data->cub->y_dir_dec = sin(deg_to_rad(data));
}

void set_player_direction_vector(t_data *data)
{
    printf(RED"> About player direction vector:\n"RESET_COLOUR);
	printf("Player direction: %c\n", data->cub->direction);
    printf("BEFORE - Player direction vector: x = %.2f, y = %.2f\n", data->cub->x_dir_dec, data->cub->y_dir_dec);
    
    get_initial_angle(data);
    angle_to_rad(data);
    
    printf("AFTER - Player direction vector: x = %.2f, y = %.2f\n", data->cub->x_dir_dec, data->cub->y_dir_dec);
    printf(RED"----------------------------------------------*/\n");
}

void set_initial_satellite_pixel_in_window(t_data *data)
{
    data->cub->x_satellite_pixel = data->cub->x_pos_pixel + (data->cub->x_dir_dec)*DISTANCE_BLUE_CIRCLE;
    data->cub->y_satellite_pixel = data->cub->y_pos_pixel + (data->cub->y_dir_dec)*DISTANCE_BLUE_CIRCLE;
}

void init_all(t_data *data)
{
    printf("BEFORE - Player direction vector: x = %.2f, y = %.2f\n", data->cub->x_dir_dec, data->cub->y_dir_dec);
    init_all_default(data);

    set_player_position(data);
    //set_player_direction_vector(data); //not necessary for now, managed in validate_player_position function
    set_initial_satellite_pixel_in_window(data);
    printf("Satellite's position (PIXELS_WINDOW): x = %d, y = %d\n", data->cub->x_satellite_pixel, data->cub->y_satellite_pixel);
    
    init_window(data->mlx);
    ft_events_init(data);
}