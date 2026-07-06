/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 00:17:05 by thcotza           #+#    #+#             */
/*   Updated: 2026/06/24 08:04:18 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_with_direct_path(t_cmd *cmd, char **argv,
						char **env_cpy, t_data *data)
{
	execve(cmd->cmd, argv, env_cpy);
	exec_path_failure(cmd->cmd, argv, NULL, data);
}
void	third_exec_search_path(t_cmd *cmd, char **argv,
						t_data *data, char *full_path)
{
	struct stat	stat_buf;

	while (data->paths[data->i])
	{
		data->tmpry = ft_strjoin(data->paths[data->i], "/");
		full_path = ft_strjoin(data->tmpry, cmd->cmd);
		free(data->tmpry);
		if (access(full_path, X_OK) == 0)
		{
			if (stat(full_path, &stat_buf) == 0 && S_ISREG(stat_buf.st_mode))
			{
				execve(full_path, argv, data->env_cpy);
				exec_path_failure(full_path, argv, data->paths, data);
			}
		}
		else if (access(full_path, F_OK) == 0)
		{
			errno = EACCES;
			exec_path_failure(full_path, argv, data->paths, data);
		}
		free(full_path);
		data->i++;
	}
	ft_free_split(data->paths);
	ft_putstr_fd("Command not found: \n", 2);
	ft_putendl_fd(cmd->cmd, 2);
	ft_free_split(argv);
	free_child_resources(data);
	exit(127);
}

void	exec_search_path_bis(t_cmd *cmd, char **argv,
						t_data *data, char *full_path)
{
	if (!cmd || !cmd->cmd || cmd->cmd[0] == '\0')
	{
		ft_free_split(data->paths);
		ft_putstr_fd("Command not found: \n", 2);
		if (cmd && cmd->cmd)
			ft_putendl_fd(cmd->cmd, 2);
		else
			ft_putendl_fd("", 2);
		ft_free_split(argv);
		free_child_resources(data);
		exit(127);
	}
	third_exec_search_path(cmd, argv, data, full_path);
}

void	child_execute_bis(int pipefd[2], t_cmd *current, t_data *data)
{
	if (data->fd_out != -1)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
		data->fd_out = -1;
		if (current->next)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		execute_command(current, data, current->next != NULL);
	}
	else if (current->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execute_command(current, data, 1);
	}
	else
		execute_command(current, data, 0);
	free_child_resources(data);
	exit(data->last_status);
}
