/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:39:14 by thcotza           #+#    #+#             */
/*   Updated: 2026/04/01 17:42:30 by ecardoua         ###   ########.fr       */
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
	//printf("token type: %d, token value: %s, len: %zu, i: %d\n", (*token)->type, (*token)->value, ft_strlen((*token)->value), *i);
	(*token)->next = malloc(sizeof(t_token));
	*token = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
}

void	d_quote_tokenizer(char *args, t_token **token, int *i)
{
	char	*d_quote;
	char	*tmp;

	d_quote = ft_strdup("\"");
	(*i)++;
	while (args[*i])
	{
		if (args[*i] == '"')
		{
			tmp = ft_strdup(d_quote);
			d_quote = ft_strcharjoin(tmp, args[*i]);
			free(tmp);
			(*i)++;
			break ;
		}
		tmp = ft_strdup(d_quote);
		d_quote = ft_strcharjoin(tmp, args[*i]);
		free(tmp);
		(*i)++;
	}
	(*token)->value = d_quote;
	(*token)->type = WORD;
	//printf("token type: %d, token value: %s, len: %zu, i: %d\n", (*token)->type, (*token)->value, ft_strlen((*token)->value), *i);
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
	while (args[*i])
	{
		if (args[*i] == '\'')
		{
			tmp = ft_strdup(d_quote);
			d_quote = ft_strcharjoin(tmp, args[*i]);
			free(tmp);
			(*i)++;
			break ;
		}
		tmp = ft_strdup(d_quote);
		d_quote = ft_strcharjoin(tmp, args[*i]);
		free(tmp);
		(*i)++;
	}
	(*token)->value = d_quote;
	(*token)->type = WORD;
	//printf("token type: %d, token value: %s, len: %zu, i: %d\n", (*token)->type, (*token)->value, ft_strlen((*token)->value), *i);
	(*token)->next = malloc(sizeof(t_token));
	*token = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
}

// void	d_more_tokenization(t_token **token, int *i)
// {
// 	(*token)->value = ft_strdup(">>");
// 	(*token)->type = D_MORE;
// 	printf("token type: %d, token value: %s, i: %d\n", (*token)->type, (*token)->value, *i);
// 	(*token)->next = malloc(sizeof(t_token));
// 	(*token) = (*token)->next;
// 	(*token)->next = NULL;
// 	(*token)->value = NULL;
// 	(*i) += 2;
// }

// void	d_less_tokenization(t_token **token, int *i)
// {
// 	(*token)->value = ft_strdup("<<");
// 	(*token)->type = D_LESS;
// 	printf("token type: %d, token value: %s, i: %d\n", (*token)->type, (*token)->value, *i);
// 	(*token)->next = malloc(sizeof(t_token));
// 	(*token) = (*token)->next;
// 	(*token)->next = NULL;
// 	(*token)->value = NULL;
// 	(*i) += 2;
// }

bool	lexer(char *args, t_token **tok, t_data **data)
{
	t_token	*token;
	int		i;
	char	*word;
	char	*tmp;

	token = *tok;
	i = 0;
	while (args[i])
	{
		if (args[i] == '>' && args[i + 1] == '>')
		{
			if ((*data)->fd_out > 0)
				close((*data)->fd_out);
			i += 2;
			word = ft_strdup("");
			while (args[i] && args[i] != '<' && args[i] != '>' && args[i] != '|' && args[i] != ' ' && args[i] != '"' && args[i] != '\'')
			{
				tmp = ft_strdup(word);
				word = ft_strcharjoin(tmp, args[i]);
				free(tmp);
				i++;
			}
			(*data)->fd_out = open(word, O_CREAT | O_WRONLY, 0644);
			free(word);
			continue ;
		}
		else if (args[i] == '<' && args[i + 1] == '<')
		{
			ft_strdup("stand by here docs");
			i += 2;
			continue ;
		}
		else if (args[i] == '<')
		{
			if ((*data)->fd_in < 0)
				close((*data)->fd_in);
			(*data)->fd_in = open(token->value, O_RDONLY, 0644);
			i++;
			continue ;
		}
		else if (args[i] == '>')
		{
			if ((*data)->fd_out < 0)
				close((*data)->fd_out);
			(*data)->fd_out = open(word, O_CREAT, O_WRONLY, 0644);
			i++;
			continue ;
		}
		else if (args[i] == '|')
			token->type = PIPE;
		else if (args[i] == ' ' || args[i] == 9)
		{
			i++;
			continue ;
		}
		else if (args[i] == '"')
		{
			d_quote_tokenizer(args, &token, &i);
			continue ;
		}
		else if (args[i] == '\'')
		{
			s_quote_tokenizer(args, &token, &i);
			continue ;
		}
		else
		{
			word_tokenizer(args, &token, &i);
			continue ;
		}
		token->value = ft_strcharjoin("", args[i]);
		//printf("token type: %d, token value: %s, len: %zu, i: %d\n", token->type, token->value, ft_strlen(token->value), i);
		token->next = malloc(sizeof(t_token));
		token= token->next;
		token->next = NULL;
		token->value = NULL;
		i++;
	}
	return (false);
}

// bool	expender(t_token **token)
// {
// 	int	i;

// 	i = -1;
// 	while ((*token))
// 	{
// 		while ((*token)->value[++i])
// 		{
// 			if ((*token)->value[i] == '\'')
// 				break ;
// 			else
// 			{
// 				if ((*token)->value[i] == '$')
// 				{
// 					if (ft_isdigit((int)(*token)->value[i + 1]) == 1)
// 						ft_strdup("faire jsp");
// 				}
// 			}
// 		}
// 	}
// 	if (ft_isdigit((*token)->value) == 1)
// 	{
// 		(*token)->value = ft_strdup("");
// 		return ;
// 	}
// 	else
// 	{
// 		(*token)->value = ft_strdup("stand by");
// 	}
// 	return (false);
// }

// open quand rediction et save le fd avec un int fd dans sruct

bool	parse_input(t_data *data, t_token **token, t_cmd **cmd)
{
	int	i;

	i = 0;
	if (!(*token))
		return (true);
	if (lexer(data->input, token, &data))
		return (true);
	// if (expender(token))
	// 	return (true);
	if (parser(*token, cmd))
		return (true);
	printf("cmd:%s, append:%d, outfile:%s, infile:%s\n", (*cmd)->cmd, (*cmd)->append, (*cmd)->outfile, (*cmd)->infile);
	while ((*cmd)->args[i])
		printf("args:%s\n", (*cmd)->args[i++]);
	return (false);
}
