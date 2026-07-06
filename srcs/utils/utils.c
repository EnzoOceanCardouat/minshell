/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:12:24 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/26 13:50:23 by ecardoua         ###   ########.fr       */
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
	if (data->input)
		free(data->input);
	if (data->fd_in >= 0)
		close(data->fd_in);
	if (data->fd_out >= 0)
		close(data->fd_out);
	if (data->env_cpy)
		ft_free_split(data->env_cpy);
	if (data->env_list)
		lst_free(data->env_list);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
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
	char	*dest;

	if (!s2)
		return (NULL);
	i = ft_strlen(s1);
	dest = ft_calloc(i + 2, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, (char *)s1, i + 1);
	dest[i] = s2;
	return (dest);
}

char	*ft_chardup(char c)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
