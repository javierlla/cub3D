/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:35:09 by uxmancis          #+#    #+#             */
/*   Updated: 2024/11/01 10:43:42 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_join2(int new_l_hol, char *holder, int l_hol, char *buffer)
{
	int		i;
	int		y;
	char	*uptd_hol;

	i = 0;
	y = 0;
	uptd_hol = malloc(sizeof(char) * (new_l_hol + 1));
	while (new_l_hol > 0)
	{
		while (l_hol > 0)
		{
			uptd_hol[i] = holder[i];
			i++;
			l_hol--;
			new_l_hol--;
		}
		uptd_hol[i] = buffer[y];
		i++;
		y++;
		new_l_hol--;
	}
	return (uptd_hol);
}

/*DESCRIPTION:
well.. let me explain this..

ft_lb_l function encapsulates ft_strchr and ft_strlen functions.

1. ind = 0: ft_strchr function checks whether if str contains c character. 
If it DOES, then
position of the character is returned. Else, -1 is returned.
Arguments that is really going to use: char *str, char c, 
int ind(to choose ft_strchr). Ex.: char *str, '\n', 0

2. ind != 0: returns len of str received as an argument.
Arguments that is really going to use: char *str, int ind (to choose ft_strlen)
Ex.: char *str, 'u', 1

----------------------------------*/
int	ft_lb_l(char *str, char c, int ind)
{
	int	i;

	i = 0;
	if (ind == 0)
	{
		if (!str)
			return (0);
		while (str[i] != '\0')
		{
			if (str[i] == c)
				return (i);
			i++;
		}
		return (-1);
	}
	else
	{
		if (!str)
			return (0);
		while (str[i] != '\0')
		{
			i++;
		}
		return (i);
	}
}

/*DESCRIPTION:
ind decides which function are we implementing: 

· ind == 0: ft_strcpy
· ind == 1: ft_free

--------------------------------------------------------------*/
char	*ft_cp_f(char *src, char *dst, int size, int ind)
{
	int	i;

	if (ind == 0)
	{
		i = 0;
		while (size > 0)
		{
			dst[i] = src[i];
			i++;
			size--;
		}
		dst[i] = '\0';
		return (dst);
	}
	else
	{
		if (src)
		{
			free (src);
			src = NULL;
		}
		return (src);
	}
}

char	*ft_free2fill(char ***src, char *dst)
{
	if (**src)
	{
		free (**src);
		**src = NULL;
	}
	**src = dst;
	return (**src);
}

int	check_lb(char *holder, int len_holder)
{
	int	i;

	i = 0;
	while (len_holder > 0)
	{
		if (holder[i] == '\n')
			return (i);
		i++;
		len_holder--;
	}
	return (-1);
}
