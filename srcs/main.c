/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:31:11 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/29 20:44:36 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_program(int ac, char **av, t_wolf3d_t *wolf3d)
{
	if (ac == 2)
		wolf3d->fname = av[1];
	else if (ac == 1)
		wolf3d->fname = NULL;
	else
	{
		ft_putendl_fd("usage : ./wolf3d [input_file]", 2);
		wolf3d->quit = 1;
		return ;
	}
	if (!(wolf3d = (t_wolf3d_t *)malloc(sizeof(t_wolf3d_t))))
	{
		free(wolf3d);
		wolf3d->quit = 1;
		return ;
	}
	ft_bzero(wolf3d, sizeof(t_wolf3d_t));
}

void	free_quit(t_wolf3d_t *w)
{
	int i;

	i = -1;
	printf("E : %i\n", w->quit);
	while (++i < 4 && w->screen.text_mandat[i])
		SDL_DestroyTexture(w->screen.text_mandat[i]);
	printf("F : %i\n", w->quit);
	if (w->screen.renderer)
		SDL_DestroyRenderer(w->screen.renderer);
	printf("G : %i\n", w->quit);
	if (w->screen.win)
		SDL_DestroyWindow(w->screen.win);
	printf("H : %i\n", w->quit);
	IMG_Quit();
	SDL_Quit();
	printf("I : %i\n", w->quit);
}

int		main(int ac, char **av)
{
	t_wolf3d_t	wolf3d;
	SDL_Event	event;

	init_program(ac, av, &wolf3d);
	!wolf3d.quit ? manage_file(ac, &wolf3d) : free_quit(&wolf3d);
	if (!wolf3d.quit)
		wolf3d.quit = manage_sdl_init(&wolf3d);
	else
		free_quit(&wolf3d);
	!wolf3d.quit ? player_pos(&wolf3d) : free_quit(&wolf3d);
	while (!wolf3d.quit)
	{
		if (wolf3d.keys[SDL_SCANCODE_ESCAPE])
			wolf3d.quit = 42;
		SDL_SetRenderDrawColor(wolf3d.screen.renderer, 40, 30, 30, 255);
		SDL_RenderClear(wolf3d.screen.renderer);
		SDL_SetRenderDrawColor(wolf3d.screen.renderer, 20, 75, 80, 255);
		SDL_RenderFillRect(wolf3d.screen.renderer, &(SDL_Rect){0, 0,
							wolf3d.screen.mode.w, wolf3d.screen.mode.h / 2});
		raycaster(&wolf3d);
		SDL_RenderPresent(wolf3d.screen.renderer);
		hook(&wolf3d);
		SDL_Delay(50);
		while (SDL_PollEvent(&event))
			wolf3d_events(&wolf3d, &event);
	}
	return (0);
}
