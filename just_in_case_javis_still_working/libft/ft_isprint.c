/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:08:53 by jllarena          #+#    #+#             */
/*   Updated: 2023/09/22 12:05:42 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
	{
		return (0);
	}
	return (1);
}
/*
int main(void)
{
	int i = 126;
	printf("el resultado es: %d\n", ft_isprint(i));
}*/