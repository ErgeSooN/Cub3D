/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:33:26 by ayaman            #+#    #+#             */
/*   Updated: 2023/07/13 18:05:37 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_default(t_game *game)
{
	game->map_width = 0;
	game->map_height = 0;
	game->player = 0;
	game->key_a = 0;
	game->key_w = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
	game->color_flag = 0;
	game->dir_flag = 0;
	game->pos_flag = 0;
	game->msws = 0.035;
	game->msad = 0.035;
	game->list = create_list();
}

void	init_game(t_game *game)
{
	int		i;

	init_default(game);
	i = -1;
	game->buf = (int **)ft_calloc(sizeof(int *) * SCREEN_H, 1);
	if (!game->buf)
		system_err("Malloc Error");
	while (++i < SCREEN_H)
	{
		game->buf[i] = (int *)ft_calloc(sizeof(int) * SCREEN_W, 1);
		if (!game->buf[i])
			system_err("Malloc Error");
	}
	i = -1;
	game->texture = (int **)ft_calloc(sizeof(int *) * 4, 1);
	if (!game->texture)
		system_err("Malloc Error");
	while (++i < 4)
	{
		game->texture[i] = \
			(int *)ft_calloc(sizeof(int) * (TEX_H * TEX_W), 1);
		if (!game->texture[i])
			system_err("Malloc Error");
	}
}

void	init_map(t_game *game)
{
	int		i;

	i = -1;
	game->map = (char **)ft_calloc(sizeof(char *) * (game->map_height + 1), 1);
	if (!game->map)
		system_err("Malloc Error");
	while (++i < game->map_height)
	{
		game->map[i] = \
			(char *)ft_calloc(sizeof(char) * (game->map_width + 1), 1);
		if (!game->map[i])
			system_err("Malloc Error");
	}
}
