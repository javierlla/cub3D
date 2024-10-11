/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:08:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/11 19:00:57 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
*   Returns x = x pixel position where image must be displayed
*   in 2d map in the window (mlx):
*
*   Window dimensions are defined in cub3d.h:
*       - HEIGHT_WINDOW = 1440
*       - WIDTH_WINDOW = 2560
*
*   Map dimensions are defined in cub3d.h:
*       - HEIGHT_MAP = 840
*       - WIDTH_MAP = 840
*
*   Map I'm using for use case: cheese_maze
*
*   cheese_maze dimensions: 21 (height) x 21 (width)
*
*   Right now image is not being resized. Just using 40x40 
*   smallest possibility Canva is allowing to us
*   Focusing on resizing could be considered one project finished
*   if still time before evaluations.
*
*   Why do we do '+40'? 40 is the size of a wall. We are hardcoding
*   it because of the image size we're using. Ideal would be resizing.
*
*/
int scale_x(/*t_mlx *mlx_2, */int x_index) //2d map
{
    int x;
    
    //printf("x_index = %d, ", x_index);
    x = 1720;
    while (x_index)
    {
        x += 40;
        x_index--;
    }
    //printf("x = %d\n", x);
    return(x);
}


/*  scale_y
*
*   The initial position of the map in the window is in the following
*   coordinates: (1720, 600)
*           x = WIDTH_WINDOW - WIDTH_MAP = 2560 - 840 = 1720    (x = 1720)
*           y = HEIGHT_WINDOW - HEIGHT_MAP = 1440 - 840 = 600    (y = 600)
*/
int scale_y(int y_index)
{
    int y;
    
    y = 600;
    //printf("y_index = %d, ", y_index);
    while (y_index)
    {
        y += 40;
        y_index--;
    }
    //printf("y = %d\n", y);
    return(y);
}

void put_each_wall(t_data *data, int x_index, int y_index)
{
    char *relative_path;
    int img_width; //40px width
    int img_height;//40px height
    void *img_wall;

    relative_path = "./textures/others/1_wall_smallest_40x40px.xpm";
    //printf(BLUE"img_width = %d, img_height = %d\n"RESET_COLOUR, img_width, img_height);
    img_wall = mlx_xpm_file_to_image(data->mlx->mlx_ptr, relative_path, &img_width, &img_height);
    if (!img_wall)
        printf(RED"Error: img is NULL\n"RESET_COLOUR);
    //printf(YELLOW"IMAGE_PTR = %p - put_each_wall (put_walls_map.c)\n"RESET_COLOUR, mlx_2->image_ptr);
    //printf(YELLOW"WIN_PTR = %p\n"RESET_COLOUR, mlx_2->win_ptr);
    //printf(YELLOW"MLX_PTR = %p\n"RESET_COLOUR, mlx_2->mlx_ptr);
    mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_wall, scale_x(x_index), scale_y(y_index)); //0,0 --> position where we're gonna put the image
    //mlx_put_image_to_window(mlx_2->mlx_ptr, mlx_2->win_ptr, mlx_2->image_ptr, 5000, 5000); //0,0 --> position where we're gonna put the image
}

/* New version */

/* put_walls_in_map
*
*   It's the #1 step to visualize 2d map in window  
*
*   The funcion iterates through 2d map .cub input file and calls put_each_wall
*   function to display each wall when '1' found.
*/
void put_walls_in_map(t_data *data)
{
    int y_nb_of_boxes; //Map Height
    int x_index;
    int y_index;

    y_nb_of_boxes = data->cub->map_height;
    //printf(MAGENTA"y_nb_of_boxes = %d\n", y_nb_of_boxes);¡
    
    /* Iterate through each line of 2d map*/
    y_index = 0;
    while (y_nb_of_boxes > 0)
    {
        x_index = 0;
        while (is_map(data->cub, x_index, y_index))
        {
            //printf(BLUE"Let's see Map[%d][%d] = %d\n"RESET_COLOUR, x_index, y_index, mlx_2->cub->map[x_index][y_index]);
            if (data->cub->map[x_index][y_index] == '1')
                put_each_wall(data, x_index, y_index);
            //else
                //printf(RED"doesn't enter here = NO WALL\n"RESET_COLOUR);
            x_index++;
        }
        //printf("------------------next line in 2d map ----------\n");
        y_index++;
        y_nb_of_boxes--;
    }
    printf(GREEN"finished visualizing walls in 2d map\n"RESET_COLOUR);
}
