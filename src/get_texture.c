/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:32:49 by ayaman            #+#    #+#             */
/*   Updated: 2023/08/29 17:15:11 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_image(t_game *game, int *texture, char *path)
{
	t_img	img;
	int		x;
	int		y;

	img.img = \
	mlx_xpm_file_to_image(game->mlx, path, &img.img_width, &img.img_height);
	img.data = \
	(int *)mlx_get_data_addr(img.img, &img.bpp, &img.bpp, &img.bpp);
	y = -1;
	while (++y < img.img_height)
	{
		x = -1;
		while (++x < img.img_width)
			texture[img.img_width * y + x] = img.data[img.img_width * y + x];
	}
	mlx_destroy_image(game->mlx, img.img);
}

void	load_texture(t_game *game, int dir, char *path)
{
	load_image(game, game->texture[dir], path);
}

int	check_extension(char *filename, char *extension)
{
	if (!filename)
		return (EXIT_FAILURE);
	if (ft_strncmp(filename + ft_strlen(filename) - 4, extension, 4))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_texture(char *line, t_game *game, int dir)
{
	int		fd;
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		system_err("Malloc Error");
	if (ft_splitlen(split) != 2 || check_extension(split[1], ".xpm"))
	{
		free_double_char(split);
		return (RETURN_FAILURE);
	}
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
		return (RETURN_FAILURE);
	load_texture(game, dir, split[1]);
	free_double_char(split);
	game->dir_flag++;
	return (RETURN_SUCCESS);
}

int	get_textures(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (get_texture(line, game, NO))
			exit_err("Map: Invalid Texture Value\n");
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (get_texture(line, game, EA))
			exit_err("Map: Invalid Texture Value\n");
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (get_texture(line, game, SO))
			exit_err("Map: Invalid Texture Value\n");
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (get_texture(line, game, WE))
			exit_err("Map: Invalid Texture Value\n");
	}
	return (RETURN_SUCCESS);
}
