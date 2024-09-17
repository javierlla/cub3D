/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/17 17:03:38 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(2, "Usage: ./cub3D <map.cub>\n", 26);
        return EXIT_FAILURE;
    }
    t_cub cub;
    t_mlx mlx;
    
    ft_memset(&cub, 0, sizeof(t_cub));
    ft_memset(&mlx, 0, sizeof(t_mlx));
    
    cub.floor_color = -1;
    cub.ceiling_color = -1;
    read_cub_file(&cub, argv[1]);
    
    if (!cub.north_texture || !cub.south_texture || !cub.west_texture || !cub.east_texture ||
    cub.floor_color == -1 || cub.ceiling_color == -1 || cub.map == NULL)
    {
        exit_with_error("Missing textures, colors, or map");
    }

    print_cub_data(&cub);

    init_window(&mlx);

    mlx_loop_mine(&mlx);

    return 0;
}
