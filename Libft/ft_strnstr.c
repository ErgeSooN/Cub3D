/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:08:10 by ayaman            #+#    #+#             */
/*   Updated: 2023/07/13 18:02:26 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	i2;

	if (*s2 == '\0')
		return ((char *)s1);
	i = 0;
	while (s1[i] && i < n)
	{
		i2 = 0;
		while (s2[i2] && s1[i + i2] && s1[i + i2] == s2[i2]
			&& (i + i2) < n)
			i2++;
		if (s2[i2] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
