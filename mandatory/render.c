/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:20:01 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/25 13:03:32 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_ceiling(t_data *data)
{
	unsigned int	ceiling_color;
	int				x;
	int				y;

	ceiling_color = data->cub->ceiling_color;
	y = 0;
	while (y < screenHeight / 2)
	{
		x = 0;
		while (x < screenWidth)
		{
			my_mlx_pixel_put(data, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

void	render_floor(t_data *data)
{
	unsigned int	floor_color;
	int				x;
	int				y;

	floor_color = data->cub->floor_color;
	y = screenHeight / 2;
	while (y < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			my_mlx_pixel_put(data, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	render_sky_and_floor(t_data *data)
{
	render_ceiling(data);
	render_floor(data);
}

void	render_update_game(t_data *data)
{
	render_sky_and_floor(data);
	raycast(data);
	if (data->mlx->mlx_ptr && data->mlx->win_ptr)
	{
		mlx_put_image_to_window(data->mlx->mlx_ptr,
			data->mlx->win_ptr, data->mlx->img, 0, 0);
	}
}
/*
*   Returns x = x pixel position where image must be displayed
*   in 2d map in the window (mlx):
*
*   Window dimensions are defined in cub3d.h:
*       - HEIGHT_WINDOW = 1440
*       - WIDTH_WINDOW = 2560
*
*   Map dimensions are defined in cub3d.h:
*       - HEIGHT_MAP = 840
*       - WIDTH_MAP = 840
*
*   Map I'm using for use case: cheese_maze
*
*   cheese_maze dimensions: 21 (height) x 21 (width)
*
*   Right now image is not being resized. Just using 40x40 
*   smallest possibility Canva is allowing to us
*   Focusing on resizing could be considered one project finished
*   if still time before evaluations.
*
*   Why do we do '+40'? 40 is the size of a wall. We are hardcoding
*   it because of the image size we're using. Ideal would be resizing.
*
*/

int	scale_x(int x_index)
{
	int	x;

	x = 1720;
	while (x_index)
	{
		x += 40;
		x_index--;
	}
	return (x);
}

/*  scale_y
*
*   The initial position of the map in the window is in the following
*   coordinates: (1720, 600)
*           x = WIDTH_WINDOW - WIDTH_MAP = 2560 - 840 = 1720    (x = 1720)
*           y = HEIGHT_WINDOW - HEIGHT_MAP = 1440 - 840 = 600    (y = 600)
*/
int	scale_y(int y_index)
{
	int	y;

	y = 600;
	while (y_index)
	{
		y += 40;
		y_index--;
	}
	return (y);
}

void	put_each_wall(t_data *data, int x_index, int y_index)
{
	char	*relative_path;
	int		img_width;
	int		img_height;
	void	*img_wall;

	relative_path = "./textures/others/1_wall_smallest_40x40px.xpm";
	img_wall = mlx_xpm_file_to_image(data->mlx->mlx_ptr,
			relative_path, &img_width, &img_height);
	if (!img_wall)
		printf(RED"Error: img is NULL\n"RESET_COLOUR);
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr,
		img_wall, scale_x(x_index), scale_y(y_index));
}

/* px_is_in_wall
*
* Returns:
*   1: YES, x and y pixel position is in a wall
*   0: NO, x and y pixel position is not in a wall
*
*
*   How?
*   > 2D Map dimensions are defined in .h file: 840 x 840 px
*   > t_data *data stores map height and width (number of boxes).
*   > We'll apply rule of 3 to get the x and y position
*
*   .h file HEIGHT_MAP (in px) ------- t_data *data
										data->cub->map_height (number of boxes)
*   (whatever) px position -----------> (result) box 
*/
int	px_is_in_wall(int x_px, int y_px, t_data *data)
{
	int	x_index;
	int	y_index;

	x_index = x_px * data->cub->map_width / WIDTH_MAP;
	y_index = y_px * data->cub->map_height / HEIGHT_MAP;
	if (data->cub->map[y_index][x_index] == '1')
		return (1);
	else
		return (0);
}

/* put_walls_in_map
*
*   It's the #1 step to visualize 2d map in window  
*
*   The funcion iterates through 2d map .cub input file and calls put_each_wall
*   function to display each wall when '1' found.
*/
void	put_walls_in_map(t_data *data)
{
	int	x_px;
	int	y_px;

	y_px = 0;
	while (y_px < HEIGHT_MAP)
	{
		x_px = 0;
		while (x_px < WIDTH_MAP)
		{
			if (px_is_in_wall(x_px, y_px, data))
			{
				my_mlx_pixel_put(data, x_px, y_px, 0x00FF0000);
			}
			x_px++;
		}
		y_px++;
	}
}

void	put_dot_in_map(t_data *data)
{
	char	*relative_path;
	int		img_width;
	int		img_height;
	void	*img_dot;

	relative_path = "./textures/others/5_pixel_by_5_pixel_red_etc.xpm";
	img_dot = mlx_xpm_file_to_image(data->mlx->mlx_ptr, relative_path,
			&img_width, &img_height);
	if (!img_dot)
		printf(RED"Error: img is NULL\n"RESET_COLOUR);
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, img_dot,
		data->cub->x_pos_pixel, data->cub->y_pos_pixel);
}

void	draw_blue_dot(t_data *data, int i, void *img_circle)
{
	float	direction_vector_x;
	float	direction_vector_y;
	int		put_blue_x_px;
	int		put_blue_y_px;

	direction_vector_x = cos((i * PI) / 180);
	direction_vector_y = sin((i * PI) / 180);
	put_blue_x_px = data->cub->x_pos_pixel + (direction_vector_x)
		* DISTANCE_BLUE_CIRCLE;
	put_blue_y_px = data->cub->y_pos_pixel + (direction_vector_y)
		* DISTANCE_BLUE_CIRCLE;
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr,
		img_circle, put_blue_x_px, put_blue_y_px);
}

void	put_circle_around_player(t_data *data)
{
	char	*relative_path;
	int		img_width;
	int		img_height;
	void	*img_circle;
	int		i;

	relative_path = "./textures/others/blue_dot.xpm";
	img_circle = mlx_xpm_file_to_image(data->mlx->mlx_ptr,
			relative_path, &img_width, &img_height);
	if (!img_circle)
	{
		printf("Error: No se pudo cargar la textura del círculo.\n");
		return ;
	}
	i = 0;
	while (i < 360)
	{
		draw_blue_dot(data, i, img_circle);
		i++;
	}
}

void	put_satellite_in_map(t_data *data)
{
	char	*relative_path;
	int		img_width;
	int		img_height;
	void	*img_satellite;

	relative_path = "./textures/others/5_pixel_by_5_pixel_red_etc.xpm";
	img_satellite = mlx_xpm_file_to_image(data->mlx->mlx_ptr,
			relative_path, &img_width, &img_height);
	if (!img_satellite)
		printf(RED"Error: img is NULL\n"RESET_COLOUR);
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr,
		img_satellite, data->cub->x_satellite_pixel,
		data->cub->y_satellite_pixel);
}

void	put_2d_map_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIDTH_MAP)
	{
		y = 0;
		while (y < HEIGHT_MAP)
		{
			my_mlx_pixel_put(data, x, y, 0x00FFFFCC);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->mlx->img, 0, 0);
}

void	render_update_2d_map(t_data *data)
{
	put_2d_map_background(data);
	put_walls_in_map(data);
	put_dot_in_map(data);
	put_circle_around_player(data);
	put_satellite_in_map(data);
}

int	*render_next_frame(t_data *data)
{
	if (!data->mlx || !data->cub)
	{
		printf("Error: Puntero a mlx o cub es nulo.\n");
		return (NULL);
	}
	render_update_game(data);
	render_update_2d_map(data);
	return (0);
}
