/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 11:48:31 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/05 16:21:33 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_all_default (t_data *data)
{
    /* Set initial mlx_game*/
    data->mlx_game->mlx_ptr = NULL;
    data->mlx_game->win_ptr = NULL;
    data->mlx_game->mlx_connection = NULL;
    // data->mlx_game->pixels_ptr = NULL; //already set in my_mlx_new_image - says chatgpt
    // data->mlx_game->image_ptr = NULL; //already set in my_mlx_new_image - says chatgpt
    data->mlx_game->bpp = 0;
    data->mlx_game->endian = 0;
    data->mlx_game->line_len = 0;
    data->mlx_game->cub = data->cub;

    /* Set initial mlx_map*/
    data->mlx_map->mlx_ptr = NULL;
    data->mlx_map->win_ptr = NULL;
    data->mlx_map->mlx_connection = NULL;
    // data->mlx_map->pixels_ptr = NULL; //already set in my_mlx_new_image - says chatgpt
    // data->mlx_map->image_ptr = NULL;  //already set in my_mlx_new_image - says chatgpt
    // data->mlx_map->bpp = 0; //already set in my_mlx_new_image - says chatgpt
    data->mlx_map->endian = 0;
    // data->mlx_map->line_len = 0; //already set in my_mlx_new_image - says chatgpt
    data->mlx_map->cub = data->cub;

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

    data->cub->keyboard_flags = malloc(sizeof(t_keyboard_flags));
    data->cub->keyboard_flags->w_flag = 0;
    data->cub->keyboard_flags->a_flag = 0;
    data->cub->keyboard_flags->s_flag = 0;
    data->cub->keyboard_flags->d_flag = 0;
    data->cub->keyboard_flags->r_flag = 0;
    data->cub->keyboard_flags->l_flag = 0;
    
    // data->cub->textures = malloc(sizeof(t_textures));
    // data->cub->textures->north = NULL;
    // data->cub->textures->south = NULL;
    // data->cub->textures->west = NULL;
    // data->cub->textures->east = NULL;
}

void init_all(t_data *data)
{
    init_all_default(data);	
    printf(">> init_all_default was "GREEN"successfully completed\n"RESET_COLOUR);
    
    /* Player's position is set in cub->map (x_index and y_index)*/
    set_player_position(data); //cub will be updated, mlx are sent so that my_mlx_pixel_put can be used
    set_player_direction_vector(data);
    //printf("🧍Player info: Position (%.2f, %.2f), Direction vector (%.2f, %.2f)\n", data->cub->player_position->x_decimal, data->cub->player_position->x_decimal, data->cub->player_direction_vector->x, data->cub->player_direction_vector->y);
    
    /*Init_window: links cub to mlx*/
    init_window(data->mlx_game, GAME, data->cub);
    init_window(data->mlx_map, MAP, data->cub);
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
    put_player_in_map(data->mlx_map); //As cub has already been linked to mlx_map in init_window, sending mlx_map as parameter should be enough
}
