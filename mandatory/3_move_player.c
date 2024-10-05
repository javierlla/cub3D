/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_move_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:12:35 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/05 17:27:21 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int move_player (t_data *data)
{
    //printf("move_player\n");
    if (data->cub->keyboard_flags->w_flag == 0
        && data->cub->keyboard_flags->a_flag == 0
        && data->cub->keyboard_flags->s_flag == 0
        && data->cub->keyboard_flags->d_flag == 0
        && data->cub->keyboard_flags->l_flag == 0
        && data->cub->keyboard_flags->r_flag == 0)
    {
        //printf("everything is 0 - flags\n");
        return (0);
    }
		return (0);
    if (data->cub->keyboard_flags->w_flag == 1)
        //move_forward(data);
    if (data->cub->keyboard_flags->a_flag == 1)
        //move_left(data);
    if (data->cub->keyboard_flags->s_flag == 1)
        //move_backwards(data);
    if (data->cub->keyboard_flags->d_flag == 1)
        //move_right(data);
    if (data->cub->keyboard_flags->l_flag == 1)
        //rotate_left(data);
    if (data->cub->keyboard_flags->r_flag == 1)
    {
        printf(MAGENTA"rotate_right\n"RESET_COLOUR);
        rotate_right(data);
    }
    return (0);
}