/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_secondary_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:13:48 by uxmancis          #+#    #+#             */
/*   Updated: 2024/09/14 18:31:04 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void put_secondary_window(t_cub *cub, t_mlx *mlx)
{
    // int y_nb_of_boxes; //Height
    // int x_nb_of_boxes; //Width
    // y_nb_of_boxes = get_height_map()
   //t_integer_position pixels;
    

    char *relative_path = "./textures/others/hannah.xpm";
    int img_width; //We store here image size
    int img_height;//We store here image size

    if (!mlx)
        printf("jeje est era\n");

    // mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, 50, 50); //Where are we gonna store it? The image itself
    // printf(GREEN"image_ptr = %p\n"RESET_COLOUR, mlx->image_ptr);
    // mlx->pixels_ptr = mlx_get_data_addr(mlx->image_ptr, &mlx->bpp, &mlx->line_len, &mlx->endian);
    // pixels.x = 5;
    // pixels.y = 5;
    // my_mlx_pixel_put(mlx->mlx_ptr, pixels, 0x00FF0000);
    // mlx->image_ptr = mlx_png_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx->image_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, relative_path, &img_width, &img_height);
    printf(YELLOW"IMAGE_PTR = %p\n"RESET_COLOUR, mlx->image_ptr);

    // mlx_put_image_to_window()


    
    (void)cub;
    // get_player_map_position(cub);
    // my_mlx_pixel_put()
    (void)mlx;

    
    // t_pixel_position window;
    
    // int cellsize_y;
    // int cellsize_x;
    // int line_nb; //starts from 0
    // int each_line_width;

    // cellsize_y = HEIGHT_WINDOW / cub->map_height;
    // cellsize_x = WIDTH_WINDOW / cub->map_width;

    // printf("Map info | nb. of lines (height, y) = %d ---------------------\n", cub->map_height);
    // line_nb = 0;
    // while (line_nb < cub->map_height - 1) //-1 because it starts from zero
    // {
    //     each_line_width = fr_strlen(cub->map[line_nb]);
    //     printf("%d line number - Width: %d\n", each_line_width);
    //     while (each_line_width > 0)
    //     {
    //         if (line_nb % cel)
    //     }
    //     line_nb++;
    // }

    

    // (void)mlx;
    // (void)cellsize_x;
    // (void)cellsize_y;
    // /* Put horizontal lines: from left to right, from up to down.
    // *
    // *   Paints n horizontal lines from left to right. In which heights?
    // *   We sum cellsize_y to y until y reaches HEIGHT_WINDOW.
    // *   cellsize_y is what makes us jump from line to line
    // * */
    // window.y = 0;
    // while (window.y < HEIGHT_WINDOW)
    // {
    //     window.x = 0;
    //     while (window.x < WIDTH_WINDOW)
    //     {
    //         //my_mlx_pixel_put(mlx, window, 0x00FF0000);
    //         window.x++;
    //     }
    //     window.y = window.y + cellsize_y;
    // }
    
    // /* Put vertical lines */
    // window.x = 0;
    // while (window.x < WIDTH_WINDOW)
    // {
    //     window.y = 0;
    //     while (window.y < HEIGHT_WINDOW)
    //     {
    //         //my_mlx_pixel_put(mlx, window, 0x00FF0000);
    //         window.y++;
    //     }
    //     window.x = window.x + cellsize_x;
    // }
}
