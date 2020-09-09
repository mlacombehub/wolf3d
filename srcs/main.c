/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:31:11 by mlacombe          #+#    #+#             */
/*   Updated: 2020/09/09 03:25:20 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf3d_t	init_program(int ac, char **av, t_wolf3d_t *wolf3d)
{
	if (!(wolf3d = (t_wolf3d_t *)malloc(sizeof(t_wolf3d_t) + 1)))
	{
		free(wolf3d);
		wolf3d->quit = 1;
		return (*wolf3d);
	}
	ft_bzero(wolf3d, sizeof(t_wolf3d_t));
	if (ac == 2)
		wolf3d->fname = av[1];
	else if (ac == 1)
		wolf3d->fname = NULL;
	else
	{
		ft_putendl_fd("usage : ./wolf3d [input_file]", 2);
		wolf3d->quit = 1;
		return (*wolf3d);
	}
	return (*wolf3d);
}

void		free_quit(t_wolf3d_t *w)
{
	int i;

	i = -1;
	while (++i < 4 && w->screen.text_walls[i])
		SDL_DestroyTexture(w->screen.text_walls[i]);
	if (w->screen.renderer)
		SDL_DestroyRenderer(w->screen.renderer);
	if (w->screen.win)
		SDL_DestroyWindow(w->screen.win);
	IMG_Quit();
	SDL_Quit();
	w->quit ? ft_putendl_nbr_fd(w->quit, 2) : 0;
}

int			main(int ac, char **av)
{
	t_wolf3d_t	wolf3d;
	SDL_Event	event;

	wolf3d = init_program(ac, av, &wolf3d);
	!wolf3d.quit ? manage_file(ac, &wolf3d) : free_quit(&wolf3d);
	if (!wolf3d.quit)
		wolf3d.quit = manage_sdl_init(&wolf3d);
	else
		free_quit(&wolf3d);
	!wolf3d.quit ? player_pos(&wolf3d) : free_quit(&wolf3d);
	while (!wolf3d.quit)
		wolf3d_events(&wolf3d, &event);
	return (0);
}
