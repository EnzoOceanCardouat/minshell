/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:11:38 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/21 22:19:43 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	char				*ldest;
	const char			*lsrc;

	i = 0;
	ldest = (char *)dest;
	lsrc = (const char *)src;
	if (!ldest && !src)
		return (0);
	if (dest >= src)
	{
		ldest += n;
		lsrc += n;
		while (n--)
			*--ldest = *--lsrc;
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
