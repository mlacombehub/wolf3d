/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:24 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/19 16:37:21 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		angle_view(t_vec2_t origin, t_point_t view)
{
	t_point_t	ab;
	t_point_t	ac;
	double		result;

	ab = (t_point_t){0, -origin.y};
	ac = (t_point_t){view.x - origin.x, view.y - origin.y};
	result = acos((ab.x * ac.x + ab.y * ac.y) / (sqrt(ab.x * ab.x + ab.y * ab.y) * sqrt(ac.x * ac.x + ac.y * ac.y)));
	return (result);
}

void		pos_origin(t_wolf3d_t *wolf3d, t_token_t **tok)
{
	t_point_t	p;
	t_point_t	view;

	p = (t_point_t){-1, -1};
	wolf3d->origin = (t_vec2_t){p.x, p.y};
	view = p;
	while (++p.y < wolf3d->nb_line)
	{
		p.x = -1;
		while (++p.x <= wolf3d->line_len[p.y])
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
		p = (t_point_t){wolf3d->line_len[p.y - 1] - 1, p.y - 1};
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
	wolf3d->angle_view = angle_view(wolf3d->origin, view);
	wolf3d->origin = (t_vec2_t){wolf3d->origin.x + 0.5, wolf3d->origin.y + 0.5};
}

void	player_pos(t_wolf3d_t *wolf3d)
{
	int		i;

	pos_origin(wolf3d, wolf3d->map);
	wolf3d->screen.w = 100;
	wolf3d->fov = 2 * tan(M_PI / 3) / wolf3d->screen.w;
	printf("fov: %f\n", wolf3d->fov);
	if (!(wolf3d->picture = (long double *)malloc(sizeof(long double)
							* wolf3d->screen.w)))
	{
		free(wolf3d->picture);
		return ;
	}
	i = -1;
	while (++i < wolf3d->screen.w)
	{
		wolf3d->picture[i] = atan((i - wolf3d->screen.w) * wolf3d->fov);
		printf("%Lf\n", wolf3d->picture[i]);
	}
}
