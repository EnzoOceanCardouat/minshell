/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 03:39:01 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/15 13:34:10 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*next;
	int		i;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->infile != -1)
			close(cmd->infile);
		if (cmd->outfile != -1)
			close(cmd->outfile);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		free(cmd);
		cmd = next;
	}
}

void	free_tokens_list(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = next;
	}
}

static int	is_out_of_range(char *str, t_data *data)
{
	int	result;

	data->llong_max_str = "9223372036854775807";
	data->llong_min_str = "9223372036854775808";
	if (!is_valid_number(str))
		return (1);
	data->is_negative = (str[0] == '-');
	if (str[0] == '-' || str[0] == '+')
		data->j = 1;
	else
		data->j = 0;
	data->length = 0;
	while (str[data->j + data->length])
		data->length++;
	if ((data->is_negative && data->length > 19)
		|| (!data->is_negative && data->length > 19))
		return (1);
	result = is_out_of_range_bis(str, data);
	return (result);
}

void	ft_exit_bis(t_data *data, int exit_code, int is_piped)
{
	if (get_sigint_status())
		exit_code = 130;
	if (!is_piped && isatty(STDIN_FILENO))
		printf("exit\n");
	clear_history();
	if (data->child_pids)
		free(data->child_pids);
	if (data->cmd_head)
		free_cmds(data->cmd_head);
	if (data->token_head)
		free_tokens_list(data->token_head);
	free_data(data);
	exit(exit_code);
}

void	ft_exit(t_cmd *cmd, t_data *data, int is_piped)
{
	int	exit_code;

	exit_code = data->last_status;
	if (cmd->args && cmd->args[0])
	{
		if (cmd->args[1])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			data->last_status = 1;
			return ;
		}
		if (is_out_of_range(cmd->args[0], data))
		{
			if (!is_piped && isatty(STDIN_FILENO))
				printf("exit\n");
			clear_history();
			if (data->child_pids)
				free(data->child_pids);
			if (data->cmd_head)
				free_cmds(data->cmd_head);
			if (data->token_head)
				free_tokens_list(data->token_head);
			free_data(data);
			exit(2);
		}
		exit_code = ft_atoi(cmd->args[0]);
	}
	ft_exit_bis(data, exit_code, is_piped);
}
