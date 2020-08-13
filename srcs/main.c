/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:31:11 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/13 22:56:13 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
I)	initialisation du programme
	1) 	vérification du paramètre en entrée
		a) si le fichier n'existe pas ou qu'il y a plusieurs ou pas de fichier en paramètre, on ferme le programme
	2) 	création de la structure
		a) allocation de la structure
		b) initialisation des éléments de la structure
*/

#include "wolf3d.h"
#include <fcntl.h>

int		ft_protect_fd(int ac, char *fname)
{
	int		fd;

	if (ac > 2 && (fd = open(fname, O_RDONLY)) == -1)
	{
		ft_putendl_fd("usage : ./wolf3d [input_file]", 2);
		return (1);
	}
	if (ac != 1 && ft_open_close_fd(fname) == 1)
		return (1);
	if (read(fd, 0, 1) == '\0' || read(fd, NULL, 0) == -1)
	{
		ft_putendl_fd("Problem with reading file : NULL or VOID", 2);
		return (1);
	}
	if (close(fd) < 0)
	{
		ft_putendl_fd("Problem with closing file", 2);
		return (1);
	}
	return (0);
}

static char	*manage_file(int ac, char **av, t_wolf3d_t *wolf3d)
{
	int		fd;

    ac == 1 ? fd = 0 : 42;
    ft_puterror(ac != 2, "Usage : ./wolf3d [input_file]");
	ft_protect_fd(ac, av[1]) == 1 ? exit(1) : 42;
    
	wolf3d->file = av[1];
}

int main(int ac, char **av)
{
	t_wolf3d_t	wolf3d;

	ft_bzero(&wolf3d, sizeof(t_wolf3d_t *));
    manage_file(ac, av, &wolf3d);
	ft_putendl(wolf3d.file);
	return (0);
}
