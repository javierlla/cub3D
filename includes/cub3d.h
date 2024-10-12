/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:28:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/12 21:32:14 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

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

/*---------- Dimensions | Window 1: Cub D (Project--------*/
# define screenWidth 2560 //HEIGHT_WINDOW in Uxu's branch
# define screenHeight 1440 //HEIGHT_WINDOW in Uxu's branch
/*---------- Dimensions | Window 2: Map (Debugging Purposes) --------*/
#define HEIGHT_MAP 840 /*Manually calculated for cheese_maze.cub. Canva allows us 40x40 smallest. 40px x 21 boxes = 840*/
#define WIDTH_MAP 840

/* ----- 2D Map Visualization ------*/
#define DISTANCE_BLUE_CIRCLE 20 //Satellite
#define SPEED_MOVE 3 //Speed of movement: each time W-A-S-D are pressed how many pixels will the player move
#define SPEED_ROTATE 3 //Speed of rotation: each time left or right arrow are pressed how many degrees will the player rotate


# define TEX_WIDTH 64 
# define TEX_HEIGHT 64 
#define NUM_TEXTURES 4

/*Keyboard events*/
# define W_MOVE_FORWARD 119
# define S_MOVE_BACKWARDS 115
# define A_MOVE_LEFT 97
# define D_MOVE_RIGHT 100
# define ROTATE_LEFT 65361 //Left arrow
# define ROTATE_RIGHT 65363 //Right arrow

enum width_or_height
{
    X_WIDTH,
    Y_HEIGHT
};

typedef struct s_mlx
{
    void    *mlx_ptr;  
    void    *win_ptr;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_mlx;

typedef struct s_cub
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    void **textures;  
    char **textures_data;
    int floor_color;
    int ceiling_color;
    char **map;
    int map_height;
    int map_width;
    t_mlx *mlx;  
    // Variables necesarias para manejar texturas en MLX
    int bits_per_pixel;
    int line_length; 
    int endian;       // Orden de bytes (endianness)
    
    
    /************************************* Info about Player *************************************/
    /*Position in 2D Map*/
    double x_pos_dec; //x_position_decimal
    double y_pos_dec;
    int x_pos_ind; //x_position_index
    int y_pos_ind;
    int x_pos_pixel; //x_position_pixel in window
    int y_pos_pixel;
    int x_satellite_pixel;
    int y_satellite_pixel;

    /* Direction vector */
    double x_dir_dec;
    double y_dir_dec;
    char direction;
    float angle_degree;
    float angle_radian;
    
    double planeX;
    double planeY;
}   t_cub;

typedef struct s_data
{
    t_mlx *mlx;
    t_cub *cub;
}   t_data;

// Prototipos de funciones
void print_cub_data(t_cub *cub);
int parse_color(char *line);
char *extract_path(char *line);
void parse_map_line(t_cub *cub, char *line);
void validate_map(t_cub *cub);
void parse_line(t_cub *cub, char *line);
void read_cub_file(t_cub *cub, const char *filename);
void exit_with_error(const char *message);
void check_file_extension(const char *filename);
void free_resources(t_cub *cub);
void print_cub_data(t_cub *cub);
char *remove_spaces(char *line);
char *trim_whitespace(char *str);
/*
void calculate_step_and_side_dist(t_cub *cub, double rayDirX, double rayDirY,
                                   int *stepX, int *stepY, double *sideDistX,
                                    double *sideDistY, int mapX, int mapY);
int perform_dda(t_cub *cub, int *mapX, int *mapY, int *side, double *sideDistX, double *sideDistY,
                int stepX, int stepY, double rayDirX, double rayDirY);
double calculate_perpendicular_distance(t_cub *cub, int mapX, int mapY, double rayDirX, double rayDirY, int stepX, int stepY);
int calculate_draw_start(int lineHeight);
int calculate_draw_end(int lineHeight);
int determine_texture_side(double rayDirX, double rayDirY, int side);
double calculate_wallX(t_cub *cub, double perpWallDist, double rayDirX, double rayDirY, int side);
int calculate_texture_y(int lineHeight);*/

// Funciones de carga de texturas
int load_texture(t_cub *cub, int index, char *texture_path);
void load_textures(t_cub *cub);

// Función para obtener el color de una textura
unsigned int get_texture_color(t_cub *cub, int texNum, int texX, int texY);
// MLX
void init_window(t_mlx *mlx);
int close_program(t_mlx *mlx);

/* 0_main.c */

/* 1_read_cub_file.c */

/* 2_init.c */
void init_all_default(t_data *data);
void init_all(t_data *data);
int is_map(t_cub *cub, int x, int y);
void angle_to_rad(t_data *data);

/* 3_events.c */
void ft_events_init(t_data *data);
int key_handler(int keycode, t_data *data);
float pixel_to_decimal_map(int pixel, enum width_or_height indicator);

/* raycast.c */
void raycast(t_data *data);

/* render.c */
void render_sky_and_floor(t_data *data);
int *render_next_frame(t_data *data);

/* textures.c */
unsigned int get_texture_color(t_cub *cub, int texNum, int texX, int texY);
int load_texture(t_cub *cub, int index, char *texture_path);
void load_textures(t_cub *cub);

/* 99_utils.c */
void my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);

#endif
