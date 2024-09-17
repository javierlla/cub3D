/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:28:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/16 14:29:21 by jllarena         ###   ########.fr       */
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

#define GRAY "\033[0;90m"
#define RED "\033[0;31m"
#define GREEN "\033[0;92m"
#define YELLOW "\033[0;93m"
#define BLUE "\033[0;94m"
#define MAGENTA "\033[0;95m"
#define CYAN "\033[0;96m"
#define WHITE "\033[0;97m"
#define WHITE_COLOR "\033[37m"
#define RESET_COLOUR "\033[0m"
#define AQUAMARINE "\033[0;96m"


#define MOVE_SPEED 0.2

/* Debugging purposes*/
#define DEBUG_MODE 1

/*---------- Dimensions | Window 1: Cub D (Project--------*/
#define HEIGHT_WINDOW 1280
#define WIDTH_WINDOW 720
/*---------- Dimensions | Window 2: Map (Debugging Purposes) --------*/
#define HEIGHT_MAP 840 /*Manually calculated for cheese_maze.cub. Canva allows us 40x40 smallest. 40px x 21 boxes = 840*/
#define WIDTH_MAP 840



//# define MAX_ITERATIONS 100 //Impacts on image quality and rendering speed

/*----------    Keys    --------*/
/*Mouse events*/
// # define MOUSE_WHEEL_UP 4
// # define MOUSE_WHEEL_DOWN 5
/*Keyboard events*/
# define W_MOVE_FORWARD 119
# define S_MOVE_BACKWARDS 115
# define A_MOVE_LEFT 97
# define D_MOVE_RIGHT 100
# define ROTATE_LEFT 65361
# define ROTATE_RIGHT 65363
//# define ESC 17
/*Other events*/
//# define CLOSE 17

/*
*	IMAGE: pixels' buffer values from mlx_get_data_addr()
*
*	- img_ptr: pointer to image struct
*	- pixels_ptr: points to actual pixels
*   - bpp: bits per pixels
*/
typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

/* Pruebitas main 2.0 de uxu*/
typedef struct s_data
{
    void *img; //result of mlx_new_image: Image is created
    char *addr; //result of mlx_get_data_addr
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

/*  We allow decimals for players' position. That's why
*   we use double type variable.
*-----------------------------------------------------*/
typedef struct s_coordinates
{
    double x_decimal; //decimal dentro de todo el mapa ()
    double y_decimal; // indice [3, 4] == [120, 180] + decimal dentro de la caja (entre 0 y 40)
    int x_index;
    int y_index;
    double offset_x; // decimal dentro de la caja 
    double offset_y;
}   t_coordinates;

/*  We allow decimals for players' position. That's why
*   we use double type variable.
*-----------------------------------------------------*/
typedef struct s_integer_position
{
    int x; 
    int y;
}   t_integer_position;

typedef struct s_cub
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int floor_color[3];
    int ceiling_color[3];

    /*Map*/
    char **map;
    int map_height;
    int map_width;

    /* Player's info*/
    t_coordinates player_position; //position
    char player_direction; //N-S-E-W
    //FOV, pending

    /* Mlx */
    /*t_img img; Creo que tiene más sentido si lo hacemos al revés.
    Es decir, crear una ventana t_mlx, y dentro ponerle un puntero que
    apunta a un tipo t_cub. Así, las 2 ventanas podremos hacer
    que apunten al mismo t_cub*/
}	t_cub;

typedef struct s_mlx
{
    void    *mlx_ptr;  
    void    *win_ptr;
    void    *mlx_connection;
    char    *pixels_ptr; //following fractal: ADDRESS
    void    *image_ptr; //following fractal
    int		bpp; //following fractal
    int		endian; //following fractal
	int		line_len; //following fractal
    t_cub   *cub; //Así es como creo que tiene más sentido. Para vincular el mismo cub a las 2 ventanas.
}   t_mlx;

enum window_type
{
	GAME,
	MAP
};

/* main.c */
//void my_mlx_pixel_put(t_data *data, int x, int y, int colour);

/* open_window.c */
void init_all(t_mlx *mlx_game, t_mlx *map, t_cub *cub);

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
void init_window(t_mlx *mlx, enum window_type for_size, t_cub *cub);
void mlx_loop_mine(t_mlx *mlx);
int close_program(t_mlx *mlx);

/* player.c */
void put_player_in_map(t_mlx *mlx_map);
int is_map(t_cub *cub, int x, int y);
int is_player_position(t_cub *cub, int x, int y);
void init_player_position(t_cub *cub);

/* player_double_position.c*/
void calculate_decimal_position(t_coordinates *player);
void update_player_position(t_coordinates *player, double move_x, double move_y);

/* render.c */
void ft_render(t_cub *cub, t_mlx *mlx);

/* put_walls_map.c */
int scale_x(/*t_mlx *mlx_2, */int x_index);
int scale_y(/*t_mlx *mlx_2, */int y_index);
void put_each_wall(t_mlx *mlx_2, int x_index, int y_index);
void put_walls_in_map(t_mlx *mlx_2);

/* utils_mlx.c */
void	my_mlx_pixel_put(t_mlx *mlx, t_integer_position pixel_window, int colour);

#endif