/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:20:01 by uxmancis          #+#    #+#             */
/*   Updated: 2024/11/15 17:26:32 by jllarena         ###   ########.fr       */
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
	if (!data->mlx || !data->cub)
	{
		return (NULL);
	}
	render_update_game(data);
	render_update_2d_map(data);
	return (0);
}
