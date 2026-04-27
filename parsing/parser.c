/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:05:13 by ecardoua          #+#    #+#             */
/*   Updated: 2026/04/20 13:01:36 by ecardoua         ###   ########.fr       */
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

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->infile = -1;
	new->outfile = -1;
	new->next = NULL;
	return (new);
}

bool	parser(t_token *token, t_cmd **cmd, t_data *data)
{
	t_cmd	*current;
	int		arg_i;
	int		word_count;

	(void)data;
	if (!token)
		return (true);
	current = *cmd;
	current->cmd = NULL;
	current->args = NULL;
	current->infile = -1;
	current->outfile = -1;
	current->next = NULL;
	while (token)
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
				word_count = count_cmd_words(token) - 1;
				if (word_count < 0)
					word_count = 0;
				current->args = malloc(sizeof(char *) * (word_count + 1));
				if (!current->args)
					return (true);
				arg_i = 0;
			}
			else
				current->args[arg_i++] = ft_strdup(token->value);
			}
		token = token->next;
	}
	if (current->args)
		current->args[arg_i] = NULL;
	else
	{
		current->args = malloc(sizeof(char *) * 1);
		if (!current->args)
			return (true);
		current->args[0] = NULL;
	}
	return (false);
}

