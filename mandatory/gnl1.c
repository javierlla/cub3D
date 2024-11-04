/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:35:00 by uxmancis          #+#    #+#             */
/*   Updated: 2024/11/01 10:43:36 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 300
#endif

int	ft_read(int fd, char **buffer)
{
	int		read_bytes;
	int		keep_read_bytes;
	char	*tmp;
	char	*filled_buffer;

	filled_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!filled_buffer)
		return (-1);
	read_bytes = read(fd, filled_buffer, BUFFER_SIZE);
	keep_read_bytes = read_bytes;
	if (read_bytes == -1 || read_bytes == 0)
		return (ft_cp_f(filled_buffer, "uxu", 0, 1), read_bytes);
	if (read_bytes < BUFFER_SIZE)
	{
		tmp = malloc(sizeof(char) * (read_bytes + 1));
		tmp = ft_cp_f(filled_buffer, tmp, read_bytes, 0);
		filled_buffer = ft_cp_f(filled_buffer, "uxu", 0, 1);
		filled_buffer = tmp;
	}
	else
		filled_buffer[BUFFER_SIZE] = '\0';
	*buffer = ft_free2fill(&buffer, filled_buffer);
	return (keep_read_bytes);
}

void	ft_join(char ***holder, char *buffer)
{
	char	*uptd_hol;
	int		new_l_hol;
	int		keep_new_l_hol;
	int		l_hol;

	l_hol = ft_lb_l(**holder, 'u', 1);
	if (!**holder)
	{
		**holder = malloc(sizeof(char) * (ft_lb_l(buffer, 'u', 1) + 1));
		**holder = ft_cp_f(buffer, **holder, ft_lb_l(buffer, 'u', 1), 0);
		return ;
	}
	if (!buffer)
		return ;
	new_l_hol = ft_lb_l(**holder, 'u', 1) + ft_lb_l(buffer, 'u', 1);
	keep_new_l_hol = new_l_hol;
	uptd_hol = ft_join2(new_l_hol, **holder, l_hol, buffer);
	uptd_hol[keep_new_l_hol] = '\0';
	**holder = ft_cp_f(**holder, "uxu", 0, 1);
	**holder = uptd_hol;
	l_hol = keep_new_l_hol;
}

void	ft_gnl_and_update_holder(char **holder, int index_lb, char **next_line)
{
	int		i;
	int		y;
	int		keep_l_holder;
	char	*updated_holder;
	char	*filled_next_line;

	keep_l_holder = ft_lb_l(*holder, 'u', 1);
	filled_next_line = malloc(sizeof(char) * (index_lb + 2));
	index_lb++;
	updated_holder = malloc(sizeof(char) * ((keep_l_holder - (index_lb)) + 1));
	i = 0;
	y = 0;
	while (index_lb-- > 0)
	{
		filled_next_line[i] = (*holder)[i];
		i++;
		keep_l_holder--;
	}
	filled_next_line[i] = '\0';
	while (keep_l_holder-- > 0)
		updated_holder[y++] = (*holder)[i++];
	updated_holder[y] = '\0';
	*holder = ft_free2fill(&holder, updated_holder);
	*next_line = ft_free2fill(&next_line, filled_next_line);
}

int	ft_read_and_go(int fd, char **holder, char *buffer, char **next_line)
{
	int		ind;
	char	*uptd_holder;

	ind = ft_read(fd, &buffer);
	if (ind == 0)
	{
		if (ft_lb_l(*holder, 'u', 1) == 0)
			return (*holder = ft_cp_f(*holder, "uxu", 0, 1), 1);
		*next_line = ft_cp_f(*next_line, "uxu", 0, 1);
		*next_line = malloc(sizeof(char) * (ft_lb_l(*holder, 'u', 1) + 1));
		*next_line = ft_cp_f(*holder, *next_line, ft_lb_l(*holder, 'u', 1), 0);
		return (*holder = ft_cp_f(*holder, "uxu", 0, 1), 1);
	}
	if (ind == -1)
		return (-1);
	if (*holder && (ft_lb_l(*holder, 'u', 1) == 0 || *holder[0] == '\0'))
	{
		*holder = ft_cp_f(*holder, "uxu", 0, 1);
		*holder = ft_cp_f(buffer, uptd_holder = malloc((ind + 1)), ind, 0);
	}
	else
		ft_join(&holder, buffer);
	buffer = ft_cp_f(buffer, "uxu", 0, 1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*next_line;
	char		*buffer;
	int			ind;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line = NULL;
	buffer = NULL;
	while (1)
	{
		if (holder && ft_lb_l(holder, '\n', 0) != -1)
			return (ft_gnl_and_update_holder(&holder, check_lb(holder,
						ft_lb_l(holder, 'u', 1)), &next_line), next_line);
		ind = ft_read_and_go (fd, &holder, buffer, &next_line);
		if (ind == -1)
		{
			holder = ft_cp_f(holder, "uxu", 0, 1);
			return (NULL);
		}
		if (ind == 1)
			return (next_line);
	}
	return (NULL);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*nl;

// 	fd = open("myfile", O_RDONLY);
// 	nl = get_next_line(fd);
// 	while (nl)
// 	{
// 		printf("nl = %s", nl);
// 		if (nl)
// 			free (nl);
// 		nl = get_next_line(fd);
// 	}
// 	if (nl)
// 		free (nl);
// 	nl = NULL;
// 	close (fd);
// }
