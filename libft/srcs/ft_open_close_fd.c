/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_close_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:50:17 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/31 17:00:57 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int	ft_open_close_fd(char *doc)
{
	t_point_t	fd;
	char		res_a[13];
	char		res_b[13];
	int			i;

	fd = (t_point_t){open(doc, O_RDONLY), open(doc, O_RDONLY)};
	if (fd.x < 0 || fd.y < 0)
	{
		ft_putendl_fd("Problem opening file", 2);
		return (0);
	}
	res_a[0] = (char)read(fd.x, res_a, 13);
	close(fd.x);
	res_b[0] = (char)read(fd.y, res_b, 13);
	close(fd.y);
	i = 0;
	while (i < ft_min(res_a[0], res_b[0]))
		res_a[i] != res_b[i] ? i = 42 : i++;
	if (i == 42)
	{
		ft_putendl_fd("Problem with reading file", 2);
		return (0);
	}
	return (1);
}
