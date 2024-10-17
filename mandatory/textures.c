/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:17:54 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/17 16:33:44 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int get_texture_color(t_data *data, int texNum, int texX, int texY)
{
    if (texNum < 0 || texNum >= 4)
    {
        printf("Error: texturas fuera de límites: %d\n", texNum);
        return 0;
    }
    if (data->cub->textures_data[texNum] == NULL)
    {
        printf("Error: La textura %d no está cargada.\n", texNum);
        return 0;
    }

    if (texX < 0 || texX >= TEX_WIDTH || texY < 0 || texY >= TEX_HEIGHT)
    {
        printf("Error: Coordenadas de textura fuera de límites: texX=%d, texY=%d\n", texX, texY);
        return 0;
    }
    unsigned int color = *(unsigned int *)(data->cub->textures_data[texNum] + (texY *data->cub->line_length + texX * (data->cub->bits_per_pixel / 8)));
    return color;
}

int load_texture(t_data *data, int index, char *texture_path)
{
    int width = TEX_WIDTH;
    
    int height = TEX_HEIGHT;

    if (index < 0 || index >= 4) {
        printf("Error: Índice de textura fuera de límites: %d\n", index);
        return -1;
    }

    if (!texture_path) {
        printf("Error: Ruta de la textura es nula para el índice %d.\n", index);
        return -1;
    }
    //printf("%p\n",  cub->textures[index]);
    data->cub->textures[index] = mlx_xpm_file_to_image(data->cub->mlx->mlx_ptr, texture_path, &width, &height);
        
    if (data->cub->textures[index])
        // printf("%p\n",  cub->textures[index]);
    if (!(data->cub->textures[index]))
    {
        printf("Error: No se pudo cargar la textura en %s\n", texture_path);
        return -1;
    }

    data->cub->textures_data[index] = mlx_get_data_addr(data->cub->textures[index], &data->cub->bits_per_pixel, &data->cub->line_length, &data->cub->endian);
    printf("Endian de la textura %d: %d\n", index, data->cub->endian);

    if (!data->cub->textures_data[index])
    {
        printf("Error: No se pudo obtener los datos de la textura en %s\n", texture_path);
        return -1;
    }

    return 0;
}

void load_textures(t_data *data)
{
    data->cub->textures = malloc(sizeof(void *) * 4);
    data->cub->textures_data = malloc(sizeof(char *) * 4);

    if (!data->cub->textures || !data->cub->textures_data)
    {
        printf("Error: No se pudo asignar memoria para las texturas.\n");
        exit(EXIT_FAILURE);
    }
    int i; 
    
    i = 0;
    while (i < 4)
    {
        data->cub->textures[i] = NULL;
        data->cub->textures_data[i] = NULL;
        i++;
    }
    if (load_texture(data, 0, data->cub->north_texture))
        printf("Error: No se pudo cargar la textura del Norte: %s\n", data->cub->north_texture);
    if (load_texture(data, 1, data->cub->south_texture))
        printf("Error: No se pudo cargar la textura del Sur: %s\n", data->cub->south_texture);
    if (load_texture(data, 2, data->cub->west_texture))
        printf("Error: No se pudo cargar la textura del Oeste: %s\n", data->cub->west_texture);
    if (load_texture(data, 3, data->cub->east_texture))
        printf("Error: No se pudo cargar la textura del Este: %s\n", data->cub->east_texture);
    i = 0;
    while (i < 4)
    {
        if (!data->cub->textures[i] || !data->cub->textures_data[i])
        {
            printf("Error: La textura %d no se ha cargado correctamente.\n", i);
            return;
        }
        i++;
    }
}
