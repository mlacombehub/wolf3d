/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:32:10 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/17 18:01:12 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define BUFF_FILE  4094
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_vec2
{
	double	x;
	double	y;
}				t_vec2_t;

# pragma pack(push)
# pragma pack(1)

typedef struct	s_token
{
	unsigned	type:1;
	unsigned	crossable:1;
	unsigned	origin:1;
	unsigned	pickable:1;
	unsigned	texture_a:1;
	unsigned	texture_b:1;
	unsigned	texture_c:1;
	unsigned	ending:1;
}				t_token_t;

# pragma pack(pop)

typedef struct	s_wolf3d
{
	char		*fname;
	t_token_t	**map;
	t_vec2_t	origin;
	t_vec2_t	view;
	int			fov;
	int			nb_line;
	int			*line_len;
	int			max_len;
}				t_wolf3d_t;

void			free_quit(t_wolf3d_t *wolf3d);

void			manage_file(int ac, t_wolf3d_t *wolf3d);

// void	player_pos(t_wolf3d_t *wolf3d);

// void	manage_sdl(t_wolf3d_t *wolf3d);
// void	rendering(t_wolf3d_t *wolf3d);

// void	hook(t_wolf3d_t *wolf3d);

#endif
