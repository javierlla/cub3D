/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:02:10 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/16 14:33:15 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Returns relative path to use in order to get a different player image
*  to be shown in the map, depending on its direction.
*
*  There will be 4 Hannahs: North_Hannah, South_Hannah, West_Hannah, East_Hannah
**/
char *get_path(t_mlx *mlx_map)
{
    if (mlx_map->cub->player_direction == 'N')
    {
        printf("N - Player direction\n");
        return("./textures/others/North_Hannah.xpm");
    }
    else if(mlx_map->cub->player_direction == 'S')
    {
        printf("S - Player direction\n");
        return("./textures/others/South_Hannah.xpm");
    }
    else if(mlx_map->cub->player_direction == 'E')
    {
        printf("E - Player direction\n");
        return("./textures/others/East_Hannah.xpm");
    }
    else if(mlx_map->cub->player_direction == 'W')
    {
        printf("W - Player direction\n");
        return("./textures/others/West_Hannah.xpm");
    }
    else
        return(NULL);
}

void put_player_in_map(t_mlx *mlx_map)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size

    relative_path = get_path(mlx_map);  //según nora dauan begira, argazki desberdina
    printf(YELLOW"relative_path = %s\n", relative_path);
    printf("mlx_ptr = %p\n", mlx_map->mlx_ptr);
    printf("win_ptr = %p\n", mlx_map->win_ptr);
    printf("image_ptr = %p\n"RESET_COLOUR, mlx_map->image_ptr);
    mlx_map->image_ptr = mlx_xpm_file_to_image(mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx_map->mlx_ptr, mlx_map->win_ptr, mlx_map->image_ptr, scale_x(mlx_map->cub->player_position.x_index), scale_y(mlx_map->cub->player_position.y_index)); //0,0 --> position where we're gonna put the image
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
        printf(GREEN "Yes player's here\n"RESET_COLOUR);
        return (1);
    }
    return (0);
}
void init_player_position(t_cub *cub)
{
    int x_map_index;
    int y_map_index;
    
    y_map_index = 0;
    while (y_map_index < cub->map_height)
    {
        x_map_index = 0;
        while (is_map(cub, x_map_index, y_map_index))
        {
            if (is_player_position(cub, x_map_index, y_map_index))
            {
                // Inicializa la posición del jugador con los índices
                cub->player_position.x_index = x_map_index;
                cub->player_position.y_index = y_map_index;
                cub->player_direction = cub->map[y_map_index][x_map_index];
                
                // Inicializa el offset en 0 al comenzar
                cub->player_position.offset_x = 0.0;
                cub->player_position.offset_y = 0.0;
                
                // Calcula la posición decimal inicial (sin movimiento)
                calculate_decimal_position(&cub->player_position);

                break;
            }
            x_map_index++;
        }
        y_map_index++;
    }
    
    // Imprimir posición inicial del jugador
    printf(BLUE"\n > init_player_position result:\n"RESET_COLOUR);
    printf("Player's position (INDEX): x = %d, y = %d\n", cub->player_position.x_index, cub->player_position.y_index);
    printf("Player's position (DECIMAL): x = %.2f, y = %.2f\n", cub->player_position.x_decimal, cub->player_position.y_decimal);
    printf("Player direction: %c\n", cub->player_direction);
    printf(BLUE"----------------------------------------------*/\n"RESET_COLOUR);
}
