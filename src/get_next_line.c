/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:16:20 by ayaman            #+#    #+#             */
/*   Updated: 2023/07/13 18:02:26 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	chk_newline(char *temp)
{
	int				i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	sep_line(char **temp, char **line, int is_line)
{
	char			*ptr;

	(*temp)[is_line] = '\0';
	*line = ft_strdup(*temp);
	if (!(*line))
		return (-1);
	ptr = ft_strdup(*temp + is_line + 1);
	if (!ptr)
		return (-1);
	free(*temp);
	*temp = ptr;
	return (1);
}

static int	return_remain(char **temp, char **line, int read_size)
{
	int				i;

	if (read_size < 0)
		return (-1);
	if (*temp && chk_newline(*temp) >= 0)
	{
		i = chk_newline(*temp);
		return (sep_line(temp, line, i));
	}
	else if (*temp)
	{
		*line = *temp;
		*temp = 0;
		return (0);
	}
	*line = ft_strdup("");
	if (!(*line))
		return (-1);
	return (0);
}

int	temp_str(char *temp[], char *buffer, int *is_line, int fd)
{
	temp[fd] = ft_strjoin_free(temp[fd], buffer);
	if (!(temp[fd]))
		return (1);
	*is_line = chk_newline(temp[fd]);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int				is_line;
	int				read_size;
	char			*buffer;
	static char		*temp[MAX_FD];

	if ((fd < 0) || !line || (BUFFER_SIZE <= 0))
		return (-1);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	read_size = read(fd, buffer, BUFFER_SIZE);
	while (read_size > 0)
	{
		buffer[read_size] = '\0';
		if (temp_str(temp, buffer, &is_line, fd))
			return (-1);
		if (is_line >= 0)
		{
			free(buffer);
			return (sep_line(&temp[fd], line, is_line));
		}
		read_size = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (return_remain(&temp[fd], line, read_size));
}
