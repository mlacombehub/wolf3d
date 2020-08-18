/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:34:47 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/18 19:01:38 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void		wolf3d_countlines(t_wolf3d_t *wolf3d, char *str)
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

void		wolf3d_countcolumns(t_wolf3d_t *wolf3d, char *str)
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
	if (!(wolf3d->map = (t_token_t **)malloc(
						sizeof(*wolf3d->map) * wolf3d->nb_line)))
	{
		free(wolf3d->map);
		return ;
	}
	while (p.y < wolf3d->nb_line)
	{
		if (!(wolf3d->map[p.y] = (t_token_t *)malloc(sizeof(*wolf3d->map[p.y])
								* (wolf3d->line_len[p.y] + 1))))
		{
			free(wolf3d->map[p.y]);
			return ;
		}
		while (*raw_map && *raw_map != '\n')
		{
			wolf3d->map[p.y][p.x] = *(t_token_t *)raw_map;
			printf("%i%i%i%i%i%i%i%i\n", wolf3d->map[p.y][p.x].type, wolf3d->map[p.y][p.x].crossable, wolf3d->map[p.y][p.x].origin, wolf3d->map[p.y][p.x].pickable, wolf3d->map[p.y][p.x].texture_a, wolf3d->map[p.y][p.x].texture_b, wolf3d->map[p.y][p.x].texture_c, wolf3d->map[p.y][p.x].ending);
			++raw_map;
			++p.x;
		}
		if (*raw_map && *raw_map == '\n')
		{
			printf("\n");
			p.x = 0;
			++p.y;
			++raw_map;
		}
		if (*raw_map == '\0')
			break ;
	}
}

double		angle_view(t_vec2_t origin, t_point_t view)
{
	t_point_t	ab;
	t_point_t	ac;
	double		result;

	ab = (t_point_t){0, -origin.y};
	ac = (t_point_t){view.x - origin.x, view.y - origin.y};
	printf("\n%i|%i %i|%i\n", ab.x, ab.y, ac.x, ac.y);
	cos(result) = (ab.x * ac.x + ab.y * ac.y) / (sqrt(ab.x + ab.y) * sqrt() )
	return (0.1);
	// wolf3d->angle_view = (xb - xa) * (xc - xa) + (yb - ya) * (yc - ya) / (sqrt(xa^2 + ya^2) * sqrt(xa^2 + ya^2))
}

void		pos_origin(t_wolf3d_t *wolf3d, t_token_t **tok)
{
	t_point_t	p;
	t_point_t	view;

	p = (t_point_t){-1, -1};
	wolf3d->origin = (t_vec2_t){p.x, p.y};
	view = p;
	while(++p.y < wolf3d->nb_line)
	{
		p.x = -1;
		while(++p.x <= wolf3d->line_len[p.y])
			if (tok[p.y][p.x].origin && tok[p.y][p.x].crossable)
			{
				wolf3d->origin = (t_vec2_t){p.x, p.y};
				tok[p.y][p.x].origin = 0;
			}
			else if (tok[p.y][p.x].origin && !tok[p.y][p.x].crossable)
				view = p;
	}
	if (wolf3d->origin.x == -1 || view.x == -1)
	{
		p = (t_point_t){wolf3d->line_len[p.y -1] - 1, p.y - 1};
		while (p.x >= 0 && p.y >= 0 && !tok[p.y][p.x].crossable)
		{
			if (wolf3d->origin.x == -1)
				wolf3d->origin = (t_vec2_t){p.x, p.y};
			else if (view.x == -1)
				view = (t_point_t){wolf3d->origin.x, wolf3d->origin.y};
			p.x == 0 ? p.x == wolf3d->line_len[--p.y] : p.x--;
		}
	}
	if (wolf3d->origin.x == view.x && wolf3d->origin.y == view.y)
		view.y -= 0.5;
	printf("orig: %.0f|%.0f\nview: %d|%d\n", wolf3d->origin.x, wolf3d->origin.y, view.x, view.y);
	wolf3d->angle_view = angle_view(wolf3d->origin, view);
	// wolf3d->origin = (t_vec2_t){wolf3d->origin.x + 0.5, wolf3d->origin.y + 0.5}
}

void		manage_file(int ac, t_wolf3d_t *wolf3d)
{
	int	fd;

	fd = 0;
	ft_puterror((ac > 2 || (fd = open(wolf3d->fname, O_RDONLY)) == -1),
				"usage : ./wolf3d [input_file]");
	if (ac != 1)
		ft_open_close_fd(wolf3d->fname) == FALSE ? free_quit(wolf3d) : 42;
	if (read(fd, NULL, 0) == -1)
		free_quit(wolf3d);
	read_file(wolf3d, fd);
	ft_puterror(close(fd) < 0, "Problem with closing file");
	pos_origin(wolf3d, wolf3d->map);
}
