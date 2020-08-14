/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:38:15 by mlacombe          #+#    #+#             */
/*   Updated: 2020/08/14 16:16:43 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	rendering(t_wolf3d_t *wolf3d)
{
	put_image_to_window();
}

void	manage_sdl(t_wolf3d_t *wolf3d)
{
	SDL_init();
	SDL_image();
	SDL_window();
	SDL_data();
}
