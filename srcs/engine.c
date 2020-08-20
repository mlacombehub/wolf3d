/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:15 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/20 18:57:22 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	rendering(t_wolf3d_t *wolf3d)
{
	while(event)
	    SDL_RenderPresent(wolf3d->screen.renderer);
}

void	manage_SDL_init(t_wolf3d_t *wolf3d)
{
	SDL_Init(0x00004021u);
	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &wolf3d->screen.win, &wolf3d->screen.renderer);
	SDL_GetDesktopDisplayMode(0, wolf3d->screen.mode);
	SDL_SetRenderDrawBlendMode(wolf3d->screen.renderer, SDL_BLENDMODE_BLEND);
}
