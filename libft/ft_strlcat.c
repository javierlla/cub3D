/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:36:42 by jllarena          #+#    #+#             */
/*   Updated: 2024/10/28 13:09:25 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	origen;
	size_t	destino;

	i = 0;
	origen = ft_strlen(src);
	destino = ft_strlen(dst);
	if (dstsize <= destino || dstsize == 0)
	{
		return (dstsize + origen);
	}
	while (dstsize > (destino + 1 + i) && src[i] != '\0')
	{
		dst[destino + i] = src[i];
		i++;
	}
	dst[destino + i] = '\0';
	return (destino + origen);
}

/*int main(void)
{
	char destino[50] = "holajuan";
	char origen [20] = "adiosivan";
	printf("el string destino es: %s\n", destino);
	printf("el string origen es: %s\n", origen);
	printf("la funcion original suma: %lu\n", ft_strlcat(destino, origen, 10));
	printf("el final es: %s\n", destino); 
}*/
