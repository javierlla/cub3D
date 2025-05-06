/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:43:45 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:51:19 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		printf("Error: circle around player not loading.\n");
		return ;
	}
	i = 0;
	while (i < 360)
	{
		draw_blue_dot(data, i, img_circle);
		i++;
	}
	mlx_destroy_image(data->mlx->mlx_ptr, img_circle);
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
	mlx_destroy_image(data->mlx->mlx_ptr, img_satellite);
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
