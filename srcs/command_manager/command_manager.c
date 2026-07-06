/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:16:23 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/24 13:00:20 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_fork_error(t_cmd *current, t_data *data)
{
	perror("fork");
	if (current->next)
	{
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
	wait_children(data->child_pids, data->idx, data);
	return (-1);
}

static void	setup_parent(t_cmd *current, t_data *data)
{
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (current->next)
	{
		close(data->pipefd[1]);
		data->prev_fd = data->pipefd[0];
	}
	else
		data->prev_fd = -1;
}

static int	fork_and_prepare(t_cmd *current, t_data *data)
{
	int	error_result;

	data->child_pids[data->idx] = fork();
	if (data->child_pids[data->idx] == -1)
	{
		error_result = handle_fork_error(current, data);
		return (error_result);
	}
	if (data->child_pids[data->idx] == 0)
		child_execute(data->prev_fd, data->pipefd, current, data);
	else
		setup_parent(current, data);
	return (0);
}

static void	spawn_commands(t_cmd *cmd, t_data *data, int *child_pids)
{
	int		idx;
	t_cmd	*current;

	idx = 0;
	data->prev_fd = -1;
	data->child_pids = child_pids;
	current = cmd;
	while (current)
	{
		if (!current->next && data->prev_fd == -1 && is_builtin(current->cmd))
			data->last_status = execute_builtin(current, data, 0);
		else
		{
			if (current->next && create_pipe_or_error(data, idx) == -1)
				return ;
			data->idx = idx;
			if (fork_and_prepare(current, data) == -1)
				return ;
			idx++;
		}
		current = current->next;
	}
	wait_children(child_pids, idx, data);
}

void	manage_commands(t_cmd *cmd, t_data *data)
{
	int	*child_pids;
	int	num_cmds;

	if (!cmd)
		return ;
	num_cmds = count_commands(cmd);
	if (num_cmds == 0)
		return ;
	child_pids = malloc(sizeof(int) * num_cmds);
	if (!child_pids)
		return ;
	spawn_commands(cmd, data, child_pids);
	free(child_pids);
}
