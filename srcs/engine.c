/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:15 by mlacombe          #+#    #+#             */
/*   Updated: 2020/09/04 15:25:01 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_texture(t_wolf3d_t *w, SDL_Point pos)
{
	SDL_Rect	orig;
	SDL_Rect	dest;

	dest = (SDL_Rect){pos.x, w->screen.mode.h / 2 - pos.y, 1, pos.y * 2};
	orig = (SDL_Rect){w->screen.walls_size[w->ray.orient].w * w->ray.offset,
			1, 1, w->screen.walls_size[w->ray.orient].h};
	SDL_RenderCopy(w->screen.renderer, w->screen.text_walls[w->ray.orient],
			&orig, &dest);
}

void	draw_decors(t_wolf3d_t *w, SDL_Point pos, int text_v)
{
	SDL_Rect	orig;
	SDL_Rect	dest;

	dest = (SDL_Rect){pos.x, (w->screen.mode.h / 2 + cos(pos.y)), 1, pos.y * 1.5};
	orig = (SDL_Rect){w->screen.decors_size[text_v].w * fabs(w->ray.offset),
		1, 1, w->screen.decors_size[text_v].h};
	SDL_RenderCopy(w->screen.renderer, w->screen.text_decors[text_v],
		&orig, &dest);
}

int		preset_walls_objects(t_wolf3d_t *w)
{
	SDL_Surface	*surf;
	int			i;

	i = -1;
	while (++i < 4)
	{
		if (!(surf = IMG_ReadXPMFromArray(g_walls_xpm[i])))
			return (12);
		if (!(w->screen.text_walls[i] = SDL_CreateTextureFromSurface(
				w->screen.renderer, surf)))
			return (13);
		w->screen.walls_size[i] = surf->clip_rect;
		SDL_FreeSurface(surf);
	}
	i = -1;
	while (++i < 8)
	{
		if (!(surf = IMG_ReadXPMFromArray(g_objects_xpm[i])))
			return (12);
		if (!(w->screen.text_objects[i] = SDL_CreateTextureFromSurface(
				w->screen.renderer, surf)))
			return (13);
		w->screen.objects_size[i] = surf->clip_rect;
		SDL_FreeSurface(surf);
	}
	return (0);
}

int		preset_decors_chests(t_wolf3d_t *w)
{
	SDL_Surface	*surf;
	int			i;

	i = -1;
	while (++i < 7)
	{
		if (!(surf = IMG_ReadXPMFromArray(g_decors_xpm[i])))
			return (12);
		if (!(w->screen.text_decors[i] = SDL_CreateTextureFromSurface(
				w->screen.renderer, surf)))
			return (13);
		w->screen.decors_size[i] = surf->clip_rect;
		SDL_FreeSurface(surf);
	}
	i = -1;
	// while (++i < 6)
	// {
	// 	if (!(surf = IMG_ReadXPMFromArray(g_chests_xpm[i])))
	// 		return (12);
	// 	if (!(w->screen.text_chests[i] = SDL_CreateTextureFromSurface(
	// 			w->screen.renderer, surf)))
	// 		return (13);
	// 	w->screen.chests_size[i] = surf->clip_rect;
	// 	SDL_FreeSurface(surf);
	// }
	return (0);
}

int		manage_sdl_init(t_wolf3d_t *w)
{
	if (SDL_Init(0x00004021u))
		return (w->quit = 8);
	if (SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
		&w->screen.win, &w->screen.renderer))
		return (w->quit = 9);
	if (SDL_GetDesktopDisplayMode(0, &w->screen.mode))
		return (w->quit = 10);
	if (SDL_SetRenderDrawBlendMode(w->screen.renderer, SDL_BLENDMODE_BLEND))
		return (w->quit = 11);
	w->quit = preset_walls_objects(w);
	w->quit = preset_decors_chests(w);
	return (w->quit);
}
