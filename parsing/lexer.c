/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:39:14 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/27 14:07:25 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	word_tokenizer(char *args, t_token **token, int *i)
{
	char	*word;
	char	*tmp;

	word = ft_strdup("");
	while (args[*i] && args[*i] != '<' && args[*i] != '>' && args[*i] != '|' && args[*i] != ' ' && args[*i] != '"' && args[*i] != '\'')
	{
		tmp = ft_strdup(word);
		word = ft_strcharjoin(tmp, args[*i]);
		free(tmp);
		(*i)++;
	}
	(*token)->value = word;
	(*token)->type = WORD;
	(*token)->next = malloc(sizeof(t_token));
	*token = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
}

void	d_quote_tokenizer(char *args, t_token **token, int *i)
{
	char	*d_quote;
	char	*tmp;
	int		s_quote;
	int		double_quote;

	s_quote = 0;
	double_quote = 0;
	d_quote = ft_strdup("\"");
	(*i)++;
	while (args[*i])
	{
		if (args[*i] == '\'' && double_quote%2 == 0)
			s_quote++;
		else if (args[*i] == '"' && s_quote%2 == 0)
			double_quote++;
		if (double_quote%2 == 0 && s_quote%2 == 0 && args[*i] == ' ' && args[*i] == '>' && args[*i] == '<' && args[*i] == '|')
			break ;
		tmp = ft_strdup(d_quote);
		d_quote = ft_strcharjoin(tmp, args[*i]);
		free(tmp);
		(*i)++;
	}
	(*token)->value = d_quote;
	(*token)->type = WORD;
	(*token)->next = malloc(sizeof(t_token));
	*token = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
}

void	s_quote_tokenizer(char *args, t_token **token, int *i)
{
	char	*d_quote;
	char	*tmp;

	d_quote = ft_strdup("\'");
	(*i)++;
	while (args[*i] && args[*i] != ' ' && args[*i] != '<' && args[*i] != '>' && args[*i] != '|')
	{
		tmp = ft_strdup(d_quote);
		d_quote = ft_strcharjoin(tmp, args[*i]);
		free(tmp);
		(*i)++;
	}
	(*token)->value = d_quote;
	(*token)->type = WORD;
	(*token)->next = malloc(sizeof(t_token));
	*token = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
}

void	redir_fd(char *args, t_data **data, int *i, bool in, bool append)
{
	char	*word;
	char	*tmp;

	if (in == false && (*data)->fd_out > 0)
		close((*data)->fd_out);
	if (in == true && (*data)->fd_in > 0)
		close((*data)->fd_out);
	(*i)++;
	word = ft_strdup("");
	while (args[*i] && args[*i] != '<' && args[*i] != '>' && args[*i] != '|' && args[*i] != ' ' && args[*i] != '"' && args[*i] != '\'')
	{
		tmp = ft_strdup(word);
		word = ft_strcharjoin(tmp, args[*i]);
		free(tmp);
		(*i)++;
	}
	if (in)
		(*data)->fd_in = open(word, O_WRONLY, 0644);
	if (append && in)
		(*data)->fd_in = open(word, O_WRONLY | O_APPEND, 0644);
	else
		(*data)->fd_out = open(word, O_WRONLY | O_CREAT, 0644);
	free(word);
}

bool	lexer(char *args, t_token **tok, t_data **data)
{
	t_token	*token;
	int		i;

	token = *tok;
	i = 0;
	while (args[i])
	{
		if (args[i] == '>' && args[i + 1] == '>')
		{
			i++;
			redir_fd(args, data, &i, false, true);
		}
		else if (args[i] == '<' && args[i + 1] == '<')
			ft_strdup("stand by here docs");
		else if (args[i] == '<')
			redir_fd(args, data, &i, true, false);
		else if (args[i] == '>')
			redir_fd(args, data, &i, false, false);
		else if (args[i] == '|')
		{
			token->type = PIPE;
			token->next = malloc(sizeof(t_token));
			token= token->next;
			token->next = NULL;
			token->value = NULL;
			i++;
		}
		else if (args[i] == ' ' || args[i] == 9)
			i++;
		else if (args[i] == '"')
			d_quote_tokenizer(args, &token, &i);
		else if (args[i] == '\'')
			s_quote_tokenizer(args, &token, &i);
		else
			word_tokenizer(args, &token, &i);
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
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '\'')
				s_quote++;
			else if (args[i][j] == '"')
				d_quote++;
		}
	}
	if (s_quote %2 == 0 && d_quote %2 == 0)
		return (false);
	else
		return (true);
}

bool	quote_del(t_cmd **cmd, t_token *token, t_data *data)
{
	char	**tmp;

	if (quote_count((*cmd)->args))
		return (true);
	tmp = ft_cpytab((*cmd)->args, token, data->env_list, true);
	if (!tmp)
		return (true);
	free((*cmd)->args);
	(*cmd)->args = tmp;
	return (false);
}

bool	parse_input(t_data *data, t_token **token, t_cmd **cmd)
{
	if (!(*token))
		return (true);
	if (lexer(data->input, token, &data))
		return (true);
	if (parser(*token, cmd, data))
		return (true);
	if (expander(cmd, *token, data))
		return (true);
	if (quote_del(cmd, *token, data))
		return (true);
	return (false);
}
