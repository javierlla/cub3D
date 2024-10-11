/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:09:29 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/11 20:30:34 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void put_dot_in_map(t_data *data)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size
    void *img_dot;

    
    printf(BLUE"put_dot_in_map | player's position in 2D Map, x_pixel = %d, y_pixel = %d\n"RESET_COLOUR, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel);
    
    relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    img_dot = mlx_xpm_file_to_image(data->mlx->mlx_ptr, relative_path, &img_width, &img_height);
    if (!img_dot)
        printf(RED"Error: img is NULL\n"RESET_COLOUR);
    mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_dot, data->cub->player_position->x_pixel, data->cub->player_position->y_pixel); //0,0 --> position where we're gonna put the image
}

void put_satellite_in_map(t_data *data)
{
    char *relative_path;
    int img_width; //We store here image size
    int img_height;//We store here image size
    void *img_satellite;

    printf(BLUE"satellite position, x = %d, y = %d\n"RESET_COLOUR, data->cub->player_direction_vector->x_satellite_pixel, data->cub->player_direction_vector->y_satellite_pixel);
    
    relative_path = "./textures/others/5_pixel_by_5_pixel_red_dot_clear_back.xpm";
    img_satellite = mlx_xpm_file_to_image(data->mlx->mlx_ptr, relative_path, &img_width, &img_height);
    if (!img_satellite)
        printf(RED"Error: img is NULL\n"RESET_COLOUR);
    mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_satellite, data->cub->player_direction_vector->x_satellite_pixel, data->cub->player_direction_vector->y_satellite_pixel); //0,0 --> position where we're gonna put the image
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

        put_blue_x_px = data->cub->player_position->x_pixel + (direction_vector_x) * DISTANCE_BLUE_CIRCLE;
        put_blue_y_px = data->cub->player_position->y_pixel + (direction_vector_y) * DISTANCE_BLUE_CIRCLE;
        
        img_circle = mlx_xpm_file_to_image(data->mlx->mlx_ptr, relative_path, &img_width, &img_height);
        mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_circle, put_blue_x_px, put_blue_y_px);
        i++;
    }
}


//new version
void render_update_game(t_data *data)
{
    raycast(data);
    mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, data->mlx->image_ptr, 0, 0);
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
    int x_start_2d_map;
    int y_start_2d_map;
    int x;
    int y;

    printf(YELLOW"render_update_2d_map\n"RESET_COLOUR);
    x_start_2d_map = WIDTH_WINDOW - WIDTH_MAP;
    y_start_2d_map = HEIGHT_WINDOW - HEIGHT_MAP;

    printf("x start = %d, y start = %d\n", x_start_2d_map, y_start_2d_map);
    /* Pintar 2d map en el mismo window*/
    y = 0;
    while (y < HEIGHT_WINDOW)
    {
        x = 0;
        while (x < WIDTH_WINDOW)
        {
            if (x >= x_start_2d_map && y >= y_start_2d_map)
            {
                /* Little test, red square */
                my_mlx_pixel_put(data, x, y, 0x00FFFFCC);

                /* Draw in image */
                //put_walls_in_map(data); //Pintar las paredes
                //     
                //     
                //     if (satellite_case == 1)
                //         put_satellite_in_map(data); //Pintar satélite (dirección)
            }
                
            x++;
        }
        y++;
    }
    put_walls_in_map(data); //Pintar las paredes
    put_dot_in_map(data); //Pintar al jugador: red dot
    put_circle_around_player(data); //Pintar al jugador: circle
    put_satellite_in_map(data); //Pintar satélite (dirección)
}

/* Let's try unify both windows so that we aim to avoid segfault issue*/
void render_update_window(t_data *data)
{
    //printf(GREEN"render_update_window\n"RESET_COLOUR);
    //mlx_clear_window(data->mlx->mlx_ptr, data->mlx->win_ptr);
    //mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->image_ptr);
    //data->mlx->image_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH_WINDOW, HEIGHT_WINDOW); //Crear nueva imagen
    
    /* Let's create the whole window image */
    
    /* #1: First, game itself is updated */
    render_update_game(data);

    /* #2: Then, also map is updated*/
    render_update_2d_map(data);

    /* Once whole image has been created, let's put it in window */
    //mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, data->mlx->image_ptr, 0, 0);
}

/* render_initial
*
*   mlx_put_image_to_window at the end is mandatory. If not, image is not shown in window.
*/
void render_initial(t_data *data)
{
    render_update_game(data);
    
    //printf(GREEN"RENDER_INITIAL | game rendered successfully\n"RESET_COLOUR);
    
    render_update_2d_map(data); //Has to be painted on top of game
    
    // mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, data->mlx->image_ptr, 0, 0);
}