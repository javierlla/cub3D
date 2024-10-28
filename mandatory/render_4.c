/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:44:06 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 11:51:49 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
