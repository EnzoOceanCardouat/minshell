/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:46:39 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:33:23 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env_search(char *src, t_data *data)
{
	char	*exp;
	size_t	len;
	t_env	*env;

	if (!src)
		return (NULL);
	env = data->env_list;
	len = ft_strlen(src);
	if (ft_strcmp(src, "?") == 0)
	{
		exp = ft_itoa(data->last_status);
		return (exp);
	}
	while (env && len != 0)
	{
		if (ft_strncmp(env->line, src, len) == 0 && (env->line[len] == '='
				|| env->line[len] == '\0'))
		{
			exp = ft_substr(env->line, len + 1, ft_strlen(env->line) - len - 1);
			return (exp);
		}
		env = env->next;
	}
	exp = ft_calloc(1, 1);
	return (exp);
}

int	while_is_variable(char *s, char **variable, int *i)
{
	char	*tmp;

	tmp = NULL;
	(*i)++;
	if (ft_isdigit(s[*i]) == 1)
		*variable = ft_chardup(s[(*i)++]);
	else if (s[*i] == '?')
		*variable = ft_chardup(s[(*i)++]);
	else
	{
		while (ft_isvariable(s[*i]) == 0)
		{
			tmp = wiv_tmp_set(*variable);
			if (!tmp)
				return (-1);
			*variable = ft_strcharjoin(tmp, s[(*i)++]);
			free(tmp);
			tmp = NULL;
		}
		if (!*variable)
			return (-1);
	}
	free(tmp);
	return (0);
}

int	dollar_and_no_s_quote(char *s, t_classic *clas, t_data *data)
{
	char	*env_value;

	env_value = NULL;
	if (while_is_variable(s, &clas->variable, &clas->i) == -1)
		return (-1);
	env_value = ft_env_search(clas->variable, data);
	if (!env_value)
		return (-1);
	clas->l += ft_strlen(env_value);
	free(env_value);
	if (clas->variable)
		free(clas->variable);
	clas->variable = NULL;
	env_value = NULL;
	return (0);
}

int	size_malloc_expand(char *s, t_data *data)
{
	t_classic	clas;
	t_env		*env;

	env = data->env_list;
	init_size_malloc_expand(&clas, s, 0);
	while (clas.s[clas.i])
	{
		quote_state(&clas.s_quote, &clas.d_quote, s, clas.i);
		if (clas.s[clas.i] == '$' && clas.s_quote % 2 == 0
			&& ft_isvariable(clas.s[clas.i +1]) == 0)
		{
			data->env_list = env;
			if (dollar_and_no_s_quote(clas.s, &clas, data) == -1)
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

bool	variable_digit_q_mark(t_classic *clas)
{
	if (ft_isdigit(clas->s[clas->i]) == 1)
	{
		clas->variable = ft_chardup(clas->s[clas->i++]);
		if (!clas->variable)
			return (true);
	}
	else if (clas->s[clas->i] == '?')
	{
		clas->variable = ft_chardup(clas->s[clas->i++]);
		if (!clas->variable)
			return (true);
	}
	return (false);
}
