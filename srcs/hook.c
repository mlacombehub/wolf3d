/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:19 by mlacombe          #+#    #+#             */
/*   Updated: 2020/09/08 18:31:54 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_map(t_wolf3d_t *w)
{
	t_point_t	p;
	SDL_Rect	rect;

	p = (t_point_t){-1, -1};
	SDL_SetRenderDrawColor(w->screen.renderer, 255, 255, 255, 80);
	while (++p.y < w->file.nb_line)
	{
		p.x = -1;
		while (++p.x < w->file.line_len[p.y])
		{
			rect = (SDL_Rect){p.x * 10, p.y * 10, 10, 10};
			if (w->map[p.y][p.x].cross)
				SDL_RenderFillRect(w->screen.renderer, &rect);
		}
	}
	SDL_SetRenderDrawColor(w->screen.renderer, 255, 0, 0, 200);
	SDL_RenderFillRect(w->screen.renderer, &(SDL_Rect){(int)w->pos.x * 10,
						(int)w->pos.y * 10, 10, 10});
	SDL_SetRenderDrawColor(w->screen.renderer, 0, 0, 255, 200);
	SDL_RenderFillRect(w->screen.renderer, &(SDL_Rect){(int)w->origin.x * 10,
						(int)w->origin.y * 10, 10, 10});
}

void	hook_1(t_wolf3d_t *w)
{
	float		speed;
	t_vec2_t	new_p;

	new_p = w->pos;
	speed = w->keys[SDL_SCANCODE_LSHIFT] ? 0.5 : 0.1;
	w->keys[SDL_SCANCODE_A] ? w->a_view -= M_PI / 32 : 0;
	w->keys[SDL_SCANCODE_D] ? w->a_view += M_PI / 32 : 0;
	if (w->keys[SDL_SCANCODE_W] && !w->keys[SDL_SCANCODE_S])
		new_p = (t_vec2_t){w->pos.x + sin(w->a_view) * speed, w->pos.y
				- cos(w->a_view) * speed};
	else if (!w->keys[SDL_SCANCODE_W] && w->keys[SDL_SCANCODE_S])
		new_p = (t_vec2_t){w->pos.x - sin(w->a_view) * speed, w->pos.y
				+ cos(w->a_view) * speed};
	if (0 <= new_p.y && new_p.y < w->file.nb_line && 0 <= w->pos.x && w->pos.x
		< w->file.line_len[(int)new_p.y])
		if (w->map[(int)new_p.y][(int)w->pos.x].cross == 1)
			w->pos.y = new_p.y;
	if (0 <= w->pos.y && w->pos.y < w->file.nb_line && 0 <= new_p.x && new_p.x
		< w->file.line_len[(int)w->pos.y])
		if (w->map[(int)w->pos.y][(int)new_p.x].cross == 1)
			w->pos.x = new_p.x;
	w->a_view >= 2 * M_PI ? w->a_view -= 2 * M_PI : 0;
	w->a_view < 0 ? w->a_view += 2 * M_PI : 0;
}

void	hook_2(t_wolf3d_t *w)
{
	if (w->keys[SDL_SCANCODE_M])
	{
		w->draw_m = !w->draw_m;
		SDL_Delay(100);
	}
	if (w->keys[SDL_SCANCODE_SPACE])
	{
		w->map[(int)w->pos.y][(int)w->pos.x].cross = 1;
		if (M_PI / 4 <= w->a_view && w->a_view < 3 * M_PI / 4
				&& w->pos.x + 1 <= w->file.line_len[(int)w->pos.y]
				&& w->pos.y <= w->file.nb_line)
			w->map[(int)w->pos.y][(int)w->pos.x + 1].cross = 1;
		else if (3 * M_PI / 4 <= w->a_view && w->a_view < 5 * M_PI / 4
				&& w->pos.y + 1 <= w->file.nb_line
				&& w->pos.x <= w->file.line_len[(int)w->pos.y + 1])
			w->map[(int)w->pos.y + 1][(int)w->pos.x].cross = 1;
		else if (5 * M_PI / 4 <= w->a_view && w->a_view < 7 * M_PI / 4
				&& w->pos.x - 1 >= 0 && w->pos.y <= w->file.nb_line)
			w->map[(int)w->pos.y][(int)w->pos.x - 1].cross = 1;
		else if ((7 * M_PI / 4 <= w->a_view || w->a_view < M_PI / 4)
				&& w->pos.y - 1 >= 0
				&& w->pos.x <= w->file.line_len[(int)w->pos.y - 1])
			w->map[(int)w->pos.y - 1][(int)w->pos.x].cross = 1;
	}
}

void	wolf3d_events(t_wolf3d_t *w, SDL_Event *event)
{
	w->keys[SDL_SCANCODE_ESCAPE] ? w->quit = 42 : 0;
	SDL_SetRenderDrawColor(w->screen.renderer, 40, 30, 30, 255);
	SDL_RenderClear(w->screen.renderer);
	SDL_SetRenderDrawColor(w->screen.renderer, 20, 75, 80, 255);
	SDL_RenderFillRect(w->screen.renderer, &(SDL_Rect){0, 0,
						w->screen.mode.w, w->screen.mode.h / 2});
	raycaster(w);
	if (w->draw_m == 1)
		draw_map(w);
	SDL_RenderPresent(w->screen.renderer);
	hook_1(w);
	hook_2(w);
	if (w->keys[SDL_SCANCODE_E])
		w->pos = w->origin;
	SDL_Delay(50);
	while (SDL_PollEvent(event))
		if (event->type == SDL_KEYUP)
			w->keys[event->key.keysym.scancode] = 0;
		else if (event->type == SDL_KEYDOWN)
			w->keys[event->key.keysym.scancode] = 1;
}
