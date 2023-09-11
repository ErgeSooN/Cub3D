/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:22:44 by ayaman            #+#    #+#             */
/*   Updated: 2023/07/13 18:02:28 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i2;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	i = ft_strlen(dst);
	i2 = 0;
	while (src[i2] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i2];
		i++;
		i2++;
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i2]));
}
