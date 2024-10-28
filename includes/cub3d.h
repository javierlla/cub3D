/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:28:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 13:06:11 by jllarena         ###   ########.fr       */
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
# include <stdbool.h>

# define GRAY "\033[0;90m"
# define RED "\033[0;31m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define WHITE_COLOR "\033[37m"
# define RESET_COLOUR "\033[0m"
# define AQUAMARINE "\033[0;96m"

# define PI 3.14159265358979323846

/*---------- Dimensions | Window 1: Cub D (Project--------*/
# define SCREENWIDTH 2560  // HEIGHT_WINDOW in Uxu's branch
# define SCREENHEIGHT 1440 // HEIGHT_WINDOW in Uxu's branch
/*---------- Dimensions | Window 2: Map (Debugging Purposes) --------*/
# define HEIGHT_MAP 600 
# define WIDTH_MAP 600

/* ----- 2D Map Visualization ------*/
# define DISTANCE_BLUE_CIRCLE 20 // Satellite
# define SPEED_MOVE 0.2          
# define SPEED_ROTATE 10         

# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define NUM_TEXTURES 4

/*Keyboard events*/
# define W_MOVE_FORWARD 119
# define S_MOVE_BACKWARDS 115
# define A_MOVE_LEFT 97
# define D_MOVE_RIGHT 100
# define ROTATE_LEFT 65363  // Left arrow
# define ROTATE_RIGHT 65361 // Right arrow

typedef struct raycast_variables
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;

/* Initial ray position based on player's decimal position*/
	int		map_x; // data->cub->x_pos_dec;
	int		map_y; // data->cub->y_pos_dec;
/* Distance of ray in space*/
	double	side_dist_x ;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side; // Which side of the wall has been hit
	double	perp_wall_dist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		texnum;
	int		d;
}	t_raycast_vars;

enum e_width_or_height
{
	X_WIDTH,
	Y_HEIGHT,
	X_PX,
	Y_PX
};

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_cub
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	void	**textures;
	char	**textures_data;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_height;
	int		map_width;
	t_mlx	*mlx;
	int		bits_per_pixel;
	int		line_length;
	int		endian; // Orden de bytes (endianness)
/**************** Info about Player *****************/
/*Position in 2D Map*/
	double	x_pos_dec; // x_position_decimal
	double	y_pos_dec;
	int		x_pos_ind; // x_position_index
	int		y_pos_ind;
	int		x_pos_pixel; // x_position_pixel in window
	int		y_pos_pixel;
	int		x_satellite_pixel;
	int		y_satellite_pixel;
/* Direction vector */
	double	x_dir_dec;
	double	y_dir_dec;
	char	direction;
	float	angle_degree;
	float	angle_radian;
	double	plane_x;
	double	plane_y;
}	t_cub;

typedef struct s_data
{
	t_mlx	*mlx;
	t_cub	*cub;
}	t_data;

// Prototipos de funciones	
void			print_cub_data(t_cub *cub);
int				parse_color(char *line);
char			*extract_path(char *line);
void			parse_map_line(t_data *data, char *line);
void			validate_map(t_data *data);
void			parse_line(t_data *data, char *line);
void			read_cub_file(t_data *data, const char *filename);
void			exit_with_error(const char *message);
void			check_file_extension(const char *filename);
void			free_resources(t_data *data);
char			*remove_spaces(char *line);
char			*trim_whitespace(char *str);
// Función para obtener el color de una textura
// MLX
void			init_window(t_data *data);
int				close_program(t_data *data);
/* read_cub_file.c */
void			validate_player_position(t_data *data,
					int *player_count, int i, int j);
void			parse_map_line(t_data *data, char *line);
void			process_line(t_data *data, char *buffer, int start, int end);
void			validate_map(t_data *data);
/* 2_init.c */
int				decimal_to_pixel(t_data *data, float decimal,
					enum e_width_or_height indicator);
void			init_all_default(t_data *data);
void			init_all(t_data *data);
int				is_map(t_cub *cub, int x, int y);
int				is_player_position(t_cub *cub, int x, int y);
void			angle_to_rad(t_data *data);
void			get_initial_angle(t_data *data);
void			set_player_position_2(t_data *data,
					int x_map_index, int y_map_index);
/* 3_moves.c */
void			ft_events_init(t_data *data);
int				key_handler(int keycode, t_data *data);
float			pixel_to_decimal_map(int pixel,
					enum e_width_or_height indicator);
void			move_right(t_data *data);
void			move_left(t_data *data);
void			move_backward(t_data *data);
void			move_forward(t_data *data);
void			apply_move_and_render(t_data *data,
					double new_x, double new_y);
int				is_map_limit(t_data *data, float tmp_x_2_check,
					float tmp_y_2_check);
/* raycast.c */
void			raycast(t_data *data);
void			calculate_delta_dist(t_raycast_vars *r);
void			define_ray_dir(t_data *data, t_raycast_vars *r);
void			dda_step(t_data *data, t_raycast_vars *r, int *hit);
void			dda(t_data *data, t_raycast_vars *r);
void			get_perp_wall_dist(t_data *data, t_raycast_vars *r);
void			get_wall_height_in_window(t_raycast_vars *r);
void			set_draw_start_and_end(t_raycast_vars *r);
void			get_texture_coordinates(t_data *data, t_raycast_vars *r);
void			verify_wallx_zero_one(t_raycast_vars *r);
void			texture_coordinates(t_raycast_vars *r);
void			paint_wall_line(t_data *data, t_raycast_vars *r, int x);
/* render.c */
void			render_update_2d_map(t_data *data);
void			put_2d_map_background(t_data *data);
void			render_sky_and_floor(t_data *data);
int				*render_next_frame(t_data *data);
void			put_each_wall(t_data *data, int x_index, int y_index);
void			put_dot_in_map(t_data *data);
void			put_walls_in_map(t_data *data);
/* textures.c */
unsigned int	get_texture_color(t_data *data, int texNum, int texX, int texY);
int				load_texture(t_data *data, int index, char *texture_path);
void			load_textures(t_data *data);
/* 99_utils.c */
void			my_mlx_pixel_put(t_data *data, int x,
					int y, unsigned int color);

#endif
