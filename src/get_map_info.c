/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:35:34 by ayaman            #+#    #+#             */
/*   Updated: 2023/08/23 14:22:59 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	b_space(t_game *game, t_node *node, int i)
{
	int		j;

	j = ft_strlen(node->map);
	while (j < game->map_width)
	{
		game->map[i][j] = ' ';
		j++;
	}
	game->map[i][game->map_width] = '\0';
}

void	dup_map(t_game *game)
{
	int		i;
	t_node	*node;
	t_node	*temp;

	node = game->list->head;
	i = 0;
	while (node)
	{
		ft_strlcpy(game->map[i], node->map, ft_strlen(node->map) + 1);
		if (ft_strlen(node->map) < (size_t)game->map_width)
			b_space(game, node, i);
		temp = node;
		node = node->next;
		free(temp->map);
		free(temp);
		game->list->size--;
		i++;
	}
	game->map[i] = NULL;
	free(game->list);
}

int	check_position(t_game *game, int i, int j)
{
	if (i - 1 < 0 || j - 1 < 0 || \
		i + 1 > game->map_height || j + 1 > game->map_width)
		return (RETURN_FAILURE);
	if (game->map[i - 1][j] != '0' && game->map[i - 1][j] != '1')
		return (RETURN_FAILURE);
	if (game->map[i + 1][j] != '0' && game->map[i + 1][j] != '1')
		return (RETURN_FAILURE);
	if (game->map[i][j - 1] != '0' && game->map[i][j - 1] != '1')
		return (RETURN_FAILURE);
	if (game->map[i][j + 1] != '0' && game->map[i][j + 1] != '1')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	check_blank(t_game *game, int i, int j)
{
	if (i - 1 > 0)
		if (game->map[i - 1][j] != ' ' && game->map[i - 1][j] != '1')
			return (RETURN_FAILURE);
	if (j - 1 > 0)
		if (game->map[i][j - 1] != ' ' && game->map[i][j - 1] != '1')
			return (RETURN_FAILURE);
	if (i + 1 < game->map_height)
		if (game->map[i + 1][j] != ' ' && game->map[i + 1][j] != '1')
			return (RETURN_FAILURE);
	if (j + 1 < game->map_width)
		if (game->map[i][j + 1] != ' ' && game->map[i][j + 1] != '1')
			return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

void	get_map_game(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (ft_isalpha(game->map[i][j]))
			{
				if (check_position(game, i, j))
					exit_err("Invalid map\n");
				player_position(game, i, j);
			}
			else if (game->map[i][j] == ' ')
				if (check_blank(game, i, j))
					exit_err("Invalid map\n");
		}
	}
}
