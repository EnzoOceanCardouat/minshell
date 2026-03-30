/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:34:02 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/17 22:11:27 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*res;
	size_t		i;

	i = 0;
	if (size != 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	else
	{
		res = malloc(nmemb * size);
		if (!res)
			return (0);
		while (i < nmemb * size)
			res[i++] = '\0';
		return ((void *)res);
	}
}
