/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:32:10 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/14 18:55:15 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define BUFF_FILE  4095
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>

#pragma pack(push)
#pragma pack(1)
typedef struct	s_token
{
    char	type;
    char	crossable;
    char	position;
    char	pickable;
    char	texture[3];
    char	ending;
}               t_token_t;
#pragma pack(pop)

typedef struct  s_wolf3d
{
    char		*fname;
    t_token_t	**map;
}				t_wolf3d_t;

void	init_program(int ac, char **av, t_wolf3d_t *wolf3d);

void	manage_file(int ac, t_wolf3d_t *wolf3d);

// void	player_pos(t_wolf3d_t *wolf3d);

// void	manage_sdl(t_wolf3d_t *wolf3d);
// void	rendering(t_wolf3d_t *wolf3d);

// void	hook(t_wolf3d_t *wolf3d);

#endif
