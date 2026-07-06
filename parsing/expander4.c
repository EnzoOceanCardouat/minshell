/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:51:40 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:35:32 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	split_dollar_no_squote(t_classic *clas, t_data *data)
{
	char	*env_value;
	int		h;

	if (split_doll_ex(clas, data, &env_value, &h))
		return (-1);
	while (clas->k < h)
	{
		if (env_value[clas->k] == ' ')
		{
			while (env_value[clas->k] == ' ')
				(clas->k)++;
			break ;
		}
		else
		{
			clas->l++;
			clas->k++;
		}
	}
	free(env_value);
	if (clas->variable)
		free(clas->variable);
	clas->variable = NULL;
	env_value = NULL;
	return (0);
}

bool	split_set_expand(t_classic *clas, t_data *data, char ***split_expand)
{
	clas->expand = ft_env_search(clas->variable, data);
	if (!clas->expand)
		return (true);
	while (clas->expand[clas->k])
	{
		if (clas->expand[clas->k] == ' ')
		{
			clas->l++;
			clas->j = 0;
			while (clas->expand[clas->k] == ' ')
				clas->k++;
		}
		(*split_expand)[clas->l][clas->j++] = clas->expand[clas->k++];
	}
	free(clas->variable);
	free(clas->expand);
	clas->variable = NULL;
	clas->expand = NULL;
	return (false);
}

bool	split_expand_extra(t_classic *clas, t_data *data, char ***split_expand)
{
	if (clas->s[clas->i] == '$' && clas->s_quote % 2 == 0
		&& ft_isexpand(clas->s[clas->i + 1], clas->s_quote, clas->d_quote))
	{
		clas->i++;
		clas->k = 0;
		clas->variable = NULL;
		if (clas->s[clas->i] == '\'' || clas->s[clas->i] == '"')
			return (false);
		else if (ft_isdigit(clas->s[clas->i]) == 1 || clas->s[clas->i] == '?')
		{
			if (variable_digit_q_mark(clas))
				return (true);
		}
		else
		{
			if (expand_variable_set(clas))
				return (true);
		}
		if (split_set_expand(clas, data, split_expand))
			return (true);
	}
	else
		(*split_expand)[clas->l][clas->j++] = clas->s[clas->i++];
	return (false);
}

int	split_size_malloc_expand(char *s, t_data *data, int *k)
{
	t_classic	clas;
	t_env		*env;

	env = data->env_list;
	init_size_malloc_expand(&clas, s, *k);
	while (clas.s[clas.i])
	{
		quote_state(&clas.s_quote, &clas.d_quote, s, clas.i);
		if (clas.s[clas.i] == '$' && clas.s_quote % 2 == 0
			&& ft_isvariable(s[clas.i +1]) == 0)
		{
			data->env_list = env;
			if (split_dollar_no_squote(&clas, data) == -1)
				return (0);
		}
		else
		{
			clas.l++;
			clas.i++;
		}
	}
	return (clas.l);
}

bool	split_expand_l(t_classic *clas, t_data *data, char ***split_expand)
{
	while (clas->l < split_expand_size(clas->s, data, true))
	{
		split_expand[clas->l++] = ft_calloc(split_size_malloc_expand(clas->s,
					data, &clas->m) + 1, sizeof(char));
		if (!split_expand[clas->l - 1])
		{
			ft_free_split(*split_expand);
			return (true);
		}
	}
	clas->l = 0;
	quote_state(&clas->s_quote, &clas->d_quote, clas->s, clas->i);
	if (split_expand_extra(clas, data, split_expand))
		return (true);
	return (false);
}
