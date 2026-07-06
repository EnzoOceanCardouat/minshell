/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 02:44:07 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/19 00:29:48 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_execute(int prev_fd, int pipefd[2], t_cmd *current, t_data *data)
{
	if (data->fd_in != -1)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
		data->fd_in = -1;
		if (prev_fd != -1)
			close(prev_fd);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	child_execute_bis(pipefd, current, data);
}

int	execute_builtin(t_cmd *cmd, t_data *data, int is_piped)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(&cmd, data);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(&cmd, data);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(data, &cmd);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(data, &cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(data);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd, data, is_piped);
	return (data->last_status);
}

void	execute_command(t_cmd *cmd, t_data *data, int is_piped)
{
	if (is_builtin(cmd->cmd))
		execute_builtin(cmd, data, is_piped);
	else
		exec_external(cmd, data);
}

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	is_builtin(char *cmd)
{
	int	result;

	if (!cmd)
		return (0);
	result = ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0;
	return (result);
}
