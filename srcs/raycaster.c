/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 16:10:50 by mlacombe          #+#    #+#             */
/*   Updated: 2020/09/09 03:27:49 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	dda_ray(t_wolf3d_t *w, t_vec2_t step, t_vec2_t dist)
{
	t_vec2_t	delta;

	delta = (t_vec2_t){fabs(1 / w->ray.text.x), fabs(1 / w->ray.text.y)};
	while (w->ray.block == 0)
	{
		if (dist.x < dist.y)
		{
			dist.x += delta.x;
			w->ray.pos.x += step.x;
			w->ray.orient = 0;
		}
		else
		{
			dist.y += delta.y;
			w->ray.pos.y += step.y;
			w->ray.orient = 1;
		}
		if (w->ray.pos.y < 0 || w->file.nb_line <= w->ray.pos.y
				|| w->ray.pos.x < 0
				|| w->file.line_len[(int)w->ray.pos.y] <= w->ray.pos.x)
			w->ray.block = -1;
		else
			w->ray.block = !w->map[(int)w->ray.pos.y][(int)w->ray.pos.x].cross;
	}
}

void	init_step_ray(t_wolf3d_t *w, t_vec2_t *step, t_vec2_t *dist)
{
	t_vec2_t	delta;

	delta = (t_vec2_t){fabs(1 / w->ray.text.x), fabs(1 / w->ray.text.y)};
	step->x = w->ray.text.x < 0 ? -1 : 1;
	if (w->ray.text.x < 0)
		dist->x = (w->pos.x - w->ray.pos.x) * delta.x;
	else
		dist->x = (w->ray.pos.x + 1.0 - w->pos.x) * delta.x;
	step->y = w->ray.text.y < 0 ? -1 : 1;
	if (w->ray.text.y < 0)
		dist->y = (w->pos.y - w->ray.pos.y) * delta.y;
	else
		dist->y = (w->ray.pos.y + 1.0 - w->pos.y) * delta.y;
}

void	raylaunch(t_wolf3d_t *w)
{
	t_vec2_t	step;
	t_vec2_t	dist;

	init_step_ray(w, &step, &dist);
	dda_ray(w, step, dist);
	if (w->ray.orient == 0)
	{
		w->ray.dist = fabs((w->ray.pos.x - w->pos.x + (1 - step.x) / 2)
			/ w->ray.text.x);
		w->ray.offset = w->pos.y + w->ray.dist * w->ray.text.y;
	}
	else
	{
		w->ray.dist = fabs((w->ray.pos.y - w->pos.y + (1 - step.y) / 2)
			/ w->ray.text.y);
		w->ray.offset = w->pos.x + w->ray.dist * w->ray.text.x;
	}
	if (w->ray.orient)
		w->ray.orient += w->ray.text.y < 0 ? 2 : 0;
	else
		w->ray.orient += w->ray.text.x < 0 ? 2 : 0;
	w->ray.offset -= floor(w->ray.offset);
}

void	raycaster(t_wolf3d_t *w)
{
	int		i;
	double	wall_h;
	double	angle;

	i = -1;
	while (++i < w->screen.mode.w)
	{
		angle = w->picture[i] + w->a_view - M_PI / 2;
		w->ray.text = (t_vec2_t){cos(angle), sin(angle)};
		w->ray.pos = (t_vec2_t){(int)w->pos.x, (int)w->pos.y};
		w->ray.block = 0;
		raylaunch(w);
		wall_h = w->screen.mode.w / 1.6 / 4 / w->ray.dist / cos(w->picture[i]);
		draw_texture(w, (SDL_Point){i, wall_h});
	}
}
