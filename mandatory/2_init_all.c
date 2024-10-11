/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:48:31 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/11 20:28:02 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_all_default (t_data *data)
{
    /* Set initial mlx_game*/
    data->mlx->mlx_ptr = NULL;
    data->mlx->win_ptr = NULL;
    data->mlx->mlx_connection = NULL;
    data->mlx->bpp = 0;
    data->mlx->endian = 0;
    data->mlx->line_len = 0;

    /* Set initial cub*/
    //data->cub->map = NULL; //already set in read_cub_file
    // data->cub->map_height = 0; //already set in read_cub_file
    data->cub->player_position = malloc(sizeof(t_coordinates));
    data->cub->player_position->x_index = 0;
    data->cub->player_position->x_decimal = 0;
    data->cub->player_position->x_pixel = 0;
    data->cub->player_position->y_index = 0;
    data->cub->player_position->y_decimal = 0;
    data->cub->player_position->y_pixel = 0;
    data->cub->initial_player_direction_in_map = 'N';
    data->cub->player_direction_vector = malloc(sizeof(t_float_x_y));
    data->cub->player_direction_vector->x = 0;
    data->cub->player_direction_vector->y = 0;
    data->cub->player_direction_vector->angle_degree = 0;
    data->cub->player_direction_vector->angle_radian = 0;
    data->cub->player_direction_vector->x_satellite_pixel = 0;
    data->cub->player_direction_vector->y_satellite_pixel = 0;

    data->cub->keyboard_flags = malloc(sizeof(t_keyboard_flags));
    data->cub->keyboard_flags->w_flag = 0;
    data->cub->keyboard_flags->a_flag = 0;
    data->cub->keyboard_flags->s_flag = 0;
    data->cub->keyboard_flags->d_flag = 0;
    data->cub->keyboard_flags->r_flag = 0;
    data->cub->keyboard_flags->l_flag = 0;

}

void init_all(t_data *data)
{
    init_all_default(data);	
    printf(">> init_all_default was "GREEN"successfully completed\n"RESET_COLOUR);
    
    /* Player's position is set in cub->map (x_index and y_index)*/
    set_player_position(data); //cub will be updated, mlx are sent so that my_mlx_pixel_put can be used
    set_player_direction_vector(data);
    set_initial_satellite_pixel_in_window(data);
                printf("Satellite's position (PIXELS_WINDOW): x = %d, y = %d\n", data->cub->player_direction_vector->x_satellite_pixel, data->cub->player_direction_vector->y_satellite_pixel);
    //printf("🧍Player info: Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->x_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
    
    /*Init_window: links cub to mlx*/
    init_window(data);
    ft_events_init(data);

    // printf(GREEN"Post INIT_ALL:--------------------------------\n"RESET_COLOUR);
    // printf("            | mlx_game | mlx_map |\n");
    // printf("x_index     |    %d       |    %d      |\n", data->mlx_game->cub->player_position->x_index, data->mlx_map->cub->player_position->x_index);
    // printf("x_decimal   |    %.2f    |    %.2f   |\n", data->mlx_game->cub->player_position->x_decimal, data->mlx_map->cub->player_position->x_decimal);
    // printf("x_pixel     |    %d      |    %d     |\n", data->mlx_game->cub->player_position->x_pixel, data->mlx_map->cub->player_position->x_pixel);
    // printf("y_index     |    %d      |    %d     |\n", data->mlx_game->cub->player_position->y_index, data->mlx_map->cub->player_position->y_index);
    // printf("y_decimal   |   %.2f    |   %.2f   |\n", data->mlx_game->cub->player_position->y_decimal, data->mlx_map->cub->player_position->y_decimal);
    // printf("y_pixel     |    %d      |    %d     |\n", data->mlx_game->cub->player_position->x_pixel, data->mlx_map->cub->player_position->x_pixel);

    /* See results: */
    //put_player_in_map(data); //As cub has already been linked to mlx_map in init_window, sending mlx_map as parameter should be enough
    // int x;
    // int y;

    // x = 0;
    // y = 0;
    
    // while (x < WIDTH_WINDOW)
    // {
    //     y = 0;
    //     while (y < HEIGHT_WINDOW)
    //     {
    //         my_mlx_pixel_put(data, x, y, 0x00FFFFCC);
    //         y++;
    //     }
    //     x++;
    // }
    
    render_initial(data);
}
