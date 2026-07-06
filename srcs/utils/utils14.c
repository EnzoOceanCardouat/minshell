/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils14.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:40:29 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:47:37 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	split_exp_size_extra(t_classic *clas, t_data *data)
{
	clas->expand = ft_env_search(clas->variable, data);
	if (clas->variable)
		free(clas->variable);
	if (!clas->expand)
		return (true);
	clas->variable = NULL;
	clas->i = 0;
	if (clas->expand[0])
		clas->l++;
	while (clas->expand[clas->i++])
	{
		quote_state(&clas->s_quote, &clas->d_quote, clas->expand, clas->i);
		if (clas->expand[clas->i - 1] == ' ' && clas->d_quote % 2 == 0
			&& clas->s_quote % 2 == 0)
			clas->l++;
	}
	free(clas->expand);
	clas->expand = NULL;
	return (false);
}

int	split_expand_size(char *s, t_data *data, bool need_expand)
{
	t_classic	clas;

	clas.d_quote = 0;
	clas.s_quote = 0;
	clas.i = 0;
	clas.l = 0;
	clas.expand = NULL;
	clas.variable = NULL;
	if (need_expand)
	{
		while (s[clas.i++])
		{
			if (s[clas.i - 1] == '$' && clas.s_quote % 2 == 0
				&& ft_isvariable(s[clas.i]) == 0)
			{
				if (while_is_variable(s, &clas.variable, &clas.i) == -1)
					return (-1);
			}
		}
	}
	if (split_exp_size_extra(&clas, data))
		return (-1);
	return (clas.l);
}

bool	expand_lentab(t_classic *clas, t_data *data, t_token *token)
{
	if (while_is_variable(token->value, &clas->variable, &clas->i) == -1)
		return (true);
	clas->expand = ft_env_search(clas->variable, data);
	if (!clas->expand)
		return (true);
	if (need_split_expand(clas->expand, false, NULL))
		clas->l += split_expand_size(clas->expand, NULL, false);
	free(clas->expand);
	if (clas->variable)
		free(clas->variable);
	clas->variable = NULL;
	clas->expand = NULL;
	return (false);
}

void	init_lentab(t_classic *clas)
{
	clas->expand = NULL;
	clas->s_quote = 0;
	clas->l = 0;
	clas->k = 0;
	clas->variable = NULL;
}

int	ft_lentab(t_token *token, t_data *data)
{
	t_classic	clas;

	init_lentab(&clas);
	while (token && token->type != PIPE)
	{
		clas.i = 0;
		if (token->type == WORD)
		{
			clas.k = ft_strlen(token->value);
			while (clas.i < clas.k)
			{
				if (token->value[clas.i] == '$' && clas.s_quote % 2 == 0
					&& ft_isvariable(token->value[clas.i +1]) == 0)
				{
					if (expand_lentab(&clas, data, token))
						return (-1);
				}
				clas.i++;
			}
			clas.l++;
		}
		token = token->next;
	}
	clas.l++;
	return (clas.l);
}
