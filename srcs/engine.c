/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:15 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/20 18:39:12 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	rendering(t_wolf3d_t *wolf3d)
{
    SDL_RenderPresent(wolf3d->screen.renderer);
}

void	manage_SDL_init(t_wolf3d_t *wolf3d)
{
	SDL_Init(0x00004021u);
	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &wolf3d->screen.win, &wolf3d->screen.renderer);
	SDL_GetDesktopDisplayMode(0, wolf3d->screen.mode);
	SDL_SetRenderDrawBlendMode(wolf3d->screen.renderer, SDL_BLENDMODE_BLEND);
}

void	manage_sdl(t_wolf3d_t *wolf3d)
{
	printf("\ttest D.0\n");
	manage_SDL_init(wolf3d);
	printf("\ttest D.1\n");
	rendering(wolf3d);
	printf("\ttest D.2\n");
	printf("\ttest D.3\n");
	printf("\ttest D.4\n");
	printf("\ttest D.5\n");
	printf("\ttest D.6\n");
	SDL_DestroyRenderer(wolf3d->screen.renderer);
	printf("\ttest D.7\n");
	SDL_DestroyWindow(wolf3d->screen.win);
	printf("\ttest D.8\n");
	SDL_Quit();
}
