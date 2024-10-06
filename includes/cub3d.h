/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:28:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/06 13:13:52 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h> //M_PI
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

#define PI 3.14159265358979323846

/* Debugging purposes*/
#define DEBUG_MODE 1

/*---------- Dimensions | Window 1: Cub D (Project--------*/
#define HEIGHT_WINDOW 720
#define WIDTH_WINDOW 1280
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
# define ROTATE_LEFT 65361 //Left arrow
# define ROTATE_RIGHT 65363 //Right arrow
//# define ESC 17
/*Other events*/
//# define CLOSE 17

/* ----- 2D Map Visualization ------*/
#define DISTANCE_BLUE_CIRCLE 20 //Satellite
#define SPEED_MOVE 3 //Speed of movement: each time W-A-S-D are pressed how many pixels will the player move
#define SPEED_ROTATE 3 //Speed of rotation: each time left or right arrow are pressed how many degrees will the player rotate


#define FOV_ANGLE 60 //Field of View

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
// typedef struct s_data
// {
//     void *img; //result of mlx_new_image: Image is created
//     char *addr; //result of mlx_get_data_addr
//     int bits_per_pixel;
//     int line_length;
//     int endian;
// } t_data;

/*  We allow decimals for players' position. That's why
*   we use double type variable.
*-----------------------------------------------------*/
typedef struct s_coordinates
{
    int x_index;
    int y_index;
    double x_decimal; //decimal dentro de todo el mapa ()
    double y_decimal; // indice [3, 4] == [120, 180] + decimal dentro de la caja (entre 0 y 40)
    int x_pixel;
    int y_pixel;
    double offset_x; // decimal dentro de la caja 
    double offset_y;
}   t_coordinates;

/*  We allow decimals for players' position. That's why
*   we use double/float type variable.
*-----------------------------------------------------*/
typedef struct s_float_x_y
{
    /* Direction vector, D[x,y]*/
    float x; 
    float y;

    /* Angle in degrees (360º) and in radians (2π)*/
    float angle_degree;
    float angle_radian;

    /* Satellite dot's pixel position */
    int x_satellite_pixel;
    int y_satellite_pixel;
}   t_float_x_y;

/* Used to handle key press/release and generate movement
*  only when flags are 1
--------------------------------------------------------*/
typedef struct keyboard_flags
{
    int		w_flag;
	int		s_flag;
	int		a_flag;
	int		d_flag;
	int		r_flag;
	int		l_flag;
}   t_keyboard_flags;

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
    t_coordinates *player_position; //Info about player's position in 2D Map
    char initial_player_direction_in_map; //N-S-E-W
    t_float_x_y *player_direction_vector; //N-S-E-W
    t_keyboard_flags *keyboard_flags;
    
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

typedef struct s_data
{
    t_mlx *mlx_game;
    t_mlx *mlx_map;
    t_cub *cub;
}   t_data;

enum window_type
{
	GAME,
	MAP
};

enum width_or_height
{
    X_WIDTH,
    Y_HEIGHT
};

/* main.c */
//void my_mlx_pixel_put(t_data *data, int x, int y, int colour);
int ft_arg_checker(int argc);

/* 1_read_cub_file.c */
void exit_with_error(const char *message);
int parse_color(char *line);
char *trim_whitespace(char *str);
char *extract_path(char *line);
void parse_map_line(t_cub *cub, char *line);
void validate_map(t_cub *cub);
void parse_line(t_cub *cub, char *line);
void read_cub_file(t_cub *cub, const char *filename);
void print_cub_data(t_cub *cub);

/* 2_init_all.c */
void init_all_default (t_data *data);
void init_all(t_data *data);

/* 2_init_mlx_events.c */
void render_update_2d_map(t_data *data, int satellite_case);
void ft_events_init(t_data *data);
void rotate_right(t_data *data);
void move_forward(t_data *data);
int key_handler(int keycode, t_data *data);

/* 2_init_mlx_utils.c */
// void	my_mlx_pixel_put(t_mlx *mlx, int x_pixel, int y_pixel, int colour);
int close_program(t_mlx *mlx);
int handle_keypress(int keycode, t_mlx *mlx);
void mlx_loop_mine(t_mlx *mlx);
int	close_handler(t_mlx *mlx);

/* 2_init_mlx_window.c */
void ft_events_init(t_data *data);
void my_mlx_new_window(t_mlx *mlx, enum window_type game_or_map);
void my_mlx_new_image(t_mlx *mlx, enum window_type game_or_map);
void init_window(t_mlx *mlx, enum window_type game_or_map, t_cub *cub);

/* 2_init_player_info.c */
void angle_to_rad(t_data *data);
void set_player_direction_vector(t_data *data);
void set_player_position_2(t_data *data, int x_map_index, int y_map_index);
void set_player_position(t_data *data);

/* 3_move_player.c*/
int move_player (t_data *data);

/* 3_raycast.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void raycast(t_data *data);

/* player_double_position.c */
void calculate_decimal_position(t_coordinates *player);
void update_player_position(t_coordinates *player, double move_x, double move_y);

/* player.c */
char *get_path(t_mlx *mlx_map);
void put_hannah_in_index(t_mlx *mlx_map);
void put_player_in_map(t_mlx *mlx_map);
int is_map(t_cub *cub, int x, int y);
int is_player_position(t_cub *cub, int x, int y);
void set_initial_index_in_2d_map(t_cub *cub, int x_map_index, int y_map_index);
void set_initial_player_direction(t_cub *cub, int x_map_index, int y_map_index);
void set_initial_decimal_in_2d_map(t_cub *cub, int x_map_index, int y_map_index);
int decimal_to_pixel(float decimal, enum width_or_height indicator);
float pixel_to_decimal_map(int pixel, enum width_or_height indicator);
void set_initial_pixel_in_map(t_data *data); //I think I don't use this one, as mlx not usable at this moment

/* put_walls_map.c*/
int scale_x(/*t_mlx *mlx_2, */int x_index);
int scale_y(/*t_mlx *mlx_2, */int y_index);
void put_each_wall(t_mlx *mlx_2, int x_index, int y_index);
void put_walls_in_map(t_mlx *mlx_2);

/* render.c */
void ft_render(t_cub *cub, t_mlx *mlx);


#endif