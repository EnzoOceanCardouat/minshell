/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:30:59 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/20 18:23:33 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	count;
	int	check;

	count = 0;
	check = 0;
	while (*s)
	{
		if (*s != c && !check)
		{
			check = 1;
			count++;
		}
		else if (*s == c)
			check = 0;
		s++;
	}
	return (count);
}

static char	**ft_malloc(char const *s, char c, char **strs)
{
	int	i;

	i = 0;
	strs = ft_splitutils(s, c, strs, i);
	return (strs);
}

static char	**ft_fill(char const *s, char c, int count, char **strs)
{
	int	k;
	int	j;
	int	i;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] && j < count)
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				strs[j][k++] = s[i++];
			strs[j][k] = 0;
			k = 0;
			j++;
		}
		else
			i++;
	}
	strs[j] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		count;

	if (!s)
		return (0);
	count = ft_countwords(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (0);
	strs = ft_malloc(s, c, strs);
	if (!strs)
		return (0);
	strs = ft_fill(s, c, count, strs);
	return (strs);
}
