/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:24 by mlacombe          #+#    #+#             */
/*   Updated: 2020/09/09 04:13:36 by mlacombe         ###   ########.fr       */
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
	return (-result);
}

void	fail_to_origin(t_wolf3d_t *w, t_token_t **tok)
{
	t_point_t	p;

	if (!tok[(int)w->origin.y][(int)w->origin.x].cross)
	{
		p = (t_point_t){0};
		while (p.y < w->file.nb_line && !tok[p.y][p.x].cross)
		{
			p.x = 0;
			while (p.x < w->file.line_len[p.y])
			{
				if (!w->origin.x && !w->origin.y && tok[p.y][p.x].cross)
					w->origin = (t_vec2_t){p.x, p.y};
				if (w->view.x == 0 && w->view.y == 0 && tok[p.y][p.x].cross)
					w->view = (t_point_t){w->origin.x, w->origin.y};
				p.x++;
			}
			p.y++;
		}
		if (!w->origin.x && !w->origin.y &&
			!tok[(int)w->origin.y][(int)w->origin.x].cross)
		{
			ft_putendl_fd("File is not containing crossable fields\n", 2);
			w->quit = 8;
		}
	}
}

void	pos_origin(t_wolf3d_t *w, t_token_t **tok)
{
	t_point_t	p;

	p.y = 0;
	w->view = (t_point_t){0};
	while (p.y < w->file.nb_line)
	{
		p.x = 0;
		while (p.x < w->file.line_len[p.y])
		{
			if (!tok[p.y][p.x].type && tok[p.y][p.x].cross
				&& tok[p.y][p.x].orig && !tok[p.y][p.x].pick)
				w->origin = (t_vec2_t){p.x, p.y};
			else if (!tok[p.y][p.x].cross && tok[p.y][p.x].orig)
				w->view = p;
			p.x++;
		}
		p.y++;
	}
	fail_to_origin(w, w->map);
	if (w->quit != 0)
		return ;
	if ((w->origin.x == w->view.x && w->origin.y == w->view.y))
		w->view = (t_point_t){0};
	w->a_view = angle_view(w->origin, w->view);
}

void	player_pos(t_wolf3d_t *w)
{
	int		i;

	pos_origin(w, w->map);
	if (w->quit != 0)
		return ;
	w->a_view < 0 ? w->a_view += 2 * M_PI : 0;
	w->origin = (t_vec2_t){w->origin.x + 0.5, w->origin.y + 0.5};
	w->pos = w->origin;
	w->fov = 2 * tan(M_PI / 3) / w->screen.mode.w;
	if (!(w->picture = (long double *)malloc(sizeof(long double)
						* (w->screen.mode.w + 1))))
	{
		free(w->picture);
		w->quit = 9;
		return ;
	}
	i = -1;
	while (++i < w->screen.mode.w)
		w->picture[i] = atan((i - w->screen.mode.w / 2) * w->fov);
}
