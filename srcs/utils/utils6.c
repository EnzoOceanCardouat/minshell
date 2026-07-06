/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:44:38 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 13:49:06 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmd_words(t_token *token)
{
	int	count;

	count = 0;
	while (token->value && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

void	init_size_malloc_expand(t_classic *clas, char *s, int k)
{
	clas->i = 0;
	clas->s_quote = 0;
	clas->d_quote = 0;
	clas->l = 0;
	clas->s = s;
	clas->k = k;
	clas->variable = NULL;
}

char	*wiv_tmp_set(char *variable)
{
	char	*tmp;

	if (variable)
		tmp = variable;
	else
		tmp = ft_calloc(1, 1);
	return (tmp);
}

void	quote_state(int *s_quote, int *d_quote, char *s, int i)
{
	if (s[i] == '\'' && *d_quote % 2 == 0)
		(*s_quote)++;
	else if (s[i] == '"' && *s_quote % 2 == 0)
		(*d_quote)++;
	return ;
}

bool	ft_isexpand(int c, int s_quote, int d_quote)
{
	if (ft_isvariable(c) == 0)
		return (true);
	else if (ft_isdigit(c) == 1)
		return (true);
	else if ((c == '\'' && s_quote % 2 == 0) || (c == '"' && d_quote % 2 == 0))
		return (true);
	return (false);
}
