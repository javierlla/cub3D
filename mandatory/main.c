/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/15 16:16:53 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
*   mlx_map: Map (Bonus: Debugging purposes)
*   mlx_game: Cub3D Project (Primary mandatory window)
*/
int main(int argc, char **argv)
{
    t_cub cub;
    t_mlx mlx_map; /* grahical interface handler */
    t_mlx mlx_game; /* grahical interface handler */
    
    if (argc != 2)
    {
        write(2, "Usage: ./cub3D <map.cub>\n", 26);
        return EXIT_FAILURE; 
    }
    
    /* Clears memory so as to start */
    ft_memset(&cub, 0, sizeof(t_cub));
    // ft_memset(&mlx_.cub, 0, sizeof(t_cub));
    ft_memset(&mlx_map, 0, sizeof(t_mlx));
    ft_memset(&mlx_game, 0, sizeof(t_mlx));

    /* - Open argv[1] file*/
    read_cub_file(&cub, argv[1]);

    /* - Prints read result: textures, colours and map in 'cub' structure. */
    print_cub_data(&cub); //Javi: puts info in standard output, terminal

    /* - Initializes mlx, events: Opens window, 'x' button and ESC closing are set
    *  - Both windowx (mlx) will point same unique cub instance of t_cub.
    *----------------------------------------------------------------------------*/
    init_all(&mlx_game, &mlx_map, &cub);


	/* In loop: get position, (re-calculate) render, move*/
    // while(1)
    // {
    //     if ()
    // }
    
    //ft_render(&cub, &mlx);
	
    /* #2 MAP WINDOW - Debugging purposes*/
	// if (DEBUG_MODE == 1)
        // put_walls_in_map(&mlx_map);
    
    /* #1 GAME WINDOW - Cub3D Project*/
    
	/* Appication keeps running listening for events (key presses, mouse, 'x', ESC, etc.) */
    mlx_loop_mine(&mlx_game);
    mlx_loop_mine(&mlx_map);
    return 0;
}
