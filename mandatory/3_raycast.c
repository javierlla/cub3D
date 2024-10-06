/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_raycast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:00:00 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/06 13:52:27 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* my_mlx_pixel_put: Puts a pixel in our image.
*
*       line_len = width of the image in bytes
*       bpp = bits per pixel
*            · 32 bits per pixel
*            · 32 / 8 = 4 bytes per pixel
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
    
    //printf("mlx->pixels_ptr = %p\n", data->mlx_game->pixels_ptr);

    /* Make sure coordinates (x, y) are within limits*/
    if (x < 0 || x >= WIDTH_WINDOW || y < 0 || y >= HEIGHT_WINDOW)
    {
        return;
    }
    
    // printf("line_len = %d\n", data->mlx_game->line_len);
    // printf("bpp = %d\n", data->mlx_game->bpp);
    
    /* Make sure pointer is valid*/
    if (data->mlx_game->pixels_ptr == NULL)
    {
        return;
    }

    /* Make sure valid bpp and line_len values */
    if (data->mlx_game->line_len < 0 || data->mlx_game->bpp < 0)
    {
        return;
    }

    /* Error: we're not working with 32 bits per pixel images*/
    if (data->mlx_game->bpp != 32)
    {
        return;
    }
    
	pixel = data->mlx_game->pixels_ptr + (y * data->mlx_game->line_len
			+ x * (data->mlx_game->bpp / 8));

    /* Trying alternatives to solve segfault*/        
	*(unsigned int *)pixel = color;
    // ft_memcpy(pixel, &color, sizeof(unsigned int)); //10 is the size of the color. E.g. 0x00FF0000
}

/* my_mlx_pixel_put: Puts a pixel in our image.*/
// void	my_mlx_pixel_put(t_data *data, int x_pixel, int y_pixel, int colour)
// {
// 	char	*dst;

//     // printf(RED"mlx->pixels_ptr = %p\n", mlx->pixels_ptr);
//     // printf("mlx->line_len = %d\n", mlx->line_len);
//     // printf("mlx->bpp = %d\n", mlx->bpp);
//     // printf("x_pixel = %d\n", x_pixel);
//     // printf("y_pixel = %d\n"RESET_COLOUR, y_pixel);
// 	dst = data->mlx_game->pixels_ptr + (y_pixel * data->mlx_game->line_len + x_pixel * (data->mlx_game->bpp / 8));
// 	*(unsigned int *)dst = colour;
// }

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
    
    printf("draw_vertical_line, beginning, x = %2.f, y = %2.f\n", wall[0], wall[1]);
    
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
    
    printf("y after sky = %d\n", y);
    /* Amarillito */
    while (wall_height > 0)
    {
        my_mlx_pixel_put(data, x, y, 0x00CC9900);
        y++;
        wall_height--;
    }

    printf("y after wall = %d\n", y);
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

