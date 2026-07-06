/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzooceancardouat <enzooceancardouat@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:11:38 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/17 15:26:11 by enzooceanca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char				*ldest;
	const char			*lsrc;

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
