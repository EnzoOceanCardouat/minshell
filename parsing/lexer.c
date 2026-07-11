/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:39:14 by thcotza           #+#    #+#             */
/*   Updated: 2026/07/11 17:11:45 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	create_cmd(t_cmd **cmd)
{
	t_classic	clas;
	t_cmd		*dup;

	if (!(*cmd)->args[0])
		return (true);
	dup = *cmd;
	if (alloc_create_cmd(&clas, &dup))
		return (true);
	if (alloc_tab_create_cmd(&clas, &dup))
		return (true);
	while (dup->args[clas.i])
	{
		clas.j = 0;
		while (dup->args[clas.i][clas.j])
		{
			clas.tab[clas.k][clas.j] = dup->args[clas.i][clas.j];
			clas.j++;
		}
		clas.i++;
		clas.k++;
	}
	final_part_create_cmd(&clas, cmd);
	return (false);
}

bool	pars_need_extra(t_cmd **cmd, t_token **token, t_data **data)
{
	if (parser(*token, cmd))
		return (true);
	(*data)->cmd_head = *cmd;
	(*data)->token_head = *token;
	if (need_expand(*cmd, NULL, true))
	{
		if (expander(cmd, *token, *data))
			return (true);
	}
	if (need_del_quote(*cmd, NULL, true))
	{
		if (quote_del(cmd, *token, *data))
			return (true);
	}
	return (false);
}

bool	pars_extra_create_cmd(t_cmd **cmd)
{
	t_cmd	*dup_cmd;

	if ((*cmd)->next)
	{
		dup_cmd = *cmd;
		while (dup_cmd)
		{
			if (create_cmd(&dup_cmd))
				return (true);
			dup_cmd = dup_cmd->next;
		}
	}
	else
	{
		if (create_cmd(cmd))
			return (true);
	}
	return (false);
}

bool	parse_input(t_data *data, t_token **token, t_cmd **cmd)
{
	if (!*token)
	{
		if (token_init(token))
			return (true);
	}
	if (!data->input[0])
		return (true);
	if (lexer(data->input, token, &data))
		return (true);
	if (need_parser(*token, data))
	{
		if (pars_need_extra(cmd, token, &data))
			return (true);
		if (pars_extra_create_cmd(cmd))
			return (true);
	}
	return (false);
}
