/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:59:26 by ecardoua          #+#    #+#             */
/*   Updated: 2026/06/29 14:39:02 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_fd(t_classic *clas, t_data *data, t_token **token)
{
	char	*word;

	clas->i++;
	if (clas->in == false && (*token)->out > 0)
		close((*token)->out);
	if (clas->in == true && (*token)->in > 0)
		close((*token)->in);
	while (clas->s[clas->i] == ' ' || clas->s[clas->i] == 9)
		clas->i++;
	word = NULL;
	while (redir_fd_condition(clas))
	{
		if (!word)
			clas->tmp = ft_strdup("");
		else
			clas->tmp = ft_strdup(word);
		if (redir_fd_extra(&word, clas))
			return (-1);
	}
	if (!word)
		return (-2);
	if (opn_fd_redir(clas, word, data, token))
		return (-1);
	return (0);
}

char	*ft_delimiter(char *args, int *i)
{
	char	*delimiter;
	char	*tmp;

	*i += 2;
	delimiter = NULL;
	if (args[*i] == ' ' || args[*i] == '\t')
	{
		while (args[*i] == ' ' || args[*i] == '\t')
			(*i)++;
	}
	while (args[*i])
	{
		if (args[*i] == ' ' || args[*i] == '<' || args[*i] == '>'
			|| args[*i] == '|' || args[*i] == '\t')
			break ;
		else
		{
			if (ft_delimiter_extra(&delimiter, &tmp, args, *i))
				return (NULL);
		}
		(*i)++;
	}
	return (delimiter);
}

int	here_doc_sig(char **line, char **delimiter, t_data **data)
{
	if (*line)
		free(*line);
	*line = readline("> ");
	if (!*line || get_sigint_status())
	{
		if (*line)
			free(*line);
		if (get_sigint_status())
			(*data)->last_status = 130;
		free(*delimiter);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		return (-1);
	}
	if (ft_strcmp(*line, *delimiter) == 0)
	{
		free(*delimiter);
		free(*line);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		return (0);
	}
	return (1);
}

int	here_doc(t_classic *clas, t_data **data)
{
	char	*delimiter;
	char	*line;
	int		r;
	char	*tmp_delimiter;

	reset_sigint_status();
	set_heredoc_signals();
	tmp_delimiter = ft_delimiter(clas->s, &clas->i);
	if (!tmp_delimiter)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		return (-2);
	}
	delimiter = del_quote(tmp_delimiter, false);
	free(tmp_delimiter);
	if (!delimiter)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		return (-2);
	}
	line = NULL;
	(*data)->fd_in = open("tmp_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if ((*data)->fd_in < 0)
	{
		perror("tmp_heredoc");
		free(delimiter);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		return (-1);
	}
	while (1)
	{
		r = here_doc_sig(&line, &delimiter, data);
		if (r != 1)
			break ;
		if (write((*data)->fd_in, line, ft_strlen(line)) < 0
			|| write((*data)->fd_in, "\n", 1) < 0)
		{
			free(delimiter);
			close((*data)->fd_in);
			(*data)->fd_in = -1;
			signal(SIGINT, handle_sigint);
			signal(SIGQUIT, SIG_IGN);
			return (-1);
		}
	}
	if (r_here_doc(r, data))
		return (-1);
	return (r);
}
