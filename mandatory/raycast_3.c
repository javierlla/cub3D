/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:26:47 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 12:47:16 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_perp_wall_dist(t_data *data, t_raycast_vars *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - data->cub->x_pos_dec
				+ (1 - r->step_x) / 2) / r->raydir_x;
	else
		r->perp_wall_dist = (r->map_y - data->cub->y_pos_dec
				+ (1 - r->step_y) / 2) / r->raydir_y;
	if (r->perp_wall_dist <= 0.01)
		r->perp_wall_dist = 0.01;
}

void	get_wall_height_in_window(t_raycast_vars *r)
{
	r->lineheight = (int)(SCREENHEIGHT / r->perp_wall_dist);
	if (r->lineheight > SCREENHEIGHT)
		r->lineheight = SCREENHEIGHT;
}

void	set_draw_start_and_end(t_raycast_vars *r)
{
	r->drawstart = -r->lineheight / 2 + SCREENHEIGHT / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + SCREENHEIGHT / 2;
	if (r->drawend >= SCREENHEIGHT)
		r->drawend = SCREENHEIGHT - 1;
}

void	get_texture_coordinates(t_data *data, t_raycast_vars *r)
{
	if (r->side == 0)
		r->wall_x = data->cub->y_pos_dec + r->perp_wall_dist * r->raydir_y;
	else
		r->wall_x = data->cub->x_pos_dec + r->perp_wall_dist * r->raydir_x;
	r->wall_x -= floor(r->wall_x);
}
