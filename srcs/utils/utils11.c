/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:26:45 by ecardoua          #+#    #+#             */
/*   Updated: 2026/07/06 08:54:40 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	quote_del(t_cmd **cmd, t_token *token, t_data *data)
{
	char	**tmp;
	t_cmd	*head;

	head = *cmd;
	while (*cmd)
	{
		if (quote_count((*cmd)->args))
			return (true);
		tmp = ft_cpytab((*cmd)->args, token, data, true);
		if (!tmp)
			return (true);
		ft_free_split((*cmd)->args);
		(*cmd)->args = tmp;
		tmp = NULL;
		*cmd = (*cmd)->next;
	}
	*cmd = head;
	return (false);
}

bool	need_expand_extra(t_cmd *cmd)
{
	int	i;
	int	j;

	while (cmd)
	{
		i = 0;
		while (cmd->args[i++])
		{
			j = 0;
			while (cmd->args[i - 1][j++])
			{
				if (cmd->args[i - 1][j - 1] == '$'
					&& ft_isexpand(cmd->args[i - 1][j], 0, 0))
					return (true);
			}
		}
		cmd = cmd->next;
	}
	return (false);
}

bool	need_expand(t_cmd *cmd, char *s, bool tab)
{
	size_t	i;

	i = 0;
	if (tab && !cmd->args)
		return (false);
	if (tab)
	{
		if (need_expand_extra(cmd))
			return (true);
	}
	else
	{
		while (s[i++])
		{
			if (s[i - 1] == '$' && (ft_isvariable(s[i]) == 0
					|| ft_isdigit(s[i]) == 1 || s[i] == '?'))
				return (true);
		}
	}
	return (false);
}

bool	need_del_q_extra(t_cmd *cmd)
{
	int	i;
	int	j;

	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			j = 0;
			while (cmd->args[i][j])
			{
				if (cmd->args[i][j] == '\''
					|| cmd->args[i][j] == '"')
					return (true);
				j++;
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (false);
}

bool	need_del_quote(t_cmd *cmd, char *s, bool tab)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		if (need_del_q_extra(cmd))
			return (true);
	}
	else
	{
		while (s[i++])
		{
			if (s[i - 1] == '\'' || s[i - 1] == '"')
				return (true);
		}
	}
	return (false);
}
