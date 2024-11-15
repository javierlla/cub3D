/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:14:15 by uxmancis          #+#    #+#             */
/*   Updated: 2024/11/15 17:23:38 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* normalize_minus_one_one
*
*  Before: x is an integer inside [0-ScreenWidth] range
*
*  After: x is a double inside [-1,1] range
*
*  Purpose: whatever the ScreenWidth may vary, for us we 
*           want work with a range of [-1,1], from left to rigt
*           of the screen.
*
*           -1 ------------------ 0 ------------------ 1
*
*  How?

*  1) Rule of 3 to get double [0-2]
*
*     2 (total) ------------------ ScreenWidth
*     (result) ------------------ (whatever)
*
*  2) -1 to get inside [-1,1] range
*		Convertir (result) de [0-2] a [-1,1]
*/
double	normalize_minus_one_one(int x)
{
	double	result;

	result = x * 2 / (double)SCREENWIDTH;
	result = result -1;
	return (result);
}

/* get_ray_dir
*
*  If conditionals are used to limit rayDirX and rayDirY to avoid
*  division by zero or extreme values.
*/
void	get_ray_dir(t_data *data, t_raycast_vars *r, int x)
{
	r->camera_x = -normalize_minus_one_one(x);
	r->raydir_x = data->cub->x_dir_dec + data->cub->plane_x * r->camera_x;
	r->raydir_y = data->cub->y_dir_dec + data->cub->plane_y * r->camera_x;
	if (fabs(r->raydir_x) < 0.0001)
		r->raydir_x = 0.0001;
	if (fabs(r->raydir_y) < 0.0001)
		r->raydir_y = 0.0001;
}

void	set_initial_ray_pos(t_data *data, t_raycast_vars *r)
{
	r->map_x = (int)data->cub->x_pos_dec;
	r->map_y = (int)data->cub->y_pos_dec;
}

void	raycast_column(t_data *data, t_raycast_vars *r, int x)
{
	get_ray_dir(data, r, x);
	set_initial_ray_pos(data, r);
	calculate_delta_dist(r);
	define_ray_dir(data, r);
	dda(data, r);
	get_perp_wall_dist(data, r);
	get_wall_height_in_window(r);
	set_draw_start_and_end(r);
	get_texture_coordinates(data, r);
	verify_wallx_zero_one(r);
	texture_coordinates(r);
	paint_wall_line(data, r, x);
}

void	raycast(t_data *data)
{
	t_raycast_vars	*r;
	int				x;

	if (data->cub->map == NULL)
	{
		exit_with_error("the map is not running.\n");
		return ;
	}
	r = malloc(sizeof(t_raycast_vars));
	if (r == NULL)
	{
		exit_with_error("memory failed.");
		return ;
	}
	x = 0;
	while (x < SCREENWIDTH)
	{
		raycast_column(data, r, x);
		x++;
	}
	free(r);
}
