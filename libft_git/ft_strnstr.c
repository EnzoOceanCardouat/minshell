/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:22:35 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/21 19:20:47 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	u;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i] && i < len)
	{
		u = 0;
		if (big[i] == little[u])
		{
			while (big[i + u] == little[u])
			{
				if (little[u + 1] == '\0' && (i + u) < len)
					return ((char *)&big[i]);
				u++;
			}
		}
		i++;
	}
	return (0);
}
