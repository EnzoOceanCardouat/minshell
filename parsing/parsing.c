/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:05:13 by ecardoua          #+#    #+#             */
/*   Updated: 2026/03/31 17:05:20 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	parser(t_token *token, t_cmd **cmd)
{
	char	*tmp;

	if (ft_strcmp(token->value, "echo") == 0 && token->type != PIPE)
	{
		(*cmd)->cmd = ft_strdup("echo");
		token = token->next;
		while (token->next && token->type == WORD)
		{
			tmp = (*cmd)->args;
			(*cmd)->args = ft_strjoin(tmp, token->value);
			free(tmp);
			token = token->next;
			if (token->next)
			{
				tmp = (*cmd)->args;
				(*cmd)->args = ft_strjoin(tmp, " ");
				free(tmp);
			}
		}
		if (token->type == MORE || token->type == D_MORE || token->type == LESS || token->type == D_LESS)
		{
			(*cmd)->append = token->type;
			token = token->next;
			if (token->type == WORD && ((*cmd)->append == MORE || (*cmd)->append == D_MORE))
			{
				(*cmd)->outfile = token->value;
				token = token->next;
			}
			// else if (token->type == WORD && (*cmd)->append == D_LESS)
			// 	(*cmd)->infile = "je sais pas encore quoi";
		}
		while (token->next && token->type == WORD)
		{
			tmp = (*cmd)->args;
			(*cmd)->args = ft_strjoin(tmp, token->value);
			free(tmp);
			token = token->next;
			if (token->next)
			{
				tmp = (*cmd)->args;
				(*cmd)->args = ft_strjoin(tmp, " ");
				free(tmp);
			}
		}
	}
	return (false);
}
