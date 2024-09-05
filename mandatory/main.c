/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:26 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/05 17:25:04 by jllarena         ###   ########.fr       */
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

    read_cub_file(&cub, argv[1]);

    print_cub_data(&cub);

    init_window(&mlx);

    mlx_loop_mine(&mlx);

    return 0;
}