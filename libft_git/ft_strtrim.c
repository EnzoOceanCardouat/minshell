/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:51:39 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/17 22:12:57 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_char(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	size_t			len;
	size_t			i;

	i = 0;
	if (!s1 || !set)
		return (0);
	while (ft_is_char(set, *s1) && *s1)
		s1++;
	len = ft_strlen(s1);
	while (ft_is_char(set, s1[len - 1]) && len)
		len--;
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
