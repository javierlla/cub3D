/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:55:33 by jllarena          #+#    #+#             */
/*   Updated: 2024/11/15 17:52:54 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Mini-función para inicializar las matrices de texturas.
void	init_textures_arrays(t_data *data)
{
	int	i;

	data->cub->textures = malloc(sizeof(void *) * 4);
	data->cub->textures_data = malloc(sizeof(char *) * 4);
	if (!data->cub->textures || !data->cub->textures_data)
	{
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 4)
	{
		data->cub->textures[i] = NULL;
		data->cub->textures_data[i] = NULL;
		i++;
	}
}

// Función principal de carga de todas las texturas.
void	load_textures(t_data *data)
{
	int	i;

	init_textures_arrays(data);
	if (load_texture(data, 0, data->cub->north_texture))
		printf("Error: North texture not loaded: %s\n",
			data->cub->north_texture);
	if (load_texture(data, 1, data->cub->south_texture))
		printf("Error: South texture not loaded: %s\n",
			data->cub->south_texture);
	if (load_texture(data, 2, data->cub->west_texture))
		printf("Error: West texture not loaded: %s\n",
			data->cub->west_texture);
	if (load_texture(data, 3, data->cub->east_texture))
		printf("Error: East texture not loaded: %s\n",
			data->cub->east_texture);
	i = 0;
	while (i < 4)
	{
		if (!data->cub->textures[i] || !data->cub->textures_data[i])
		{
			exit_with_error("texture failed");
			return ;
		}
		i++;
	}
}
