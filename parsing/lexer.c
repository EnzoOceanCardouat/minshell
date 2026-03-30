/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:39:14 by thcotza           #+#    #+#             */
/*   Updated: 2026/03/26 13:50:50 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	word_tokenizer(char *args, t_token **token, int *i)
{
	char	*word;
	char	*tmp;

	word = ft_strdup("");
	while (args[*i] && args[*i] != '<' && args[*i] != '>' && args[*i] != '|' && args[*i] != ' ' && args[*i] != '"')
	{
		tmp = ft_strdup(word);
		word = ft_strcharjoin(tmp, args[*i]);
		free(tmp);
		(*i)++;
	}
	(*token)->value = word;
	(*token)->type = WORD;
	printf("token type: %d, token value: %s, len: %zu, i: %d\n", (*token)->type, (*token)->value, ft_strlen((*token)->value), *i);
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
	printf("token type: %d, token value: %s, len: %zu, i: %d\n", (*token)->type, (*token)->value, ft_strlen((*token)->value), *i);
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
	printf("token type: %d, token value: %s, len: %zu, i: %d\n", (*token)->type, (*token)->value, ft_strlen((*token)->value), *i);
	(*token)->next = malloc(sizeof(t_token));
	*token = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
}

void	d_more_tokenization(t_token **token, int *i)
{
	(*token)->value = ft_strdup(">>");
	(*token)->type = D_MORE;
	printf("token type: %d, token value: %s, i: %d\n", (*token)->type, (*token)->value, *i);
	(*token)->next = malloc(sizeof(t_token));
	(*token) = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*i) += 2;
}

void	d_less_tokenization(t_token **token, int *i)
{
	(*token)->value = ft_strdup("<<");
	(*token)->type = D_LESS;
	printf("token type: %d, token value: %s, i: %d\n", (*token)->type, (*token)->value, *i);
	(*token)->next = malloc(sizeof(t_token));
	(*token) = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*i) += 2;
}

bool	tokenization(char *args, t_token **tok)
{
	t_token	*token;
	int		i;

	token = *tok;
	i = 0;
	while (args[i])
	{
		if (args[i] == '>' && args[i + 1] == '>')
		{
			d_more_tokenization(&token, &i);
			continue ;
		}
		else if (args[i] == '<' && args[i + 1] == '<')
		{
			d_less_tokenization(&token, &i);
			continue ;
		}
		else if (args[i] == '<')
			token->type = LESS;
		else if (args[i] == '>')
			token->type = MORE;
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
		printf("token type: %d, token value: %s, len: %zu, i: %d\n", token->type, token->value, ft_strlen(token->value), i);
		token->next = malloc(sizeof(t_token));
		token= token->next;
		token->next = NULL;
		token->value = NULL;
		i++;
	}
	return (false);
}

bool	parse_input(t_data *data, t_token **token)
{
	if (!(*token))
		return (true);
	if (tokenization(data->input, token))
		return (true);
	return (false);
}
