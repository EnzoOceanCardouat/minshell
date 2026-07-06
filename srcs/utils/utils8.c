/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:00:15 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:43:44 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	word_tok_ex(t_classic *clas, t_env *env, t_token **token, char **nw_wrd)
{
	if (!clas->variable)
		clas->tmp = ft_strdup("");
	else
		clas->tmp = ft_strdup(clas->variable);
	if (!clas->tmp)
		return (true);
	if (clas->s[clas->i] == '\'' && clas->d_quote % 2 == 0)
		clas->s_quote++;
	else if (clas->s[clas->i] == '"' && clas->s_quote % 2 == 0)
		clas->d_quote++;
	if (clas->s[clas->i] == '\'' || clas->s[clas->i] == '"')
		(*token)->quote = true;
	if (clas->s[clas->i] == '$' && ft_keep_quote(clas->s, clas->i, env) == 1)
		(*token)->not_del_quote = true;
	*nw_wrd = ft_strcharjoin(clas->tmp, clas->s[clas->i]);
	free(clas->tmp);
	if (!*nw_wrd)
	{
		free(clas->variable);
		return (true);
	}
	free(clas->variable);
	clas->variable = *nw_wrd;
	clas->i++;
	return (false);
}

bool	word_tokenizer(t_classic *clas, t_token **token, t_env *env)
{
	char	*new_word;

	clas->d_quote = 0;
	clas->s_quote = 0;
	clas->variable = NULL;
	while (clas->s[clas->i])
	{
		if (clas->d_quote % 2 == 0 && clas->s_quote % 2 == 0
			&& (clas->s[clas->i] == '<' || clas->s[clas->i] == '>'
				|| clas->s[clas->i] == '|' || clas->s[clas->i] == '\t'
				|| clas->s[clas->i] == ' '))
			break ;
		if (word_tok_ex(clas, env, token, &new_word))
			return (true);
	}
	if (word_token_init(token, clas->variable))
		return (true);
	return (false);
}

bool	token_next_init(t_token **token)
{
	(*token)->next = ft_calloc(1, sizeof(t_token));
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

bool	token_init(t_token **token)
{
	*token = ft_calloc(1, sizeof(t_token));
	if (!*token)
		return (true);
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*token)->type = NONE;
	(*token)->not_del_quote = false;
	(*token)->quote = false;
	(*token)->in = -1;
	(*token)->out = -1;
	return (false);
}

bool	fd_need_exp_del_quote(t_classic *clas, char *word, t_data *data)
{
	if (need_expand(NULL, word, false))
	{
		clas->tmp = ft_strdup(word);
		free (word);
		if (!clas->tmp)
			return (true);
		word = ft_expand_strdup(clas->tmp, data);
		free(clas->tmp);
		if (!word)
			return (true);
	}
	if (need_del_quote(NULL, word, false))
	{
		clas->tmp = ft_strdup(word);
		free (word);
		if (!clas->tmp)
			return (true);
		word = del_quote(clas->tmp, false);
		free(clas->tmp);
		if (!word)
			return (true);
	}
	return (false);
}
