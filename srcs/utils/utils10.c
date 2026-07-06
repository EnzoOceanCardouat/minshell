/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:03:43 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:44:09 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	r_here_doc(int r, t_data **data)
{
	if (r == 0)
	{
		if (lseek((*data)->fd_in, 0, SEEK_SET) < 0)
		{
			perror("tmp_heredoc");
			close((*data)->fd_in);
			(*data)->fd_in = -1;
			return (true);
		}
	}
	else if ((*data)->fd_in >= 0)
	{
		close((*data)->fd_in);
		(*data)->fd_in = -1;
	}
	return (false);
}

void	lexer_redir_pipe(t_classic *clas, t_data **data, t_token **token)
{
	if (clas->s[clas->i] == '>' && clas->s[clas->i + 1] == '>')
	{
		clas->i++;
		clas->append = true;
		clas->l = redir_fd(clas, *data, token);
	}
	else if (clas->s[clas->i] == '<' && clas->s[clas->i + 1] == '<')
		clas->l = here_doc(clas, data);
	else if (clas->s[clas->i] == '<')
	{
		clas->in = true;
		clas->l = redir_fd(clas, *data, token);
	}
	else if (clas->s[clas->i] == '>')
		clas->l = redir_fd(clas, *data, token);
	else if (clas->s[clas->i] == '|')
	{
		(*token)->type = PIPE;
		token_next_init(token);
		clas->i++;
	}
}

bool	lexer_code_return(t_classic clas, t_data **data)
{
	if (clas.l == -2)
	{
		(*data)->last_status = 2;
		return (true);
	}
	else if (clas.l == -1)
	{
		(*data)->last_status = 1;
		return (true);
	}
	return (false);
}

bool	lexer(char *args, t_token **tok, t_data **data)
{
	t_token		*token;
	t_classic	clas;

	token = *tok;
	clas.i = 0;
	clas.l = 0;
	clas.s = args;
	clas.in = false;
	clas.append = false;
	while (clas.s[clas.i])
	{
		lexer_redir_pipe(&clas, data, &token);
		if (clas.s[clas.i] == ' ' || clas.s[clas.i] == 9)
			clas.i++;
		else
		{
			if (word_tokenizer(&clas, &token, (*data)->env_list))
				return (false);
		}
		if (lexer_code_return(clas, data))
			return (true);
	}
	return (false);
}

bool	quote_count(char **args)
{
	int	s_quote;
	int	d_quote;
	int	i;
	int	j;

	s_quote = 0;
	d_quote = 0;
	i = -1;
	if (!args)
		return (false);
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '\'' && d_quote % 2 == 0)
				s_quote++;
			else if (args[i][j] == '"' && s_quote % 2 == 0)
				d_quote++;
		}
	}
	if (s_quote % 2 == 0 && d_quote % 2 == 0)
		return (false);
	else
		return (true);
}
