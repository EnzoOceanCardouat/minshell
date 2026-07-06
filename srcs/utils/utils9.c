/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:01:52 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:43:56 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	opn_fd_redir(t_classic *clas, char *word, t_data *data, t_token **token)
{
	if (fd_need_exp_del_quote(clas, word, data))
		return (true);
	if (clas->append)
		(*token)->out = open(word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (clas->in)
		(*token)->in = open(word, O_RDONLY, 0644);
	else
		(*token)->out = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (((*token)->out < 0 && !clas->in) || ((*token)->in < 0 && clas->in))
	{
		perror(word);
		free(word);
		return (true);
	}
	free(word);
	(*token)->type = REDIR;
	if (token_next_init(token))
		return (true);
	return (false);
}

bool	redir_fd_extra(char **word, t_classic *clas)
{
	free(*word);
	if (!clas->tmp)
		return (true);
	*word = ft_strcharjoin(clas->tmp, clas->s[clas->i]);
	free(clas->tmp);
	if (!*word)
		return (true);
	clas->i++;
	return (false);
}

bool	redir_fd_condition(t_classic *clas)
{
	if (clas->s[clas->i] && (clas->s[clas->i] != '<'
			&& clas->s[clas->i] != '>' && clas->s[clas->i] != '|'
			&& clas->s[clas->i] != ' '))
		return (true);
	else
		return (false);
}

bool	ft_delimiter_extra(char **delimiter, char **tmp, char *args, int i)
{
	if (*delimiter)
		*tmp = *delimiter;
	else
	{
		*tmp = ft_strdup("");
		if (!*tmp)
			return (true);
	}
	*delimiter = ft_strcharjoin(*tmp, args[i]);
	free(*tmp);
	if (!*delimiter)
		return (true);
	return (false);
}

bool	result_heredoc(ssize_t r, t_classic *clas, char *delimiter)
{
	if (r < 0 && errno == EINTR)
	{
		free(clas->s);
		return (true);
	}
	if (r == 0 && clas->i == 0)
	{
		printf("\nminishell: warning: here-document delimited ");
		printf("by end-of-file (wanted '%s')\n", delimiter);
		free(clas->s);
		return (true);
	}
	return (false);
}
