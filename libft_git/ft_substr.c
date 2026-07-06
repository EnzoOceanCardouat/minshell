/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:23:48 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/17 22:12:12 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sstr;
	unsigned int	i;
	size_t			lens;

	if (!s)
		return (0);
	lens = ft_strlen(s);
	if (lens < start)
		lens = 0;
	else
		lens -= start;
	if (lens > len)
		lens = len;
	i = 0;
	sstr = malloc(sizeof(char) * (lens + 1));
	if (!(sstr))
		return (0);
	while (i < lens)
	{
		sstr[i] = s[start + i];
		i++;
	}
	sstr[i] = '\0';
	return (sstr);
}
