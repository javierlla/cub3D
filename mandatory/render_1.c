/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:20:01 by uxmancis          #+#    #+#             */
/*   Updated: 2024/11/01 18:34:26 by uxmancis         ###   ########.fr       */
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
	while (y < SCREENHEIGHT / 2)
	{
		x = 0;
		while (x < SCREENWIDTH)
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
	y = SCREENHEIGHT / 2;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
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

int	*render_next_frame(t_data *data)
{
	printf(RED"AAAAAAAAAAAAH red\n"RESET_COLOUR);
	if (!data->mlx || !data->cub)
	{
		printf("Error: Puntero a mlx o cub es nulo.\n");
		return (NULL);
	}
	render_update_game(data);
	render_update_2d_map(data);

	printf("                     |      x = %d, y = %d   | x = %.2f, y = %.2f |   x = %d, y = %d       |     %c     | x = %.2f, y = %.2f |   x = %d, y = %d |\n",
    data->cub->x_pos_ind, data->cub->y_pos_ind, //Map position (INDEX) %d
    data->cub->x_pos_dec, data->cub->y_pos_dec, //Map position (dec) %.2f
    data->cub->x_pos_pixel, data->cub->y_pos_pixel, //Window Position (pixel) %d
    data->cub->direction, //DIRECTION
    data->cub->x_dir_dec, data->cub->y_dir_dec, //DirVector (dec)
    data->cub->x_satellite_pixel, data->cub->y_satellite_pixel); //SAT. (pixel)

    
	return (0);
}
