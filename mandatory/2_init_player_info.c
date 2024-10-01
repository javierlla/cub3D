/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_player_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:52:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/22 13:47:48 by uxmancis         ###   ########.fr       */
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
    else if(cub->initial_player_direction_in_map == 'S')
        cub->player_direction_vector->angle_degree = 270;
    else if(cub->initial_player_direction_in_map == 'W')
        cub->player_direction_vector->angle_degree = 180;
    else if(cub->initial_player_direction_in_map == 'E')
        cub->player_direction_vector->angle_degree = 0;
    else
        return;
}

void update_direction_vector(t_data *data)
{
    data->cub->player_direction_vector->x = cos(deg_to_rad(data));
    data->cub->player_direction_vector->y = sin(deg_to_rad(data));
}

void set_player_direction_vector(t_data *data)
{
    get_initial_angle(data->cub);
    update_direction_vector(data);
    //printf(RED"Player direction vector: x = %.2f, y = %.2f\n"RESET_COLOUR, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
}

void set_player_position_2(t_data *data, int x_map_index, int y_map_index)
{
	printf(MAGENTA"\n > set_player_position result (Position in 2D Map):\n"RESET_COLOUR);
    set_initial_index_in_2d_map(data->cub, x_map_index, y_map_index);
	printf("Player's position (INDEX_2D_MAP): x = %d, y = %d\n", data->cub->player_position->x_index, data->cub->player_position->y_index);
    set_initial_player_direction(data->cub, x_map_index, y_map_index);
	printf("Player direction: %c\n", data->cub->initial_player_direction_in_map);

    /*Initial decimal and pixel refer to same info. Will be printed in set_initial_pixel_in_map function*/
    set_initial_decimal_in_2d_map(data->cub, x_map_index, y_map_index);
	printf("Player's position (DECIMAL_2D_MAP): x = %.2f, y = %.2f\n", data->cub->player_position->x_decimal, data->cub->player_position->y_decimal);
    set_initial_pixel_in_map(data);
	printf("Player's position (PIXELS_2D_MAP): x = %d, y = %d\n", data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);
	printf(BLUE"----------------------------------------------*/\n"RESET_COLOUR);
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
