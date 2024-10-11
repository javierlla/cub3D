/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_player_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:52:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/11 20:27:51 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
*   360 degrees    ------------------  2 * π radians
*   angle degree   ------------------  result radians
*/
float deg_to_rad(t_data *data)
{
    //printf("Before angle (DEGREE) = %f\n", angle);
    data->cub->player_direction_vector->angle_radian = data->cub->player_direction_vector->angle_degree * PI / 180;
    //printf("After angle (RADIANS)= %f\n", angle);
    return (data->cub->player_direction_vector->angle_radian);
}

/* We first set it in DEGREES */
void get_initial_angle(t_cub *cub)
{
    if(cub->initial_player_direction_in_map == 'N')
        cub->player_direction_vector->angle_degree = 90;
    if(cub->initial_player_direction_in_map == 'S')
        cub->player_direction_vector->angle_degree = 270;
    if(cub->initial_player_direction_in_map == 'W')
        cub->player_direction_vector->angle_degree = 180;
    if(cub->initial_player_direction_in_map == 'E')
        cub->player_direction_vector->angle_degree = 0;
    printf("Direction angle in degrees: %.2f\n", cub->player_direction_vector->angle_degree);
}

void angle_to_rad(t_data *data)
{
    data->cub->player_direction_vector->x = cos(deg_to_rad(data));
    data->cub->player_direction_vector->y = sin(deg_to_rad(data));
}

void set_player_direction_vector(t_data *data)
{
    printf(RED"> About player direction vector:\n"RESET_COLOUR);
	printf("Player direction: %c\n", data->cub->initial_player_direction_in_map);
    
    get_initial_angle(data->cub);
    angle_to_rad(data);
    
    printf("Player direction vector: x = %.2f, y = %.2f\n", data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
    printf(RED"----------------------------------------------*/\n");
}

void set_initial_satellite_pixel_in_window(t_data *data)
{
    data->cub->player_direction_vector->x_satellite_pixel = data->cub->player_position->x_pixel + (data->cub->player_direction_vector->x)*DISTANCE_BLUE_CIRCLE;
    data->cub->player_direction_vector->y_satellite_pixel = data->cub->player_position->y_pixel + (data->cub->player_direction_vector->y)*DISTANCE_BLUE_CIRCLE;
}

void set_player_position_2(t_data *data, int x_map_index, int y_map_index)
{
	            printf(MAGENTA"\n > set_player_position result (Position in 2D Map):\n"RESET_COLOUR);
    set_initial_index_in_2d_map(data->cub, x_map_index, y_map_index);
	            printf("Player's position (INDEX_2D_MAP): x = %d, y = %d\n", data->cub->player_position->x_index, data->cub->player_position->y_index);

    set_initial_player_direction(data->cub, x_map_index, y_map_index);
                //printf(RED"Player direction: %c\n"RESET_COLOUR, data->cub->initial_player_direction_in_map); //We set it now, but print if later in sset_player_directioin_vector, as it makes more sense
    
    /*Initial decimal and pixel refer to same info. Will be printed in set_initial_pixel_in_map function*/
    set_initial_decimal_in_2d_map(data->cub, x_map_index, y_map_index);
	            printf("Player's position (DECIMAL_2D_MAP): x = %.2f, y = %.2f\n", data->cub->player_position->x_decimal, data->cub->player_position->y_decimal);
    set_initial_pixel_in_window(data);
	            printf("Player's position (PIXELS_WINDOW): x = %d, y = %d\n", data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);
	            
                printf(BLUE"----------------------------------------------*/\n"RESET_COLOUR);
}

/* set_initial_pixel_in_map
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
    tmp_x_pixel = decimal_to_pixel(data->cub->player_position->x_decimal, X_WIDTH);
    tmp_y_pixel = decimal_to_pixel(data->cub->player_position->y_decimal, Y_HEIGHT);

    // printf(YELLOW"Before regla 3, x_pixel = %d\n"RESET_COLOUR, tmp_x_pixel);
    // printf(YELLOW"Before regla 3, y_pixel = %d\n"RESET_COLOUR, tmp_y_pixel);

    /* Taking into account 2D Map is located in a particular part of window, which starts in 
    (1720, 600) in whole window, rule of 3 must be implemented.*/
    data->cub->player_position->x_pixel = 1720 + tmp_x_pixel;
    data->cub->player_position->y_pixel = 600 + tmp_y_pixel;

    // printf(BLUE"regla 3, x_pixel = %d\n"RESET_COLOUR, data->cub->player_position->x_pixel);
    // printf(BLUE"regla 3, y_pixel = %d\n"RESET_COLOUR, data->cub->player_position->y_pixel);
    //my_mlx_pixel_put(data->mlx_map, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel, 0x00FF0000); //ez dogu inprimiduko ze oindiok initializau gabe dago punterua
}        

void set_player_position(t_data *data)
{
    int x_map_index;
    int y_map_index;
    
    printf(MAGENTA"set_player_position\n"RESET_COLOUR);
    printf("cub->map_height = %d\n", data->cub->map_height);
    
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
