/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/11 16:59:31 by uxmancis         ###   ########.fr       */
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

/*
*   mlx_map: Map (Bonus: Debugging purposes)
*   mlx_game: Cub3D Project (Primary mandatory window)
*/
int main(int argc, char **argv)
{
    t_data *data;
    t_cub *cub;
    t_mlx *mlx; /* grahical interface handler */
    
    if (ft_arg_checker(argc) == EXIT_FAILURE)
        return EXIT_FAILURE;

    data = malloc(sizeof(t_data));
    cub = malloc(sizeof(t_cub));
    mlx = malloc(sizeof(t_mlx));
    if (!data || !cub || !mlx)
    {
        perror("Failed to allocate memory for data");
        exit(1);
    }
    /* Clears memory so as to start */
    ft_memset(cub, 0, sizeof(t_cub));
    ft_memset(mlx, 0, sizeof(t_mlx));
    data->mlx = mlx;
    data->cub = cub;
	
    
    /* - Open argv[1] file*/
    read_cub_file(data->cub, argv[1]);

    /* - Prints read result: textures, colours and map in 'cub' structure. */
    print_cub_data(data->cub); //Javi: puts info in standard output, terminal

    /* - Initializes mlx, events: Opens window, 'x' button and ESC closing are set
    *  - Both windowx (mlx) will point same unique cub instance of t_cub.
    *----------------------------------------------------------------------------*/
    init_all(data);


    // mlx_loop_hook(mlx_game->mlx_ptr, render_next_frame, data);
    // mlx_loop_hook(mlx_map->mlx_ptr, render_next_frame, data);
    
	/* Appication keeps running listening for events (key presses, mouse, 'x', ESC, etc.) */
    mlx_loop_mine(data->mlx);
    return 0;
}
