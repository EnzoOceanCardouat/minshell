/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:27:41 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:45:13 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	need_parser(t_token *prev_token, t_data *data)
{
	t_token	*token;
	bool	word;

	word = true;
	if (!prev_token)
		return (false);
	token = prev_token->next;
	if (prev_token->type == PIPE)
		word = false;
	while (token)
	{
		if (token->type == PIPE && (prev_token->type != WORD
				|| token->next->type == PIPE || (token->next->type != WORD
					&& token->next->in == -1 && token->next->out == -1)))
			word = false;
		token = token->next;
		prev_token = prev_token->next;
	}
	if (!word)
		data->last_status = 2;
	return (word);
}

int	size_del_args(t_cmd *cmd)
{
	int	i;
	int	size;

	size = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->args[i++])
		{
			if (cmd->args[i - 1][0])
				size++;
		}
		cmd = cmd->next;
	}
	return (size);
}

bool	del_args(t_cmd **cmd)
{
	int		i;
	char	**new_tab;
	t_cmd	*dup_cmd;
	int		j;

	dup_cmd = *cmd;
	new_tab = ft_calloc(size_del_args(*cmd) + 1, sizeof (char *));
	while (dup_cmd)
	{
		i = 0;
		j = 0;
		while (dup_cmd->args[i++])
		{
			if (!dup_cmd->args[i - 1][0])
				free(dup_cmd->args[i -1]);
			else
				new_tab[j++] = dup_cmd->args[i - 1];
		}
		free((*cmd)->args);
		(*cmd)->args = new_tab;
		dup_cmd = dup_cmd->next;
	}
	return (false);
}

int	len_newtab(char **args)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (args[i])
	{
		size++;
		i++;
	}
	return (size);
}

void	set_index_create_cmd(int *clas_1, int *clas_2, int one, int two)
{
	*clas_1 = one;
	*clas_2 = two;
}
