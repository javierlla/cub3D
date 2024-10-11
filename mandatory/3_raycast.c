/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_raycast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:00:00 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/11 17:04:37 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* my_mlx_pixel_put: Puts a pixel in our image.
*
*       > data->mlx_game->pixels_ptr: points to actual pixels
*                Apunta al primer byte de la memoria donde se almacenan
*                todos los píxeles de la imagen (el buffer de la imagen).       
*
*       > x and y are pixel coordinates --> 
*           x and y (0,0) are top left corner of the image           
*
*       line_len and bpp are image setup.
*       > data->mlx_game->line_len = width of the image in bytes.
*       NO es el número de píxeles. Sí es el número de bytes
*       que ocupa una fila completa de píxeles en la memoria.
*
*       > bpp = bits per pixel. La cantidad de bits que se usan para
*       almacenar la información de un píxel en la memoria. En nuestro
*       caso son 32 bits por píxel = 4 bytes por píxel.
*            · 32 bits per pixel
*            · 32 / 8 = 4 bytes per pixel
*
*
*       pixels_ptr = mlx_get_data_addr 
*          // Pointer that points to 1st byte in image buffer.
*          // char * pointer type, when doing ++, we move in bytes
*
*       y * line_len = number of bytes we have to move from beginning
*                      of pixels_ptr to get to the correct line of pixels.
*
*       x * (bpp / 8) =
*                 > bpp / 8: 1 pixel's size in bytes 
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
    int		move_y;
	int		move_x;
	int 	total_move;
    
    //printf("mlx->pixels_ptr = %p\n", data->mlx_game->pixels_ptr);

    /* Make sure coordinates (x, y) are within limits*/
    if (x < 0 || x >= WIDTH_WINDOW || y < 0 || y >= HEIGHT_WINDOW)
    {
        return;
    }

    //printf(GREEN"pixels_ptr: %p, line_len: %d, bpp: %d\n"RESET_COLOUR, data->mlx_game->pixels_ptr, data->mlx_game->line_len, data->mlx_game->bpp);
    
    /* Make sure pointer is valid*/
    /* Make sure valid bpp and line_len values */
    /* Error: we're not working with 32 bits per pixel images*/
    if (data->mlx->pixels_ptr == NULL || data->mlx->line_len < 0 || data->mlx->bpp < 0 || data->mlx->bpp != 32)
    {
        return;
    }

	move_x = x * (data->mlx->bpp / 8);
	move_y = y * data->mlx->line_len;
	total_move = move_x + move_y;
    /* y * line_len: para movernos a la línea correcta de píxeles, coordenada Y
    *  */
	pixel = data->mlx->pixels_ptr + total_move;

    /* Trying alternatives to solve segfault*/        
	*(unsigned int *)pixel = color;
    // ft_memcpy(pixel, &color, sizeof(unsigned int)); //10 is the size of the color. E.g. 0x00FF0000
}

/* Normalizes angle making sure it's between [0-360] degrees*/
double	nor_angle(double angle)
{
	if (angle < 0)
		angle += 360;
	if (angle >= 360)
		angle -= 360;
	return (angle);
}

double set_ray_angle(t_data *data)
{
    double ray_angle;

    ray_angle = data->cub->player_direction_vector->angle_degree - (FOV_ANGLE / 2);
    ray_angle = nor_angle(ray_angle);
    return (ray_angle);
}

/*
*   sky_height, wall_height, floor_height are represented in pixels
*/
void draw_vertical_line(t_data *data, int x, double *wall)
{
    int y;
    int sky_height;
    int wall_height;
    int floor_height;
    
    //printf("draw_vertical_line, beginning, x = %2.f, y = %2.f\n", wall[0], wall[1]);
    
    y = 0;
    sky_height = wall[0];
    wall_height = wall[1] - wall[0];
    floor_height = HEIGHT_WINDOW - wall[1];
    
    /* Blue */
    while (sky_height > 0)
    {
        my_mlx_pixel_put(data, x, y, 0x0000CCFF);
        y++;
        sky_height--;
    }
    
    //printf("y after sky = %d\n", y);
    /* Amarillito */
    while (wall_height > 0)
    {
        my_mlx_pixel_put(data, x, y, 0x00CC9900);
        y++;
        wall_height--;
    }

   // printf("y after wall = %d\n", y);
    /* Moradito */
    while (floor_height > 0)
    {
        my_mlx_pixel_put(data, x, y, 0x009999FF);
        y++;
        floor_height--;
    }
}

void get_wall_height(t_data *data, double *wall/*, int x*/)
{
    (void)data;

    wall[0] = 50;
    wall[1] = 150;

    // if (x < WIDTH_WINDOW / 2)
    // {
    //     wall[0] = 50;
    //     wall[1] = 150;
    // }
    // else
    // {
    //     wall[0] = 100;
    //     wall[1] = 200;
    // }
}

/* raycast: Draws the game screen
*
*   About wall[2];
*       wall[0] = y pixel where the wall starts
*       wall[1] = y pixel where the wall ends
*/
void raycast(t_data *data)
{
    printf("raycast\n");
    
    double ray_angle;
    double end_ray_angle;
    double wall[2];

    /* Let's start by calculating the first ray angle,  */
    ray_angle = set_ray_angle(data);

    /* Last ray, normalized angle making sure [0-360]*/
    end_ray_angle = nor_angle(ray_angle + FOV_ANGLE);
    (void) end_ray_angle;
    // while (ray_angle < end_ray_angle)
    // {
        
    //     ray_angle += 1;
    // }

    /* Test: draw 1 single line */
    // draw_vertical_line(data, 5);
    
    
    /* Draw whole screen */
    int x;

    

    x = 0;
    while (x < WIDTH_WINDOW)
    {
        //printf("hellowis\n");

        /* 1. calculate distance */
        

        /* 2. Get wall height*/ //We're not gonna actually send 'x', it's just for testing purposes
        get_wall_height(data, wall);

        /* 3. Draw vertical line*/
        draw_vertical_line(data, x, wall);
        //my_mlx_pixel_put(data, x, 1, 0x00FF0000);
        x++;
    }
    printf("game_screen was successfull painted\n");
}

