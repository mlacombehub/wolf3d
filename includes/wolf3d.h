/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:32:10 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/20 18:48:39 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>

# define BUFF_FILE  4095

typedef struct		s_vec2
{
	double			x;
	double			y;
}					t_vec2_t;

# pragma pack(push)
# pragma pack(1)

typedef struct		s_token
{
	unsigned		type:1;
	unsigned		crossable:1;
	unsigned		origin:1;
	unsigned		pickable:1;
	unsigned		texture_a:1;
	unsigned		texture_b:1;
	unsigned		texture_c:1;
	unsigned		ending:1;
}					t_token_t;

# pragma pack(pop)

typedef struct		s_screen
{
	int				w;
	int				h;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_DisplayMode	*mode;
	SDL_Texture		*text_mandat[4];
	SDL_Texture		*text_walls[6];
	SDL_Texture		*text_objects[6];
	SDL_Texture		*text_chest[6];
	SDL_Texture		*text_decor[6];
}					t_screen_t;

typedef struct	s_file
{
	int				*line_len;
	int				nb_line;
	int				max_len;
}					t_file_t;

typedef struct	s_wolf3d
{
	t_screen_t		screen;
	t_token_t		**map;
	t_vec2_t		origin;
	t_file_t		file;
	long double		*picture;
	double			angle_view;
	double			fov;
	char			*fname;
}					t_wolf3d_t;

void	free_quit(t_wolf3d_t *wolf3d);

void	manage_file(int ac, t_wolf3d_t *wolf3d);

void	player_pos(t_wolf3d_t *wolf3d);

void	manage_sdl_init(t_wolf3d_t *wolf3d);
void	rendering(t_wolf3d_t *wolf3d);

// void	hook(t_wolf3d_t *wolf3d);

#endif
