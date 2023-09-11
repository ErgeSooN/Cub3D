/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:33:05 by ayaman            #+#    #+#             */
/*   Updated: 2023/08/25 17:28:56 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	parse_line(t_game *game, char *line)
{
	if (game->dir_flag > 4 || game->color_flag > 2)
		exit_err(".cub: Too Much gamermation Error\n");
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
		!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		get_textures(line, game);
	else if (!ft_strncmp(line, "F ", 2))
		get_background_color(line, game, FLOOR);
	else if (!ft_strncmp(line, "C ", 2))
		get_background_color(line, game, CEILING);
	else if (ft_strlen(line) <= 0)
		return ;
	else if (game->color_flag == 2 && game->dir_flag == 4)
		parse_map(line, game);
	else
		exit_err(".cub: Invalid Identifier Error\n");
}

void	parse_cub(int fd, t_game *game)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (!line)
			exit_err("GNL Error\n");
		parse_line(game, line);
		free(line);
	}
	parse_last(game, line);
	free(line);
	if (game->dir_flag != 4 || game->color_flag != 2 || game->pos_flag != 1)
		exit_err(".cub: Too Few gamermation\n");
}

void	check_arg(int argc, char **argv, t_game *game)
{
	int		i;
	int		fd;

	if (argc != 2)
		exit_err("Input Argument Error\n");
	i = ft_strlen(argv[1]) - 4;
	if (ft_strncmp(&argv[1][i], ".cub", 4))
		exit_err("File Extension Error\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		system_err(".cub Path Error");
	parse_cub(fd, game);
	if (close(fd) < 0)
		system_err("Close Failed Error");
}
