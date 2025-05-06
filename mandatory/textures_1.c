/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:17:54 by uxmancis          #+#    #+#             */
/*   Updated: 2024/11/15 17:50:04 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	get_texture_color(t_data *data, int texNum, int texX, int texY)
{
	unsigned int	color;

	if (texNum < 0 || texNum >= 4)
	{
		return (0);
	}
	if (data->cub->textures_data[texNum] == NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (texX < 0 || texX >= TEX_WIDTH || texY < 0 || texY >= TEX_HEIGHT)
	{
		return (0);
	}
	color = *(unsigned int *)(data->cub->textures_data[texNum]
			+ (texY * data->cub->line_length
				+ texX * (data->cub->bits_per_pixel / 8)));
	return (color);
}

// Función auxiliar para verificar índice y ruta de textura.
int	verify_texture_params(int index, char *texture_path)
{
	if (index < 0 || index >= 4)
	{
		return (-1);
	}
	if (!texture_path)
	{
		return (-1);
	}
	return (0);
}

// Función auxiliar para cargar la imagen de textura.
int	load_texture_image(t_data *data, int index, char *texture_path)
{
	int	width;
	int	height;

	width = TEX_WIDTH;
	height = TEX_HEIGHT;
	data->cub->textures[index] = mlx_xpm_file_to_image(data->cub->mlx->mlx_ptr,
			texture_path, &width, &height);
	if (!data->cub->textures[index])
	{
		return (-1);
	}
	return (0);
}

// Función auxiliar para obtener los datos de la textura.
int	get_texture_data(t_data *data, int index)
{
	data->cub->textures_data[index] = mlx_get_data_addr(
			data->cub->textures[index], &data->cub->bits_per_pixel,
			&data->cub->line_length, &data->cub->endian);
	if (!data->cub->textures_data[index])
	{
		return (-1);
	}
	return (0);
}

// Función principal de carga de textura que llama a las funciones auxiliares.
int	load_texture(t_data *data, int index, char *texture_path)
{
	if (verify_texture_params(index, texture_path) == -1)
		return (-1);
	if (load_texture_image(data, index, texture_path) == -1)
		return (-1);
	if (get_texture_data(data, index) == -1)
		return (-1);
	return (0);
}
