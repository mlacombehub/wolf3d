/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 18:32:10 by mlacombe          #+#    #+#             */
/*   Updated: 2020/09/01 14:51:45 by mlacombe         ###   ########.fr       */
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
	unsigned		cross:1;
	unsigned		orig:1;
	unsigned		pick:1;
	unsigned		text_a:1;
	unsigned		text_b:1;
	unsigned		text_c:1;
	unsigned		ending:1;
}					t_token_t;

# pragma pack(pop)

typedef struct		s_screen
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_DisplayMode	mode;
	SDL_TimerID		start_timeout;
	SDL_Texture		*text_mandat[4];
	SDL_Rect		mandat_size[4];
	SDL_Texture		*text_objects[6];
	SDL_Rect		objects_size[6];
	SDL_Texture		*text_chests[6];
	SDL_Rect		chests_size[6];
	SDL_Texture		*text_decors[6];
	SDL_Rect		decors_size[6];
}					t_screen_t;

typedef struct		s_rayc
{
	double			dist;
	t_vec2_t		text;
	t_vec2_t		pos;
	double			offset;
	char			block;
	int				orient;

}					t_rayc_t;

typedef struct		s_file
{
	int				*line_len;
	int				nb_line;
	int				max_len;
}					t_file_t;

typedef struct		s_wolf3d
{
	t_screen_t		screen;
	t_token_t		**map;
	t_vec2_t		origin;
	t_vec2_t		pos;
	t_file_t		file;
	t_rayc_t		ray;
	int				keys[SDL_NUM_SCANCODES];
	long double		*picture;
	double			angle_view;
	double			fov;
	char			*fname;
	int				mandat;
	int				quit;
}					t_wolf3d_t;

void				free_quit(t_wolf3d_t *wolf3d);

void				manage_file(int ac, t_wolf3d_t *wolf3d);

void				player_pos(t_wolf3d_t *wolf3d);

int					manage_sdl_init(t_wolf3d_t *wolf3d);
void				rendering(t_wolf3d_t *wolf3d);
void				raycaster(t_wolf3d_t *wolf3d);

void				draw_texture(t_wolf3d_t *wolf3d, SDL_Point point);
void				draw_objects(t_wolf3d_t *wolf3d, SDL_Point point, int text_v);

void				wolf3d_events(t_wolf3d_t *wolf3d, SDL_Event *event);

void				hook(t_wolf3d_t *wolf3d);

#endif
