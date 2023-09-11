/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:14:55 by ayaman            #+#    #+#             */
/*   Updated: 2023/08/23 13:49:47 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_string(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (RETURN_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parse_color(char *str, int *rgb, int *count)
{
	char	**split;
	int		i;
	int		color;

	split = ft_split(str, ',');
	if (!split)
		system_err("Malloc Error");
	i = 0;
	while (split[i])
	{
		color = -1;
		if (is_valid_string(split[i]))
			return (free_return_err(split));
		color = ft_atoi(split[i]);
		if ((color < 0 || color > 255) || *count > 2)
			return (free_return_err(split));
		rgb[*count] = color;
		*count += 1;
		i++;
	}
	free_double_char(split);
	return (RETURN_SUCCESS);
}

int	get_comma(char *line)
{
	int		i;
	int		comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	return (comma);
}

void	floor_ceiling(t_game *game, int *rgb, int flag)
{
	if (flag == FLOOR)
		game->floor = ((rgb[0] * 256 * 256) + (rgb[1] * 256 + rgb[2]));
	else
		game->ceiling = ((rgb[0] * 256 * 256) + (rgb[1] * 256 + rgb[2]));
}

void	get_background_color(char *line, t_game *game, int flag)
{
	char	**split;
	int		rgb[3];
	int		i;
	int		count;

	i = 1;
	count = 0;
	if (get_comma(line) != 2)
		exit_err("Map: Invalid Color Value\n");
	split = ft_split(line, ' ');
	if (!split)
		system_err("Malloc Error");
	if (ft_splitlen(split) < 2)
		free_exit_err(split, "Map: Invalid Color Value\n");
	while (split[i])
	{
		if (parse_color(split[i], rgb, &count))
			free_exit_err(split, "Map: Invalid Color Value\n");
		i++;
	}
	floor_ceiling(game, rgb, flag);
	game->color_flag++;
	free_double_char(split);
}