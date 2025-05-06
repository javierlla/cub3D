/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:26:45 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 12:46:53 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	verify_wallx_zero_one(t_raycast_vars *r)
{
	if (r->wall_x < 0 || r->wall_x > 1)
	{
		printf("Warning: wallX fuera de rango. Valor actual: %f\n", r->wall_x);
		r->wall_x = fmod(r->wall_x + 1, 1);
	}
}

void	texture_coordinates(t_raycast_vars *r)
{
	r->tex_x = (int)(r->wall_x * (double)TEX_WIDTH);
	if (r->side == 0 && r->raydir_x > 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if (r->tex_x < 0)
		r->tex_x = 0;
	if (r->tex_x >= TEX_WIDTH)
		r->tex_x = TEX_WIDTH - 1;
	if (r->side == 0)
	{
		if (r->raydir_x < 0)
			r->texnum = 2;
		else
			r->texnum = 3;
	}
	else
	{
		if (r->raydir_y < 0)
			r->texnum = 0;
		else
			r->texnum = 1;
	}
}

void	paint_wall_line(t_data *data, t_raycast_vars *r, int x)
{
	int				y;
	unsigned int	colour;

	y = r->drawstart;
	while (y < r->drawend)
	{
		r->d = y * 256 - SCREENHEIGHT * 128 + r->lineheight * 128;
		r->tex_y = ((r->d * TEX_HEIGHT) / r->lineheight) / 256;
		if (r->tex_y < 0)
			r->tex_y = 0;
		if (r->tex_y >= TEX_HEIGHT)
			r->tex_y = TEX_HEIGHT - 1;
		colour = get_texture_color(data, r->texnum, r->tex_x, r->tex_y);
		my_mlx_pixel_put(data, x, y, colour);
		y++;
	}
}
