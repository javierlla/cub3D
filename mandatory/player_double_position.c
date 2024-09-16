/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_double_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:58:47 by jllarena          #+#    #+#             */
/*   Updated: 2024/09/16 14:31:02 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define TILE_SIZE 40 // Tamaño de cada caja en píxeles

void calculate_decimal_position(t_coordinates *player)
{
    // Convertimos los índices y offsets a coordenadas decimales en el mapa
    player->x_decimal = player->x_index * TILE_SIZE + player->offset_x;
    player->y_decimal = player->y_index * TILE_SIZE + player->offset_y;
}

void update_player_position(t_coordinates *player, double move_x, double move_y)
{
    // Actualiza el offset en función del movimiento del jugador
    player->offset_x += move_x;
    player->offset_y += move_y;

    // Si el jugador se mueve fuera de la celda actual, actualizamos el índice
    if (player->offset_x >= TILE_SIZE)
    {
        player->x_index += 1;
        player->offset_x -= TILE_SIZE; // Reseteamos el offset dentro de la nueva celda
    }
    else if (player->offset_x < 0)
    {
        player->x_index -= 1;
        player->offset_x += TILE_SIZE; // Movemos el jugador a la celda izquierda
    }

    if (player->offset_y >= TILE_SIZE)
    {
        player->y_index += 1;
        player->offset_y -= TILE_SIZE;
    }
    else if (player->offset_y < 0)
    {
        player->y_index -= 1;
        player->offset_y += TILE_SIZE;
    }

    // Calculamos la nueva posición decimal
    calculate_decimal_position(player);
}

/*int main()
{
    t_coordinates player;

    // Posición inicial del jugador en índices (en la celda 3, 4)
    player.x_index = 3;
    player.y_index = 4;
    player.offset_x = 0.0;
    player.offset_y = 0.0;

    Supongamos que el jugador se mueve 25 píxeles a la derecha y 15 píxeles hacia abajo,
    en el momento que supere loss 40 pixeles offset, sumara 1 al indice, es decir pasará
    a la siguiente caja
    
    double move_x = 25.0;
    double move_y = 15.0;

    // Actualizamos la posición del jugador con ese movimiento
    update_player_position(&player, move_x, move_y);

    printf("Nueva posición decimal del jugador: (%.2f, %.2f)\n", player.x_decimal, player.y_decimal);
    printf("Nueva posición en índices: (%d, %d)\n", player.x_index, player.y_index);
    printf("Offset dentro de la celda: (%.2f, %.2f)\n", player.offset_x, player.offset_y);

    return 0;
}*/
