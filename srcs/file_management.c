/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:34:47 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/14 18:54:18 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char	*wolf3d_reallocfile(int fd)
{
	long long	n;
	char		buff[BUFF_FILE + 1];
	char		*tmp;
	char		*result;
	int			readres;

	ft_bzero(buff, 4095 + 1);
	n = 0;
	result = NULL;
	while ((readres = read(fd, buff, BUFF_FILE)) > 0)
	{
		if (!(tmp = (char *)malloc(sizeof(tmp) * (n + readres + 1))))
			ft_free_return(tmp);
		ft_memmove(tmp, result, n);
		ft_memmove(tmp + n, buff, readres);
		n += readres;
		free(result);
		result = tmp;
		ft_bzero(buff, BUFF_FILE + 1);
	}
	if (n != 0 && readres >= 0)
		result[n] = '\0';
	return (result);
}

t_token_t	**read_file(t_wolf3d_t *wolf3d, int fd)
{
	wolf3d_reallocfile();
}

void	manage_file(int ac, t_wolf3d_t *wolf3d)
{
	int	fd;

	ft_puterror((ac > 2 || (fd = open(wolf3d->fname, O_RDONLY)) == -1), "usage : ./wolf3d [input_file]");
	if (ac != 1)
		ft_open_close_fd(wolf3d->fname) == FALSE ? exit(1) : 42;
	if (read(fd, NULL, 0) == -1)
		exit(1);
	wolf3d->map = read_file(wolf3d, fd);
	ft_puterror(close(fd) < 0, "Problem with closing file");
	stock_map_length();
	bit_verification();
}
