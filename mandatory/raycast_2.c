/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:26:49 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 20:05:49 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* calculate_delta_dist
*
*	fabs is used to make sure distance is positive.
*
*	deltaDistX and deltaDistY represent the distance
*   the ray has to travel from one x or y-side to the
*	next x or y-side.
*
*	Example:
*   If rayDirX = 1, then deltaDistX = 1
*   If rayDirX = -1, then deltaDistX = 1
*   If rayDirX = 0.5, then deltaDistX = 2
*   If rayDirX = -0.5, then deltaDistX = 2
*
*   Summary:
*
*
*
*   Explanation of logic behind operation: 
*    - We only care about when ray crosses a grid line
*
*
*  7 ---|---|---|---|---|-         P (1, 6): 1 unit in X direction,
*  6 ---P---|---|---|---|-         6 units in Y direction for every 
*  4 ---|---|---|---|---|-         step along ray's path.
*  5 ---|---|---|---|---|-         
*  3 ---|---|---|---|---|-  rayDirX = 1;
*  2 ---|---|---|---|---|-      deltaDistX = 1 / rayDirX = 1 / 1 = 1
*  1 ---|---|---|---|---|-  rayDirY = 6;
*  0   1   2   3   4   5        deltaDistY = 1 / rayDirY= 1 / 6 = 0.166666      
*
*
* R (3, 2) P is more vertical than horizontalR is more horizontal than vertical
*/
void	calculate_delta_dist(t_raycast_vars *r)
{
	r->delta_dist_x = fabs(1 / r->raydir_x);
	r->delta_dist_y = fabs(1 / r->raydir_y);
}

void	define_ray_dir(t_data *data, t_raycast_vars *r)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (data->cub->x_pos_dec - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - data->cub->x_pos_dec)
			* r->delta_dist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (data->cub->y_pos_dec - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - data->cub->y_pos_dec)
			* r->delta_dist_y;
	}
}

void	dda_step(t_data *data, t_raycast_vars *r, int *hit)
{
	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dist_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
	if (r->map_x < 0 || r->map_x >= data->cub->map_width
		|| r->map_y < 0 || r->map_y >= data->cub->map_height)
	{
		*hit = 1;
	}
	else if (data->cub->map[r->map_y][r->map_x] == '1')
	{
		*hit = 1;
	}
}

void	dda(t_data *data, t_raycast_vars *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		dda_step(data, r, &hit);
	}
}
