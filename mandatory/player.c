/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:02:10 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/14 16:47:26 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

/*  Checks whether if x-y passed coordinate in map indicates
*   player's position or not.
*
*   Player's position is indicated with 'N', 'S', 'W', 'E'.
*/
int is_player_position(t_cub *cub, int x, int y)
{
    if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
        || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
        return (1);
    return (0);
}

void get_player_map_position(t_cub *cub)
{
    int x_map_index;
    int y_map_index;
    
    printf(BLUE"\n\n/*---------- get_player_map_position:----------\n"RESET_COLOUR);
    printf("Map info:\n");
    printf(" > Height (Y) = %d\n", cub->map_height);
    printf(" > Width (X) = can vary on each line\n");
    y_map_index = 0;
    while (y_map_index < cub->map_height) //each line of map
    {
        x_map_index = 0;
        while (is_map(cub, x_map_index, y_map_index))
        {
            if (is_player_position(cub, x_map_index, y_map_index))
            {
                cub->player_position.x = x_map_index + 1; //+1 as x starts from 0 (as map's index for iteration)
                cub->player_position.y = y_map_index + 1; //+1 as y starts from 0 (as map's index for iteration)
                cub->player_direction = cub->map[y_map_index][x_map_index];
                break;
            }
            x_map_index++;
        }
        y_map_index++;
    }
    printf(BLUE"\n > result:\n"RESET_COLOUR);
    printf("Player's position: x = %f, y = %f\n", cub->player_position.x, cub->player_position.y);
    printf("Player direction: %c\n", cub->player_direction);
    printf(BLUE"----------------------------------------------*/\n"RESET_COLOUR);
}
