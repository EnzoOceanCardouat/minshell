/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:12:24 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/27 11:25:24 by ecardoua         ###   ########.fr       */
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

void	free_box(t_data *data, t_cmd **cmd, t_token **token)
{
	if (data->input)
		free(data->input);
	if (data->command)
		free(data->command);
	if ((*cmd)->cmd)
	{
		while ((*cmd)->next)
		{
			if ((*cmd)->args)
				free((*cmd)->args);
			if ((*cmd)->cmd)
				free((*cmd)->cmd);
			*cmd = (*cmd)->next;
		}
		if ((*cmd)->args)
			free((*cmd)->args);
		if ((*cmd)->cmd)
			free((*cmd)->cmd);
	}
	*cmd = malloc(sizeof(t_cmd));
	(*cmd)->next = NULL;
	if ((*token))
	{
		while ((*token)->next)
		{
			if ((*token)->value)
				free((*token)->value);
			*token = (*token)->next;
		}
	}

	*token = malloc(sizeof(t_token));
	(*token)->next = NULL;
	(*token)->value = NULL;
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
	dest[i++] = s2;
	dest[i] = '\0';
	return (dest);
}
