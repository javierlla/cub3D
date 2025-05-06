/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:33:56 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/25 14:48:15 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*  Checks whether if x-y passed coordinate in map indicates
*   player's position or not.
*
*   Player's position is indicated with 'N', 'S', 'W', 'E'.
*/
int	is_player_position(t_cub *cub, int x, int y)
{
	if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
		|| cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
	{
		return (1);
	}
	return (0);
}

/* Checks whether if x-y passed as parameter
*  are part of map.
*----------------------------------------------------------*/
int	is_map(t_cub *cub, int x, int y)
{
	if (cub->map[y][x] == '1' || cub->map[y][x] == '0'
		|| cub->map[y][x] == 'N' || cub->map[y][x] == 'S'
		|| cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
		return (1);
	return (0);
}
