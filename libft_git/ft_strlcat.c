/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:22:55 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/17 22:14:35 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	a;

	j = ft_strlen(src);
	i = ft_strlen((const char *)dst);
	a = 0;
	if (size <= i)
		return (size + j);
	while (src[a] && i + a < size - 1)
	{
		dst[i + a] = src[a];
		a++;
	}
	dst[a + i] = 0;
	return (j + i);
}
