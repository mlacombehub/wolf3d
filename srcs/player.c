/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:24 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/29 20:37:01 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	angle_view(t_vec2_t origin, t_point_t view)
{
	t_point_t	ab;
	t_point_t	ac;
	double		result;

	ab = (t_point_t){0, -origin.y};
	ac = (t_point_t){view.x - origin.x, view.y - origin.y};
	result = acos((ab.x * ac.x + ab.y * ac.y)
			/ (sqrt(ab.x * ab.x + ab.y * ab.y)
			* sqrt(ac.x * ac.x + ac.y * ac.y)));
	return (result);
}

void	pos_origin(t_wolf3d_t *w, t_token_t **tok)
{
	t_point_t	p;
	t_point_t	view;

	p = (t_point_t){-1, -1};
	view = p;
	while (++p.y < w->file.nb_line)
	{
		p.x = -1;
		while (++p.x <= w->file.line_len[p.y])
			if (tok[p.y][p.x].orig && tok[p.y][p.x].cross)
			{
				w->origin = (t_vec2_t){p.x, p.y};
				tok[p.y][p.x].orig = 0;
			}
			else if (tok[p.y][p.x].orig && !tok[p.y][p.x].cross)
				view = p;
	}
	if (w->origin.x == -1 || view.x == -1)
	{
		p = (t_point_t){w->file.line_len[p.y - 1] - 1, p.y - 1};
		while (p.x >= 0 && p.y >= 0 && !tok[p.y][p.x].cross)
		{
			if (w->origin.x == -1)
				w->origin = (t_vec2_t){p.x, p.y};
			else if (view.x == -1)
				view = (t_point_t){w->origin.x, w->origin.y};
			p.x == 0 ? p.x == w->file.line_len[--p.y] : p.x--;
		}
		if (p.y == -1)
		{
			ft_putendl_fd("File is not containing crossable fields\n", 2);
			w->quit = 8;
			return ;
		}
	}
	if (w->origin.x == view.x && w->origin.y == view.y)
		view.y -= 0.5;
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
	if (!(w->picture = (long double *)malloc(sizeof(long double)
						* w->screen.mode.w)))
	{
		free(w->picture);
		w->quit = 9;
		return ;
	}
	i = -1;
	while (++i < w->screen.mode.w)
		w->picture[i] = atan((i - w->screen.mode.w / 2) * w->fov);
}
