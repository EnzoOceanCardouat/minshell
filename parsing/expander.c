/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:54:43 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:33:04 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	cpytab_else(t_classic *clas, t_data *data, t_token *token)
{
	if (need_split_expand(clas->s, true, data))
	{
		clas->tab = split_ft_expand_strdup(clas->exel[clas->i], data);
		if (!clas->tab)
		{
			free(clas->tab);
			return (true);
		}
	}
	else
	{
		clas->expand = ft_expand_strdup(clas->exel[clas->i], data);
		if (!clas->expand)
		{
			ft_free_split(clas->tab);
			return (true);
		}
		if (clas->expand && clas->expand[0] == '\0'
			&& token->not_del_quote == false)
			free(clas->expand);
		else
			clas->tab[clas->j++] = clas->expand;
	}
	return (false);
}

bool	cpytab_extra(t_classic *clas, t_token **token, bool del, t_data *data)
{
	if (del)
	{
		clas->tab[clas->j] = del_quote(clas->exel[clas->i],
				(*token)->not_del_quote);
		if (!clas->tab[clas->j])
		{
			while (clas->j > 0)
				free(clas->tab[--clas->j]);
			free(clas->tab);
			return (NULL);
		}
		clas->j++;
	}
	else
	{
		if (cpytab_else(clas, data, *token))
			return (true);
	}
	clas->i++;
	*token = (*token)->next;
	return (false);
}

char	**ft_cpytab(char **args, t_token *token, t_data *data, bool del)
{
	t_classic	clas;

	clas.tab = ft_calloc(ft_lentab(token, data) + 1, sizeof(char *));
	if (!clas.tab)
		return (NULL);
	clas.i = 0;
	clas.j = 0;
	clas.exel = args;
	clas.expand = NULL;
	while (clas.exel[clas.i])
	{
		clas.s = clas.exel[clas.i];
		while (token && token->type != WORD)
			token = token->next;
		if (!token)
			break ;
		if (cpytab_extra(&clas, &token, del, data))
			return (NULL);
	}
	return (clas.tab);
}

bool	expander(t_cmd **cmd, t_token *token, t_data *data)
{
	char	**tmp;
	t_cmd	*head;

	head = *cmd;
	if (!(*cmd)->args)
		return (true);
	while (*cmd)
	{
		tmp = ft_cpytab((*cmd)->args, token, data, false);
		if (!tmp)
			return (true);
		ft_free_split((*cmd)->args);
		(*cmd)->args = tmp;
		*cmd = (*cmd)->next;
		tmp = NULL;
	}
	*cmd = head;
	return (false);
}
