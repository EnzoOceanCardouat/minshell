/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:05:13 by ecardoua          #+#    #+#             */
/*   Updated: 2026/05/06 14:23:59 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_cmd_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

static t_cmd	*create_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->infile = -1;
	new->outfile = -1;
	new->next = NULL;
	return (new);
}

bool	parser(t_token *token, t_cmd **cmd)
{
	t_cmd	*current;
	int		i;
	int		word_count;

	i = 0;
	if (!token)
		return (true);
	*cmd = create_cmd();
	current = *cmd;
	while (token->next)
	{
		if (token->type == PIPE)
		{
			current->next = create_cmd();
			if (!current->next)
				return (true);
			current = current->next;
			token = token->next;
			continue ;
		}
		if (token->type == WORD)
		{
			if (!current->cmd)
			{
				current->cmd = ft_strdup(token->value);
				if (!current->cmd)
					return (true);
				word_count = count_cmd_words(token) - 1;
				if (word_count < 0)
					word_count = 0;
				current->args = malloc(sizeof(char *) * (word_count + 1));
				if (!current->args)
					return (true);
			}
			else
			{
				current->args[i++] = ft_strdup(token->value);
				if (!current->args[i -1])
					return (true);
			}
		token = token->next;
		}
	}
	if (current->args)
		current->args[i] = NULL;
	else
	{
		current->args = malloc(sizeof(char *) * 1);
		if (!current->args)
			return (true);
		current->args[0] = NULL;
	}
	*cmd = current;
	return (false);
}

