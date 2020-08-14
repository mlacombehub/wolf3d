/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:31:11 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/14 18:54:27 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_structure(t_wolf3d_t *wolf3d, t_token_t **map)
{
	if(!(wolf3d = (t_wolf3d_t *)malloc(sizeof(t_wolf3d_t))))
		return ;
	ft_bzero(&wolf3d, sizeof(t_wolf3d_t *));
	if(!(map = (t_token_t **)malloc(sizeof(t_token_t *))))
		return ;
}

void	init_program(int ac, char **av, t_wolf3d_t *wolf3d)
{
	if (ac == 1)
		wolf3d->fname = NULL;
	else if (ac == 2)
		wolf3d->fname = av[1];
	else
		ft_puterror(ac != 2, "Usage : ./wolf3d [input_file]");
	init_structure(wolf3d, wolf3d->map);
	wolf3d->fname = av[1];
}

int		main(int ac, char **av)
{
	t_wolf3d_t	wolf3d;

	init_program(ac, av, &wolf3d);
	ft_putendl_nbr(sizeof(wolf3d.map));
	ft_putendl(wolf3d.fname);
	manage_file(ac, av[1], &wolf3d);
	// player_pos(&wolf3d);
	// manage_sdl(&wolf3d);
	// rendering(&wolf3d);
	// hook(&wolf3d);
	return (0);
}
