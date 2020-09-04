/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:24 by mlacombe          #+#    #+#             */
/*   Updated: 2020/09/04 13:02:48 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	angle_view(t_vec2_t origin, t_point_t view)
{
	t_point_t	ab;
	t_point_t	ac;
	double		result;

	result = 0;
	ab = (t_point_t){0, -origin.y};
	ac = (t_point_t){view.x - origin.x, view.y - origin.y};
	if (sqrt(ab.x * ab.x + ab.y * ab.y) * sqrt(ac.x * ac.x + ac.y * ac.y))
		result = acos((ab.x * ac.x + ab.y * ac.y)
			/ (sqrt(ab.x * ab.x + ab.y * ab.y)
			* sqrt(ac.x * ac.x + ac.y * ac.y)));
	else
		result = 0;
	return (result);
}

void	pos_origin(t_wolf3d_t *w, t_token_t **tok)
{
	t_point_t	p;
	t_point_t	view;

	p = (t_point_t){-1, -1};
	view = (t_point_t){0, 0};
	while (++p.y < w->file.nb_line)
	{
		p.x = -1;
		while (++p.x < w->file.line_len[p.y])
			if (!tok[p.y][p.x].type && tok[p.y][p.x].cross && tok[p.y][p.x].orig && !tok[p.y][p.x].pick)
				w->origin = (t_vec2_t){p.x, p.y};
			else if (!tok[p.y][p.x].cross && tok[p.y][p.x].orig)
				view = p;
	}
	if ((w->origin.x == 0 && w->origin.y == 0) || w->file.nb_line != 1 || w->file.max_len != 1)
	{
		p.y = -1;
		while (++p.y < w->file.nb_line && !tok[p.y][p.x].cross)
		{
			p.x = 0;
			while (++p.x < w->file.line_len[p.y] && !tok[p.y][p.x].cross)
			{
				if (w->origin.x == 0 && w->origin.y == 0)
					w->origin = (t_vec2_t){p.x, p.y};
				if (view.x == 0 && view.y == 0)
					view = (t_point_t){w->origin.x, w->origin.y};
			}
		}
		if (w->origin.x < 0 && w->origin.y < 0)
		{
			ft_putendl_fd("File is not containing crossable fields\n", 2);
			w->quit = 8;
			return ;
		}
	}
	if ((w->origin.x == view.x && w->origin.y == view.y))
		view = (t_point_t){0, 0};
	w->angle_view = angle_view(w->origin, view);
}

void	player_pos(t_wolf3d_t *w)
{
	int		i;

	pos_origin(w, w->map);
	w->origin = (t_vec2_t){w->origin.x + 0.5, w->origin.y + 0.5};
	w->pos = w->origin;
	if (w->quit != 0)
		return ;
	w->fov = 2 * tan(M_PI / 3) / w->screen.mode.w;
	if (!(w->picture = malloc(sizeof(long double) * (w->screen.mode.w))))
	{
		free(w->picture);
		w->quit = 9;
		return ;
	}
	i = -1;
	while (++i < w->screen.mode.w)
		w->picture[i] = atan((i - w->screen.mode.w / 2) * w->fov);
}
