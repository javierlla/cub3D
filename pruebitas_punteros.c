/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebitas_punteros.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:09:06 by uxmancis          #+#    #+#             */
/*   Updated: 2024/10/01 11:40:15 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main(void)
{
   int *dst1;
   int *dst2;
   int src = 3;

   dst1 = &src;
   dst2 = &src;
   printf("dst1 = %d, dst2 = %d\n", *dst1, *dst2);
   return (0);
} 