/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:20:01 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/15 21:53:05 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void render_sky_and_floor(t_data *data)
{
    unsigned int floor_color = data->cub->floor_color;
    unsigned int ceiling_color = data->cub->ceiling_color;
	int x;
    int y = 0;
    
    while (y < screenHeight / 2) 
	{
        x = 0;
        while (x < screenWidth)
		{
            my_mlx_pixel_put(data, x, y, ceiling_color);
            x++;
        }
        y++;
    }
    while (y < screenHeight)
	{
        x = 0;
        while (x < screenWidth)
		{
            my_mlx_pixel_put(data, x, y, floor_color);
            x++;
        }
        y++;
    }
}


void render_update_game(t_data *data)
{
    render_sky_and_floor(data);
    raycast(data);

    if (data->mlx->mlx_ptr && data->mlx->win_ptr)
    {
        mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, data->mlx->img, 0, 0);
    }
}

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
    // printf(YELLOW"IMAGE_PTR = %p - put_each_wall (put_walls_map.c)\n"RESET_COLOUR, data->mlx->img);
    // printf(YELLOW"WIN_PTR = %p\n"RESET_COLOUR, data->mlx->win_ptr);
    // printf(YELLOW"MLX_PTR = %p\n"RESET_COLOUR,data->mlx->mlx_ptr);
    
    // printf("x_index = %d, y_index = %d\n", x_index, y_index);
    // printf("result_x = %d, result_y = %d\n", , );
    
    mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_wall, scale_x(x_index), scale_y(y_index)); //0,0 --> position where we're gonna put the image
    //mlx_put_image_to_window(mlx_2->mlx_ptr, mlx_2->win_ptr, mlx_2->image_ptr, 5000, 5000); //0,0 --> position where we're gonna put the image
}

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
    // printf(GREEN"finished visualizing walls in 2d map\n"RESET_COLOUR);
}

void put_dot_in_map(t_data *data)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size
    void *img_dot;

    
    // printf(BLUE"put_dot_in_map | player's position in 2D Map, x_pixel = %d, y_pixel = %d\n"RESET_COLOUR, data->cub->x_pos_pixel, data->cub->y_pos_pixel);
    
    relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    img_dot = mlx_xpm_file_to_image(data->mlx->mlx_ptr, relative_path, &img_width, &img_height);
    if (!img_dot)
        printf(RED"Error: img is NULL\n"RESET_COLOUR);
    mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_dot, data->cub->x_pos_pixel, data->cub->y_pos_pixel); //0,0 --> position where we're gonna put the image
}

void put_circle_around_player(t_data *data)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size
    int i;
    void *img_circle;
    
    /* Vector de dirección del círculo azul 360 grados */
    float direction_vector_x;
    float direction_vector_y;

    int put_blue_x_px;
    int put_blue_y_px;

    relative_path = "./textures/others/blue_dot.xpm";
    
    i = 0;
    while (i < 360)
    {
        direction_vector_x = cos((i*PI)/180); //i * PI / 180 = deg to rad
        direction_vector_y = sin((i*PI)/180);//i * PI / 180 = deg to rad

        put_blue_x_px = data->cub->x_pos_pixel + (direction_vector_x) * DISTANCE_BLUE_CIRCLE;
        put_blue_y_px = data->cub->y_pos_pixel + (direction_vector_y) * DISTANCE_BLUE_CIRCLE;
        
        img_circle = mlx_xpm_file_to_image(data->mlx->mlx_ptr, relative_path, &img_width, &img_height);
        mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_circle, put_blue_x_px, put_blue_y_px);
        i++;
    }
}

void put_satellite_in_map(t_data *data)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size
    void *img_satellite;

    // printf(BLUE"satellite position, x = %d, y = %d\n"RESET_COLOUR, data->cub->x_satellite_pixel, data->cub->y_satellite_pixel);
    
    relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    img_satellite = mlx_xpm_file_to_image(data->mlx->mlx_ptr, relative_path, &img_width, &img_height);
    if (!img_satellite)
        printf(RED"Error: img is NULL\n"RESET_COLOUR);
    mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_satellite, data->cub->x_satellite_pixel, data->cub->y_satellite_pixel); //0,0 --> position where we're gonna put the image
}

void put_2d_map_background(t_data *data)
{
    int x;
    int y;

    x = 0;
    y = 0;
    // printf(BLUE"hey\n"RESET_COLOUR);
    while (x < WIDTH_MAP)
    {
        y = 0;
        while (y < HEIGHT_MAP)
        {
            my_mlx_pixel_put(data, x, y, 0x00FFFFCC);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, data->mlx->img, 0, 0);
}

/* put_vertical_lines
*
*   Applies rule of 3 to get the x position where vertical lines
*   must be displayed in 2d map in the window (mlx).
*
*   Total nb of boxes (width) ---------- WIDTH_MAP px
*   1 box ------------------------------ horizontal_size_box px
*
*/
void put_vertical_lines(t_data *data)
{
    int tmp_nb_columns;
    int hor_size_box; //horizontal size of each box
    int total_added_size;
    int x;
    int y;

    tmp_nb_columns = data->cub->map_width;
    //printf(YELLOW"number of columns = %d\n"RESET_COLOUR, tmp_nb_columns);

    hor_size_box = WIDTH_MAP / tmp_nb_columns;
    total_added_size = 0;
    x = 0;
    while (total_added_size < WIDTH_MAP)
    {
        y = 0;
        //printf("barruan - VERTICAL, x = %d\n", x);
        while (y < HEIGHT_MAP)
        {
            my_mlx_pixel_put(data, x, y, 0x00FF0000);
            y++;
        }
        x = x + hor_size_box; //let's go to next vertical line
        total_added_size = total_added_size + hor_size_box; //to tell while where to stop
    }
    
}

/* put_horizontal_lines
*
*   Applies rule of 3 to get the y position where vertical lines
*   must be displayed in 2d map in the window (mlx).
*
*   Total nb of boxes (height) ---------- HEIGHT_MAP px
*   1 box ------------------------------ vertical_size_box px
*
*/
void put_horizontal_lines(t_data *data)
{
    int tmp_nb_rows;
    int vert_size_box; //vertical size of each box
    int total_added_size;
    int x;
    int y;

    tmp_nb_rows = data->cub->map_height;
    //printf(YELLOW"number of rows = %d\n"RESET_COLOUR, tmp_nb_rows);

    vert_size_box = HEIGHT_MAP / tmp_nb_rows;
    total_added_size = 0;
    y = 0;
    while (total_added_size < HEIGHT_MAP)
    {
        x = 0;
        //printf("barruan - HORIZONTAL, y = %d\n", y);
        while (x < WIDTH_MAP)
        {
            
            my_mlx_pixel_put(data, x, y, 0x00FF0000);
            x++;
        }
        y = y + vert_size_box; //let's go to next vertical line
        total_added_size = total_added_size + vert_size_box; //to tell while where to stop
    }
    
}

/* Whole window has the following dimensions, as defined in .h file:
*       
*       #define HEIGHT_WINDOW 1440
*       #define WIDTH_WINDOW 2560
*
*
*  Then, 2D Map will have the following dimensions: 840 x 840px
*  and will be located on the right side of the window.
*
*  Walls are 40x40px by choice.
*  Then, 21x21 walls will be displayed in the map as maximum.
*
*   If map with bigger dimensions is used, we will print message
*/
void render_update_2d_map(t_data *data)
{
    put_2d_map_background(data); //new
    put_vertical_lines(data); //new - idk why no visualiza, pero creo que es prescindible
    put_horizontal_lines(data); //new - idk why no visualiza, pero creo que es prescindible
    //put_walls_in_map(data); //Pintar las paredes - new: por ahora voy a prescindir
    put_dot_in_map(data); //Pintar al jugador: red dot
    put_circle_around_player(data); //Pintar al jugador: circle
    put_satellite_in_map(data); //Pintar satélite (dirección)
}


int *render_next_frame(t_data *data)
{
    //printf(MAGENTA"agaaaain\n"RESET_COLOUR);
    
    if (!data->mlx || !data->cub)
    {
        printf("Error: Puntero a mlx o cub es nulo.\n");
        return (NULL);
    }

    render_update_game(data);
    render_update_2d_map(data);
    //put_2d_map_background(data);

    //printf(YELLOW"\n Player information"RESET_COLOUR"  |   POSITION (dec)  |   POSITION (pixel)  | Map position (INDEX) | Map position (dec)  | DIRECTION |   (dec)   |    SAT. (pixel)   |\n");
    printf("                     |      x = %d, y = %d   | x = %.2f, y = %.2f |   x = %d, y = %d       |     %c     | x = %.2f, y = %.2f |   x = %d, y = %d |\n", 
    
    data->cub->x_pos_ind, data->cub->y_pos_ind, //Map position (INDEX) %d
    data->cub->x_pos_dec, data->cub->y_pos_dec, //Map position (dec) %.2f
    data->cub->x_pos_pixel, data->cub->y_pos_pixel, //Window Position (pixel) %d
    data->cub->direction, //DIRECTION
    data->cub->x_dir_dec, data->cub->y_dir_dec, //DirVector (dec)
    data->cub->x_satellite_pixel, data->cub->y_satellite_pixel); //SAT. (pixel)

    
    return 0;
}