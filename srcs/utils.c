/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:12:24 by thcotza           #+#    #+#             */
/*   Updated: 2026/03/27 04:03:01 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->input)
		free(data->input);
	if (data->command)
		free(data->command);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strcharjoin(char const *s1, char const s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	dest = malloc((i + 2) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	dest[i++] = s2;
	dest[i] = '\0';
	return (dest);
}
