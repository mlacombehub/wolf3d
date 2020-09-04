/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:34:47 by mlacombe          #+#    #+#             */
/*   Updated: 2020/09/04 14:00:35 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	wolf3d_countlines(t_wolf3d_t *wolf3d, char *str)
{
	wolf3d->file.nb_line = 0;
	if (str == NULL)
		wolf3d->quit = 4;
	else
	{
		while (*str)
		{
			if (*str == '\n')
				wolf3d->file.nb_line++;
			str++;
		}
		if (*--str && !ft_isspace(*str) && *str != '\n')
			wolf3d->file.nb_line++;
		if (wolf3d->file.nb_line == 0 || !(wolf3d->file.line_len =
			(int *)malloc(sizeof(*wolf3d->file.line_len)
			* (wolf3d->file.nb_line + 1))))
		{
			free(wolf3d->file.line_len);
			wolf3d->quit = 4;
		}
	}
}

static void	wolf3d_countcolumns(t_wolf3d_t *w, char *str)
{
	uint32_t	i;

	i = 0;
	w->file.line_len[i] = 0;
	while (*str)
	{
		while (*str && *str != '\n')
		{
			w->file.line_len[i]++;
			str++;
		}
		if ((*str && *str == '\n') || (!*str && *--str != '\n'))
		{
			w->file.max_len = ft_max(w->file.line_len[i], w->file.max_len);
			w->file.line_len[++i] ? w->file.line_len[i] = 0 : 42;
		}
		str++;
	}
	if (!(w->map = (t_token_t **)malloc(sizeof(*w->map) * w->file.nb_line)))
	{
		free(w->map);
		w->quit = 5;
		return ;
	}
}

static char	*wolf3d_reallocfile(int fd)
{
	int		n;
	char	buff[BUFF_FILE];
	char	tmp[100000];
	char	*result;
	int		readres;

	ft_bzero(buff, BUFF_FILE);
	n = 0;
	result = NULL;
	while ((readres = read(fd, buff, BUFF_FILE)) > 0)
	{
		ft_memmove(tmp, result, n);
		ft_memmove(tmp + n, buff, readres);
		n += readres;
		free(result);
		result = tmp;
		ft_bzero(buff, BUFF_FILE);
		if (result[ft_strlen(result)] == 0 || ft_strlen(result) > 100000)
			break ;
	}
	if (n != 0 && readres >= 0)
		result[n] = '\0';
	return (result);
}

static void	transl_file(t_wolf3d_t *w, char *raw_map)
{
	t_point_t	p;

	p = (t_point_t) {0, 0};
	while (p.y < w->file.nb_line)
	{
		if (w->quit != 0)
			return ;
		if (!(w->map[p.y] = malloc(sizeof(t_token_t **)
				* ((w->file.line_len[p.y] + 1)))))
		{
			free(w->map[p.y]);
			w->quit = 6;
			return ;
		}
		while (*raw_map && *raw_map != '\n')
			w->map[p.y][p.x++] = *(t_token_t *)raw_map++;
		if (*raw_map && *raw_map == '\n')
		{
			p = (t_point_t){0, ++p.y};
			++raw_map;
		}
		if (*raw_map == '\0')
			break ;
	}
}

void		manage_file(int ac, t_wolf3d_t *w)
{
	char	*raw_map;
	int		fd;

	fd = 0;
	fd = open(w->fname, O_RDONLY);
	if (ac > 2 || fd == -1 || read(fd, NULL, 0) < 0)
	{
		ft_putendl_fd("problem reading file, please use a valid file", 2);
		w->quit = 2;
		return ;
	}
	raw_map = wolf3d_reallocfile(fd);
	wolf3d_countlines(w, raw_map);
	if (w->quit != 0)
		return ;
	wolf3d_countcolumns(w, raw_map);
	transl_file(w, raw_map);
	if (close(fd) < 0)
	{
		ft_putendl_fd("Problem with closing file", 2);
		w->quit = 7;
	}
}
