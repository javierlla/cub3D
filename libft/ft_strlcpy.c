/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:53:55 by jllarena          #+#    #+#             */
/*   Updated: 2023/09/22 13:34:48 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
	{
		dst[i] = '\0';
	}
	while (src[i])
	{
		i++;
	}
	return (i);
}
/*
int main() {
    char destination[] = "" ;
    char *source = "HellosgWi";
    size_t resultado = ft_strlcpy(destination, source,0);


    printf("Cadena copiada: %s\n", destination);
    printf("Longitud de la cadena copiada: %zu\n", resultado);
}
*/

/*
int main(void)
{
	char cdena[8];
	char cadena2[] = "adidfgheg" ;

	size_t dstsize = 5;

	printf("el resultado es: %d\n", strlcpy(cdena, cadena2, 5));
	printf("prueba: %s\n", cdena);
	return 0;
}*/
