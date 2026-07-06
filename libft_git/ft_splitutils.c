/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:08:24 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/17 22:49:33 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freeall(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	**ft_splitutils(char const *s, char c, char **strs, int i)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
			{
				s++;
				count++;
			}
			strs[i] = malloc(sizeof(char) * (count + 1));
			if (!strs[i++])
			{
				ft_freeall(strs);
				return (0);
			}
			count = 0;
		}
		else
			s++;
	}
	return (strs);
}
