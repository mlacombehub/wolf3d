/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:34:47 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/16 18:39:25 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf3d_countlines(t_wolf3d_t *wolf3d, char *str)
{
	wolf3d->nb_line = 0;
	while (*str)
	{
		if (*str == '\n')
			wolf3d->nb_line++;
		str++;
	}
	if (*--str && !ft_isspace(*str) && *str != '\n')
		wolf3d->nb_line++;
	if (!(wolf3d->line_len = (int *)malloc(
		sizeof(*wolf3d->line_len) * (wolf3d->nb_line + 1))))
	{
		free(wolf3d->line_len);
		return ;
	}
}

void	wolf3d_countcolumns(t_wolf3d_t *wolf3d, char *str)
{
	uint32_t	i;

	i = 0;
	wolf3d->line_len[i] = 0;
	while (*str)
	{
		while (*str && *str != '\n')
		{
			wolf3d->line_len[i]++;
			str++;
		}
		if ((*str && *str == '\n') || (!*str && *--str != '\n'))
		{
			wolf3d->max_len = ft_max(wolf3d->line_len[i], wolf3d->max_len);
			wolf3d->line_len[++i] ? wolf3d->line_len[i] = 0 : 42;
		}
		str++;
	}
}

static char	*wolf3d_reallocfile(int fd)
{
	long long	n;
	char		buff[BUFF_FILE + 1];
	char		*tmp;
	char		*result;
	int			readres;

	ft_bzero(buff, BUFF_FILE + 1);
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

void	read_file(t_wolf3d_t *wolf3d, int fd)
{
	char		*raw_map;
	t_point_t	p;

	raw_map = wolf3d_reallocfile(fd);
	p = (t_point_t) {0, 0};
	wolf3d_countlines(wolf3d, raw_map);
	wolf3d_countcolumns(wolf3d, raw_map);
	printf("nb_line : %i\n", wolf3d->nb_line);
	if(!(wolf3d->map = (t_token_t **)malloc(sizeof(*wolf3d->map) * wolf3d->nb_line)))
	{
		free(wolf3d->map);
		return ;
	}
	while (p.y < wolf3d->nb_line)
	{
		printf("\tline_len : %i\n", wolf3d->line_len[p.y]);
		if (!(wolf3d->map[p.y] = (t_token_t *)malloc(sizeof(*wolf3d->map[p.y]) * (wolf3d->line_len[p.y] + 1))))
		{
			free(wolf3d->map[p.y]);
			return ;
		}
		while (*raw_map && *raw_map != '\n')
		{
			(*raw_map <= 47) ? (*raw_map += 127 - 47) : (*raw_map -= 47);
			if (*raw_map >= 127 - 47)
				printf("test : %i\n", *raw_map - 127 + 47);
			// wolf3d->map[p.y][p.x].type = ;
			// wolf3d->map[p.y][p.x].crossable = ;
			// wolf3d->map[p.y][p.x].position = ;
			// wolf3d->map[p.y][p.x].pickable = ;
			// wolf3d->map[p.y][p.x].texture_A = ;
			// wolf3d->map[p.y][p.x].texture_B = ;
			// wolf3d->map[p.y][p.x].texture_C = ;
			// wolf3d->map[p.y][p.x].ending = 0;
			++raw_map;
			++p.x;
		}
		if (*raw_map && *raw_map == '\n')
		{
			p.x = 0;
			++p.y;
			++raw_map;
		}
	}
}

void	manage_file(int ac, t_wolf3d_t *wolf3d)
{
	int	fd;

	fd = 0;
	ft_puterror((ac > 2 || (fd = open(wolf3d->fname, O_RDONLY)) == -1), "usage : ./wolf3d [input_file]");
	if (ac != 1)
		ft_open_close_fd(wolf3d->fname) == FALSE ? free_quit(wolf3d) : 42;
	if (read(fd, NULL, 0) == -1)
		free_quit(wolf3d);
	read_file(wolf3d, fd);
	ft_puterror(close(fd) < 0, "Problem with closing file");
	// stock_map_length();
	// bit_verification();
}
