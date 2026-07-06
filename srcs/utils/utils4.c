/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 02:55:09 by thcotza           #+#    #+#             */
/*   Updated: 2026/07/06 08:49:35 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

int	count_args(t_cmd *cmd)
{
	int	count;

	if (!cmd || !cmd->args)
		return (0);
	count = 0;
	while (cmd->args[count])
		count++;
	return (count);
}

bool	env_val_need_split_exp(t_classic *clas, t_data *data,
			int s_quote, int d_quote)
{
	clas->expand = NULL;
	clas->expand = ft_env_search(clas->variable, data);
	if (clas->variable)
		free(clas->variable);
	if (!clas->expand)
		return (false);
	clas->variable = NULL;
	clas->i = 0;
	while (clas->expand[clas->i])
	{
		if (clas->expand[clas->i] == ' ' && d_quote % 2 == 0
			&& s_quote % 2 == 0)
		{
			free(clas->expand);
			return (true);
		}
		clas->i++;
	}
	free(clas->expand);
	clas->expand = NULL;
	return (false);
}

void	init_need_split_exp(t_classic *clas, char *s)
{
	clas->d_quote = 0;
	clas->s_quote = 0;
	clas->i = 0;
	clas->variable = NULL;
	clas->s = s;
}

bool	need_split_expand(char *s, bool need_expand, t_data *data)
{
	t_classic	clas;

	init_need_split_exp(&clas, s);
	if (need_expand)
	{
		while (s[clas.i])
		{
			quote_state(&clas.s_quote, &clas.d_quote, clas.s, clas.i);
			if (s[clas.i] == '$' && clas.s_quote % 2 == 0
				&& ft_isvariable(s[clas.i + 1]) == 0 && s[clas.i + 1] != '"'
				&& s[clas.i + 1] != '\'')
			{
				if (while_is_variable(s, &clas.variable, &clas.i) == -1)
					return (-1);
				continue ;
			}
			clas.i++;
		}
	}
	if (env_val_need_split_exp(&clas, data, clas.s_quote, clas.d_quote))
		return (true);
	return (false);
}
