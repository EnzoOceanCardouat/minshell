/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 03:39:01 by thcotza           #+#    #+#             */
/*   Updated: 2026/05/06 14:02:17 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_box(t_data *data, t_cmd **cmd, t_token **token)
{
	t_cmd	*cmd_next;
	// t_token	*tok_next;

	if (data->input)
		free(data->input);
	if (data->command)
		free(data->command);
	if ((*cmd)->cmd)
	{
		cmd_next = NULL;
		if ((*cmd)->cmd)
			free((*cmd)->cmd);
		if ((*cmd)->args)
			free((*cmd)->args);
		if ((*cmd)->next)
			cmd_next = (*cmd)->next;
		free(*cmd);
		if (cmd_next)
			*cmd = cmd_next;
	}
	(void)token;
	// while (token)
	// {
	// 	tok_next = NULL;
	// 	if ((*token)->value)
	// 		free((*token)->value);
	// 	free(*token);
	// 	if (tok_next)
	// 		*token = tok_next;
	// }
}

void	ft_exit(t_cmd *cmd, t_data *data, int is_piped, t_token **token)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->args && cmd->args[0])
		exit_code = ft_atoi(cmd->args[0]);
	if (!is_piped && isatty(STDIN_FILENO))
		printf("exit\n");
	free_box(data, &cmd, token);
	exit(exit_code);
}
