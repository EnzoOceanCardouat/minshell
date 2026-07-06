/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:50:10 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:33:40 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	expand_variable_set(t_classic *clas)
{
	while (ft_isvariable(clas->s[clas->i]) == 0)
	{
		if (clas->variable)
			clas->tmp = clas->variable;
		else
			clas->tmp = ft_strdup("");
		if (!clas->tmp)
			return (true);
		clas->variable = ft_strcharjoin(clas->tmp, clas->s[clas->i++]);
		free(clas->tmp);
		if (!clas->variable)
			return (true);
		clas->tmp = NULL;
	}
	return (false);
}

bool	set_expand(t_data *data, t_classic *clas, char **new_str)
{
	clas->expand = ft_env_search(clas->variable, data);
	if (!clas->expand)
	{
		if (clas->variable)
			free(clas->variable);
		clas->variable = NULL;
		return (true);
	}
	while (clas->expand[clas->k])
		(*new_str)[clas->j++] = clas->expand[clas->k++];
	free(clas->variable);
	free(clas->expand);
	clas->variable = NULL;
	clas->expand = NULL;
	return (false);
}

bool	expand_str(t_classic *clas, t_data *data, char **new_str)
{
	quote_state(&clas->s_quote, &clas->d_quote, clas->s, clas->i);
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
		if (set_expand(data, clas, new_str))
			return (true);
	}
	else
		(*new_str)[clas->j++] = clas->s[clas->i++];
	return (false);
}

char	*ft_expand_strdup(char *s, t_data *data)
{
	t_classic	clas;
	char		*new_str;

	clas.i = 0;
	clas.j = 0;
	clas.s_quote = 0;
	clas.d_quote = 0;
	clas.s = s;
	new_str = ft_calloc(size_malloc_expand(clas.s, data) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (s[clas.i])
	{
		if (expand_str(&clas, data, &new_str))
		{
			free(new_str);
			return (NULL);
		}
	}
	return (new_str);
}

bool	split_doll_ex(t_classic *clas, t_data *data, char **env_value, int *h)
{
	*env_value = NULL;
	if (while_is_variable(clas->s, &clas->variable, &clas->i) == -1)
		return (true);
	*env_value = ft_env_search(clas->variable, data);
	if (!*env_value)
		return (true);
	*h = ft_strlen(*env_value);
	return (false);
}
