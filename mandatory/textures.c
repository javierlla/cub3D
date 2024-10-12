/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:17:54 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/12 17:18:22 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int get_texture_color(t_cub *cub, int texNum, int texX, int texY)
{
    if (texNum < 0 || texNum >= 4)
    {
        printf("Error: texturas fuera de límites: %d\n", texNum);
        return 0;
    }
    if (cub->textures_data[texNum] == NULL)
    {
        printf("Error: La textura %d no está cargada.\n", texNum);
        return 0;
    }

    if (texX < 0 || texX >= TEX_WIDTH || texY < 0 || texY >= TEX_HEIGHT)
    {
        printf("Error: Coordenadas de textura fuera de límites: texX=%d, texY=%d\n", texX, texY);
        return 0;
    }
    unsigned int color = *(unsigned int *)(cub->textures_data[texNum] + (texY * cub->line_length + texX * (cub->bits_per_pixel / 8)));
    return color;
}

int load_texture(t_cub *cub, int index, char *texture_path)
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
    cub->textures[index] = mlx_xpm_file_to_image(cub->mlx->mlx_ptr, texture_path, &width, &height);
        
    if (cub->textures[index])
        printf("%p\n",  cub->textures[index]);
    if (!(cub->textures[index])) {
        printf("Error: No se pudo cargar la textura en %s\n", texture_path);
        return -1;
    }

    cub->textures_data[index] = mlx_get_data_addr(cub->textures[index], &cub->bits_per_pixel, &cub->line_length, &cub->endian);
    if (!cub->textures_data[index])
    {
        printf("Error: No se pudo obtener los datos de la textura en %s\n", texture_path);
        return -1;
    }

    return 0;
}

void load_textures(t_cub *cub)
{
    cub->textures = malloc(sizeof(void *) * 4);
    cub->textures_data = malloc(sizeof(char *) * 4);

    if (!cub->textures || !cub->textures_data)
    {
        printf("Error: No se pudo asignar memoria para las texturas.\n");
        exit(EXIT_FAILURE);
    }
    int i; 
    
    i = 0;
    while (i < 4)
    {
        cub->textures[i] = NULL;
        cub->textures_data[i] = NULL;
        i++;
    }
    if (load_texture(cub, 0, cub->north_texture))
        printf("Error: No se pudo cargar la textura del Norte: %s\n", cub->north_texture);
    if (load_texture(cub, 1, cub->south_texture))
        printf("Error: No se pudo cargar la textura del Sur: %s\n", cub->south_texture);
    if (load_texture(cub, 2, cub->west_texture))
        printf("Error: No se pudo cargar la textura del Oeste: %s\n", cub->west_texture);
    if (load_texture(cub, 3, cub->east_texture))
        printf("Error: No se pudo cargar la textura del Este: %s\n", cub->east_texture);
    i = 0;
    while (i < 4)
    {
        if (!cub->textures[i] || !cub->textures_data[i])
        {
            printf("Error: La textura %d no se ha cargado correctamente.\n", i);
            return;
        }
        i++;
    }
}