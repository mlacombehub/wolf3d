/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:31:11 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/20 18:48:17 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_structure(t_wolf3d_t *wolf3d)
{
	if (!(wolf3d = (t_wolf3d_t *)malloc(sizeof(t_wolf3d_t))))
	{
		free(wolf3d);
		return ;
	}
	ft_bzero(&wolf3d, sizeof(t_wolf3d_t *));
}

void	init_program(int ac, char **av, t_wolf3d_t *wolf3d)
{
	if (ac == 1)
		wolf3d->fname = NULL;
	else if (ac == 2)
		wolf3d->fname = av[1];
	else
		ft_puterror(ac != 2, "Usage : ./wolf3d [input_file]");
	wolf3d->fname = av[1];
	init_structure(wolf3d);
}

void	free_quit(t_wolf3d_t *wolf3d)
{
	wolf3d->map ? free(&wolf3d->map) : 42;
	wolf3d ? free(&wolf3d) : 42;
	exit(1);
}

int		main(int ac, char **av)
{
	t_wolf3d_t	wolf3d;

	printf("test A\n");
	init_program(ac, av, &wolf3d);
	printf("\ntest B\n");
	manage_file(ac, &wolf3d);
	printf("\ntest C\n");
	player_pos(&wolf3d);
	printf("\ntest D\n");
	manage_sdl_init(&wolf3d);
	printf("\ntest E\n");
	rendering(&wolf3d);
	// printf("\ntest F\n");
	// hook(&wolf3d);
	// printf("\ntest G\n");
	// printf("\ntest H\n");
	return (0);
}
