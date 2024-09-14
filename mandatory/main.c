/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/14 18:27:51 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_cub cub;
    t_mlx mlx_primary; /* grahical interface handler */
    t_mlx mlx_secondary_debug; /* grahical interface handler */
    
    if (argc != 2)
    {
        write(2, "Usage: ./cub3D <map.cub>\n", 26);
        return EXIT_FAILURE; 
    }
    
    /* Clears memory so as to start */
    ft_memset(&cub, 0, sizeof(t_cub));
    // ft_memset(&mlx_.cub, 0, sizeof(t_cub));
    ft_memset(&mlx_primary, 0, sizeof(t_mlx));
    ft_memset(&mlx_secondary_debug, 0, sizeof(t_mlx));

    /* - Open argv[1] file*/
    read_cub_file(&cub, argv[1]);

    /* - Prints read result: textures, colours and map in 'cub' structure. */
    print_cub_data(&cub);

    /* - Initializes mlx, events: Opens window, 'x' button and ESC closing are set
    *  - Both windowx (mlx) will point same unique cub instance of t_cub.
    *----------------------------------------------------------------------------*/
    init_window(&mlx_primary, GAME, &cub);
    if (DEBUG_MODE == 1)
        init_window(&mlx_secondary_debug, DEBUG_SCREEN_MAP, &cub);

	/* In loop: get position, (re-calculate) render, move*/
    //ft_render(&cub, &mlx);
    //get_player_map_position(&cub);
	
    /* #1 GAME WINDOW - Cub3D Project*/
    
    /* #2 MAP WINDOW - Debugging purposes*/
	if (DEBUG_MODE == 1)
        put_secondary_window(&cub, &mlx_secondary_debug);

    //0,0 --> position where we're gonna put the image
    printf(YELLOW"WINDOW_PTR = %p\n"RESET_COLOUR, mlx_secondary_debug.win_ptr);
    printf(YELLOW"IMAGE_PTR = %p\n"RESET_COLOUR, mlx_secondary_debug.image_ptr);
    
    
    mlx_put_image_to_window(mlx_secondary_debug.mlx_ptr, mlx_secondary_debug.win_ptr, mlx_secondary_debug.image_ptr, 0, 0);

	/* Appication keeps running listening for events (key presses, mouse, 'x', ESC, etc.) */
    mlx_loop_mine(&mlx_primary);
    if (DEBUG_MODE == 1)
        mlx_loop_mine(&mlx_secondary_debug);

    return 0;
}

// void my_mlx_pixel_put(t_data *data, int x, int y, int colour)
// {
//     char *dst;

//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = colour;
// }

// /* Main for mlx tests
// *
// *   - Pixels = ints (usually 4 bytes)
// **/
// int main(void)
// {
//     void *mlx;
//     void *mlx_win;
//     t_data img;
//     int x_window;
//     int y_window;

//     /* Access to functions by establishing a connection to the correct
//     *  graphical system and will return a void * which holds location of our
//     *  current MLX insstance.
//     * ----------------------------------------------------------------------*/
//     mlx = mlx_init(); 

//     mlx_win = mlx_new_window(mlx, WIDTH_WINDOW, HEIGHT_WINDOW, "Hello world!");
//     img.img = mlx_new_image(mlx, WIDTH_WINDOW, HEIGHT_WINDOW);

//     /* Get image address:
//     *  After image is created, we set bits_per_pixel, line_length and endian for
//     *  *current* data address.
//     *---------------------------------------------------------------------------*/
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//     x_window = 0;
//     while (x_window < WIDTH_WINDOW)
//     {
//         y_window = 0;
//         while (y_window < HEIGHT_WINDOW)
//         {
//             my_mlx_pixel_put(&img, x_window, y_window, 0x00FF0000);
//             y_window++;
//         }
//         x_window++;
//     }
//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//     mlx_loop(mlx); /* Initiates the window rendering. */
// }