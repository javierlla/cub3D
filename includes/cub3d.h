/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:28:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/03 18:50:32 by jllarena         ###   ########.fr       */
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

# define screenWidth 1000
# define screenHeight 750
# define TEX_WIDTH 64 // Ancho de las texturas
# define TEX_HEIGHT 64 // Alto de las texturas

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
    void **textures;          // Arreglo para las texturas
    char **textures_data;     // Datos de las texturas (imagen cruda)
    int floor_color;
    int ceiling_color;
    char **map;
    int map_height;
    int map_width;
    t_mlx *mlx;               // Puntero a t_mlx (MLX)
    
    // Variables necesarias para manejar texturas en MLX
    int bits_per_pixel;       // Bits por píxel (profundidad de color)
    int line_length;          // Longitud de una línea de la imagen
    int endian;               // Orden de bytes (endianness)

    double posX;
    double posY;  // Posición inicial del jugador
    double dirX;
    double dirY;   // Dirección inicial (mirando hacia la izquierda)
    double planeX;
    double planeY; // Plano de la cámara (campo de visión)
}   t_cub;


// Prototipos de funciones
void print_cub_data(t_cub *cub);
int parse_color(char *line);
char *extract_path(char *line);
void parse_map_line(t_cub *cub, char *line);
void validate_map(t_cub *cub);
void parse_line(t_cub *cub, char *line);
void read_cub_file(t_cub *cub, const char *filename);
void exit_with_error(const char *message);
void normalize_map(t_cub *cub);
void check_file_extension(const char *filename);
void validate_closed_map(t_cub *cub);
void free_resources(t_cub *cub);
void print_cub_data(t_cub *cub);
char *remove_spaces(char *line);
char *trim_whitespace(char *str);

//raycast
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
int calculate_texture_y(int lineHeight);


// Funciones de carga de texturas
int load_texture(t_cub *cub, int index, char *texture_path);
void free_textures(t_cub *cub);
void load_textures(t_cub *cub);

// Función para obtener el color de una textura
unsigned int get_texture_color(t_cub *cub, int texNum, int texX, int texY);

// MLX
void init_window(t_mlx *mlx);
void mlx_loop_mine(t_mlx *mlx);
int close_program(t_mlx *mlx);

#endif
