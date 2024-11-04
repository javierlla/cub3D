/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:17:54 by uxmancis          #+#    #+#             */
/*   Updated: 2024/11/04 18:03:23 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	get_texture_color(t_data *data, int texNum, int texX, int texY)
{
	unsigned int	color;

	if (texNum < 0 || texNum >= 4)
	{
		printf("Error: texturas fuera de límites: %d\n", texNum);
		return (0);
	}
	if (data->cub->textures_data[texNum] == NULL)
	{
		printf("Error: La textura %d no está cargada.\n", texNum);
		// return (0);
		exit(EXIT_FAILURE);
	}
	if (texX < 0 || texX >= TEX_WIDTH || texY < 0 || texY >= TEX_HEIGHT)
	{
		printf("Coordenadas extralimitadas : texX=%d, texY=%d\n", texX, texY);
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
		printf("Error: Índice de textura fuera de límites: %d\n", index);
		return (-1);
	}
	if (!texture_path)
	{
		//		exit(EXIT_FAILURE);
		printf("Error: Ruta de la textura es nula %d.\n", index);
		return (-1);
	}
	printf(GREEN"verify_texture_params completed\n"RESET_COLOUR);
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
	//printf(BLUE"test, void * textures = %p\n"RESET_COLOUR, data->cub->textures[index]);
	if (!data->cub->textures[index])
	{
		printf("Error: Textura no cargada en %s\n", texture_path);
		return (-1);
	}
	printf(GREEN"load_texture_image completed\n"RESET_COLOUR);
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
		printf("Error: No se pudo obtener los datos en %p\n",
			data->cub->textures[index]);
		return (-1);
	}
	printf(GREEN"get_texture_data completed\n"RESET_COLOUR);
	return (0);
}

// Función principal de carga de textura que llama a las funciones auxiliares.
int	load_texture(t_data *data, int index, char *texture_path)
{
	printf(RED"texture_path = %s\n"RESET_COLOUR, texture_path);
	
	if (verify_texture_params(index, texture_path) == -1)
		return (-1);
	if (load_texture_image(data, index, texture_path) == -1)
		return (-1);
	if (get_texture_data(data, index) == -1)
		return (-1);
	return (0);
}