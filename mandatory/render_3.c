/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:44:01 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/13 19:51:34 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (data->cub->map[y_index][x_index])
	{
		if (data->cub->map[y_index][x_index] == '1'
			|| data->cub->map[y_index][x_index] == '3')
			return (1);
		else
			return (0);
	}
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
	mlx_destroy_image(data->mlx->mlx_ptr, img_dot);
}
