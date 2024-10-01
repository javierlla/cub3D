/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:02:10 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/22 14:34:03 by uxmancis         ###   ########.fr       */
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
    if (mlx_map->cub->initial_player_direction_in_map == 'N')
    {
        //printf("N - Player direction\n");
        return("./textures/others/North_Hannah.xpm");
    }
    else if(mlx_map->cub->initial_player_direction_in_map == 'S')
    {
        //printf("S - Player direction\n");
        return("./textures/others/South_Hannah.xpm");
    }
    else if(mlx_map->cub->initial_player_direction_in_map == 'E')
    {
        //printf("E - Player direction\n");
        return("./textures/others/East_Hannah.xpm");
    }
    else if(mlx_map->cub->initial_player_direction_in_map == 'W')
    {
        //printf("W - Player direction\n");
        return("./textures/others/West_Hannah.xpm");
    }
    else
        return(NULL);
}

void put_hannah_in_index(t_mlx *mlx_map)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size

    relative_path = get_path(mlx_map);  //según nora dauan begira, argazki desberdina
    // printf(YELLOW"relative_path = %s\n", relative_path);
    // printf("mlx_ptr = %p\n", mlx_map->mlx_ptr);
    // printf("win_ptr = %p\n", mlx_map->win_ptr);
    // printf("image_ptr = %p\n"RESET_COLOUR, mlx_map->image_ptr);
    mlx_map->image_ptr = mlx_xpm_file_to_image(mlx_map->mlx_ptr, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx_map->mlx_ptr, mlx_map->win_ptr, mlx_map->image_ptr, scale_x(mlx_map->cub->player_position->x_index), scale_y(mlx_map->cub->player_position->y_index)); //0,0 --> position where we're gonna put the image
}


// void put_red_dot_in_decimal(t_mlx *mlx_map)
// {
    
// }

void put_player_in_map(t_mlx *mlx_map)
{
    put_hannah_in_index(mlx_map);
    // put_red_dot_in_decimal(mlx_map);
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
        //printf(GREEN "Yes player's here\n"RESET_COLOUR);
        return (1);
    }
    return (0);
}

void set_initial_index_in_2d_map(t_cub *cub, int x_map_index, int y_map_index)
{
    printf("set_initial_index_checeker, x_indexPTR = %p, y_indexPTR = %p\n", &cub->player_position->x_index, &cub->player_position->y_index);
    cub->player_position->x_index = x_map_index;
    cub->player_position->y_index = y_map_index;
}

void set_initial_player_direction(t_cub *cub, int x_map_index, int y_map_index)
{
    cub->initial_player_direction_in_map = cub->map[y_map_index][x_map_index];
}

void set_initial_decimal_in_2d_map(t_cub *cub, int x_map_index, int y_map_index)
{
    cub->player_position->x_decimal = (float)x_map_index + 0.5; //1 box = 1 unit. Position begins we set it in the middle of the [ x ] index position they're set at the beginning.
    cub->player_position->y_decimal = (float)y_map_index + 0.5;
}

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
	printf("📍pixel_to_decimal_map | Before: pixel(int) = %d\n", pixel);
    if (indicator == X_WIDTH)
		return ((float)pixel * 21.00 / WIDTH_MAP); //instead of 21.00 it should be as a defined in .h as well ideally
	else if (indicator == Y_HEIGHT)
		return ((float)pixel * 21.00 / HEIGHT_MAP);//instead of 21.00 it should be as a defined in .h as well ideally
	else
		return (-1);
}

void set_initial_pixel_in_map(t_data *data)
{
    data->cub->player_position->x_pixel = decimal_to_pixel(data->cub->player_position->x_decimal, X_WIDTH);
    data->cub->player_position->y_pixel = decimal_to_pixel(data->cub->player_position->y_decimal, Y_HEIGHT);
    //my_mlx_pixel_put(data->mlx_map, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel, 0x00FF0000); //ez dogu inprimiduko ze oindiok initializau gabe dago punterua
}

