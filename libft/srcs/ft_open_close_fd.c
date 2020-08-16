/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_close_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:50:17 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/16 15:05:24 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_open_close_fd(char *doc)
{
	t_point_t	fd;
	char		res_a[13];
	char		res_b[13];
	int			i;

	ft_puterror(((fd.x = open(doc, O_RDONLY)) < 0), "Problem opening file");
	res_a[0] = (char)read(fd.x, res_a, 13);
	close(fd.x);
	ft_puterror(((fd.y = open(doc, O_RDONLY)) < 0), "Problem opening file");
	res_b[0] = (char)read(fd.y, res_b, 13);
	close(fd.y);
	i = 0;
	while (i < ft_min(res_a[0], res_b[0]))
		res_a[i] != res_b[i] ? i = 42 : i++;
	ft_puterror(i == 42, "Problem with reading file");
	return (1);
}
