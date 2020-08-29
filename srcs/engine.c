/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:15 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/29 20:19:46 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "xpm/mandat/mandat.xpm"

void	draw_texture(t_wolf3d_t *w, SDL_Point pos)
{
	SDL_Rect	orig;
	SDL_Rect	dest;

	dest = (SDL_Rect){pos.x, w->screen.mode.h / 2 - pos.y, 1, pos.y * 2};
	if (w->mandat == 0)
	{
		orig = (SDL_Rect){w->screen.mandat_size[w->ray.orient].w *
			w->ray.offset, 1, 1, w->screen.mandat_size[w->ray.orient].h};
		SDL_RenderCopy(w->screen.renderer, w->screen.text_mandat[w->ray.orient],
						&orig, &dest);
	}
}

int		preset_textures(t_wolf3d_t *w)
{
	SDL_Surface	*surf;
	int			i;

	i = -1;
	while (++i < 4)
	{
		if (!(surf = IMG_ReadXPMFromArray(g_mandat_xpm[i])))
			return (12);
		if (!(w->screen.text_mandat[i] = SDL_CreateTextureFromSurface(
				w->screen.renderer, surf)))
			return (13);
		w->screen.mandat_size[i] = surf->clip_rect;
		SDL_FreeSurface(surf);
	}
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
	w->quit = preset_textures(w);
	return (w->quit);
}
