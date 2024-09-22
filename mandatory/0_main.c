/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/22 12:38:28 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* ft_arg_checker returns EXIT_FAILURE if argc is not 2 as expected.*/
int ft_arg_checker(int argc)
{
    if (argc != 2)
    {
        write(2, "Usage: ./cub3D <map.cub>\n", 26);
        return EXIT_FAILURE; 
    }
    return 0;
}

// int main(void)
// {
//     printf("pi = %f\n", M_PI);
//     return (0);
// }

/*
*   mlx_map: Map (Bonus: Debugging purposes)
*   mlx_game: Cub3D Project (Primary mandatory window)
*/
int main(int argc, char **argv)
{
    t_data *data;
    t_cub *cub;
    t_mlx *mlx_map; /* grahical interface handler */
    t_mlx *mlx_game; /* grahical interface handler */
    
    if (ft_arg_checker(argc) == EXIT_FAILURE)
        return EXIT_FAILURE;

    data = malloc(sizeof(t_data));
    cub = malloc(sizeof(t_cub));
    mlx_map = malloc(sizeof(t_mlx));
    mlx_game = malloc(sizeof(t_mlx));
    if (!data || !cub || !mlx_map || !mlx_game)
    {
        perror("Failed to allocate memory for data");
        exit(1);
    }
    /* Clears memory so as to start */
    ft_memset(cub, 0, sizeof(t_cub));
    ft_memset(mlx_map, 0, sizeof(t_mlx));
    ft_memset(mlx_game, 0, sizeof(t_mlx));
    data->mlx_game = mlx_game;
	data->mlx_map = mlx_map;
    data->cub = cub;
	
    
    /* - Open argv[1] file*/
    read_cub_file(data->cub, argv[1]);

    /* - Prints read result: textures, colours and map in 'cub' structure. */
    print_cub_data(data->cub); //Javi: puts info in standard output, terminal

    /* - Initializes mlx, events: Opens window, 'x' button and ESC closing are set
    *  - Both windowx (mlx) will point same unique cub instance of t_cub.
    *----------------------------------------------------------------------------*/
    init_all(data);


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
    mlx_loop_mine(mlx_game);
    mlx_loop_mine(mlx_map);
    return 0;
}
