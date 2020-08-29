/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:19 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/29 19:52:26 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf3d_events(t_wolf3d_t *w, SDL_Event *event)
{
	if (event->type == SDL_KEYUP)
		w->keys[event->key.keysym.scancode] = 0;
	else if (event->type == SDL_KEYDOWN)
		w->keys[event->key.keysym.scancode] = 1;
}

void	hook(t_wolf3d_t *w)
{
	float		speed;
	t_vec2_t	new_p;

	new_p = w->pos;
	speed = w->keys[SDL_SCANCODE_LCTRL] ? 0.5 : 0.1;
	w->keys[SDL_SCANCODE_A] ? w->angle_view -= M_PI / 32 : 0;
	w->keys[SDL_SCANCODE_D] ? w->angle_view += M_PI / 32 : 0;
	if (w->keys[SDL_SCANCODE_W] && !w->keys[SDL_SCANCODE_S])
		new_p = (t_vec2_t){w->pos.x + sin(w->angle_view) * speed, w->pos.y
				- cos(w->angle_view) * speed};
	else if (!w->keys[SDL_SCANCODE_W] && w->keys[SDL_SCANCODE_S])
		new_p = (t_vec2_t){w->pos.x - sin(w->angle_view) * speed, w->pos.y
				+ cos(w->angle_view) * speed};
	if (0 <= new_p.y && new_p.y < w->file.nb_line && 0 <= w->pos.x && w->pos.x
		< w->file.line_len[(int)w->pos.y])
		if (w->map[(int)new_p.y][(int)w->pos.x].cross == 1)
			w->pos.y = new_p.y;
	if (0 <= w->pos.y && w->pos.y < w->file.nb_line && 0 <= new_p.x && new_p.x
		< w->file.line_len[(int)w->pos.y])
		if (w->map[(int)w->pos.y][(int)new_p.x].cross == 1)
			w->pos.x = new_p.x;
	if (!w->mandat && w->keys[SDL_SCANCODE_P])
		w->mandat = 1;
	else if (w->mandat && w->keys[SDL_SCANCODE_P])
		w->mandat = 0;
}
