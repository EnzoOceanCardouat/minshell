/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:05:13 by ecardoua          #+#    #+#             */
/*   Updated: 2026/04/01 17:17:14 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	parser(t_token *token, t_cmd **cmd)
{
	int	i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp->next)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	(*cmd)->args = malloc(i * sizeof(char *));
	i = 0;
	if (ft_strcmp(token->value, "echo") == 0 && token->type != PIPE)
	{
		(*cmd)->cmd = ft_strdup("echo");
		token = token->next;
		while (token->next && token->type == WORD)
		{
			(*cmd)->args[i] = ft_strdup(token->value);
			token = token->next;
			i++;
		}
	}
	return (false);
}

