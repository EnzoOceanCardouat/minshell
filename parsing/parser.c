/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:05:13 by ecardoua          #+#    #+#             */
/*   Updated: 2026/07/06 09:12:15 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_node_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->infile = -1;
	new->outfile = -1;
	new->next = NULL;
	return (new);
}

bool	parse_pipe(t_cmd **cmd, t_token *cur_tok, int *i)
{
	(*cmd)->next = create_node_cmd();
	if (!(*cmd)->next)
		return (true);
	*cmd = (*cmd)->next;
	cur_tok = cur_tok->next;
	*i = 0;
	(*cmd)->args = ft_calloc(count_cmd_words(cur_tok) + 1, sizeof(char *));
	if (!(*cmd)->args)
		return (true);
	return (false);
}

static bool	parse_word(t_cmd *cmd, t_token *cur_tok, int *i)
{
	cmd->args[*i] = ft_strdup(cur_tok->value);
	if (!cmd->args[(*i)++])
		return (true);
	cur_tok = cur_tok->next;
	return (false);
}

static void	parser_fd(t_token **token, t_cmd **cur_cmd)
{
	if ((*token)->in > -1)
		(*cur_cmd)->infile = (*token)->in;
	if ((*token)->out > -1)
		(*cur_cmd)->outfile = (*token)->out;
	*token = (*token)->next;
}

bool	parser(t_token *token, t_cmd **cmd)
{
	int		i;
	t_cmd	*cur_cmd;

	if (!token)
		return (true);
	*cmd = create_node_cmd();
	cur_cmd = *cmd;
	cur_cmd->args = ft_calloc(count_cmd_words(token) + 3, sizeof(char *));
	if (!cur_cmd->args)
		return (true);
	i = 0;
	while (token)
	{
		if (token->type == PIPE && parse_pipe(&cur_cmd, token, &i))
			return (true);
		else if (token->type == WORD && token->value
			&& parse_word(cur_cmd, token, &i))
			return (true);
		else if (token->type == REDIR)
			parser_fd(&token, &cur_cmd);
		else
			token = token->next;
	}
	return (false);
}
