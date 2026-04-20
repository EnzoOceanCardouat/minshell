/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzooceancardouat <enzooceancardouat@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:05:13 by ecardoua          #+#    #+#             */
/*   Updated: 2026/04/17 15:26:36 by enzooceanca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	parser(t_token *token, t_cmd **cmd, t_data *data)
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
	(*cmd)->args = malloc((i + 1) * sizeof(char *));
	i = 0;
	if (token->type != PIPE)
	{
		(*cmd)->cmd = ft_strdup(token->value);
		token = token->next;
		while (token->next && token->type == WORD)
		{
			(*cmd)->args[i] = ft_strdup(token->value);
			token = token->next;
			i++;
			if (data->fd_in > 0 && (*cmd)->infile != data->fd_in)
			(*cmd)->infile = data->fd_in;
			else if (data->fd_out > 0 && (*cmd)->outfile != data->fd_out)
				(*cmd)->outfile = data->fd_out;
		}
	}
	(*cmd)->args[i] = NULL;
	return (false);
}

