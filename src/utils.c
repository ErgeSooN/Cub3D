/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:41:09 by ayaman            #+#    #+#             */
/*   Updated: 2023/07/13 18:02:26 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_splitlen(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_double_int(int **arr, int size)
{
	int		i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}

void	free_double_char(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_list(t_game *game)
{
	t_node	*node;
	t_node	*temp;

	node = game->list->head;
	if (!node)
		return ;
	while (node)
	{
		free(node->map);
		temp = node;
		node = node->next;
		free(temp);
	}
	free(game->list);
}

void	deinitialize(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	free_double_int(game->texture, 4);
	free_double_int(game->buf, SCREEN_H);
}
