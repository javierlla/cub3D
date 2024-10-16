/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/16 12:21:05 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        write(2, "Usage: ./cub3D <map.cub>\n", 26);
        return EXIT_FAILURE;
    }

    t_data *data;
    t_cub *cub;
    t_mlx *mlx;
    
    data = malloc(sizeof(t_data));
    cub = malloc(sizeof(t_cub));
    mlx = malloc(sizeof(t_mlx));
    ft_memset(cub, 0, sizeof(t_cub));
    ft_memset(mlx, 0, sizeof(t_mlx));
    data->mlx = mlx;
    data->cub = cub;

    data->cub->x_pos_dec = -1;
    data->cub->y_pos_dec = -1;
    data->cub->floor_color = -1;
    data->cub->ceiling_color = -1;
    
    /*data->cub->x_dir_dec = 1; // O cualquier valor significativo
    data->cub->y_dir_dec = 0; // Para iniciar mirando hacia la derecha
    data->cub->planeX = 0; // Ajusta según tu implementación
    data->cub->planeY = 0.66; // Este valor puede depender de cómo se desea el FOV*/

    // - Open argv[1] file
    read_cub_file(data, argv[1]);

    // - Prints read result: textures, colours and map in 'cub' structure. 
    print_cub_data(cub);

    init_all(data);

    cub->mlx = mlx;
    load_textures(cub);
    
    /*if (!cub->north_texture || !cub->south_texture || !cub->west_texture || !cub->east_texture ||
    cub->floor_color == -1 || cub->ceiling_color == -1 || cub->map == NULL ||
    cub->x_pos_dec < 0 || cub->x_pos_dec >= cub->map_width || 
    cub->y_pos_dec < 0 || cub->y_pos_dec >= cub->map_height) 
    {
    exit_with_error("Missing textures, colors, map or player start position");
    free_resources(data); 
    }*/


    mlx_loop_hook(mlx->mlx_ptr, ((void *)render_next_frame(data)), cub); 
    mlx_loop(mlx->mlx_ptr); 

    return 0;
}
