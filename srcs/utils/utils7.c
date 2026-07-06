/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:49:25 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:43:10 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	split_init(t_classic *clas, char *s, char ***split_expand, t_data *data)
{
	clas->i = 0;
	clas->j = 0;
	clas->s_quote = 0;
	clas->d_quote = 0;
	clas->l = 0;
	clas->m = 0;
	clas->s = s;
	*split_expand = ft_calloc(split_expand_size(s, data, true) + 1,
			sizeof(char *));
	if (!split_expand)
		return (true);
	return (false);
}

size_t	num_del_quote(char *args)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	while (args[++i])
	{
		if (args[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		if (args[i] == '"' && s_quote % 2 == 0)
			d_quote++;
	}
	return (s_quote + d_quote);
}

bool	quote_env(char *src, t_env *env)
{
	size_t	len;
	bool	keep;

	keep = false;
	len = ft_strlen(src);
	while (env && len != 0)
	{
		if (ft_strncmp(env->line, src, len) == 0 && (env->line[len] == '='
				|| env->line[len] == '\0') && (env->line[len +1] == '"'
				|| env->line[len +1] == '\''))
			keep = true;
		env = env->next;
	}
	return (keep);
}

int	ft_keep_quote(char *args, int i, t_env *env)
{
	t_classic	clas;

	i++;
	clas.variable = NULL;
	while (ft_isvariable(args[i]) == 0)
	{
		if (!clas.variable)
			clas.tmp = ft_strdup("");
		else
			clas.tmp = clas.variable;
		if (!clas.tmp)
			return (-1);
		clas.variable = ft_strcharjoin(clas.tmp, args[i++]);
		free (clas.tmp);
		if (!clas.variable)
			return (-1);
	}
	if (quote_env(clas.variable, env))
		clas.m = 1;
	else
		clas.m = 0;
	free(clas.variable);
	return (clas.m);
}

bool	word_token_init(t_token **token, char *word)
{
	(*token)->value = word;
	(*token)->type = WORD;
	(*token)->next = malloc(sizeof(t_token));
	if (!(*token)->next)
		return (true);
	*token = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*token)->type = NONE;
	(*token)->not_del_quote = false;
	(*token)->quote = false;
	(*token)->in = -1;
	(*token)->out = -1;
	return (false);
}
