/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:00:29 by ayaman            #+#    #+#             */
/*   Updated: 2023/07/13 18:02:26 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map_content(t_game *game, char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (game->pos_flag)
			return (RETURN_FAILURE);
		game->pos_flag = 1;
		return (RETURN_SUCCESS);
	}
	else if (c == ' ' || c == '0' || c == '1')
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

int	check_map(t_game *game, char *line, int size)
{
	int		i;

	i = -1;
	if (game->list->head == NULL)
	{
		while (++i < size)
		{
			if (line[i] != '1' && line[i] != ' ')
				return (RETURN_FAILURE);
		}
	}
	else
	{
		while (++i < size)
		{
			if (check_map_content(game, line[i]))
				return (RETURN_FAILURE);
		}
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] != '1' && line[size - 1] != '1')
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

void	parse_map(char *line, t_game *game)
{
	int		size;
	t_node	*node;

	size = ft_strlen(line);
	if (check_map(game, line, size))
		exit_err("Map: Invalid Map Value\n");
	node = create_node(line);
	add_node(game->list, node);
	if (game->map_width < size)
		game->map_width = size;
	game->map_height++;
}

void	parse_last(t_game *game, char *line)
{
	t_node	*node;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(line);
	while (i < size)
	{
		if (line[i] != '1' && line[i] != ' ')
			exit_err("Map: Invalid Last Line\n");
		i++;
	}
	node = create_node(line);
	add_node(game->list, node);
	if (game->map_width < size)
		game->map_width = size;
	game->map_height++;
}
