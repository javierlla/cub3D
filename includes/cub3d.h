/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:28:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/05 17:30:38 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct s_cub
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int floor_color[3];
    int ceiling_color[3];
    char **map;
    int map_height;
    int map_width;
}	t_cub;

typedef struct s_mlx
{
    void    *mlx_ptr;  
    void    *win_ptr;  
}   t_mlx;

//parseo
void print_cub_data(t_cub *cub);
int parse_color(char *line);
char *extract_path(char *line);
void parse_map_line(t_cub *cub, char *line);
void validate_map(t_cub *cub);
void parse_line(t_cub *cub, char *line);
void read_cub_file(t_cub *cub, const char *filename);
void exit_with_error(const char *message);

//MLX
void init_window(t_mlx *mlx);
void mlx_loop_mine(t_mlx *mlx);
int close_program(t_mlx *mlx);

#endif